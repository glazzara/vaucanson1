// algebra.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
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
   *     - @c SemigroupBase
   *     - @c NumericalSemiring
   *     - @c TropicalSemiring
   *     - @c Series
   */
  namespace algebra {}

  /** @} */

} // End of namespace vcsn.

#endif // ! VCSN_ALGEBRA_ALGEBRA_HH
