// element.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_DESIGN_PATTERN_ELEMENT_HXX
# define VCSN_DESIGN_PATTERN_ELEMENT_HXX

# include <vaucanson/misc/contract.hh>
# include <vaucanson/design_pattern/element.hh>

namespace vcsn {

  /*-------------.
  | Constructors |
  `-------------*/

  template <class S, class T>
  Element<S,T>::Element() :
    MetaElement<S, T>(),
    SetSlot<S>(),
    value_(op_default(SELECT(S), SELECT(T)))
  {
    static_assertion_(not dynamic_traits<S>::ret,
		      need_dynamic_structural_element);
  }

  /*--------------------------.
  | Constructors from Element |
  `--------------------------*/

  template <class S, class T>
  Element<S,T>::Element(const Element& other) :
    MetaElement<S, T>(other),
    SetSlot<S>(other),
    value_(other.value_)
  {}

  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const Element<S, U>& other) :
    SetSlot<S>(other.structure()),
    value_(op_convert(other.structure(), SELECT(T), other.value()))
  {}

  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>::Element(const Element<OtherS, U>& other)
    : SetSlot<S>(op_convert(SELECT(S), other.structure())),
      value_ (op_convert(this->_structure_get(), value_,
			 other.structure(), other.value()))
  {
  }

  /*-------------------------.
  | Constructors from values |
  `-------------------------*/

  template <class S, class T>
  Element<S,T>::Element(const T& other)
    : SetSlot<S> (),
      value_(op_convert(SELECT(S), SELECT(T), other))
  {
    static_assertion_(not dynamic_traits<S>::ret,
		      need_dynamic_structural_element);
  }

  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const U& other)
    : SetSlot<S> (),
      value_(op_convert(SELECT(S), SELECT(T), other))
  {
    static_assertion_(not dynamic_traits<S>::ret,
		      need_dynamic_structural_element);
  }

  /*--------------------------------------.
  | Constructors from structural elements |
  `--------------------------------------*/

  template <class S, class T>
  Element<S,T>::Element(const S& structure)
    : SetSlot<S>(structure),
      value_(op_default(this->_structure_get(), SELECT(T)))
  {}

  template <class S, class T>
  Element<S,T>::Element(const S& structure, const T& other)
    : SetSlot<S>(structure),
      value_(op_convert(this->_structure_get(), SELECT(T), other))
  {}
  template <class S, class T>
  template<typename U>
  Element<S,T>::Element(const S& structure, const U& other)
    : SetSlot<S>(structure),
      value_(op_convert(this->_structure_get(), SELECT(T), other))
  {}

  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>::Element(const S& structure, const Element<OtherS, U>& other)
    : SetSlot<S> (structure),
      value_(op_convert(this->_structure_get(), SELECT(T),
		        other.structure(), other.value()))
  {}

  /*-----------.
  | Assignment |
  `-----------*/

  template <class S, class T>
  Element<S,T>&
  Element<S,T>::operator = (const Element& other)
  {
    _structure_assign(other.structure());
    op_assign(structure(), other.structure(), value_, other.value());
    return *this;
  }

  template <class S, class T>
  template<typename U>
  Element<S,T>&
  Element<S,T>::operator = (const Element<S, U>& other)
  {
    _structure_assign(other.structure());
    op_assign(structure(), other.structure(), value_, other.value());
    return *this;
  }

  template <class S, class T>
  template<typename OtherS, typename U>
  Element<S,T>& Element<S,T>::operator = (const Element<OtherS, U>& other)
  {
    _structure_assign(op_convert(SELECT(S), other.structure()));
    op_assign(structure(), other.structure(), value_, other.value());
    return *this;
  }

  template <class S, class T>
  template<typename U>
  Element<S,T>& Element<S,T>::operator = (const U& other)
  {
    op_assign(structure(), value(), other);
    return *this;
  }

  /*------.
  | Sugar |
  `------*/

  template <class S, class T>
  void
  Element<S,T>::attach(const S& structure)
  {
    _structure_attach(structure);
  }

  template <class S, class T>
  const S&
  Element<S,T>::structure() const
  {
    return this->_structure_get();
  }

  template <class S, class T>
  T&	Element<S,T>::value()
  {
    return value_;
  }

  template <class S, class T>
  const T&	Element<S,T>::value() const
  {
    return value_;
  }

} // vcsn


#endif // ! VCSN_DESIGN_PATTERN_ELEMENT_HXX
