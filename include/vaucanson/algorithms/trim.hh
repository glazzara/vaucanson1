// trim.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_TRIM_HH
# define VCSN_ALGORITHMS_TRIM_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file trim.hh
 *
 * Declaration of useful_states() and trim().
 *
 * @see useful_states(), trim()
 */
/** @} */

// INTERFACE: HList useful_states(const Automaton& a) { return list_of_set(vcsn::useful_states(*a)); }

// INTERFACE: Automaton trim(const Automaton& a) { return vcsn::trim(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief Returns a useful states of the automaton.
   *
   * This functions returns the states that are reachable and co-reachable.
   *
   * @param a The input automaton.
   */
  template<typename A, typename AI>
  std::set<typename Element<A, AI>::hstate_t>
  useful_states(const Element<A, AI>& a);

  /**
   * @brief Return a fresh automaton in which non useful states are removed.
   *
   * @param a The input automaton.
   */
  template<typename A, typename AI>
  Element<A, AI>
  trim(const Element<A, AI>& a);

  /// Trim \a a.
  /**
   * @brief Remove non useful states from the automaton.
   *
   * @param a The input automaton.
   */
  template<typename A, typename AI>
  void
  trim_here(Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/trim.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_TRIM_HH
