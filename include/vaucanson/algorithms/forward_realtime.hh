// forward_realtime.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_FORWARD_REALTIME_HH
# define VCSN_ALGORITHMS_FORWARD_REALTIME_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file forward_realtime.hh
 *
 * Algorithms to make an automaton realtime.
 *
 * This file  contains algorithms  to build realtime  automaton. These
 * algorithms use the forward version of eps_removal.
 *
 * @see forward_realtime(), forward_realtime_here()
 */
/** @} */

// INTERFACE: void forward_realtime_here(Automaton& a) { return vcsn::forward_realtime_here(*a); }
// INTERFACE: void forward_realtime_here(GenAutomaton& a) { return vcsn::forward_realtime_here(*a); }

// INTERFACE: Automaton forward_realtime(const Automaton& a) { return vcsn::forward_realtime(*a); }
// INTERFACE: GenAutomaton forward_realtime(const GenAutomaton& a) { return vcsn::forward_realtime(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * In place modification of the automaton to make it realtime.
   *
   * This function  make an automaton realtime,  using forward version
   * of eps_removal for building.
   *
   * @param a The automaton to make realtime.
   *
   * @see realtime(), forward_realtime(), backward_realtime_here()
   */
  template<typename A, typename T>
  void
  forward_realtime_here(Element<A, T>& a);

  /**
   * Returns a fresh realtime automaton.
   *
   * This fonction build a  fresh realtime automaton from those given,
   * using forward version of eps_removal.
   *
   * @param a The automaton to make realtime.
   *
   * @see realtime(), forward_realtime_here(), backward_realtime()
   */
  template<typename A, typename T>
  Element<A, T>
  forward_realtime(const Element<A, T>& a);

  /** @} */

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/forward_realtime.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_FORWARD_REALTIME_HH
