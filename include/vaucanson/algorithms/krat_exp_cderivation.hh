// krat_exp_cderivation.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HH
# define VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_cderivation.hh
 *
 * This file contains the declaration for the cderivate() algorithms.
 *
 * @see cderivate(), word_cderivate()
 */
/** @} */

// INTERFACE: Exp cderivate(const Exp& e, char l) { return vcsn::cderivate(e, l); }

// INTERFACE: Exp cderivate(const Exp& e, const std::string& w) { return vcsn::word_cderivate(e, Series::monoid_elt_t(e.structure().monoid(), w)); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

  /// The c-derivative of the krat expression w.r.t to a letter.
  template <class Series, class T, class Letter>
  Element<Series, T>
  cderivate(const Element<Series, T>& exp,
	   Letter a);

  /// The c-derivative of the krat expression w.r.t to a word.
  template <class Series, class T, class Word>
  Element<Series, T>
  word_cderivate(const Element<Series, T>& exp,
		Word a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/krat_exp_cderivation.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HH
