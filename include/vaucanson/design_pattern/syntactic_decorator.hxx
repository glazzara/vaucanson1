// syntactic_decorator.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_DESIGN_PATTERN_SYNTACTIC_DECORATOR_HXX
# define VCSN_DESIGN_PATTERN_SYNTACTIC_DECORATOR_HXX

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/design_pattern/syntactic_decorator.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn {
  template <typename S, typename T>
  Element<S, T>&
  SyntacticDecorator<S, T>::self()
  {
    return *static_cast<Element<S, T>*>(this);
  }

  template <typename S, typename T>
  const Element<S, T>&
  SyntacticDecorator<S, T>::self() const
  {
    return *static_cast<const Element<S, T>*>(this);
  }


  template <typename S, typename T>
  const S&
  SyntacticDecorator<S, T>::structure() const
  {
    return self().structure();
  }

  template <typename S, typename T>
  T&
  SyntacticDecorator<S, T>::value()
  {
    return self().value();
  }

  template <typename S, typename T>
  const T&
  SyntacticDecorator<S, T>::value() const
  {
    return self().value();
  }

#define ELEMENT_IN_OPERATOR(Op, HookName)					\
      template <typename S, typename T>						\
      template<typename OtherS, typename U>					\
      Element<S, T>&							\
      SyntacticDecorator<S, T>::Op (const Element<OtherS, U>& other)		\
      {										\
    op_in_ ## HookName (self().structure(),				   \
			other.structure(),				   \
			value(),					   \
			other.value());					   \
	return self();								\
      }										\
									   \
      template <typename S, typename T>						\
      template<typename U>							\
      Element<S, T>&							\
      SyntacticDecorator<S, T>::Op (const U& other)				\
      {										\
    op_in_ ## HookName (self().structure(),				   \
			value(),					   \
			op_convert(self().structure(), SELECT(T), other)); \
	return self();								\
      }

  ELEMENT_IN_OPERATOR(operator +=, add);
  ELEMENT_IN_OPERATOR(operator -=, sub);
  ELEMENT_IN_OPERATOR(operator /=, div);
  ELEMENT_IN_OPERATOR(operator *=, mul);
  ELEMENT_IN_OPERATOR(operator %=, mod);

#undef ELEMENT_IN_OPERATOR

  template <typename S, typename T>
  Element<S, T>&
  SyntacticDecorator<S, T>::operator++()
  {
    op_in_inc(self().structure(), self().value());
    return self();
  }

  template <typename S, typename T>
  Element<S, T>
  SyntacticDecorator<S, T>::operator++(int)
  {
    Element<S, T> ret(self());
    op_in_inc(self().structure(), self().value());
    return ret;
  }

  template <typename S, typename T>
  Element<S, T>&
  SyntacticDecorator<S, T>::operator--()
  {
    op_in_dec(self().structure(), self().value());
    return self();
  }

  template <typename S, typename T>
  Element<S, T>
  SyntacticDecorator<S, T>::operator--(int)
  {
    Element<S, T> ret(self());
    op_in_dec(self().structure(), self().value());
    return ret;
  }

  template <typename S, typename T>
  template <typename U>
  Element<S, T>&
  SyntacticDecorator<S, T>::swap(Element<S, U>& other)
  {
    precondition(&structure() == &other.structure());
    op_swap(structure(), value(), other.value());
    return self();
  }

  template <typename S, typename T>
  SyntacticDecorator<S, T>::SyntacticDecorator()
  {}

  template <typename S, typename T>
  SyntacticDecorator<S, T>::SyntacticDecorator(const SyntacticDecorator&)
  {}

} // vcsn

#endif // ! VCSN_DESIGN_PATTERN_SYNTACTIC_DECORATOR_HXX
