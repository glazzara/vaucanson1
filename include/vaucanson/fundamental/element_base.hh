// fundamental/element_base.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_FUNDAMENTAL_ELEMENT_BASE_HH
# define VCSN_FUNDAMENTAL_ELEMENT_BASE_HH

# include <vaucanson/fundamental/predefs.hh>

namespace vcsn {

  // FIXME: general remark : this file should be called syntactic_decorator.hh

  /*! @addtogroup fundamental */ /*! @{ */

  /*-------------------.
  | SyntacticDecorator |
  `-------------------*/
  //! SyntacticDecorator provides the standard operator to Element.
  //
  /*! SyntacticDecorator defines all the self-application operators
    of C++. In fact, this decorator is essential because it is
    the wrapper of standard operators to Vaucanson op_*. 
  */
  template<typename S, typename T> 
  struct SyntacticDecorator
  {
    /*! Structural element virtual accessor. (const) */
    const S&	set() const;
      
    /*! Virtual accessor to implementation. */
    T&		value();
      
    /*! Virtual accessor to implementation. (const version) */
    const T&	value() const;

    /*! self addition between two a priori different elements. */
    template<typename OtherS, typename U>				 
    Element<S, T>& operator+=(const Element<OtherS, U>& other);	 

    /*! self addition between an element and something else. */
    template<typename U>						 
    Element<S, T>& operator+=(const U& other);    

    /*! self substraction between two a priori different elements. */
    template<typename OtherS, typename U>				 
    Element<S, T>& operator-=(const Element<OtherS, U>& other);	 

    /*! self substraction between an element and something else. */
    template<typename U>						 
    Element<S, T>& operator-=(const U& other);    

    /*! self substraction between two a priori different elements. */
    template<typename OtherS, typename U>				 
    Element<S, T>& operator/=(const Element<OtherS, U>& other);	
 
    template<typename U>						 
    Element<S, T>& operator/=(const U& other);    

    /*! self substraction between two a priori different elements. */
    template<typename OtherS, typename U>				 
    Element<S, T>& operator*=(const Element<OtherS, U>& other);	
 
    template<typename U>						 
    Element<S, T>& operator*=(const U& other);    

    /*! self substraction between two a priori different elements. */
    template<typename OtherS, typename U>				 
    Element<S, T>& operator%=(const Element<OtherS, U>& other);	
 
    template<typename U>						 
    Element<S, T>& operator%=(const U& other);    

    /*! pre-incrementation. */
    Element<S, T>& operator++();

    /*! post-incrementation. */
    Element<S, T> operator++(int);
      
    /*! pre-decrementation.  */
    Element<S, T>& operator--();

    /*! post-decrementation. */
    Element<S, T> operator--(int);

    /*! standard swap between two a priori different
      implementations. */
    template<typename U>
    Element<S, T>& swap(Element<S, U>& other);

    /*! standard swap between two a priori different elements. */
    template<typename OtherS, typename U>
    Element<S, T>& swap(Element<OtherS, U>& other);

    /*! static inheritance method. */
    // FIXME: is it really the good place ?
    Element<S, T>& self();

    /*! static inheritance method. (const version) */
    // FIXME: is it really the good place ?
    const Element<S, T>& self() const;

  protected:

    /*! Constructors are protected since SyntaticDecorator can be
      instantiated alone. */
    SyntacticDecorator();

    /*! Constructors are protected since SyntaticDecorator can be
      instantiated alone. */
    SyntacticDecorator(const SyntacticDecorator& other);
  };

  /*! @} */

} // vcsn

# include <vaucanson/fundamental/element_base.hxx>

#endif // VCSN_FUNDAMENTAL_ELEMENT_BASE_HH
