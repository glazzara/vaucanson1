// fundamental/element.hxx
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

#ifndef VCSN_FUNDAMENTAL_ELEMENT_HXX
# define VCSN_FUNDAMENTAL_ELEMENT_HXX

# include <vaucanson/fundamental/element.hh>

namespace vcsn {

  /*-------------.
  | Constructors |
  `-------------*/

  template <class S, class T>
  inline
  Element<S,T>::Element() :
    MetaElement<S, T>(),
    set_(), 
    value_(op_default(SELECT(S), SELECT(T)))
  {}

  /*--------------------------.
  | Constructors from Element |
  `--------------------------*/
    
  template <class S, class T>
  inline
  Element<S,T>::Element(const Element& other) :
    MetaElement<S, T>(other),
    set_(other.set_), 
    value_(other.value_)
  {}
    
  template <class S, class T>
  template<typename U>
  inline
  Element<S,T>::Element(const Element<S, U>& other)
    : set_(other.set()),
      value_(op_convert(other.set(), SELECT(T), other.value()))
  {}
    
  template <class S, class T>
  template<typename OtherS, typename U>
  inline
  Element<S,T>::Element(const Element<OtherS, U>& other)
    : set_(),
      value_(op_convert(SELECT(S), SELECT(T), 
			other.set(), other.value()))
  {}

  /*-------------------------.
  | Constructors from values |
  `-------------------------*/
    
  template <class S, class T>
  inline
  Element<S,T>::Element(const T& other)
    : set_(),
      value_(op_convert(SELECT(S), SELECT(T), other))
  {}
    
  template <class S, class T>
  template<typename U>
  inline
  Element<S,T>::Element(const U& other)
    : set_(),
      value_(op_convert(SELECT(S), SELECT(T), other))
  {}
    
  /*--------------------------------------.
  | Constructors from structural elements |
  `--------------------------------------*/

  template <class S, class T>
  inline
  Element<S,T>::Element(const S& set)
    : set_(set),
      value_(op_default(set_.get(), SELECT(T)))
  {}
    
  template <class S, class T>
  inline  
  Element<S,T>::Element(const S& set, const T& other)
    : set_(set),
      value_(op_convert(set_.get(), SELECT(T), other))
  {}
  template <class S, class T>
  template<typename U>
  inline
  Element<S,T>::Element(const S& set, const U& other)
    : set_(set),
      value_(op_convert(set_.get(), SELECT(T), other))
  {}
    
  template <class S, class T>
  template<typename OtherS, typename U>
  inline
  Element<S,T>::Element(const S& set, const Element<OtherS, U>& other)
    : set_(set),
      value_(op_convert(set_.get(), SELECT(T), 
		        other.set(), other.value()))
  {}
    
  /*-----------.
  | Assignment |
  `-----------*/
    
  template <class S, class T>
  inline
  Element<S,T>& 
  Element<S,T>::operator=(const Element& other)
  {
    if (!set_.bound())
      set_.assign(other.set_);
    op_assign(set(), other.set(), value_, other.value());
    return *this;
  }
    
  template <class S, class T>
  template<typename U>
  inline
  Element<S,T>& 
  Element<S,T>::operator=(const Element<S, U>& other)
  {
    if (!set_.bound())
      set_.assign(other.set());
    op_assign(set(), other.set(), value_, other.value());
    return *this; 
  }

  template <class S, class T>
  template<typename OtherS, typename U>
  inline
  Element<S,T>& Element<S,T>::operator=(const Element<OtherS, U>& other)
  { 
    // FIXME: recommendation(set_.bound())
    op_assign(set(), other.set(), value_, other.value());
    return *this; 
  }

  template <class S, class T>
  template<typename U>
  inline
  Element<S,T>& Element<S,T>::operator=(const U& other)
  {
    // FIXME: recommendation(set_.bound());
    op_assign(set(), value(), other);
    return *this;
  }

  /*------.
  | Sugar |
  `------*/

  template <class S, class T>
  inline
  void 
  Element<S,T>::attach(const S& set)
  { 
    set_.attach(set); 
  }

  template <class S, class T>
  inline
  const S&
  Element<S,T>::set() const 
  { 
    return set_.get(); 
  }

  template <class S, class T>
  inline
  bool Element<S,T>::bound() const
  { 
    return set_.bound(); 
  }

  template <class S, class T>
  inline
  T&	Element<S,T>::value()       
  { 
    return value_; 
  }

  template <class S, class T>
  inline
  const T&	Element<S,T>::value() const 
  { 
    return value_; 
  }

} // vcsn


#endif // VCSN_FUNDAMENTAL_ELEMENT_HXX
