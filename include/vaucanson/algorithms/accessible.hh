// accessible.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_ACCESSIBLE_HH
# define VCSN_ALGORITHMS_ACCESSIBLE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file accessible.hh
 *
 * @brief Algorithms for accessible/coaccessible states computation.
 *
 * A few algorithms to get accessible or coaccessible
 * states from an automaton.
 *
 * @see accessible_states(), accessible(), accessible_here(),
 *      coaccessible_states(), coaccessible(), coaccessible_here()
 */
/** @} */

// INTERFACE: HList accessible_states(const Automaton& a) { return list_of_set(vcsn::accessible_states(*a)); }

// INTERFACE: Automaton accessible(const Automaton& a) { return vcsn::accessible(*a); }

// INTERFACE: void accessible_here(Automaton& a) { return vcsn::accessible_here(*a); }

// INTERFACE: HList coaccessible_states(const Automaton& a) { return list_of_set(vcsn::coaccessible_states(*a)); }

// INTERFACE: Automaton coaccessible(const Automaton& a) { return vcsn::coaccessible(*a); }

// INTERFACE: void coaccessible_here(Automaton& a) { return vcsn::coaccessible_here(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>

# include <set>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

  /**
   * @brief Return accessible states.
   *
   * This functions returns the accessible states set of its input automaton.
   *
   * @param a The input automaton.
   *
   * @see accessible(), coaccessible(), coaccessible_states()
   */
  template<typename A, typename AI>
  std::set<typename Element<A, AI>::hstate_t>
  accessible_states(const Element<A, AI>& a);

  /**
   * Extract the sub-automaton composed of accessible states.
   *
   * This  function  returns  a   fresh  sub-automaton  of  its  input
   * containing only accessible states.
   *
   * @param a The input automaton.
   *
   * @see accessible_here(), accessible_states(), coaccessible(),
   *      coaccessible_states()
   */
  template<typename A, typename AI>
  Element<A, AI>
  accessible(const Element<A, AI>& a);

  /**
   * In-place extract the sub-automaton of accessible states.
   *
   * This function computes the sub-autmaton of accessible states from
   * its input automaton. The operation is performed in-place.
   *
   * @param a An in/out parameter which contains the automaton to work on as
   *          input and the result as output.
   *
   * @see accessible(), accessible_states(), coaccessible(),
   *      coaccessible_states()
   */
  template<typename A, typename AI>
  void
  accessible_here(Element<A, AI>& a);

  /**
   * Return co-accessible states.
   *
   * This functions returns the  co-accessible states set of its input
   * automaton, i.e. states which are accessible from final states.
   *
   * @param a The input automaton.
   *
   * @see coaccessible(), accessible(), accessible_states()
   */
  template<typename A, typename AI>
  std::set<typename Element<A, AI>::hstate_t>
  coaccessible_states(const Element<A, AI>& a);

  /**
   * Extract the sub-automaton composed of co-accessible states.
   *
   * This  function  returns  a   fresh  sub-automaton  of  its  input
   * containing  only  co-accessible  states,  i.e. states  which  are
   * accessible from final states.
   *
   * @param a The input automaton.
   *
   * @see coaccessible_here(), coaccessible_states(), accessible(),
   *      accessible_states()
   */
  template<typename A, typename AI>
  Element<A, AI>
  coaccessible(const Element<A, AI>& a);

  /**
   * In-place extract the sub-automaton of co-accessible states.
   *
   * This function  computes the sub-autmaton  of co-accessible states
   * from its input automaton. The operation is performed in-place.
   *
   * @param a An in/out parameter which contains the automaton to work on as
   *          input and the result as output.
   *
   * @see coaccessible(), coaccessible_states(), accessible(),
   *      accessible_states()
   */
  template<typename A, typename AI>
  void
  coaccessible_here(Element<A, AI>& a);

  /** @} */

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/accessible.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_ACCESSIBLE_HH
