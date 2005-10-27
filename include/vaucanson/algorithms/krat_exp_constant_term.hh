// krat_exp_constant_term.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HH
# define VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_constant_term.hh
 *
 * This file contains the declaration for the constant_term() algorithm.
 *
 * @see constant_term()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <utility>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Return the constant term of the krat expression.
  template <class Series, class T>
  std::pair<typename Element<Series, T>::semiring_elt_t, bool>
  constant_term(const Element<Series, T>& exp);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/krat_exp_constant_term.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HH
