// minimization_moore.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_MINIMIZATION_MOORE_HH
# define VCSN_ALGORITHMS_MINIMIZATION_MOORE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file minimization_moore.hh
 *
 * This file containes the declaration of minimization_moore().
 */
/** @} */

// INTERFACE: Automaton minimization_moore(const Automaton& a) { return vcsn::minimization_moore(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Returns the minimal deterministic automaton associated to the input one.
   *
   * Use   Moore's  algorithm  to   compute  the   minimal  equivalent
   * deterministic  automaton.  The complexity  of  this algorithm  is
   * O(n2). See  minimize_hopcroft for O(nlogn).
   *
   * @see http://cs.engr.uky.edu/~lewis/essays/compilers/min-fa.html
   * @see ETA p123-125
   *
   * @pre @a a must be deterministic.
   * @pre @a a must be a Boolean automaton.
   */
  template<typename A, typename AI>
  Element<A, AI>
  minimization_moore(const Element<A, AI>& a);

  /**
   * Returns the co-minimal co-deterministic automaton associated to
   * the input one.
   *
   * Use   Moore's  algorithm  to   compute  the   minimal  equivalent
   * co-deterministic  automaton.  The complexity  of  this algorithm  is
   * O(n2).
   *
   * @see http://cs.engr.uky.edu/~lewis/essays/compilers/min-fa.html
   * @see ETA p123-125
   *
   * @pre @a a must be co-deterministic.
   * @pre @a a must be a Boolean automaton.
   */
  template<typename A, typename AI>
  Element<A, AI>
  co_minimization_moore(const Element<A, AI>& a);


  /**
   * Minimalize the deterministic input automaton.
   *
   * Use Moore's algorithm to minimalize (in place) the input
   * automaton. The complexity of this algorithm is O(n2). See
   * minimize_hopcroft for O(nlogn).
   *
   * @see http://cs.engr.uky.edu/~lewis/essays/compilers/min-fa.html
   * @see ETA p123-125
   *
   * @pre @a a must be deterministic.
   * @pre @a a must be a Boolean automaton.
   */
  template<typename A, typename AI>
  void
  minimization_moore_here(Element<A, AI>& a);


  /**
   * Co-minimalize the co-deterministic input automaton.
   *
   * Use Moore's algorithm to co-minimalize (in place) the input
   * automaton. The complexity of this algorithm is O(n2). See
   * minimize_hopcroft for O(nlogn).
   *
   * @see http://cs.engr.uky.edu/~lewis/essays/compilers/min-fa.html
   * @see ETA p123-125
   *
   * @pre @a a must be co-deterministic.
   * @pre @a a must be a Boolean automaton.
   */
  template<typename A, typename AI>
  void
  co_minimization_moore_here(Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/minimization_moore.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_MINIMIZATION_MOORE_HH
