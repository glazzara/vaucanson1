// projection.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_PROJECTION_HH
# define VCSN_ALGORITHMS_PROJECTION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file projection.hh
 *
 * @brief Build an FMP transducer that realizes the identity relation.
 * x -> (x,x)
 *
 */
/** @} */

// INTERFACE: void identity(const InputProjection& a, Automaton& b) { return vcsn::identity(*a, *b); }

# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/automata/concept/transducer.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  template <typename auto_t, typename trans_t>
  void
  set_states(const trans_t&, auto_t&,
	     std::map<typename trans_t::hstate_t, typename auto_t::hstate_t>&);

  /*---------.
  | Identity |
  `---------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  identity(const Element<S,T>& aut, Element<S2, T2>& res);

  /** @} */

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/projection.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_PROJECTION_HH
