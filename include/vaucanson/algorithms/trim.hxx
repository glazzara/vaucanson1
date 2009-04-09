// trim.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_TRIM_HXX
# define VCSN_ALGORITHMS_TRIM_HXX

# include <vaucanson/algorithms/trim.hh>

# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/algorithms/sub_automaton.hh>
# include <vaucanson/algorithms/accessible.hh>

# include <algorithm>

namespace vcsn {

  /*---------------------.
  | do_start_trim_states |
  `---------------------*/
  // preconditions :
  //
  //
  template <typename A, typename AI>
  std::set<typename Element<A, AI>::hstate_t>
  do_useful_states(const AutomataBase<A>&,
		   const Element<A, AI>&   a)
  {
    BENCH_TASK_SCOPED("useful_states");
    typedef typename Element<A, AI>::hstate_t hstate_t;

    std::set<hstate_t> start = accessible_states(a);
    std::set<hstate_t> final = coaccessible_states(a);
    std::set<hstate_t> result;
    std::insert_iterator<std::set<hstate_t> > i(result, result.begin());

    set_intersection(start.begin(), start.end(), final.begin(), final.end(), i);
    return result;
  }

  template<typename A, typename AI>
  std::set<typename Element<A, AI>::hstate_t>
  useful_states(const Element<A, AI>& a)
  {
    return do_useful_states(a.structure(), a);
  }

  template<typename A, typename AI>
  Element<A, AI>
  trim(const Element<A, AI>& a)
  {
    return sub_automaton(a, useful_states(a));
  }

  template<typename A, typename AI>
  void
  trim_here(Element<A, AI>& a)
  {
    sub_automaton_here(a, useful_states(a));
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_TRIM_HXX
