// search.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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

# include <vaucanson/algorithms/search.hh>

# include <vaucanson/misc/window.hh>
# include <vaucanson/misc/bitset.hh>

# include <vector>

namespace vcsn {

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

  /** @addtogroup algorithms *//** @{ */

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
    typedef typename vcsn::Element<Automata<Series>, T>	automaton_t;
    AUTOMATON_TYPES(automaton_t);

    // Code.
    StatesSet		s_new (a.states().max() + 1);
    StatesSet		s_old (a.states().max() + 1);
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

  /**
   * @brief Back search inside a window.
   *
   * Returns whether the window is a potential match for the given
   * automaton or not as the first element of the pair. The second
   * element is the maximal value we can use to shift the window
   * without skipping matches.
   *
   * @param w The window.
   * @param a The automaton to use.
   * @param distances Distances get from compute_distances().
   *
   * @see search(), build_reverse_factor_automaton(), compute_distances()
   */
  template <class InputIterator, class Series, class T, class StatesSet>
  static
  std::pair<bool, unsigned int>
  window_backsearch(const utility::Window<InputIterator,
		    typename Element<Automata<Series>, T>::letter_t>& w,
		    const Element<Automata<Series>, T>& a,
		    const std::vector<StatesSet>& distances)
  {
    precondition(w.size() > 0);

    // Typedefs.
    typedef typename vcsn::Element<Automata<Series>, T>		automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef typename utility::Window<InputIterator, letter_t>	window_t;
    typedef typename window_t::length_t				length_t;
    typedef utility::Bitset					bitset_t;

    // Code.
    bitset_t	s_new (a.states().max() + 1);
    bitset_t	s_old (a.states().max() + 1);
    int		pos = w.size();
    length_t	critpos = pos;

    s_old.insert(distances[pos].begin(), distances[pos].end());
    while ((--pos >= 0) && !s_old.empty())
      {
	s_new.clear();
	for (bitset_t::const_iterator s = s_old.begin(); s != s_old.end(); ++s)
	  if (distances[pos + 1].find(*s) != distances[pos + 1].end())
	    {
	      if (a.is_initial(*s))
		critpos = pos + 1;
	      a.letter_rdeltac(s_new, *s, w[pos], delta_kind::states());
	    }
	std::swap(s_new, s_old);
      }
    if (pos < 0)
      for (bitset_t::const_iterator s = s_old.begin(); s != s_old.end(); ++s)
	if (a.is_initial(*s))
	  return std::make_pair(true, critpos);
    return std::make_pair(false, critpos);
  }

  /// Finds the longest match of a starting from w, and report it to the functor.
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
    bitset_t	s_old (a.states().max() + 1);
    bitset_t	s_new (a.states().max() + 1);
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

  /** @} */

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
    std::vector<bitset_t>	distances;
    length_t			wl = compute_distances(a, distances);

    if (wl == 0)
      warning("Search match every position in the stream, ignored.");
    else
      {
	window_t		w (begin, end, eol, wl);
	InputIterator		it;

	while (!w.eof())
	  {
	    if (w.size() != wl)
	      w.shift();
	    else
	      {
		std::pair<bool, length_t> p =
		  window_backsearch(w, a, distances);
		if (p.first &&
		    (it = confirm_and_report_match(w, a, f)) != w.stream())
		  w.moveto(it);
		else
		  w.shift(p.second);
	      }
	  }
      }
  }

} // vcsn

#endif // VCSN_ALGORITHMS_SEARCH_HH
