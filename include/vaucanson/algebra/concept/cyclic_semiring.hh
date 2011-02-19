// tropical_semiring.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_CYCLIC_SEMIRING_HH
# define VCSN_ALGEBRA_CONCEPT_CYCLIC_SEMIRING_HH

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {

    template <unsigned int n>
    struct CyclicSemiring;

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup semiring *//** @{ */

  /*-----------------------------------------------------------.
  |  dynamic_traits : traits about the set of cyclic semiring  |
  `-----------------------------------------------------------*/

  /// Meta information about the cyclic semirings.
  template<unsigned int n>
  struct dynamic_traits<algebra::CyclicSemiring<n> >
    : dynamic_traits<algebra::SemiringBase<algebra::CyclicSemiring<n> > >
  {
  };

  template<unsigned int n>
  struct virtual_types<algebra::CyclicSemiring<n> >
    : virtual_types<algebra::SemiringBase<algebra::CyclicSemiring<n> > >
  {
  };


  /** @} */
  /** @} */

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup semiring *//** @{ */

    /*-----------------.
    | CyclicSemiring |
    `-----------------*/

    /// Structural element that denotes tropical semiring.
    template <unsigned int n>
    struct CyclicSemiring
      : SemiringBase<CyclicSemiring<n> >
    {
      bool	operator == (const CyclicSemiring&) const;
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup semiring *//** @{ */

  /*---------------------------------------.
  |   MetaElement<CyclicSemiring<n>, T>    |
  `---------------------------------------*/

  /// Services of element of a tropical semiring.
  template<unsigned int n, typename T>
  struct MetaElement<algebra::CyclicSemiring<n> , T>
    : MetaElement<algebra::SemiringBase<algebra::CyclicSemiring<n> >, T>
  {};

  /** @} */
  /** @} */

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/concept/cyclic_semiring.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_CONCEPT_CYCLIC_SEMIRING_HH
