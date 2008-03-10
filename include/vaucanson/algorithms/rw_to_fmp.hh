// rw_to_fmp.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_RW_TO_FMP_HH
# define VCSN_ALGORITHMS_RW_TO_FMP_HH

# include <vaucanson/design_pattern/design_pattern.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   rw_to_fmp.hh
 *
 * This file provides a transformation function that computes
 * the equivalent FMP automaton of a Rational Weight tranducer.
 *
 * @author Robert Bigaignon <robert.bigaignon@lrde.epita.fr>
 * @date   Mon Mar 16 16:15:15 2005
 *
 * @see rw_to_fmp()
 */
/** @} */

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

  /// @name Rational Weight transducer to FMP automaton conversion
  //@{
  /// Compute the equivalent FMP automaton of a Rational Weight
  /// transducer.  Please note that for the moment this function works
  /// only if the support of each transition is finite.
  ///
  /// @pre \a trans should use rational weights with finite support.
  template<typename S, typename T,
	   typename SS, typename TT>
  Element<SS, TT>&
  rw_to_fmp(const Element<S, T>& trans, Element<SS, TT>& res);

  //@}

  /** @} */
}

# include <vaucanson/algorithms/rw_to_fmp.hxx>

#endif // ! VCSN_ALGORITHMS_REALTIME_TO_FMP_HH
