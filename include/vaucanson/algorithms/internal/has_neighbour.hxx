// has_neighbour.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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
  // Determine wether there is at least a successor of a state.
  namespace internal {
    template <typename T>
    struct has_neighbour_helper
    {
      has_neighbour_helper () : has_neighbour_ (false) {}
      bool operator() (typename automaton_traits<T>::htransition_t)
      {
	this->has_neighbour_ = true;
	// Stop the loop over successors by returning false.
	return false;
      }
      bool has_neighbour_;
    };
  }

  template<typename A, typename T>
  bool	has_successors(const Element<A, T>& a,
		       const typename automaton_traits<T>::hstate_t s)
  {
    precondition (a.has_state (s));
    internal::has_neighbour_helper<T> functor;
    a.deltaf (functor, s, delta_kind::transitions());
    return functor.has_neighbour_;
  }

  template<typename A, typename T>
  bool	has_predecessors(const Element<A, T>& a,
			 const typename automaton_traits<T>::hstate_t s)
  {
    precondition (a.has_state (s));
    internal::has_neighbour_helper<T> functor;
    a.rdeltaf (functor, s, delta_kind::transitions());
    return functor.has_neighbour_;
  }
} // vcsn

#endif // ! VCSN_ALGORITHMS_INTERNAL_HAS_NEIGHBOUR_HXX
