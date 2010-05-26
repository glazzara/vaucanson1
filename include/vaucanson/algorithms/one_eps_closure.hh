// one_eps_closure.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2010 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_ONE_EPS_CLOSURE_HH
# define VCSN_ALGORITHMS_ONE_EPS_CLOSURE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   one_eps_closure.hh
 *
 * This file declares the backward and forward one_eps_closure algorithm.
 *
 * @see one_eps_closure(), * forward_one_eps_closure(), one_eps_closure()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/misc/direction.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief In place one_eps_closure of an automaton (default is
   * backward eps_closure).
   *
   * This algorithm closes the given automaton with respect to the
   * given "epsilon transition".  The epsilon transition type can be
   * any type supporting src(), dst(), and weight().
   *
   * @pre eps.src() != eps.dst()
   *
   * @param a    The weighted automaton to close.
   * @param eps_set  The epsilon transition that induces the closure.
   * @param dir  The orientation of the eps_closure.
   *
   * @see one_eps_closure(), forward_one_eps_closure(),
   * backward_one_eps_closure()
   * @author Sylvain Lombardy
   */
  template<typename A, typename AI, typename EPS>
  void
  one_eps_closure(Element<A, AI>& a, const EPS& eps,
		  misc::direction_type dir = misc::backward);

  /**
   * @brief In place backward_one_eps_closure of an automaton.
   *
   * This algorithm closes the given automaton with respect to each
   * epsilon transition of the given collection.  The epsilon
   * transition can be any type supporting src(), dst(), and weight().
   * The behaviour of the algorithm depends on the ordering of epsilon
   * transitions.
   *
   * For every transition 't' in 'a' with source eps.dst(), a
   * transition is created in 'a', with source eps.src(), destination
   * t.dst(), and series eps.weight()*t.series()
   *
   * @pre eps.src() != eps.dst()
   *
   * @param a    The weighted automaton to close.
   * @param eps  The collection of epsilon transitions that induces the closure.
   * @param dir  The orientation of the eps_closure.
   *
   * @see one_eps_closure(), forward_one_eps_closure(),
   * backward_one_eps_closure()
   * @author Sylvain Lombardy
   */
  template<typename A, typename AI, typename EPS>
  void
  backward_one_eps_closure(Element<A, AI>& a, const EPS& eps);


  /**
   * @brief In place forward one_eps_closure of an automaton.
   *
   * This algorithm closes the given automaton with respect to each
   * epsilon transition of the given collection.  The epsilon
   * transition can be any type supporting src(), dst(), and weight().
   * The behaviour of the algorithm depends on the ordering of epsilon
   * transitions.
   *
   * For every transition 't' in 'a' wist destination eps.src(), a
   * transition is created in 'a', with source t.src(), destination
   * eps.dst(), and series t.series()*eps.weight().
   *
   * @pre eps.src() != eps.dst()
   *
   * @param a    The weighted automaton to close.
   * @param eps  The collection of epsilon transitions that induces the closure.
   * @param dir  The orientation of the eps_closure.
   *
   * @see one_eps_closure(), forward_one_eps_closure(),
   * backward_one_eps_closure()
   * @author Sylvain Lombardy
   */
  template<typename A, typename AI, typename EPS>
  void
  forward_one_eps_closure(Element<A, AI>& a, const EPS& eps);

  /// @}

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/one_eps_closure.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_ONE_EPS_CLOSURE_HH
