// numerical_semiring.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH
# define VCSN_ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup semiring *//** @{ */

    /*------------------.
    | NumericalSemiring |
    `------------------*/
    /// NumericalSemiring is the set of semirings implemented with
    /// usual operations (+, *).
    struct NumericalSemiring
      : SemiringBase<NumericalSemiring>
    {
      bool	operator == (const NumericalSemiring&) const;
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup semiring *//** @{ */

  /*----------------------------------.
  | dynamic_traits<NumericalSemiring> |
  `----------------------------------*/
  /// Meta information about then NumericalSemiring structural element.
  template<>
  struct dynamic_traits<algebra::NumericalSemiring>
    : dynamic_traits<algebra::SemiringBase<algebra::NumericalSemiring> >
  {
  };

  template<>
  struct virtual_types<algebra::NumericalSemiring>
    : virtual_types<algebra::SemiringBase<algebra::NumericalSemiring> >
  {
    /**
     * It is possible to consider a NumericalSemiring as a semigroup with +.
     *
     * It is an arbitrary decision, it could be mul_kind too.
     */
    typedef           algebra::add_kind    semigroup_kind;
  };

  /// Services of @c Element for numerical semirings.
  template<typename T>
  struct MetaElement<algebra::NumericalSemiring, T>
    : MetaElement<algebra::SemiringBase<algebra::NumericalSemiring>, T>
  {};

  /** @} */
  /** @} */


} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/numerical_semiring.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH
