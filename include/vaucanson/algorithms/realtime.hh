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
 * if all its transitons are labeled by single letters of
 * @f$A@f$.  (Weights do not matter.)
 *
 * @see is_realtime(), realtime_here(), realtime()
 */
/** @} */

// INTERFACE: bool is_realtime(const Automaton& a) { return vcsn::is_realtime(*a); }
// INTERFACE: bool is_realtime(const GenAutomaton& a) { return vcsn::is_realtime(*a); }

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/direction.hh>
namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * In place modification of the automaton to make it realtime.
   *
   * This algorithm makes an automaton realtime.  It calls @c
   * forward_realtime or @c backward_realtime according @a type.
   * If @a type is omitted, @c forward_realtime is used by default.
   *
   * @param a The automaton to make realtime.
   * @param type The type of algorithm used.
   *
   * @see realtime(), forward_realtime_here(), backward_realtime_here()
   */
  template<typename A, typename AI>
  void
  realtime_here(Element<A, AI>& a, misc::direction_type type);

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
  template<typename A, typename AI>
  Element<A, AI>
  realtime(const Element<A, AI>& a, misc::direction_type type);

  /** @} */

} // vcsn

// FIXME: this should be the correct one, should be fixed with:
//	    - the correct INTERFACE tag
//	    - a generation script that do not use INTERFACE tag
//# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
# if !defined VCSN_USE_INTERFACE_ONLY
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
