// krat_exp_partial_derivation.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HH
# define VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_partial_derivation.hh
 *
 * Declarations for the partial_derivate() algorithm.
 *
 * @see partial_derivate()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>

# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// The partial derivative of the krat expression w.r.t to a letter.
  template <class Series, class T, class Letter>
  std::pair<std::set<Element<Series, T> >, bool>
  partial_derivate(const Element<Series, T>& exp,
	   	   Letter a);

  /** @} */

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/krat_exp_partial_derivation.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HH
