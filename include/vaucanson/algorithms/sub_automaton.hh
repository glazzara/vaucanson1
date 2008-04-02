// sub_automaton.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_SUB_AUTOMATON_HH
# define VCSN_ALGORITHMS_SUB_AUTOMATON_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   sub_automaton.hh
 *
 * This file provides the extraction of sub automaton.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 20:37:59 2003
 *
 * @see sub_automaton(), sub_automaton_here()
 */
/** @} */

// INTERFACE: Automaton sub_automaton(const Automaton& a, const HList& s, bool c) { return vcsn::sub_automaton(*a, s, c); }
// INTERFACE: GenAutomaton sub_automaton(const GenAutomaton& a, const HList& s, bool c) { return vcsn::sub_automaton(*a, s, c); }

// INTERFACE: void sub_automaton_here(Automaton& a, const HList& s, bool c) { return vcsn::sub_automaton_here(*a, s, c); }
// INTERFACE: void sub_automaton_here(GenAutomaton& a, const HList& s, bool c) { return vcsn::sub_automaton_here(*a, s, c); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {


  /** @addtogroup algorithms *//** @{ */

  /**
   *  Returns a fresh automaton that is the sub-automaton defined by a set.
   *
   * @param a The automaton into which we have to extract the sub-automaton.
   * @param s The set of states of the sub-automaton included in the
   *          state of 'a'.
   * @param check_states A flag to enable/disable the inclusion checking.
   * @return A fresh sub-automaton.
   *
   * @see sub_automaton_here()
   */
  template<typename A, typename AI, typename HStatesSet>
  Element<A, AI>
  sub_automaton(const Element<A, AI>& a, const HStatesSet& s,
		bool check_states =
#if defined VCSN_NDEBUG
		                    false
#else
		                    true
#endif
		);

  /**
   * Select a sub-automaton into a given automaton.
   *
   * @param a The automaton into which we have to extract the sub-automaton.
   * @param s The set of states of the sub-automaton included in the
   *          state of 'a'.
   * @param check_states A flag to enable/disable the inclusion checking.
   *
   * @see sub_automaton()
   */
  template<typename A, typename AI, typename HStatesSet>
  void
  sub_automaton_here(Element<A, AI>& a,
		     const HStatesSet& s,
		     bool check_states =
#if defined VCSN_NDEBUG
		                    false
#else
		                    true
#endif
		     );

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/sub_automaton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_SUB_AUTOMATON_HH
