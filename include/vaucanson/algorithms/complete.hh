// complete.hh: this file is part of the Vaucanson project.
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
   *
   * @see complete(), is_complete()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename T>
  void
  complete_here(Element<A, T>& a);

  /**
   * Make the transition function of an automaton total w.r.t alphabet.
   *
   * @note This algorithm returns a fresh automaton.
   *
   * @param a the deterministic and Boolean automaton to complete.
   *
   * @see complete_here(), is_complete()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename T>
  Element<A, T>
  complete(const Element<A, T>& a);

  /**
   * Test if the transition function is complete for each state.
   *
   * @param a The Boolean automaton to test.
   *
   * @return true if the transition function of e is complete w.r.t alphabet.
   *
   * @see complete(), complete_here()
   * @author Yann Régis-Gianas
   */
  template <class A, class T>
  bool
  is_complete(const Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/complete.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_COMPLETE_HH
