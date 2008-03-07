// has_succ_comp.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_HAS_SUCC_COMP_HH
# define VCSN_ALGORITHMS_HAS_SUCC_COMP_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file has_succ_comp.hh
 *
 * Declaration of has_succ_comp().
 *
 * @see has_succ_comp()
 */
/** @} */

// INTERFACE: bool has_succ_comp(const Automaton& a) { return vcsn::has_succ_comp(*a); }
// INTERFACE: bool has_succ_comp(const GenAutomaton& a) { return vcsn::has_succ_comp(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Return true if the automaton has successful computation
  /// (has at least one state that is both accessible and
  /// co-accessible), false otherwise.
  template<typename A, typename T>
  bool
  has_succ_comp(const Element<A, T>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/has_succ_comp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_HAS_SUCC_COMP_HH
