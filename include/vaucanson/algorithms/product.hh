// product.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_PRODUCT_HH
# define VCSN_ALGORITHMS_PRODUCT_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file product.hh
 *
 * This file contains the declarations of product().
 *
 * @see product()
 */
/** @} */

// INTERFACE: Automaton product(const Automaton& a1, const Automaton& a2) { return vcsn::product(*a1, *a2); }
// INTERFACE: GenAutomaton product(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::product(*a1, *a2); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <utility>
# include <map>

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

  /// @name Product algorithm
  //@{
  /// Returns a fresh automaton that is the product of the two input ones.
  template<typename A, typename T, typename U>
  Element<A, T>
  product(const Element<A, T>& lhs, const Element<A, U>& rhs,
	  const bool use_geometry = false);

  template<typename A, typename T, typename U>
  Element<A, T>
  product(const Element<A, T>& lhs,
	  const Element<A, U>& rhs,
	  std::map<hstate_t, std::pair<hstate_t, hstate_t> >&,
	  const bool use_geometry = false);
  //@}

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/product.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_PRODUCT_HH
