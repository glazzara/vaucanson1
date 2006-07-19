// product.hh: this file is part of the Vaucanson project.
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

#ifndef INVERSE_HH
# define INVERSE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file inverse.hh
 *
 * Declarations of inverse().
 *
 * @see inverse()
 */
/** @} */

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/transducer.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// @name invert algorithm
  //@{

  /// Compute the automaton performing the invert rationnal relation.
  template<typename A, typename T>
  void
  invert(const Element<A, T>&,
	 Element<A, T>&);

  template<typename A, typename T>
  Element<A, T>&
  invert(const Element<A, T>&);

  //@}

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/invert.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !INVERSE_HH
