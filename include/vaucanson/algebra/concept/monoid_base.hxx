// monoid_base.hxx
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003  Sakarovitch, Lombardy, Poss, Rey and 
// Regis-Gianas.
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


#ifndef ALGEBRA_MONOID_BASE_HXX
# define ALGEBRA_MONOID_BASE_HXX

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
      return Element<Self, T>(self(), 
			      identity_value(SELECT(Self), SELECT(T)));
    }
    
    template<class Self>
    template<typename T>
    Element<Self, T>  MonoidBase<Self>::zero(SELECTOR(T)) const
    {
      return Element<Self, T>(self(), 
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
    inline
    Element<S, T>
    identity_as<T>::of(const S& s)
    {
      return s.identity(SELECT(T));
    }

    template <class T>
    template <class S>
    inline
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

  //! By default, an element of a monoid is the identity.
  template<typename T, typename Self>
  T op_default(SELECTOR(algebra::MonoidBase<Self>), SELECTOR(T))
  { 
    return identity_value(SELECT(Self), SELECT(T)); 
  }

} // vcsn

#endif // ALGEBRA_MONOID_BASE_HXX
