// monoid_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCEPT_MONOID_BASE_HXX
# define VCSN_ALGEBRA_CONCEPT_MONOID_BASE_HXX

# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/algebra/concept/semigroup_base.hh>

namespace vcsn {

  namespace algebra {

    /*-----------------.
    | MonoidBase<Self> |
    `-----------------*/
    template<class Self>
    template<typename T>
    Element<Self, T>
    MonoidBase<Self>::identity(SELECTOR(T)) const
    {
      return Element<Self, T>(this->self(),
			      identity_value(SELECT(Self), SELECT(T)));
    }

    template<class Self>
    template<typename T>
    Element<Self, T>  MonoidBase<Self>::zero(SELECTOR(T)) const
    {
      return Element<Self, T>(this->self(),
			      zero_value(SELECT(Self), SELECT(T)));
    }

    template <class Self>
    MonoidBase<Self>::MonoidBase()
    {}

    template <class Self>
    MonoidBase<Self>::MonoidBase(const MonoidBase& other) :
      SemigroupBase<Self>(other)
    {}

    template <class T>
    template <class S>
    Element<S, T>
    identity_as<T>::of(const S& s)
    {
      return s.identity(SELECT(T));
    }

    template <class T>
    template <class S>
    Element<S, T>
    zero_as<T>::of(const S& s)
    {
      return s.zero(SELECT(T));
    }

  } // algebra

    /*---------------------------------.
    | MetaElement<MonoidBase<Self>, T> |
    `---------------------------------*/

  template<class Self, typename T>
  MetaElement<algebra::MonoidBase<Self>, T>::MetaElement()
  {}

  template<class Self, typename T>
  MetaElement<algebra::MonoidBase<Self>, T>::MetaElement(const MetaElement& other) :
    MetaElement<algebra::SemigroupBase<Self>, T>(other)
  {}

  template<typename T, typename Self>
  T
  op_default(SELECTOR(algebra::MonoidBase<Self>), SELECTOR(T))
  {
    // By default, an element of a monoid is the identity.
    return identity_value(SELECT(Self), SELECT(T));
  }

} // vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_MONOID_BASE_HXX
