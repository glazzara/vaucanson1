// rw_composition.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_RW_COMPOSITION_HH
# define VCSN_ALGORITHMS_RW_COMPOSITION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file rw_composition.hh
 *
 * Composition of two Rational-Weight transducers.
 *
 * @see rw_composition()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Composition for Rational-Weight transducers.
  template<typename S, typename T>
  void
  rw_composition(const Element<S, T>&, const Element<S, T>&, Element<S, T>&);

  /// Composition for Rational-Weight transducers.
  template<typename S, typename T>
  Element<S, T>
  rw_composition(const Element<S, T>&, const Element<S, T>&);

  /** @} */

}

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/rw_composition.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_RW_COMPOSITION_HH
