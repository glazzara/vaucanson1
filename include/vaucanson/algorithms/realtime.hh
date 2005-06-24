// realtime.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
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
 * This file contains algorithms concerning realtime aspect of automata, i.e.
 * presence or absence of epsilon transitions in the automaton.
 *
 * @see is_realtime(), realtime_here(), realtime()
 */
/** @} */

// INTERFACE: bool is_realtime(Automaton& a) { return vcsn::is_realtime(*a); }
// INTERFACE: bool is_realtime(GenAutomaton& a) { return vcsn::is_realtime(*a); }

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Enum to indicate which kind of realtime algorithms must be used.
  enum realtime_type { forward, backward };

  /**
   * In place modification of the automaton to make it realtime.
   *
   * This  algorithm   makes  an  automaton  realtime.   It  calls  @c
   * forward_realtime or @c backward_realtime according to type given.
   * The type may not be precised, it is the @c forward_realtime which
   * is used by default.
   *
   * @param a The automaton to make realtime.
   * @param type The type of algorithm used.
   *
   * @see realtime(), forward_realtime_here(), backward_realtime_here()
   */
  template<typename A, typename T>
  void
  realtime_here(Element<A, T>& a, realtime_type type);

  /**
   * Returns a fresh realtime automaton.
   *
   * As  @c  realtime_here, it  build  a  realtime  automaton, but  it
   * returns a new one instead of changing the given one.
   *
   * @param a The automaton to make realtime.
   * @param type The type of algorithm used.
   *
   * @see realtime_here(), forward_realtime(), backward_realtime()
   */
  template<typename A, typename T>
  Element<A, T>
  realtime(const Element<A, T>& a, realtime_type type);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/realtime.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

/*
 * Include the declaration of realtime().
 *
 * Must  be  included _after_  the  .hxx  file  because it  needs  the
 * declarations of do_realtime_here() and do_realtime().
 */
# include <vaucanson/algorithms/realtime_decl.hh>

#endif // ! VCSN_ALGORITHMS_REALTIME_HH
