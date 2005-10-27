// letter_to_letter_composition.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_LETTER_TO_LETTER_COMPOSITION_HH
# define VCSN_ALGORITHMS_LETTER_TO_LETTER_COMPOSITION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file letter_to_letter_composition.hh
 *
 * Undocumented stuff.
 *
 * @see letter_to_letter_composition()
 * @bug FIXME: Document!
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Undocumented.
  template <class S, class T>
  Element<S, T>
  letter_to_letter_composition(const Element<S, T>& lhs,
			       const Element<S, T>& rhs);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/letter_to_letter_composition.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_LETTER_TO_LETTER_COMPOSITION_HH
