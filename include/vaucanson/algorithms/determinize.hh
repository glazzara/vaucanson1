// determinize.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_DETERMINIZE_HH
# define VCSN_ALGORITHMS_DETERMINIZE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   determinize.hh
 *
 * Boolean automata determinization.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 19:13:10 2003
 *
 * @see determinize()
 */
/** @} */

// INTERFACE: Automaton determinize(const Automaton& a) { return vcsn::determinize(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <map>
# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// @name Determinization algorithms
  //@{
  /**
   * Build a deterministic automaton from a Boolean automaton.
   *
   * This function build a complete and deterministic automaton
   * using the so called "subset construction".
   *
   * @see is_deterministic() for the definition of a deterministic automaton.
   *
   * @param a The Boolean automaton to determinize.
   *
   * @pre @a a must be a Boolean automaton.
   * @pre @a a must be a realtime automaton.
   *
   * @return A new Boolean automaton that is an accessible, complete and
   * deterministic automaton recognizing the same language as @a a.
   */
  template<typename A, typename AI>
  Element<A, AI>
  determinize(const Element<A, AI>& a);

  /**
   * @brief Build a deterministic automaton from a Boolean automaton, keeping
   * trace of state-to-states correspondences.
   *
   * This function build a complete and deterministic automaton using
   * the so called "subset construction" but also returns the map
   * associating each state of the new automaton to the corresponding
   * subset of states from the original automaton.
   *
   * @see is_deterministic() for the definition of a deterministic automaton.
   *
   * @param a The Boolean automaton to determinize.
   * @param m A map which will be augmented with the correspondance
   *          from one state of the resulting automaton to a subset
   *          of states of the input automaton.
   *
   * @pre @a a must be a Boolean automaton.
   * @pre @a a must be a realtime automaton.
   *
   * @return A new Boolean automaton that is an accessible, complete and
   * deterministic automaton recognizing the same language as @a a.
   */
  template<typename A, typename AI>
  Element<A, AI>
  determinize(const Element<A, AI>& a,
	      std::map<typename Element<A, AI>::hstate_t,
	               std::set<typename Element<A, AI>::hstate_t> >&m);
  //@}

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/determinize.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_DETERMINIZE_HH
