// suffix.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_SUFFIX_HH
# define VCSN_ALGORITHMS_SUFFIX_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   suffix.hh
 *
 * Compute an automaton which accepts any suffix
 * of the language accepted by the given automaton.
 *
 * @see is_realtime()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>

// INTERFACE: Automaton suffix(const Automaton& a) { return vcsn::suffix(*a); }

// INTERFACE: void suffix_here(Automaton& a) { return vcsn::suffix_here(*a); }

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Make every states of the automaton initial states (in place).
   *
   * @param a The realtime automaton to work on.
   *
   * @pre @a a must be realtime and trim
   */
  template<typename A, typename AI>
  void
  suffix_here (const Element<A, AI>& a);

  /**
   * Make every states of the automaton initial states.
   *
   * @param a The realtime automaton to work on.
   *
   * @pre @a a must be realtime and trim
   */
  template<typename A, typename AI>
  Element<A, AI>
  suffix (const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/suffix.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGORITHMS_SUFFIX_HH
