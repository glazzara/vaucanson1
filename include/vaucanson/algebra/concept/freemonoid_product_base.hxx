// freemonoid_product_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_BASE_HXX

# include <vaucanson/algebra/concept/freemonoid_product_base.hh>

namespace vcsn {

  namespace algebra {

    /*----------------------------.
    | FreeMonoidProductBase<Self> |
    `----------------------------*/

    template <class Self>
    typename FreeMonoidProductBase<Self>::first_monoid_t&
    FreeMonoidProductBase<Self>::first_monoid()
    {
      return this->self().first_monoid();
    }

    template <class Self>
    const typename FreeMonoidProductBase<Self>::first_monoid_t&
    FreeMonoidProductBase<Self>::first_monoid() const
    {
      return this->self().first_monoid();
    }
    template <class Self>
    typename FreeMonoidProductBase<Self>::second_monoid_t&
    FreeMonoidProductBase<Self>::second_monoid()
    {
      return this->self().second_monoid();
    }

    template <class Self>
    const typename FreeMonoidProductBase<Self>::second_monoid_t&
    FreeMonoidProductBase<Self>::second_monoid() const
    {
      return this->self().second_monoid();
    }

    template <class Self>
    FreeMonoidProductBase<Self>::FreeMonoidProductBase()
    {}

    template <class Self>
    FreeMonoidProductBase<Self>::
    FreeMonoidProductBase(const FreeMonoidProductBase& m) :
      MonoidBase<Self>(m)
    {}

  } // algebra

  /*--------------------------------------------.
  | MetaElement<FreeMonoidProductBase<Self>, T> |
  `--------------------------------------------*/
  template <class Self, typename T>
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::MetaElement() :
    MetaElement<algebra::MonoidBase<Self>, T>()
  {}

  template <class Self, typename T>
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::
  MetaElement(const MetaElement& o)  :
    MetaElement<algebra::MonoidBase<Self>, T>(o)
  {}

  template <class Self, typename T>
  typename
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::first_monoid_elt_t&
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::first()
  {
    return op_first(this->structure(), this->value());
  }

  template <class Self, typename T>
  const
  typename
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::first_monoid_elt_t&
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::first() const
  {
    return op_first(this->structure(), this->value());
  }

  template <class Self, typename T>
  typename
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::second_monoid_elt_t&
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::second()
  {
    return op_second(this->structure(), this->value());
  }

  template <class Self, typename T>
  const
  typename
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::second_monoid_elt_t&
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::second() const
  {
    return op_second(this->structure(), this->value());
  }

  template <class Self, typename T>
  void
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::mirror()
  {
    op_in_mirror(this->structure(), this->value());
  }

  template <class Self, typename T>
  template <class Ftor>
  typename Ftor::result_type
  MetaElement<algebra::FreeMonoidProductBase<Self>, T>::length(Ftor f)
  {
    return op_length(this->structure(), this->value(), f);
  }

} // vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_BASE_HXX
