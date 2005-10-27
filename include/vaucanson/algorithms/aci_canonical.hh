// aci_canonical.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_ACI_CANONICAL_HH
# define VCSN_ALGORITHMS_ACI_CANONICAL_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file aci_canonical.hh
 *
 * This file contains the declaration for the canonical() algorithm.
 *
 * @see canonical()
 */
/** @} */

// INTERFACE: Exp canonical(const Exp& e) { return vcsn::canonical(e); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

  /// Transform a krat expression into its canonical form, following aci-rules.
  template <class Series, class T>
  Element<Series, T>
  canonical(const Element<Series, T>& exp);

  /** @} */

}


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/aci_canonical.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_ACI_CANONICAL_HH
