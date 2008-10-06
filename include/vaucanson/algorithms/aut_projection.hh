// aut_projection.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_AUT_PROJECTION_HH
# define VCSN_ALGORITHMS_AUT_PROJECTION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file aut_projection.hh
 *
 * @brief Projections for automata that support it (it depends on the
 * letter type).
 *
 * @author Jerome Galtier <jerome.galtier@lrde.epita.fr>
 */
/** @} */

// INTERFACE: void first_projection(const Automaton& a, FirstProjection& b) { return vcsn::first_projection(*a, *b); }
// INTERFACE: void second_projection(const Automaton& a, SecondProjection& b) { return vcsn::second_projection(*a, *b); }

# include <map>

# include <vaucanson/automata/concept/automata.hh>

namespace vcsn
{
  template <typename S, typename T>
  void
  first_projection(const Element<S, T>&,
		   typename projection_traits<S, T>::first_projection_t&);

  template <typename S, typename T>
  typename projection_traits<S, T>::first_projection_t
  first_projection(const Element<S, T>&);

  template <typename S, typename T>
  void
  second_projection(const Element<S, T>&,
		    typename projection_traits<S, T>::second_projection_t&);

  template <typename S, typename T>
  typename projection_traits<S, T>::second_projection_t
  second_projection(const Element<S, T>&);

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/aut_projection.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_AUT_PROJECTION_HH
