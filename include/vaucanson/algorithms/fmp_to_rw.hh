// fmp_to_rw.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_FMP_TO_RW_HH
# define VCSN_ALGORITHMS_FMP_TO_RW_HH

# include <vaucanson/design_pattern/design_pattern.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   fmp_to_rw.hh
 *
 * This file provides a transformation function that computes
 * the Rational Weight transducer of a FMP automaton.
 *
 * @author Robert Bigaignon <robert.bigaignon@lrde.epita.fr>
 * @date   Mon Mar 16 16:15:15 2005
 *
 * @see fmp_to_rw()
 */
/** @} */

namespace vcsn
{
  /** @addtogroup algorithms *//** @{ */

  /// @name FMP automaton to rational weight transducer algorithm.
  ///@{
  /// Compute the equivalent Rational Weight transducer of a FMP
  /// automaton.  Please note that for the moment this function works
  /// only if the support of each transition is finite.
  ///
  /// Algorithm :
  /// If the FMP contains transitions with "complex" expression (E),
  ///	 i.e. infinite support,
  ///	 then Thompson of E.
  /// With the resulting automaton apply a conversion.
  ///	 i.e. (a,x) -> a|x

  template<typename S, typename T,
	   typename SS, typename TT>
  Element<SS, TT>&
  fmp_to_rw(const Element<S, T>& fmp, Element<SS, TT>& res);
  ///@}

  /** @} */
}

# include <vaucanson/algorithms/fmp_to_rw.hxx>

#endif // ! VCSN_ALGORITHMS_FMP_TO_RW_HH
