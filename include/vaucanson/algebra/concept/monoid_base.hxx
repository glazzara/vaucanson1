// monoid_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2010 The Vaucanson Group.
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

  template<class Self, typename T>
  bool
  MetaElement<algebra::MonoidBase<Self>, T>::is_atom() const
  {
    return op_is_atom(this->structure, this->value);
  }

  namespace algebra {

    template<typename T, typename Self>
    T
    op_default(SELECTOR(algebra::MonoidBase<Self>), SELECTOR(T))
    {
      // By default, an element of a monoid is the identity.
      return identity_value(SELECT(Self), SELECT(T));
    }

    template<typename Self, typename T>
    bool
    op_is_atom(const algebra::MonoidBase<Self>& s, const T& v)
    {
      return op_is_atom(s.self(), v);
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_MONOID_BASE_HXX
