// prefix.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_PREFIX_HH
# define VCSN_ALGORITHMS_PREFIX_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   prefix.hh
 *
 * Compute an automaton which accepts any prefix
 * of the language accepted by the given automaton.
 *
 * @see is_realtime()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>

// INTERFACE: Automaton prefix(const Automaton& a) { return vcsn::prefix(*a); }

// INTERFACE: void prefix_here(Automaton& a) { return vcsn::prefix_here(*a); }

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Make every states of the automaton final states (in place).
   *
   * @param a The realtime automaton to work on.
   *
   * @pre @a a must be realtime.
   */
  template<typename A, typename AI>
  void
  prefix_here (const Element<A, AI>& a);

  /**
   * Make every states of the automaton final states.
   *
   * @param a The realtime automaton to work on.
   *
   * @pre @a a must be realtime.
   */
  template<typename A, typename AI>
  Element<A, AI>
  prefix (const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/prefix.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGORITHMS_PREFIX_HH
