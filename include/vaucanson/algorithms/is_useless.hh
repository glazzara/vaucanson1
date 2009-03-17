// is_useless.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_USELESS_HH
# define VCSN_ALGORITHMS_IS_USELESS_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file is_useless.hh
 *
 * Declaration of is_useless().
 *
 * @see is_useless()
 */
/** @} */

// INTERFACE: bool is_useless(const Automaton& a) { return vcsn::is_useless(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief Return true if the automaton has no successful computation.
   *
   * Return false if the automaton has a successful computation,
   * true otherwise.
   *
   * An automaton has a successful computation if it has at least
   * one state that is both accessible and co-accessible.
   *
   * @param a The input automaton.
   */
  template<typename A, typename AI>
  bool
  is_useless(const Element<A, AI>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/is_useless.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_IS_USELESS_HH
