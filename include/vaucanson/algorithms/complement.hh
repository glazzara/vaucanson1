// complement.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_COMPLEMENT_HH
# define VCSN_ALGORITHMS_COMPLEMENT_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   complement.hh
 *
 * Complementation algorithm for Boolean automata.
 *
 * @see complement(), complement_here()
 */
/** @} */

// INTERFACE: void complement_here(Automaton& a) { return vcsn::complement_here(*a); }
// INTERFACE: void complement_here(GenAutomaton& a) { return vcsn::complement_here(*a); }

// INTERFACE: Automaton complement(const Automaton& a) { return vcsn::complement(*a); }
// INTERFACE: GenAutomaton complement(const GenAutomaton& a) { return vcsn::complement(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Complement in place the set of final states.
   *
   * @param a The deterministic Boolean automaton to complement.
   *
   * @pre @a a must be complete.
   * @pre @a a must be deterministic.
   *
   * @see complement()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename AI>
  void
  complement_here(Element<A, AI>& a);

  /**
   * Complement the set of final states.
   *
   * @param a the deterministic Boolean automaton to complement.
   *
   * @pre @a a must be complete.
   * @pre @a a must be deterministic.
   *
   * @see complement_here()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename AI>
  Element<A, AI>
  complement(const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/complement.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_COMPLEMENT_HH
