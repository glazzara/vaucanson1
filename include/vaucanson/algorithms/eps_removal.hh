// eps_removal.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EPS_REMOVAL_HH
# define VCSN_ALGORITHMS_EPS_REMOVAL_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   eps_removal.hh
 *
 * This files declares the backward and forward eps_removal algorithm.
 *
 * @see backward_eps_removal(), backward_eps_removal_here(),
 * forward_eps_removal(),
 * forward_eps_removal_here(), eps_removal(), eps_removal_here()
 */
/** @} */


// INTERFACE: void forward_eps_removal_here(Automaton& a) { return vcsn::forward_eps_removal_here(*a); }
// INTERFACE: void forward_eps_removal_here(GenAutomaton& a) { return vcsn::forward_eps_removal_here(*a); }

// INTERFACE: Automaton forward_eps_removal(const Automaton& a) { return vcsn::forward_eps_removal(*a); }
// INTERFACE: GenAutomaton forward_eps_removal(const GenAutomaton& a) { return vcsn::forward_eps_removal(*a); }

// INTERFACE: void backward_eps_removal_here(Automaton& a) { return vcsn::backward_eps_removal_here(*a); }
// INTERFACE: void backward_eps_removal_here(GenAutomaton& a) { return vcsn::backward_eps_removal_here(*a); }

// INTERFACE: Automaton backward_eps_removal(const Automaton& a) { return vcsn::backward_eps_removal(*a); }
// INTERFACE: GenAutomaton backward_eps_removal(const GenAutomaton& a) { return vcsn::backward_eps_removal(*a); }

// INTERFACE: void eps_removal_here(Automaton& a) { return vcsn::eps_removal_here(*a); }
// INTERFACE: void eps_removal_here(GenAutomaton& a) { return vcsn::eps_removal_here(*a); }

// INTERFACE: Automaton eps_removal(const Automaton& a) { return vcsn::eps_removal(*a); }
// INTERFACE: GenAutomaton eps_removal(const GenAutomaton& a) { return vcsn::eps_removal(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/misc/direction.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * In place eps_removal of an automaton (default is backward eps_removal).
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a    The weighted automaton to close.
   * @param dir  The orientation of the eps_removal.
   *
   * @see eps_removal(), forward_eps_removal(), forward_eps_removal_here(),
   * backward_eps_removal(), backward_eps_removal_here()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  void
  eps_removal_here(Element<A, T>& a, misc::direction_type dir = misc::backward);


  /**
   * Eps_Removal of an automaton (default is backward eps_removal).
   *
   * This algorithm completes the given	 automaton into a copy to make
   * it close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a    The weighted automaton to close.
   * @param dir  The orientation of the eps_removal.
   *
   * @see eps_removal_here(), forward_eps_removal(), forward_eps_removal_here(),
   * backward_eps_removal(), backward_eps_removal_here()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  Element<A, T>
  eps_removal(const Element<A, T>& a, misc::direction_type dir = misc::backward);


  /**
   * In place backward eps_removal of an automaton.
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see backward_eps_removal(), eps_removal_here(), eps_removal(),
   * forward_eps_removal_here(), forward_eps_removal()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  void
  backward_eps_removal_here(Element<A, T>& a);


  /**
   * Backward eps_removal of an automaton.
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see backward_eps_removal_here(), eps_removal(), eps_removal_here(),
   * forward_eps_removal(), forward_eps_removal_here()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  Element<A, T>
  backward_eps_removal(const Element<A, T>& a);


  /**
   * In place forward eps_removal of an automaton.
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see forward_eps_removal(), eps_removal_here(), eps_removal(),
   * backward_eps_removal_here(), backward_eps_removal()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  void
  forward_eps_removal_here(Element<A, T>& a);


  /**
   * Forward eps_removal of an automaton.
   *
   * This algorithm completes in place	the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see forward_eps_removal_here(), eps_removal(), eps_removal_here(),
   * backward_eps_removal(), backward_eps_removal_here()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  Element<A, T>
  forward_eps_removal(const Element<A, T>& a);

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/eps_removal.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_EPS_REMOVAL_HH
