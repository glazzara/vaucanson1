// freemonoid_product_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004, 2005 The Vaucanson Group.
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

#endif // VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_BASE
