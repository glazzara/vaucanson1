// tropical_semiring.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH
# define VCSN_ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {

    template <class TropicalKind>
    struct TropicalSemiring;

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup semiring *//** @{ */

  /*-----------------------------------------------------------.
  | dynamic_traits : traits about the set of tropical semiring |
  `-----------------------------------------------------------*/

  /// Meta information about the tropical semirings.
  template<class TropicalKind>
  struct dynamic_traits<algebra::TropicalSemiring<TropicalKind> >
    : dynamic_traits<algebra::SemiringBase<algebra::TropicalSemiring<TropicalKind> > >
  {
  };

  template<class TropicalKind>
  struct virtual_types<algebra::TropicalSemiring<TropicalKind> >
    : virtual_types<algebra::SemiringBase<algebra::TropicalSemiring<TropicalKind> > >
  {
    /**
     * We can see a NumericalSemiring as a semigroup with +.
     *
     * It is an arbitrary decision, it could be mul_kind too.
     */
    typedef algebra::add_kind	semigroup_kind;
  };


  /** @} */
  /** @} */

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup semiring *//** @{ */

    /*-----------------.
    | Kind of tropical |
    `-----------------*/

    /// Static information about the kind of tropical we are confronted with.
    struct TropicalMin
    {
    };

    /// Static information about the kind of tropical we are confronted with.
    struct TropicalMax
    {
    };

    /*-----------------.
    | TropicalSemiring |
    `-----------------*/

    /// Structural element that denotes tropical semiring.
    template <class TropicalKind>
    struct TropicalSemiring
      : SemiringBase<TropicalSemiring<TropicalKind> >
    {};

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup semiring *//** @{ */

  /*---------------------------------------.
  | MetaElement<TropicalSemiring<Kind>, T> |
  `---------------------------------------*/

  /// Services of element of a tropical semiring.
  template<class TropicalKind, typename T>
  struct MetaElement<algebra::TropicalSemiring<TropicalKind> , T>
    : MetaElement<algebra::SemiringBase<algebra::TropicalSemiring<TropicalKind> >, T>
  {};

  /** @} */
  /** @} */

} // vcsn

#endif // VCSN_ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH
