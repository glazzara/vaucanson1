// numerical_semiring.hh
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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
#ifndef ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH
# define ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {
    
    /*! \addtogroup algebra */  /* @{ */
    /*! \addtogroup semiring */ /* @{ */
    
    /*------------------.
    | NumericalSemiring |
    `------------------*/
    //! NumericalSemiring is the set of semirings implemented with 
    //! usual operations (+, *).
    struct NumericalSemiring
      : SemiringBase<NumericalSemiring>
    { };

    /*! @} @} */

  } // algebra
  
  /*! \addtogroup algebra */  /* @{ */
  /*! \addtogroup semiring */ /* @{ */
  
  /*---------------------------.
  | dynamic_traits<NumericalSemiring> |
  `---------------------------*/
  //! dynamic_traits<NumericalSemiring> defines meta information about then
  //! NumericalSemiring structural element. 
  template<>
  struct dynamic_traits<algebra::NumericalSemiring>
    : dynamic_traits<algebra::SemiringBase<algebra::NumericalSemiring> >
  {
  };


  template<>
  struct virtual_types<algebra::NumericalSemiring>
    : virtual_types<algebra::SemiringBase<algebra::NumericalSemiring> >
  {
    //! We can see a NumericalSemiring as a semigroup with +. It is
    //! an arbitrary decision, it could be mul_kind too.
    typedef           algebra::add_kind    semigroup_kind;
  };

  //! MetaElement<NumericalSemiring, T> defines the services of
  //! element of numerical semirings. 
  template<typename T>
  struct MetaElement<algebra::NumericalSemiring, T>
    : MetaElement<algebra::SemiringBase<algebra::NumericalSemiring>, T>
  {};

  /*! @} @} */

} // vcsn

#endif // ALGEBRA_CONCEPT_NUMERICAL_SEMIRING_HH
