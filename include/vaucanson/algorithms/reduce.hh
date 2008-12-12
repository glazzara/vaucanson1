// reduce.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_REDUCE_HH
# define VCSN_ALGORITHMS_REDUCE_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/misc/direction.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   reduce.hh
 *
 * This files declares the reduce algorithm.
 *
 * @see reduce()
 */
/** @} */

// INTERFACE: Automaton reduce(const Automaton& a, vcsn::misc::direction_type dir) { return vcsn::reduce(*a); }

// INTERFACE: void reduce_here(Automaton& a, vcsn::misc::direction_type dir) { return vcsn::reduce_here(*a); }

namespace vcsn {

  template<typename A, typename AI>
  Element<A, AI>
  reduce(const Element<A, AI>& a, misc::direction_type dir = misc::backward);

  template<typename A, typename AI>
  void
  reduce_here(Element<A, AI>& a, misc::direction_type dir = misc::backward);

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/reduce.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGORITHMS_REDUCE_HH //
