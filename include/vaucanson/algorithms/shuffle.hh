// shuffle.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_SHUFFLE_HH
# define VCSN_ALGORITHMS_SHUFFLE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file shuffle.hh
 *
 * Declarations of shuffle().
 * @see shuffle()
 */
/** @} */

// INTERFACE: Automaton shuffle(const Automaton& a1, const Automaton& a2, const bool use_geometry) { return vcsn::shuffle(*a1, *a2); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <utility>
# include <map>

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

  /// @name Shuffle algorithm
  /// @{
  ///
  /// Returns a fresh automaton that is the shuffle of the two input ones.
  ///
  /// @pre The two input automata must be realtime.
  template<typename A, typename T, typename U>
  Element<A, T>
  shuffle(const Element<A, T>& lhs, const Element<A, U>& rhs,
	  const bool use_geometry = false);

  template<typename A, typename T, typename U>
  Element<A, T>
  shuffle(const Element<A, T>& lhs,
	  const Element<A, U>& rhs,
	  std::map<typename T::hstate_t,
	    std::pair<typename T::hstate_t, typename U::hstate_t> >&,
	  const bool use_geometry = false);
  /** @} */

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/shuffle.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_PRODUCT_HH
