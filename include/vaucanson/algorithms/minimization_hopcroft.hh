// minimization_hopcroft.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HH
# define VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   minimization_hopcroft.hh
 *
 * This file provides minimization and quotient algorithms.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 21:08:54 2003
 *
 * @see minimization_hopcroft(), quotient()
 */
/** @} */

// INTERFACE: Automaton minimization_hopcroft(const Automaton& a) { return vcsn::minimization_hopcroft(*a); }
// INTERFACE: Automaton quotient(const Automaton& a) { return vcsn::quotient(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {


  /** @addtogroup algorithms *//** @{ */

  /**
   * Return the minimal automaton using the hopcroft algorithm.
   *
   * @param a The deterministic Boolean automaton to minimize.
   *
   * @pre @a a must be a Boolean automaton.
   * @pre @a a must be deterministic.
   * @pre @a a must be complete.
   *
   * @return A fresh automaton that is the canonical minimal automaton of 'a'.
   */
  template<typename A, typename AI>
  Element<A, AI>
  minimization_hopcroft(const Element<A, AI>& a);

  /**
   * Return the quotient of a non-deterministic acceptor.
   * This algorithms works with both Boolean and weighted automata.
   *
   * @param a The automaton to minimize.
   *
   * @pre @a a must be realtime.
   *
   * @return A fresh automaton that is the quotient of 'a'.
   *
   * @see CIAA 2005, "Inside Vaucanson" (in which the algorithm is
   * described by Sylvain Lombardy)
   */
  template<typename A, typename AI>
  Element<A, AI>
  quotient(const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/minimization_hopcroft.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HH
