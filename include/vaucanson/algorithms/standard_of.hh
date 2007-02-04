// standard_of.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_STANDARD_OF_HH
# define VCSN_ALGORITHMS_STANDARD_OF_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   standard_of.hh
 *
 * This file provides a converter from expression to standard automaton.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 20:46:53 2003
 *
 * @see standard_of()
 */
/** @} */

// INTERFACE: void standard_of(Automaton& a, const Exp& e) { return vcsn::standard_of(*a, e.value()); }
// INTERFACE: void standard_of(GenAutomaton& a, const Exp& e) { return vcsn::standard_of(*a, e.value()); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Convert a rational expression into a standard automaton.
   *
   * @param  e The expression to convert.
   * @param  a The automaton to store the result.
   *
   * @note The automaton is used to enable the use of different series
   *       from the expression.
   */
  template <typename A, typename T, typename Exp>
  void
  standard_of(Element<A, T>& a, const Exp& e);

  /**
   * Convert a rational expression into a standard automaton.
   *
   * @param  e The expression to convert.
   * @return A standard automaton.
   *
   * @note The automaton is defined using the series of the expression.
   */
  template <typename A, typename T, typename Exp>
  Element<A, T>
  standard_of(const Exp& e);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/standard_of.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_STANDARD_OF_HH
