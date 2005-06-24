// transpose.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_TRANSPOSE_HH
# define VCSN_ALGORITHMS_TRANSPOSE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file algorithms/transpose.hh
 *
 * This file contain the function which transpose an automaton.
 *
 * @see transpose()
 */
/** @} */

// INTERFACE: void transpose(Automaton& dst, const Automaton& src) { vcsn::transpose(*dst, *src); }
// INTERFACE: void transpose(GenAutomaton& dst, const GenAutomaton& src) { vcsn::transpose(*dst, *src); }

// INTERFACE: Automaton transpose(const Automaton& a) { return vcsn::transpose(*a); }
// INTERFACE: GenAutomaton transpose(const GenAutomaton& a) { return vcsn::transpose(*a); }

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Transposition of an automaton.
   *
   * This function copy in @c dst the transposition of the automaton @c from.
   *
   * @param from Automaton to transpose
   * @param dst Destination
   */
  template<typename lhs_t, typename rhs_t>
  void
  transpose(lhs_t& dst, const rhs_t& from);

  /**
   * Return a fresh transposed automaton.
   *
   * This function returns the transposition of an automaton.
   *
   * @param from Automaton to transpose.
   */
  template<typename auto_t>
  auto_t
  transpose(const auto_t& from);

  /** @} */

} //vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/transpose.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_TRANSPOSE_HH
