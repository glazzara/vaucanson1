// isomorph.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EQUIVALENT_HH
# define VCSN_ALGORITHMS_EQUIVALENT_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file equivalent.hh
 *
 * This file contains the declarations for the are_equivalent() algorithm.
 *
 * @see are_equivalent()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

  /// Returns true iff the two boolean automata are equivalents, i.e., if they
  /// recognize the same language.
  template<typename S, typename A, typename B>
  bool
  are_equivalent(const Element<S, A>& a, const Element<S, B>& b);

// INTERFACE: bool are_equivalent(const Automaton& a1, const Automaton& a2) { return vcsn::are_equivalent(a1, a2); }
// INTERFACE: bool are_equivalent(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::are_equivalent(a1, a2); }

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/equivalent.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_EQUIVALENT_HH
