// freemonoid_product_base.hh: this file is part of the Vaucanson project.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_BASE_HH
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_BASE_HH

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>
# include <string>
# include <list>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup freemonoid product *//** @{ */

    /*----------------------------.
    | FreeMonoidProductBase<Self> |
    `----------------------------*/

    /**
     * Structural element for free monoid product.
     *
     * @c FreeMonoidProductBase is the mother class of free monoid products.
     * A free monoid product A* x B* is a monoid which is the product of the
     * free monoids A* and B*.
     */

    template<class Self>
    struct FreeMonoidProductBase
      : MonoidBase<Self>
    {
      /// The type of free monoid A*.
      typedef typename virtual_types<Self>::first_monoid_t first_monoid_t;

      /// The type of free monoid B*.
      typedef typename virtual_types<Self>::second_monoid_t second_monoid_t;

      /// First monoid's accessor.
      first_monoid_t&	first_monoid();

      /// First monoid's const accessor.
      const first_monoid_t& first_monoid() const;

      /// Second monoid's accessor.
      second_monoid_t& second_monoid();

      /// Second monoid's const accessor.
      const second_monoid_t& second_monoid() const;

    protected:
      /// Default constructor accessor.
      FreeMonoidProductBase();

      /// Copy constructor accessor.
      FreeMonoidProductBase(const FreeMonoidProductBase& m);
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup freemonoid *//** @{ */

  /*-------------------------------------------.
  | dynamic_traits<FreeMonoidProductBase<Self> |
  `-------------------------------------------*/

  template<class Self>
  struct dynamic_traits<algebra::FreeMonoidProductBase<Self> >
    : dynamic_traits<algebra::MonoidBase<Self> >
  { };

  template<typename S>
  struct virtual_types<algebra::FreeMonoidProductBase<S> >
    : virtual_types<algebra::MonoidBase<S> >
  {
    typedef undefined_type first_monoid_t;
    typedef undefined_type second_monoid_t;
  };


  /*--------------------------------------------.
  | MetaElement<FreeMonoidProductBase<Self>, T> |
  `--------------------------------------------*/

  /// Element of a monoid i.e. words.
  template<class Self, typename T>
  struct MetaElement<algebra::FreeMonoidProductBase<Self>, T>
    : MetaElement<algebra::MonoidBase<Self>, T>
  {
    typedef typename virtual_types<Self>::first_monoid_t first_monoid_t;
    typedef typename virtual_types<Self>::second_monoid_t second_monoid_t;

    typedef typename T::first_type		first_monoid_elt_value_t;
    typedef typename T::second_type		second_monoid_elt_value_t;

    typedef Element<first_monoid_t, first_monoid_elt_value_t>
						first_monoid_elt_t;
    typedef Element<second_monoid_t, second_monoid_elt_value_t>
						second_monoid_elt_t;

    /// First monoid's accessor.
    first_monoid_elt_t&	first();

    /// First monoid's const accessor.
    const first_monoid_elt_t& first() const;

    /// Second monoid's accessor.
    second_monoid_elt_t& second();

    /// Second monoid's const accessor.
    const second_monoid_elt_t& second() const;

    /// In-place mirror transformation.
    void mirror();

  protected:
    /// Default constructor is protected since it is an abstract class.
    MetaElement();

    /// Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };


} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/freemonoid_product_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif //VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_BASE_HH
