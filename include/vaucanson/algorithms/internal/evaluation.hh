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
 * Undocumented stuff.
 *
 * @see vcsn::evaluation()
 * @bug FIXME: Document!
 */
/** @} */

# include<vaucanson/design_pattern/design_pattern.hh>

# include <vaucanson/automata/concept/handlers.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Evaluate for a "letterized" automaton and a realtime transducer.
  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename SARET, typename TARET>
  void
  evaluation(const Element<SA, TA>&,
	     const Element<ST, TT>&,
	     Element<SARET, TARET>&);

  // Evalutation algorithm's internals
  // The following functions are absolutely not for public calls.

  template<typename SE, typename TE,
	   typename ST, typename TT,
	   typename M>
  void
  partial_evaluation(const Element<SE, TE>& exp,
		     const Element<ST, TT>& trans,
		     M& state_exp_pair);

  template<typename SA, typename TA,
	   typename M>
  void
  partial_elimination(const Element<SA, TA>& a,
		      M& state_exp_pair);

  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename M>
  void
  partial_1(const Element<SA, TA>&,
	    const Element<ST, TT>&, M&);

  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename Exp>
  void
  partial_2(const Element<SA, TA>&,
	    const Element<ST, TT>&,
	    const hstate_t, Exp&);

  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename M>
  void
  partial_3(const Element<SA, TA>&,
	    const Element<ST, TT>&,
	    const hstate_t, M&);

  /** @} */

}

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include<vaucanson/algorithms/internal/evaluation.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_EVALUATION_HH
