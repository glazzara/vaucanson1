// is_empty.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_IS_EMPTY_HH
# define VCSN_ALGORITHMS_IS_EMPTY_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file is_empty.hh
 *
 * Declaration of is_empty().
 *
 * @see is_empty()
 */
/** @} */

// INTERFACE: bool is_empty(const Automaton& a) { return vcsn::is_empty(*a); }
// INTERFACE: bool is_empty(const GenAutomaton& a) { return vcsn::is_empty(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Return true if the automaton is empty (has no state),
  /// false otherwise.
  template<typename A, typename T>
  bool
  is_empty(const Element<A, T>& a);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/is_empty.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_IS_EMPTY_HH
