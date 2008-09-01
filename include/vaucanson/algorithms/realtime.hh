// realtime.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_REALTIME_HH
# define VCSN_ALGORITHMS_REALTIME_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file  realtime.hh
 *
 * General algorithms concerning realtime aspect of automata.
 *
 * An automaton over a free monoid @f$A^\star@f$ is realtime
 * if all its transitions are labeled by single letters of
 * @f$A@f$.  (Weights do not matter.)
 *
 * @see is_realtime(), realtime_here(), realtime()
 */
/** @} */

// INTERFACE: bool is_realtime(const Automaton& a) { return vcsn::is_realtime(*a); }
// INTERFACE: bool is_realtime(const GenAutomaton& a) { return vcsn::is_realtime(*a); }

// See realtime_decl.hh
// INTERFACE: Automaton realtime(const Automaton& a) { return vcsn::realtime(*a); }
// INTERFACE: GenAutomaton realtime(const GenAutomaton& a) { return vcsn::realtime(*a); }

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/direction.hh>
namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Modify an automaton in place to make it realtime.
   *
   * An automaton over a free monoid @f$A^\star@f$ is realtime
   * if all its transitions are labeled by single letters of
   * @f$A@f$.  (Weights do not matter.)
   *
   * This algorithm works in two steps: first transitions labeled by
   * words are split into transitions labeled by singled letters
   * separated by newly created states (if there is a weight
   * associated to the word, it will be associated to the first letter
   * and the other letter will be associated to the identity of the
   * semiring); second the epsilon transitions are removed.
   *
   * Removing epsilon transitions can be done in two ways: forward or
   * backward.  The @a dir argument can be used to control the direction
   * and default to forward.
   *
   * @param a The automaton to make realtime.
   * @param dir The direction of the epsilon removal algorithm.
   * @pre @a must be defined over a free monoid.
   *
   * @see realtime()
   */
  template<typename A, typename AI>
  void
  realtime_here(Element<A, AI>& a, misc::direction_type dir);

  /**
   * Create a realtime automaton from another one.
   *
   * As @c realtime_here, this algorithm builds a realtime automaton,
   * but it returns a new one instead of changing the given one.
   *
   * @param a The automaton to make realtime.
   * @param dir The direction of the epsilon removal algorithm.
   *
   * @see realtime_here()
   */
  template<typename A, typename AI>
  Element<A, AI>
  realtime(const Element<A, AI>& a, misc::direction_type dir);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/realtime.hxx>
# endif // VCSN_USE_INTERFACE_ONLY
/*
 * Include the declaration of realtime().
 *
 * Must  be  included _after_  the  .hxx  file  because it  needs  the
 * declarations of do_realtime_here() and do_realtime().
 */
#  include <vaucanson/algorithms/realtime_decl.hh>

#endif // ! VCSN_ALGORITHMS_REALTIME_HH
