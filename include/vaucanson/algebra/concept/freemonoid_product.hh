// freemonoid_product.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HH
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HH

# include <string>
# include <vaucanson/algebra/concept/freemonoid_product_base.hh>
# include <vaucanson/misc/unique.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra    */ /** @{ */
    /** @addtogroup freemonoid product */ /** @{ */

    /*------------------------.
    | FreeMonoidProduct<F, S> |
    `------------------------*/

    /// Implementation of a monoid which is a product of two free monoids.
    template<class F, class S>
    struct FreeMonoidProduct
      : FreeMonoidProductBase< FreeMonoidProduct<F, S> >
    {
      typedef F			first_monoid_t;
      typedef S			second_monoid_t;

      /// Constructor based on two free monoids.
      FreeMonoidProduct(const F& a, const S& b);

      /// Copy constructor.
      FreeMonoidProduct(const FreeMonoidProduct& w);

      /// Monoid's accessor.
      /// @bug FIXME: this interface should not exist
      /// (s.e. are const once instantiated)
      first_monoid_t&		first_monoid();

      const first_monoid_t&	first_monoid() const;

      second_monoid_t&		second_monoid();

      const second_monoid_t&	second_monoid() const;

    protected:
      first_monoid_t	first_monoid_;
      second_monoid_t	second_monoid_;
    };

    template<class F, class S>
    bool operator==(const FreeMonoidProduct<F, S>& m1,
		    const FreeMonoidProduct<F, S>& m2);

    /** @} @} */

  } // algebra

  /** @addtogroup algebra    */ /** @{ */
  /** @addtogroup freemonoid product */ /** @{ */

  /*-----------------------------------------.
  | dynamic_traits<FreeMonoidProduct<F, S> > |
  `-----------------------------------------*/
  /// Meta information about FreeMonoidProduct.
  template<class F, class S>
  struct dynamic_traits<algebra::FreeMonoidProduct<F, S> >
    : dynamic_traits<algebra::FreeMonoidProductBase<algebra::FreeMonoidProduct<F, S> > >
  {
    /// SetWord is dynamic if one of its free monoids is.
    static const bool
    ret = dynamic_traits<F>::ret or dynamic_traits<S>::ret;
  };

  /*----------------------------------------.
  | MetaElement<FreeMonoidProduct<F, S>, T> |
  `----------------------------------------*/
  /// Services of an element of a monoid implemented with
  /// FreeMonoidProduct.
  template<class F, class S, typename T>
  struct MetaElement<algebra::FreeMonoidProduct<F, S>, T>
    : MetaElement<algebra::FreeMonoidProductBase<algebra::FreeMonoidProduct<F, S> >, T>
  {
    typedef F	first_monoid_t;
    typedef S	second_monoid_t;
  };

  /** @} @} */

  template <class F, class S>
  struct virtual_types<algebra::FreeMonoidProduct<F, S> >
    : virtual_types<algebra::FreeMonoidProductBase<algebra::FreeMonoidProduct<F, S> > >
  {
    /// Commonly a free monoid use the multiplication symbol as operation.
    typedef algebra::mul_kind semigroup_kind;

    typedef F		first_monoid_t;
    typedef S		second_monoid_t;
  };

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/freemonoid_product.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HH
