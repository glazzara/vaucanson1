// krat_exp_pattern.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PATTERN_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PATTERN_HXX

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
      v_(v)
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

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PATTERN_HXX