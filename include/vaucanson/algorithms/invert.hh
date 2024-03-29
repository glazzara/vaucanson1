// product.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_INVERT_HH
# define VCSN_ALGORITHMS_INVERT_HH

# include <vaucanson/design_pattern/design_pattern.hh>

/**
 * @file invert.hh
 *
 * Declarations of invert().
 * Compute the automaton performing the inverse rationnal relation.
 *
 * This algorithm is described in "Weighted automata and transducers
 * in Vaucanson" by Akim Demaille, Sylvain Lombardy and Jacques
 * Sakarovitch, for WOWA 2006.
 *
 * @author Robert Bigaignon <robert.bigaignon@lrde.epita.fr>
 *
 * @see invert()
 */

// FIXME: the return type must be InvertAutomaton (but alas there is no invert_traits_helper
// as for now)
// FIXME: the algorithm shouldn't return a reference
// INTERFACE: Automaton& invert(const Automaton& a1) { return vcsn::invert(*a1); }

namespace vcsn {

  /**
   * @brief Invert a transducer.
   *
   * @param t	Input transducer.
   * @param res	Inverse transducer.
   *
   */
  template<typename A, typename T>
  void
  invert(const Element<A, T>& t,
	 Element<A, T>& res);

  /**
   * @brief Invert a transducer.
   *
   * @param t	Input transducer.
   * @return	Inverse transducer.
   *
   */
  template<typename A, typename T>
  Element<A, T>&
  invert(const Element<A, T>& t);

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/invert.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGORITHMS_INVERT_HH
