// freemonoid_product.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HH
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HH

# include <string>
# include <vaucanson/algebra/concept/freemonoid_product_base.hh>
# include <vaucanson/misc/unique.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra    */ /** @{ */
    /** @addtogroup fmp */ /** @{ */

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

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra    */ /** @{ */
  /** @addtogroup fmp */ /** @{ */

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

  /*------------------------------------------------.
  | representation_traits<FreeMonoidProduct<F, S> > |
  `------------------------------------------------*/
  /// Meta information about FreeMonoidProduct.
  template<class F, class S>
  struct representation_traits<algebra::FreeMonoidProduct<F, S> >
    : representation_traits<algebra::FreeMonoidProductBase<algebra::FreeMonoidProduct<F, S> > >
  { };

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

  /** @} */
  /** @} */


  template <class F, class S>
  struct virtual_types<algebra::FreeMonoidProduct<F, S> >
    : virtual_types<algebra::FreeMonoidProductBase<algebra::FreeMonoidProduct<F, S> > >
  {
    typedef F		first_monoid_t;
    typedef S		second_monoid_t;
  };

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/algebra/concept/freemonoid_product.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HH
