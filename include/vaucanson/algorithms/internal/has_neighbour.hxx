// has_neighbour.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_HAS_NEIGHBOUR_HXX
# define VCSN_ALGORITHMS_INTERNAL_HAS_NEIGHBOUR_HXX

# include <vaucanson/algorithms/internal/has_neighbour.hh>

namespace vcsn {
  // Determine whether there is at least one neighbour of a state.

  template<typename A, typename T>
  bool has_successors(const Element<A, T>& a,
                      const typename automaton_traits<T>::hstate_t s)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    precondition (a.has_state (s));
    delta_iterator i(a.value(), s);
    return ! i.done();
  }
  
  template<typename A, typename T>
  bool has_predecessors(const Element<A, T>& a,
                        const typename automaton_traits<T>::hstate_t s)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    precondition (a.has_state (s));
    rdelta_iterator i(a.value(), s);
    return ! i.done();
  }
} // vcsn

#endif // ! VCSN_ALGORITHMS_INTERNAL_HAS_NEIGHBOUR_HXX
