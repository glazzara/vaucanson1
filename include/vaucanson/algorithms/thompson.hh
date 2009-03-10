// thompson.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008, 2009 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_THOMPSON_HH
# define VCSN_ALGORITHMS_THOMPSON_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file thompson.hh
 *
 * The thompson automaton.
 *
 * This  file  contains functions  to  build  automata from  rationnal
 * expressions, using thompson algorithm.
 *
 * @see thompson_of()
 */
/** @} */

// INTERFACE: void thompson_of(Automaton& a, const ExpImpl& e) { vcsn::thompson_of(*a, e.value()); }

# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/automata/concept/automata.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * The Thompson automaton associated to the krat expression.
   *
   * This  function build  the  automaton associated  to the  rational
   * expression implemented by a krat_exp, using Thompson algorithm.
   *
   * @param out The resulting automaton. `out' must be empty.
   * @param kexp The rational expression
   */
  template<typename A,      typename T,
	   typename Letter, typename Weight>
  void
  thompson_of(Element<A, T>& out, const rat::exp<Letter, Weight>& kexp);

  /**
   * The Thompson automaton associated to the krat expression.
   *
   * This  function build  the  automaton associated  to the  rational
   * expression   implemented   by    a   krat_exp,   using   Thompson
   * algorithm. The kind of returned automaton is a default one.
   *
   * @param exp The rational expression
   */
  template <typename AutoType, typename S, typename K, class T>
  Element<Automata<S, K>, AutoType>
  thompson_of(const Element<S, T>& exp);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/thompson.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_THOMPSON_HH
