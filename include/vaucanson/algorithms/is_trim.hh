// trim.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_IS_TRIM_HH
# define VCSN_ALGORITHMS_IS_TRIM_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file is_trim.hh
 *
 * Declaration of is_trim()
 *
 * @see trim()
 */
/** @} */

// INTERFACE: bool is_trim (const Automaton& a) { return vcsn::is_trim (*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <set>

namespace vcsn
{
  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief Return true is all states are reachable and co-reachable
   *
   * This function return true if all states are reachable and co-reachable
   *
   * @param a The input automaton.
   */
  template<typename A, typename AI>
  bool
  is_trim (const Element<A, AI>& a);
  /** @} */
} // !vcsn


# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/is_trim.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGORITHMS_IS_TRIM_HH
