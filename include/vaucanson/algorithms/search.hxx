// search.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//

#ifndef VCSN_ALGORITHMS_SEARCH_HXX
# define VCSN_ALGORITHMS_SEARCH_HXX

/**
 * @file search.hxx
 * 
 * @brief Rational expression search in text.
 * 
 * This file contains functions to perform rational expression search.
 */

# include <vaucanson/algorithms/search.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/sub_automaton.hh>
# include <vaucanson/misc/window.hh>
# include <vaucanson/misc/bitset.hh>

# include <vector>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  template <class InputIterator, class FoundFunctor, class Series, class T>
  void
  search(const Element<Automata<Series>, T>& a,
	 const InputIterator& begin,
	 const InputIterator& end,
	 typename Element<Automata<Series>, T>::letter_t eol,
	 FoundFunctor& f)
  {
    FindBestSearch::search(a, begin, end, eol, f);
  }
  
  template <class InputIterator, class FoundFunctor, class Series, class T>
  void
  FindBestSearch::search(const Element<Automata<Series>, T>& a,
			 const InputIterator& begin,
			 const InputIterator& end,
			 typename Element<Automata<Series>, T>::
			 letter_t eol,
			 FoundFunctor& f)
  {
    WindowedBackSearch::search(a, begin, end, eol, f);
  }

  /**
   * @brief Compute distances from initial states to final states.
   *
   * For each i, compute the set of states reachable in i steps or
   * less. the result is stored into a vector of set of states
   * distances[i].  This algorithm stops when it first encounter a
   * final state.  The last i value is returned.
   */
  template <class Series, class T, class StatesSet>
  static
  unsigned int
  compute_distances(const Element<Automata<Series>, T>& a,
		    std::vector<StatesSet>& distances)
  {
    precondition(a.initial().size() > 0);
    precondition(a.final().size() > 0);
    precondition(distances.size() == 0);

    // Typedefs.
    typedef typename vcsn::Element<Automata<Series>, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    // Code.
    StatesSet		s_new (a.states().size());
    StatesSet		s_old (a.states().size());
    unsigned int	i = 0;

    s_old.insert(a.initial().begin(), a.initial().end());
    for (bool get_out = false; !get_out; ++i)
      {
	s_new.clear();
	distances.push_back(s_old);
	if (i > 0)
	  distances[i].insert(distances[i - 1].begin(),
			      distances[i - 1].end());
	for (typename StatesSet::const_iterator s = s_old.begin();
	     s != s_old.end();
	     ++s)
	  {
	    if (a.is_final(*s))
	      // FIXME: Could be optimized with a return i, but code
	      // is easier to read this way.
	      get_out = true;
	    a.deltac(s_new, *s, delta_kind::states());
	  }
	std::swap(s_new, s_old);
      }

    postcondition(i == distances.size());
    return i - 1;
  }
  
  /// Build an automaton to recognize reverse factors of L(a).
  template <class Series, class T>
  static
  void
  build_reverse_factor_automaton(Element<Automata<Series>, T>& a)
  {
    // Typedefs.
    typedef typename vcsn::Element<Automata<Series>, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    // Code.
    automaton_t tmp (a);
    transpose(a, tmp);
    // All states are initial...
    for_each_state(s, tmp)
      a.set_initial(*s);
    // Forget about final states.
    for_each_final_state(f, tmp)
      a.unset_final(*f);
    // Each initial state is now final.
    for_each_initial_state(i, tmp)
      a.set_final(*i);
  }

  /**
   * @brief Back search inside a window.
   *
   * Returns whether the window is a potential match for the given
   * reverse factor automaton or not as the first element of the
   * pair. The second element is the maximal value we can use to shift
   * the window without skipping matches.
   *
   * @param w The window.
   * @param rfa The reverse factor automaton to use.
   * @param distances Distances get from compute_distances().
   *
   * @see search(), build_reverse_factor_automaton(), compute_distances()
   */
  template <class InputIterator, class Series, class T, class StatesSet>
  static
  std::pair<bool, unsigned int>
  window_backsearch(const utility::Window<InputIterator,
		    typename Element<Automata<Series>, T>::letter_t>& w,
		    const Element<Automata<Series>, T>& rfa,
		    const std::vector<StatesSet>& distances)
  {
    precondition(w.size() > 0);
    precondition(rfa.initial().size() > 0);

    // Typedefs.
    typedef typename vcsn::Element<Automata<Series>, T>		automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename utility::Window<InputIterator, letter_t>	window_t;
    typedef typename window_t::length_t				length_t;
    typedef utility::Bitset					bitset_t;

    // Code.
    bitset_t	s_new (rfa.states().size());
    bitset_t	s_old (rfa.states().size());
    length_t	critpos = w.size();
    int		pos;

    s_old.insert(rfa.initial().begin(), rfa.initial().end());
    for (pos = critpos - 1; (pos >= 0) && !s_old.empty(); --pos)
      {
	s_new.clear();
	for (bitset_t::const_iterator s = s_old.begin(); s != s_old.end(); ++s)
	  if (distances[pos + 1].count(*s))
	    {
	      if (rfa.is_final(*s))
		critpos = pos + 1;
	      rfa.letter_deltac(s_new, *s, w[pos], delta_kind::states());
	    }
	std::swap(s_new, s_old);
      }
    if (pos < 0)
      for (bitset_t::const_iterator s = s_old.begin(); s != s_old.end(); ++s)
	if (rfa.is_final(*s))
	  return std::make_pair(true, critpos);
    return std::make_pair(false, critpos);
  }

  /// Finds the longest match of a starting from w, and report it to
  /// the functor.
  template <class InputIterator, class FoundFunctor, class Series, class T>
  static
  InputIterator
  confirm_and_report_match(const utility::Window<InputIterator,
			   typename Element<Automata<Series>, T>::letter_t>& w,
			   const Element<Automata<Series>, T>& a,
			   FoundFunctor& f)
  {
    // Typedefs.
    typedef typename vcsn::Element<Automata<Series>, T>		automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename utility::Window<InputIterator, letter_t>	window_t;
    typedef typename window_t::length_t				length_t;
    typedef typename window_t::iterator_t			iterator_t;
    typedef utility::Bitset					bitset_t;

    // Code.
    bitset_t	s_old (a.states().size());
    bitset_t	s_new (a.states().size());
    iterator_t  pos = w.stream();
    iterator_t	last = pos;

    s_old.insert(a.initial().begin(), a.initial().end());
    while (!s_old.empty() && (*pos != w.eol_value()))
      {
	s_new.clear();
	for (bitset_t::const_iterator s = s_old.begin(); s != s_old.end(); ++s)
	  {
	    if (a.is_final(*s))
	      last = pos - 1;
	    a.letter_deltac(s_new, *s, *pos, delta_kind::states());
	  }
	std::swap(s_old, s_new);
	++pos;
      }
    for (bitset_t::const_iterator s = s_old.begin(); s != s_old.end(); ++s)
      if (a.is_final(*s))
	last = pos - 1;
    if (last != pos)
      return f(w.begin(), w.stream(), last);
    else
      return w.stream();
  }

  template <class InputIterator, class FoundFunctor, class Series, class T>
  void
  WindowedBackSearch::search(const Element<Automata<Series>, T>& a,
			     const InputIterator& begin,
			     const InputIterator& end,
			     typename Element<Automata<Series>, T>::
			     letter_t eol,
			     FoundFunctor& f)
  {
    // Typedefs.
    typedef typename vcsn::Element<Automata<Series>, T>		automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename utility::Window<InputIterator, letter_t>	window_t;
    typedef typename window_t::length_t				length_t;
    typedef utility::Bitset					bitset_t;

    // Code.
    std::vector<bitset_t> distances;
    length_t wl = compute_distances(a, distances);
    if (wl == 0)
      {
	warning("Search match every position in the stream, ignored.");
	return ;
      }
    automaton_t	rfa = sub_automaton(a, distances[wl]);
    build_reverse_factor_automaton(rfa);
    window_t	w (begin, end, eol, wl);
    while (! w.eof())
      {
	if (w.size() == wl)
	  {
	    std::pair<bool, length_t> p = window_backsearch(w, rfa, distances);
	    if (p.first)
	      {
		InputIterator it = confirm_and_report_match(w, a, f);
		if (it != w.stream())
		    w.moveto(it);
		else
		  w.shift(p.second);
	      }
	    else
	      w.shift(p.second);
	  }
	else
	  w.shift();
      }
  }

  /** @} */
  
} // vcsn

#endif // VCSN_ALGORITHMS_SEARCH_HH
