// evaluation.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EVALUATION_HH
# define VCSN_ALGORITHMS_EVALUATION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file evaluation.hh
 *
 * Internal functions used by the rw_composition algorithm.
 *
 * @see vcsn::evaluation()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>

# include <vaucanson/automata/concept/handlers.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  // FIXME: be more precise in the documentation
  /**
   * Evaluate for a "letterized" automaton and a realtime transducer.
   *
   * @param a lhs
   * @param t rhs
   * @param ret the result of the evaluation
   */
  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename SARET, typename TARET>
  void
  evaluation(const Element<SA, TA>& a,
	     const Element<ST, TT>& t,
	     Element<SARET, TARET>& ret);

  /**
   * This function computes a set of expression, after
   * having eliminated all states which are not initial
   * or final.
   *
   * @param a input automaton
   * @param state_exp_pair the output mapping
   * @param state_exp_pair a mapping from the final
   *        to the expression of the label connecting it
   *        to the initial state.
   * @bug The algorithm should be inplace.
   */
  template<typename SA, typename TA,
	   typename M>
  void
  partial_elimination(const Element<SA, TA>& a,
		      M& state_exp_pair);

  /**
   * This function computes a set of expression
   * according to the rw_composition algorithm
   * description.
   *
   * @param E lhs
   * @param S rhs
   * @param p the state from which the evaluation is run
   * @param res the output map
   */
  template<typename S1, typename T1, 
	   typename S2, typename T2, 
	   typename M>
  void
  partial_evaluation(const Element<S1, T1>& E,
		     const Element<S2, T2>& S,
		     const typename Element<S2, T2>::hstate_t& p,
		     M& res);

  /** @} */

}

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/internal/evaluation.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_EVALUATION_HH
