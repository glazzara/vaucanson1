// berry_sethi.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_BERRY_SETHI_HH
# define VCSN_ALGORITHMS_BERRY_SETHI_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file berry_sethi.hh
 *
 * Contains the declaration for the Berry-Sethi algorithm.
 *
 * @see berry_sethi()
 */
/** @} */

// INTERFACE: void berry_sethi(Automaton& a, const Exp& e) { return vcsn::berry_sethi(*a, e); }
// INTERFACE: void berry_sethi(GenAutomaton& a, const Exp& e) { return vcsn::berry_sethi(*a, e); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Build an automaton from an expression using the Berry-Sethi construction.
  template <typename A, typename T, typename Exp>
  void
  berry_sethi(Element<A, T>&, const Exp&);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/berry_sethi.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_BERRY_SETHI_HH
