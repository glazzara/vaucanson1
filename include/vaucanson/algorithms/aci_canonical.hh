// aci_canonical.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_ACI_CANONICAL_HH
# define VCSN_ALGORITHMS_ACI_CANONICAL_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file aci_canonical.hh
 *
 * Declaration for the canonical() algorithm.
 *
 * @see canonical()
 */
/** @} */

// INTERFACE: Exp canonical(const Exp& e) { return vcsn::canonical(e); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

   /**
   * @brief Transform a krat expression into its canonical form, following aci-rules.
   *
   * @param exp The input krat expression.
   *
   * @bug FIXME write doc.
   */
  template <typename S, typename SI>
  Element<S, SI>
  canonical(const Element<S, SI>& exp);

  /** @} */

}


# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/aci_canonical.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_ACI_CANONICAL_HH
