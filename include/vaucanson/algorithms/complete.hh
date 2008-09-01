// complete.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_COMPLETE_HH
# define VCSN_ALGORITHMS_COMPLETE_HH

/** @addtogroup algorithms */  /** @{ */
/**
 * @file   complete.hh
 *
 * Testing and building complete automata.
 * See is_complete() for the definition of a complete automaton.
 *
 * @see complete(), complete_here(), is_complete()
 */
/** @} */

// INTERFACE: void complete_here(Automaton& a) { return vcsn::complete_here(*a); }

// INTERFACE: Automaton complete(const Automaton& a) { return vcsn::complete(*a); }

// INTERFACE: bool is_complete(const Automaton& a) { return vcsn::is_complete(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

  /**
   * Make the transition function of an automaton total w.r.t. the alphabet.
   *
   * See is_complete() for the definition of a complete automaton.
   *
   * @note This algorithm works in place.
   *
   * @param a the automaton to complete.
   * @pre @a a must be a realtime automaton over a free-monoid.
   * @see complete(), is_complete()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename AI>
  void
  complete_here(Element<A, AI>& a);

  /**
   * Make the transition function of an automaton total w.r.t. the alphabet.
   *
   * See is_complete() for the definition of a complete automaton.
   *
   * @note This algorithm returns a new automaton.
   *
   * @param a the automaton to complete.
   * @pre @a a must be a realtime automaton over a free-monoid.
   * @see complete_here(), is_complete()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename AI>
  Element<A, AI>
  complete(const Element<A, AI>& a);

  /**
   * Test whether an automaton is complete.
   *
   * An automaton over a free-monoid is complete if each letter of the
   * alphabet can be read from any of its state (i.e., for each state
   * @c s and each letter @c l, there is <i>at least</i> one
   * outgoing transition labeled by @c s), and if there is <i>at least</i>
   * one initial state.
   *
   * @note Complete automata are not necessarily deterministic.
   * @note The above definition will also work with non-boolean automata.
   *
   * @param a automaton to test.
   *
   * @return true if the automaton @a a is complete.
   * @pre @a a must be a realtime automaton over a free-monoid.
   * @see complete(), complete_here(), is_deterministic()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename AI>
  bool
  is_complete(const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/complete.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_COMPLETE_HH
