// derived_term_automaton.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_DERIVED_TERM_AUTOMATON_HH
# define VCSN_ALGORITHMS_DERIVED_TERM_AUTOMATON_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   derived_term_automaton.hh
 *
 * Provides a converter from expression to automaton based on derivatives.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 17:58:19 2003
 *
 * @see derived_term_automaton()
 */
/** @} */

// INTERFACE: void derived_term_automaton(Automaton& a, const Exp& e) { return vcsn::derived_term_automaton(*a, e); }
// INTERFACE: void derived_term_automaton(GenAutomaton& a, const Exp& e) { return vcsn::derived_term_automaton(*a, e); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Convert a krat expression into an automaton using derivatives.
   *
   * This algorithm produces an automaton from an expression using the
   * Brzozowski  construction.   This  construction involves  multiple
   * derivations on the initial expression.
   *
   * @param a An automaton to store the results.
   * @param e The expression to convert.
   *
   * @note 'a' is generally an  empty automaton. It enables the choice
   * of the  series to  work with. Thus,  the series can  be different
   * from the expresion ones.
   */
  template <typename A, typename T, typename Exp>
  void
  derived_term_automaton(Element<A, T>& a, const Exp& e);

  template <typename A, typename T, typename Exp>
  void
  broken_derived_term_automaton(Element<A, T>& a, const Exp& e);

  /**
   * Convert a krat expression into an automaton using derivatives.
   *
   * @param e The expression to convert.
   *
   * @return A fresh automaton which recognizes the language denoted by 'e'.
   *
   * @note The series of the expression are used to define the automaton.
   */
  template <typename A, typename T, typename Exp>
  Element<A, T>
  derived_term_automaton(const Exp& e);

  /**
   * Convert a krat expression into an automaton using derivatives.
   *
   * Derivations are first performed on the starting expression with the
   * following formulae:
   * d(0)={0}, d(1)={1}, d(a)={a} for all a in the alphabet,
   * d(E+F)=d(E) union d(F), d(E.F)=[d(E)].F, d(E*)={E*}
   *
   * @param e The expression to convert.
   *
   * @return A fresh automaton which recognizes the language denoted by 'e'.
   *
   * @note The series of the expression are used to define the automaton.
   */
  template <typename A, typename T, typename Exp>
  Element<A, T>
  broken_derived_term_automaton(const Exp& e);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/derived_term_automaton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_DERIVED_TERM_AUTOMATON_HH
