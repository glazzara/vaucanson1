// trim.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
  template <class A_, typename Auto_>
  std::set<hstate_t>
  do_useful_states(const AutomataBase<A_>&,
		   const Auto_&		   a)
  {
    std::set<hstate_t> start = accessible_states(a);
    std::set<hstate_t> final = coaccessible_states(a);
    std::set<hstate_t> result;
    std::insert_iterator<std::set<hstate_t> > i(result, result.begin());

    set_intersection(start.begin(), start.end(), final.begin(), final.end(), i);
    return result;
  }

  template<typename A, typename T>
  std::set<hstate_t>
  useful_states(const Element<A, T>& a)
  {
    return do_useful_states(a.structure(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  trim(const Element<A, T>& a)
  {
    return sub_automaton(a, useful_states(a));
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_TRIM_HXX
