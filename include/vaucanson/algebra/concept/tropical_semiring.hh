// tropical_semiring.hh
//
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH
# define ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {

    // Forward declaration.
    template <class TropicalKind>
    struct TropicalSemiring;

  } // algebra


    /*----------------------------------------------------.
    | MetaSet : traits about the set of tropical semiring |
    `----------------------------------------------------*/
    template<class TropicalKind>
    struct MetaSet<TropicalSemiring<TropicalKind> >
    {
      static const bool dynamic_set = false;
      typedef mul_kind	semigroup_kind;
    };

  namespace algebra {

    /*-----------------.
    | Kind of tropical |
    `-----------------*/
    struct TropicalMin
    {};

    struct TropicalMax
    {};

    /*-----------------.
    | TropicalSemiring |
    `-----------------*/
    template <class TropicalKind>
    struct TropicalSemiring
      : SemiringBase<TropicalSemiring<TropicalKind> >
    {};

  } // algebra

    /*------------.
    | MetaElement |
    `------------*/
    template<class TropicalKind, typename T>
    struct MetaElement<TropicalSemiring<TropicalKind> , T>
      : MetaElement<SemiringBase<TropicalSemiring<TropicalKind> >, T>
    {};

} // vcsn


#endif // ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH
