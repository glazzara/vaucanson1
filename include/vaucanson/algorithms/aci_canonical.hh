// aci_canonical.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008, 2009 The Vaucanson Group.
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
   * @brief Transform a krat expression into a canonical form
   * using only ACI-rules.
   *
   * We call <b>ACI</b>-rules the following equivalences:
   * - <b>A</b>ssociativity of the sum: <tt>(E+F)+G = E+(F+G)</tt>
   * - <b>C</b>ommutativity of the sum: <tt>E+F = F+E</tt>
   * - <b>I</b>dempotence of the sum: <tt>E+E = E</tt>
   *
   * This algorithm will take a krat expression, and rebuild
   * it from the ground up.  Each time a sum (or a sum of sums)
   * is found, its operands are ordered in a way that is unique
   * and duplicate operands are removed.
   *
   * Note that two krat expressions can be equivalent even though
   * their canonical forms are different.  For instance <tt>E.E*</tt>
   * and <tt>E*.E</tt> are equivalent, but they will not be rewritten
   * by this algorithm since they do not contain any sum.
   *
   * This algorithm will run in \f$ O(n\log n) \f$, where \f$n\f$ is
   * the number of nodes of the input expression.
   *
   * @param exp The input krat expression.
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
