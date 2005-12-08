// freemonoid_product.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HXX
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HXX

# include <vaucanson/algebra/concept/freemonoid_product.hh>

namespace vcsn {

  namespace algebra {

    /*------------------------.
    | FreeMonoidProduct<F, S> |
    `------------------------*/

    template <class F, class S>
    FreeMonoidProduct<F, S>::FreeMonoidProduct(const F& a, const S& b) :
      first_monoid_ (a), second_monoid_ (b)
    {}

    template <class F, class S>
    FreeMonoidProduct<F, S>::FreeMonoidProduct(const FreeMonoidProduct& w) :
      FreeMonoidProductBase<FreeMonoidProduct<F, S> >(w),
      first_monoid_(w.first_monoid_),
      second_monoid_(w.second_monoid_)
    {}

    template <class F, class S>
    typename FreeMonoidProduct<F, S>::first_monoid_t&
    FreeMonoidProduct<F, S>::first_monoid()
    {
      return first_monoid_;
    }

    template <class F, class S>
    const typename FreeMonoidProduct<F, S>::first_monoid_t&
    FreeMonoidProduct<F, S>::first_monoid() const
    {
      return first_monoid_;
    }

    template <class F, class S>
    typename FreeMonoidProduct<F, S>::second_monoid_t&
    FreeMonoidProduct<F, S>::second_monoid()
    {
      return second_monoid_;
    }

    template <class F, class S>
    const typename FreeMonoidProduct<F, S>::second_monoid_t&
    FreeMonoidProduct<F, S>::second_monoid() const
    {
      return second_monoid_;
    }

    template<class F, class S>
    bool operator==(const FreeMonoidProduct<F, S>& a,
		    const FreeMonoidProduct<F, S>& b)
    {
      return (a.first_monoid() == b.first_monoid()) and
	     (a.second_monoid() == b.second_monoid());
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HXX
