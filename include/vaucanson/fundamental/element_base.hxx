// fundamental/element_base.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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


#ifndef ALGEBRA_ELEMENT_BASE_HXX
# define ALGEBRA_ELEMENT_BASE_HXX

# include <vaucanson/fundamental/element_ops.hh>
# include <vaucanson/fundamental/element_base.hh>

namespace vcsn {

  template <typename S, typename T> 
  inline const S& 
  SyntacticDecorator<S, T>::set() const 
  { 
    return self().set(); 
  }

  template <typename S, typename T>
  inline T& 
  SyntacticDecorator<S, T>::value()
  { 
    return self().value(); 
  }
    
  template <typename S, typename T>
  inline const T& 
  SyntacticDecorator<S, T>::value() const
  { 
    return self().value(); 
  }
    
#define ELEMENT_IN_OPERATOR(Op, HookName)				 \
      template <typename S, typename T>					 \
      template<typename OtherS, typename U>				 \
      inline Element<S, T>&						 \
      SyntacticDecorator<S, T>::Op (const Element<OtherS, U>& other)	 \
      {									 \
	op_in_ ## HookName (set(), other.set(), value(), other.value()); \
	return self();							 \
      }									 \
      template <typename S, typename T>					 \
      template<typename U>						 \
      inline Element<S, T>&						 \
      SyntacticDecorator<S, T>::Op (const U& other)			 \
      {									 \
	op_in_ ## HookName (set(), value(),				 \
			    op_convert(SELECT(T), SELECT(S), other));	 \
	return self();							 \
      }

  ELEMENT_IN_OPERATOR(operator +=, add);
  ELEMENT_IN_OPERATOR(operator -=, sub);
  ELEMENT_IN_OPERATOR(operator /=, div);
  ELEMENT_IN_OPERATOR(operator *=, mul);
  ELEMENT_IN_OPERATOR(operator %=, mod);
    
#undef ELEMENT_IN_OPERATOR

  template <typename S, typename T>
  inline Element<S, T>& 
  SyntacticDecorator<S, T>::operator++()
  { 
    op_in_inc(set(), value()); 
    return self(); 
  }
    
  template <typename S, typename T>
  inline Element<S, T> 
  SyntacticDecorator<S, T>::operator++(int)
  { 
    Element<S, T> ret(*this); 
    op_in_inc(set(), value()); 
    return ret; 
  }
    
  template <typename S, typename T>
  inline Element<S, T>& 
  SyntacticDecorator<S, T>::operator--()
  { 
    op_in_dec(set(), value()); 
    return self(); 
  }
    
  template <typename S, typename T>
  inline Element<S, T> 
  SyntacticDecorator<S, T>::operator--(int)
  { 
    Element<S, T> ret(*this); 
    op_in_dec(set(), value()); 
    return ret; 
  }
    
  template <typename S, typename T>
  template <typename U>
  inline Element<S, T>& 
  SyntacticDecorator<S, T>::swap(Element<S, U>& other)
  { 
    op_swap(SELECT(S), value(), other.value());
    return self(); 
  }
    
  template <typename S, typename T>
  template <typename OtherS, typename U>
  inline Element<S, T>&
  SyntacticDecorator<S, T>::swap(Element<OtherS, U>& other)
  { 
    op_swap(SELECT(S), SELECT(OtherS), value(), other.value());
    return self(); 
  }
    
  // static inheritance stuff. what's good is that we know
  // at this point the derived type.
  template <typename S, typename T>
  inline Element<S, T>&
  SyntacticDecorator<S, T>::self() 
  { 
    return static_cast<Element<S, T>&>(*this); 
  }
    
  template <typename S, typename T>
  inline const Element<S, T>& 
  SyntacticDecorator<S, T>::self() const
  { 
    return static_cast<const Element<S, T>&>(*this); 
  }
    
  template <typename S, typename T>
  inline SyntacticDecorator<S, T>::SyntacticDecorator() 
  {}
    
  template <typename S, typename T>
  inline SyntacticDecorator<S, T>::SyntacticDecorator(const SyntacticDecorator& other) 
  {} 

} // vcsn

#endif // ALGEBRA_ELEMENT_BASE_HXX
