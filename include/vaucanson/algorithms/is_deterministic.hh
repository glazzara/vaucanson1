// determinize.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The
// Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_DETERMINISTIC_HH
# define VCSN_ALGORITHMS_IS_DETERMINISTIC_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   is_deterministic.hh
 *
 * Boolean automata determinization.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 19:13:10 2003
 *
 * @see is_deterministic()
 */
/** @} */

// INTERFACE: bool is_deterministic(const Automaton& a) { return vcsn::is_deterministic(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Test if an automaton is deterministic.
   *
   * A realtime boolean automaton is deterministic if for each state
   * @c s and each letter @c l, there is <i>at most</i> one
   * outgoing transition labeled by @c s, and if there is <i>at most</i>
   * one initial state.
   *
   * @note Being realtime implies that the automaton is defined over a free
   *       monoid.
   * @note The empty automaton is deterministic (but not complete).
   * @param a the automaton to check.
   * @pre @a a is a realtime Boolean automaton.
   * @return true if @a a is deterministic.
   * @see is_complete(), determinize().
   */
  template<typename A, typename AI>
  bool
  is_deterministic(const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/is_deterministic.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_DETERMINIZE_HH
