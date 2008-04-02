// backward_realtime.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_BACKWARD_REALTIME_HH
# define VCSN_ALGORITHMS_BACKWARD_REALTIME_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file backward_realtime.hh
 *
 * Algorithms to make an automaton realtime.
 *
 * Algorithms to build realtime automaton. These algorithms
 * use the backward version of eps_removal.
 *
 * @see backward_realtime(), backward_realtime_here()
 */
/** @} */

// INTERFACE: void backward_realtime_here(Automaton& a) { return vcsn::backward_realtime_here(*a); }
// INTERFACE: void backward_realtime_here(GenAutomaton& a) { return vcsn::backward_realtime_here(*a); }

  // INTERFACE: Automaton backward_realtime(const Automaton& a) { return vcsn::backward_realtime(*a); }
  // INTERFACE: GenAutomaton backward_realtime(const GenAutomaton& a) { return vcsn::backward_realtime(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * In place modification of the automaton to make it realtime.
   *
   * Make an  automaton realtime, using backward version
   * of eps_removal for building.
   *
   * @param a The automaton to make realtime.
   *
   * @see realtime(), backward_realtime(), forward_realtime_here()
   */
  template<typename A, typename AI>
  void
  backward_realtime_here(Element<A, AI>& a);

  /**
   * Returns a fresh realtime automaton.
   *
   * Build a  fresh realtime automaton from those given,
   * using backward version of eps_removal.
   *
   * @param a The automaton to make realtime.
   *
   * @see realtime(), backward_realtime_here(), forward_realtime()
   */
  template<typename A, typename AI>
  Element<A, AI>
  backward_realtime(const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/backward_realtime.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_BACKWARD_REALTIME_HH
