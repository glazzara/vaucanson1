// realtime_to_fmp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_REALTIME_TO_FMP_HH
# define VCSN_ALGORITHMS_REALTIME_TO_FMP_HH

# include <vaucanson/design_pattern/design_pattern.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   realtime_to_fmp.hh
 *
 * This file provides a transformation function that computes
 * the equivalent FMP automaton of a tranducer.
 *
 * @author Robert Bigaignon <robert.bigaignon@lrde.epita.fr>
 * @date   Mon Mar 16 16:15:15 2005
 *
 * @see realtime_to_fmp()
 */
/** @} */

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

  /// @name Realtime transducer to FMP automaton algorithm
  //@{
  /// Compute the equivalent FMP automaton of a transducer.
  /// Please note that for the moment this function works
  /// only if the support of each edge is finite.
  ///
  /// Preconditions :
  /// The transducer is realtime.
  /// The weight of each edge must have a finite support.
  template<typename S, typename T,
	   typename SS, typename TT>
  Element<SS, TT>&
  realtime_to_fmp(const Element<S, T>& trans,
		  Element<SS, TT>& res);

  //@}

  /** @} */
}

# include <vaucanson/algorithms/realtime_to_fmp.hxx>

#endif // ! VCSN_ALGORITHMS_REALTIME_TO_FMP_HH
