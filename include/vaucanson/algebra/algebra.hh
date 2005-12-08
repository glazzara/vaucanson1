// algebra.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_ALGEBRA_HH
# define VCSN_ALGEBRA_ALGEBRA_HH

/** @addtogroup algebra
 *
 * Algebra constructs for Vaucanson.
 *
 * This group  aggregates the documentation of  compounds related to
 * algebraic structures  of Vaucanson,  such as Monoids,  Series, or
 * rational expressions (as implementation of series).
 *
 * @see
 *     - vcsn::algebra
 *     - vcsn::algebra::AlphabetSet
 *     - vcsn::algebra::MonoidBase
 *     - vcsn::algebra::FreeMonoid
 *     - vcsn::algebra::FreeMonoidProduct
 *     - vcsn::algebra::SemigroupBase
 *     - vcsn::algebra::NumericalSemiring
 *     - vcsn::algebra::TropicalSemiring
 *     - vcsn::algebra::Series
 */
/** @{ */
/**
 * @file algebra.hh
 *
 * Workaround to give Doxygen documentation about the algebra namespace.
 *
 * This file is only provided  to give Doxygen documentation about the
 * algebra namespace,  and therefore should  not be included  by other
 * files. Furthermore, no declaration or definition should be there.
 *
 * @see
 *     - @ref algebra
 *     - ::vcsn::algebra
 */
/** @} */

namespace vcsn {

  /** @addtogroup algebra *//** @{ */

  /**
   * Namespace for algebra constructs in Vaucanson.
   *
   * The  algebra namespace  in Vaucanson  contains all  the compounds
   * which  are  needed   to  manipulate  algebraic  structures.  Both
   * structural   elements  (e.g.   Alphabets,   Monoids,  etc.)   and
   * implementations    of   those   elements    (polynoms,   rational
   * expressions, etc.) are presents in this namespace.
   *
   * @see
   *     - @ref algebra
   *     - @c AlphabetSet
   *     - @c MonoidBase
   *     - @c FreeMonoid
   *     - @c FreeMonoidProduct
   *     - @c SemigroupBase
   *     - @c NumericalSemiring
   *     - @c TropicalSemiring
   *     - @c Series
   */
  namespace algebra {}

  /** @} */

} // End of namespace vcsn.

#endif // ! VCSN_ALGEBRA_ALGEBRA_HH
