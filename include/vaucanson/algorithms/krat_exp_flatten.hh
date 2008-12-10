// krat_exp_flatten.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HH
# define VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_flatten.hh
 *
 * This file holds the declaration of the flatten() algorithm.
 *
 * This is the  header file for the flatten  algorithm. This algorithm
 * extracts the letters from a rational expression and store them in a
 * list.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 * @see flatten()
 */
/** @} */

// INTERFACE: std::list<Exp::set_t::monoid_t::alphabet_t::letter_t> flatten(const Exp& e) { return vcsn::flatten(e); }

# include <vaucanson/design_pattern/design_pattern.hh>

# include <list>

namespace vcsn
{
  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief This algorithm extracts the letters from a rational expression.
   *
   * The  flatten()  function  extracts  the  letters  of  a  rational
   * expression,  keeping  the  order  in  which they  appear  in  the
   * expression.   The result  is just  a std::list  of  letters, with
   * letters  having the same  type as  the expression's  letter, i.e.
   * Element<S, T>::monoid_elt_t::set_t::alphabet_t::letter_t.
   *
   * @param exp The expression to work on.
   *
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   */

  template <class Series, class T>
  std::list<typename Series::monoid_t::alphabet_t::letter_t>
  flatten(const Element<Series, T>& exp);

  /** @} */

} // end of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/krat_exp_flatten.hxx>
# endif

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HH
