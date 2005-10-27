// tropical_semiring.hh: this file is part of the Vaucanson project.
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
    {
      bool	operator == (const TropicalSemiring&) const;
    };

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


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/tropical_semiring.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_CONCEPT_TROPICAL_SEMIRING_HH
