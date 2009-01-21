// evaluation_rw.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2009 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EVALUATION_RW_HH
# define VCSN_ALGORITHMS_EVALUATION_RW_HH

# include <vaucanson/automata/concept/transducer.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file evaluation_rw.hh
 *
 * @brief Evaluation of an RW transducer over a realtime automaton.
 *
 * @see evaluation_fmp(), evaluation_rw()
 */
/** @} */

namespace vcsn
{
  /** @addtogroup algorithms *//** @{ */

  // FIXME: be more precise in the documentation
  // FIXME: precondition is_ltl (see the short description)?
  /**
   * @brief Evaluate for a "letterized" automaton and a realtime transducer.
   *
   * @param a lhs
   * @param t rhs
   * @param ret the result of the evaluation
   */
  template <typename SA, typename TA,
	    typename ST, typename TT,
	    typename SRET, typename TRET>
  void
  evaluation_rw(const Element<SA, TA>& a, const Element<ST, TT>& t,
		Element<SRET, TRET>& ret);

  /// @}

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/evaluation_rw.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_EVALUATION_RW_HH
