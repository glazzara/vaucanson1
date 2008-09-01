// has_neighbour.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_HAS_NEIGHBOUR_HH
# define VCSN_ALGORITHMS_INTERNAL_HAS_NEIGHBOUR_HH

# include <vaucanson/automata/concept/automata.hh>

namespace vcsn
{
  /**
   * @brief    Whether a state has successors.
   *
   * @param a	Automaton.
   * @param s	State.
   * @return	True is the state @a s has successors.
   *
   */
  template<typename A, typename T>
  bool	has_successors(const Element<A, T>&	a,
		       const typename automaton_traits<T>::hstate_t		s);

  /**
   * @brief    Whether a state has predecessors.
   *
   * @param a	Automaton.
   * @param s	State.
   * @return	True is the state @a s has predecessors.
   *
   */
  template<typename A, typename T>
  bool	has_predecessors(const Element<A, T>& a,
			 const typename automaton_traits<T>::hstate_t		s);
}

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/internal/has_neighbour.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_INTERNAL_HAS_NEIGHBOUR_HH
