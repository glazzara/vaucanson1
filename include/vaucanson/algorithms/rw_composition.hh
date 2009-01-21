// rw_composition.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_RW_COMPOSITION_HH
# define VCSN_ALGORITHMS_RW_COMPOSITION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file rw_composition.hh
 *
 * Composition of two Rational-Weight transducers.
 *
 * @see rw_composition()
 */
/** @} */

// INTERFACE: Automaton rw_composition(const Automaton& a, const Automaton& b) { return vcsn::rw_composition(*a, *b); }
// INTERFACE: void rw_composition(const Automaton& a, const Automaton& b, Automaton& c) { vcsn::rw_composition(*a, *b, *c); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief Composition for Rational-Weight transducers.
   *
   * @pre @a rhs must be realtime.
   */
  template<typename S, typename T>
  void
  rw_composition(const Element<S, T>& lhs, const Element<S, T>& rhs, Element<S, T>& ret);

  /**
   * @brief Composition for Rational-Weight transducers.
   *
   * @pre @a rhs must be realtime.
   */
  template<typename S, typename T>
  Element<S, T>
  rw_composition(const Element<S, T>& lhs, const Element<S, T>& rhs);

  /** @} */

}

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/rw_composition.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_RW_COMPOSITION_HH
