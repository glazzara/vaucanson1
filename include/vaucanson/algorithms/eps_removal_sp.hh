// eps_removal_sp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EPS_REMOVAL_SP_HH
# define VCSN_ALGORITHMS_EPS_REMOVAL_SP_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   eps_removal_sp.hh
 *
 * This files declares the backward and forward eps_removal algorithm.
 *
 * @see backward_eps_removal(), backward_eps_removal_here(),
 * forward_eps_removal(),
 * forward_eps_removal_here(), eps_removal(), eps_removal_here()
 */
/** @} */


// INTERFACE: void forward_eps_removal_here_sp(Automaton& a) { return vcsn::forward_eps_removal_here(*a); }

// INTERFACE: Automaton forward_eps_removal_sp(const Automaton& a) { return vcsn::forward_eps_removal(*a); }

// INTERFACE: void backward_eps_removal_here_sp(Automaton& a) { return vcsn::backward_eps_removal_here(*a); }

// INTERFACE: Automaton backward_eps_removal_sp(const Automaton& a) { return vcsn::backward_eps_removal(*a); }

// INTERFACE: void eps_removal_here_sp(Automaton& a, vcsn::misc::direction_type dir) { return vcsn::eps_removal_here(*a); }

// INTERFACE: Automaton eps_removal_sp(const Automaton& a, vcsn::misc::direction_type dir) { return vcsn::eps_removal(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/misc/direction.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * In place eps_removal_sp of an automaton (default is backward eps_removal).
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the shortest-path algorithm.
   *
   * @param a    The weighted automaton to close.
   * @param dir  The orientation of the eps_removal.
   *
   * @see eps_removal(), forward_eps_removal(), forward_eps_removal_here(),
   * backward_eps_removal(), backward_eps_removal_here()
   * @author Vivien Delmon
   */
  template<typename A, typename AI>
  void
  eps_removal_here_sp(Element<A, AI>& a, misc::direction_type dir = misc::backward);


  /**
   * Eps_Removal of an automaton (default is backward eps_removal).
   *
   * This algorithm completes the given	 automaton into a copy to make
   * it close over epsilon transition.
   *
   * It is based on the shortest-path algorithm.
   *
   * @param a    The weighted automaton to close.
   * @param dir  The orientation of the eps_removal.
   *
   * @see eps_removal_here(), forward_eps_removal(), forward_eps_removal_here(),
   * backward_eps_removal(), backward_eps_removal_here()
   * @author Vivien Delmon
   */
  template<typename A, typename AI>
  Element<A, AI>
  eps_removal_sp(const Element<A, AI>& a, misc::direction_type dir = misc::backward);


  /**
   * In place backward eps_removal_sp of an automaton.
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the shortest-path algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see backward_eps_removal(), eps_removal_here(), eps_removal(),
   * forward_eps_removal_here(), forward_eps_removal()
   * @author Vivien Delmon
   */
  template<typename A, typename AI>
  void
  backward_eps_removal_here_sp(Element<A, AI>& a);


  /**
   * Backward eps_removal_sp of an automaton.
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the shortest-path algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see backward_eps_removal_here(), eps_removal(), eps_removal_here(),
   * forward_eps_removal(), forward_eps_removal_here()
   * @author Vivien Delmon
   */
  template<typename A, typename AI>
  Element<A, AI>
  backward_eps_removal_sp(const Element<A, AI>& a);


  /**
   * In place forward eps_removal_sp of an automaton.
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the shortest-path algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see forward_eps_removal(), eps_removal_here(), eps_removal(),
   * backward_eps_removal_here(), backward_eps_removal()
   * @author Vivien Delmon
   */
  template<typename A, typename AI>
  void
  forward_eps_removal_here_sp(Element<A, AI>& a);


  /**
   * Forward eps_removal_sp of an automaton.
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the shortest-path algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see forward_eps_removal_here(), eps_removal(), eps_removal_here(),
   * backward_eps_removal(), backward_eps_removal_here()
   * @author Vivien Delmon
   */
  template<typename A, typename AI>
  Element<A, AI>
  forward_eps_removal_sp(const Element<A, AI>& a);

  /// @}

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/eps_removal_sp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_EPS_REMOVAL_SP_HH
