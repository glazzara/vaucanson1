// determinize.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_DETERMINISTIC_HH
# define VCSN_ALGORITHMS_IS_DETERMINISTIC_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   is_deterministic.hh
 *
 * Boolean automata determinization.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 19:13:10 2003
 *
 * @see is_deterministic()
 */
/** @} */

// INTERFACE: bool is_deterministic(const Automaton& a) { return vcsn::is_deterministic(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Test if an automaton is deterministic.
   *
   * @param a A Boolean automaton.
   *
   * @return true if 'a' is deterministic.
   */
  template<typename A, typename T>
  bool
  is_deterministic(const Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/is_deterministic.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_DETERMINIZE_HH
