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
 * Completion algorithm for deterministic and Boolean automaton.
 *
 * @see complete(), complete_here(), is_complete()
 */
/** @} */

// INTERFACE: void complete_here(Automaton& a) { return vcsn::complete_here(*a); }
// INTERFACE: void complete_here(GenAutomaton& a) { return vcsn::complete_here(*a); }

// INTERFACE: Automaton complete(const Automaton& a) { return vcsn::complete(*a); }
// INTERFACE: GenAutomaton complete(const GenAutomaton& a) { return vcsn::complete(*a); }

// INTERFACE: bool is_complete(const Automaton& a) { return vcsn::is_complete(*a); }
// INTERFACE: bool is_complete(const GenAutomaton& a) { return vcsn::is_complete(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

  /**
   * Make the transition function of an automaton total w.r.t alphabet.
   *
   * @note This algorithm works in place.
   *
   * @param a the deterministic and Boolean automaton to complete.
   * @pre @a a must be a realtime automaton.
   * @see complete(), is_complete()
   * @author Yann R�gis-Gianas
   */
  template <typename A, typename AI>
  void
  complete_here(Element<A, AI>& a);

  /**
   * Make the transition function of an automaton total w.r.t alphabet.
   *
   * @note This algorithm returns a fresh automaton.
   *
   * @param a the deterministic and Boolean automaton to complete.
   * @pre @a a must be a realtime automaton.
   * @see complete_here(), is_complete()
   * @author Yann R�gis-Gianas
   */
  template <typename A, typename AI>
  Element<A, AI>
  complete(const Element<A, AI>& a);

  /**
   * Test if the transition function is complete for each state.
   *
   * @param a The Boolean automaton to test.
   *
   * @return true if the transition function of e is complete w.r.t alphabet.
   * @pre @a a must be a realtime automaton.
   * @see complete(), complete_here()
   * @author Yann R�gis-Gianas
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
