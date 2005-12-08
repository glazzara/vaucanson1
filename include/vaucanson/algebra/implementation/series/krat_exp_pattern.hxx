// krat_exp_pattern.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PATTERN_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PATTERN_HXX

# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn {

  namespace algebra {

    template <class T, class U>
    BinaryOp<T, U>::BinaryOp()
    {}

    template <class T, class U>
    BinaryOp<T, U>::BinaryOp(const BinaryOp& b) :
      lhs_(b.lhs_),
      rhs_(b.rhs_)
    {}

    template <class T, class U>
    BinaryOp<T, U>::BinaryOp(const T& lhs, const U& rhs) :
      lhs_(lhs),
      rhs_(rhs)
    {}

    template <class T, class U>
    T&
    BinaryOp<T, U>::lhs()
    {
      return lhs_;
    }

    template <class T, class U>
    const T&
    BinaryOp<T, U>::lhs() const
    {
      return lhs_;
    }

    template <class T, class U>
    U&
    BinaryOp<T, U>::rhs()
    {
      return rhs_;
    }

    template <class T, class U>
    const U&
    BinaryOp<T, U>::rhs() const
    {
      return rhs_;
    }

    template <class T>
    UnaryOp<T>::UnaryOp()
    {}

    template <class T>
    UnaryOp<T>::UnaryOp(const UnaryOp& b) :
      node_(b.node_)
    {}

    template <class T>
    UnaryOp<T>::UnaryOp(const T& node) :
      node_(node)
    {}

    template <class T>
    T&
    UnaryOp<T>::value()
    {
      return node_;
    }

    template <class T>
    const T&
    UnaryOp<T>::value() const
    {
      return node_;
    }

    template <class T>
    Value<T>::Value()
    {}

    template <class T>
    Value<T>::Value(const Value& v) :
      v_ (v.v_)
    {}

    template <class T>
    Value<T>::Value(const T& v) :
      v_(v)
    {}

    template <class T>
    T&
    Value<T>::value()
    {
      return v_;
    }

    template <class T>
    const T&
    Value<T>::value() const
    {
      return v_;
    }

    template <class Self, class T, class U, class F>
    U
    GenericMatcher<Self, T, U, F>::match(const T& ast)
    {
      return F::d(*static_cast<Self*>(this), ast);
    }

    template <class Self, class T, class U, class F>
    GenericMatcher<Self, T, U, F>::GenericMatcher()
    {}

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PATTERN_HXX
