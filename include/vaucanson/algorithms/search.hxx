// search.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_SEARCH_HXX
# define VCSN_ALGORITHMS_SEARCH_HXX

# include <vaucanson/algorithms/search.hh>

# include <vaucanson/misc/window.hh>
# include <vaucanson/misc/bitset.hh>

# include <vector>

namespace vcsn {

  template <typename InputIterator, typename FoundFunctor, typename Series, typename Kind, typename T>
  void
  search(const Element<Automata<Series, Kind>, T>& a,
	 const InputIterator& begin,
	 const InputIterator& end,
	 typename Element<Automata<Series, Kind>, T>::letter_t eol,
	 FoundFunctor& f)
  {
    BENCH_TASK_SCOPED("search");
    FindBestSearch::search(a, begin, end, eol, f);
  }

  template <typename InputIterator, typename FoundFunctor, typename Series, typename Kind, typename T>
  void
  FindBestSearch::search(const Element<Automata<Series, Kind>, T>& a,
			 const InputIterator& begin,
			 const InputIterator& end,
			 typename Element<Automata<Series, Kind>, T>::
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
   * fewer. the result is stored into a vector of sets of states
   * distances[i].  The algorithm stops when it encounters a
   * final state.  The last i value is returned.
   */
  template <typename Series, typename Kind, typename T, typename StatesSet>
  static
  unsigned int
  compute_distances(const Element<Automata<Series, Kind>, T>& a,
		    std::vector<StatesSet>& distances)
  {
    precondition(a.initial().size() > 0);
    precondition(a.final().size() > 0);
    precondition(distances.size() == 0);

    // Typedefs.
    typedef typename vcsn::Element<Automata<Series, Kind>, T>	automaton_t;
    AUTOMATON_TYPES(automaton_t);

    // Code.
    StatesSet		s_new (a.states().back() + 1);
    StatesSet		s_old (a.states().back() + 1);

    s_old.insert(a.initial().begin(), a.initial().end());
    for (unsigned int i = 0; true; ++i)
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
        {
          postcondition(i == distances.size());
          return i;
        }
        for (delta_iterator i(a.value(), *s);
             ! i.done();
             i.next())
          s_new.insert(a.dst_of(*i));
        s_old = s_new;
      }
    }
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
  template <typename InputIterator, typename Series, typename Kind, typename T, typename StatesSet>
  static
  std::pair<bool, unsigned int>
  window_backsearch(const misc::Window<InputIterator,
		    typename Element<Automata<Series, Kind>, T>::letter_t>& w,
		    const Element<Automata<Series, Kind>, T>& a,
		    const std::vector<StatesSet>& distances)
  {
    precondition(w.size() > 0);

    // Typedefs.
    typedef typename vcsn::Element<Automata<Series, Kind>, T>		automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    typedef typename misc::Window<InputIterator, letter_t>	window_t;
    typedef typename window_t::length_t				length_t;
    typedef misc::Bitset					bitset_t;

    // Code.
    bitset_t	s_new (a.states().back() + 1);
    bitset_t	s_old (a.states().back() + 1);
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
              std::insert_iterator<bitset_t> i(s_new, s_new.begin());
              for (delta_iterator t(a.value(), *s); ! t.done(); t.next())
              {
                monoid_elt_t w(a.series_of(*t).structure().monoid(), w[pos]);
                if (a.series_of(*t).get(w) != a.series().semiring().wzero_)
                  *i++ = a.src_of(*t);
              }
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
  template <typename InputIterator, typename FoundFunctor, typename Series, typename Kind, typename T>
  static
  InputIterator
  confirm_and_report_match(const misc::Window<InputIterator,
			   typename Element<Automata<Series, Kind>, T>::letter_t>& w,
			   const Element<Automata<Series, Kind>, T>& a,
			   FoundFunctor& f)
  {
    // Typedefs.
    typedef typename vcsn::Element<Automata<Series, Kind>, T>		automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    typedef typename misc::Window<InputIterator, letter_t>	window_t;
    typedef typename window_t::length_t				length_t;
    typedef typename window_t::iterator_t			iterator_t;
    typedef misc::Bitset					bitset_t;

    // Code.
    bitset_t	s_old (a.states().back() + 1);
    bitset_t	s_new (a.states().back() + 1);
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
            std::insert_iterator<bitset_t> i(s_new, s_new.begin());
            for (delta_iterator t(a.value(), *s); ! t.done(); t.next())
            {
              monoid_elt_t w(a.series_of(*t).structure().monoid(), *pos);
              if (a.series_of(*t).get(w) != a.series().semiring().wzero_)
                *i++ = a.dst_of(*t);
            }
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

  template <typename InputIterator, typename FoundFunctor, typename Series, typename Kind, typename T>
  void
  WindowedBackSearch::search(const Element<Automata<Series, Kind>, T>& a,
			     const InputIterator& begin,
			     const InputIterator& end,
			     typename Element<Automata<Series, Kind>, T>::
			     letter_t eol,
			     FoundFunctor& f)
  {
    // Typedefs.
    typedef typename vcsn::Element<Automata<Series, Kind>, T>		automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    typedef typename misc::Window<InputIterator, letter_t>	window_t;
    typedef typename window_t::length_t				length_t;
    typedef misc::Bitset					bitset_t;

    // Code.
    std::vector<bitset_t>	distances;
    length_t			wl = compute_distances(a, distances);

    if (wl == 0)
      WARNING("Search match every position in the stream, ignored.");
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

#endif // ! VCSN_ALGORITHMS_SEARCH_HXX
