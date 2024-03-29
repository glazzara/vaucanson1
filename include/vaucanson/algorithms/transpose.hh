// transpose.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_TRANSPOSE_HH
# define VCSN_ALGORITHMS_TRANSPOSE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file algorithms/transpose.hh
 *
 * This file contains the function which transposes an automaton.
 *
 * @see transpose()
 */
/** @} */

# include <vaucanson/automata/concept/automata.hh>

// INTERFACE: void transpose(Automaton& dst, const Automaton& src) { vcsn::transpose(*dst, *src); }

// INTERFACE: Automaton transpose(const Automaton& a) { return vcsn::transpose(*a); }

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Transposition of an automaton.
   *
   * This function copies in @c dst the transposition of the automaton @c src.
   *
   * @param dst Destination
   * @param src Automaton to transpose
   */
  template<typename A, typename AI1, typename AI2>
  void
  transpose(Element<A, AI1>& dst, const Element<A, AI2>& src);

  /**
   * Return a fresh transposed automaton.
   *
   * This function returns the transposition of an automaton.
   *
   * @param src Automaton to transpose.
   */
  template<typename A, typename AI>
  Element<A, AI>
  transpose(const Element<A, AI>& src);

  /** @} */

} //vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/transpose.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_TRANSPOSE_HH
