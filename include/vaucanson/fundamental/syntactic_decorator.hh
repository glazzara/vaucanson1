// fundamental/syntactic_decorator.hh
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

#ifndef VCSN_FUNDAMENTAL_SYNTACTIC_DECORATOR_HH
# define VCSN_FUNDAMENTAL_SYNTACTIC_DECORATOR_HH

# include <vaucanson/fundamental/predecls.hh>

/**
 * @file syntactic_decorator.hh
 * @brief Declaration of the very base class of @c Element
 */

namespace vcsn {

  /** @addtogroup fundamental *//** @{ */

  /*-------------------.
  | SyntacticDecorator |
  `-------------------*/

  /**
   * @brief This class provides the standard operator delegations to Element.
   *
   * It defines all the self-application operators
   * of C++, and delegates them to corresponding @c op_* functions.
   */
  template<typename S, typename T> 
  struct SyntacticDecorator
  {
    /// Virtual accessor to the structural element
    const S&	set() const;
      
    /** @{ */
    /// Virtual accessor to value data
    T&		value();
    const T&	value() const;
    /** @} */

    /// self addition between Element instances. Maps to @c op_in_add.
    template<typename OtherS, typename U>				 
    Element<S, T>& operator+=(const Element<OtherS, U>& other);	 

    /// self addition between Element and foreign values. Maps to @c op_in_add.
    template<typename U>						 
    Element<S, T>& operator+=(const U& other);    

    /// self substraction between Element instances. Maps to @c op_in_sub.
    template<typename OtherS, typename U>				 
    Element<S, T>& operator-=(const Element<OtherS, U>& other);	 

    /// self substraction between Element and foreign values. Maps to @c op_in_sub.
    template<typename U>						 
    Element<S, T>& operator-=(const U& other);    

    /// self division between Element instances. Maps to @c op_in_div.
    template<typename OtherS, typename U>				 
    Element<S, T>& operator/=(const Element<OtherS, U>& other);	
 
    /// self division between Element and foreign values. Maps to @c op_in_div.
    template<typename U>						 
    Element<S, T>& operator/=(const U& other);    

    /// self multiplication between Element instances. Maps to @c op_in_mul.
    template<typename OtherS, typename U>				 
    Element<S, T>& operator*=(const Element<OtherS, U>& other);	
 
    /// self multiplication between Element and foreign values. Maps to @c op_in_mul.
    template<typename U>						 
    Element<S, T>& operator*=(const U& other);    

    /// self modulus between Element instances. Maps to @c op_in_mod.
    template<typename OtherS, typename U>				 
    Element<S, T>& operator%=(const Element<OtherS, U>& other);	
 
    /// self modulus between Element and foreign values. Maps to @c op_in_mod.
    template<typename U>						 
    Element<S, T>& operator%=(const U& other);    

    /// In-place, prefix incrementation. Maps to @c op_in_inc.
    Element<S, T>& operator++();

    /// Postfix incrementation. Maps to @c op_in_dec, with Element copy.
    Element<S, T> operator++(int);
      
    /// In-place, prefix decrementation. Maps to @c op_in_dec.
    Element<S, T>& operator--();

    /// Postfix decrementation. Maps to @c op_in_dec, with Element copy.
    Element<S, T> operator--(int);

    /// Standard constant-time swap between Element instances. Maps to @c op_swap.
    template<typename U>
    Element<S, T>& swap(Element<S, U>& other);

    /** @{ */
    /** 
     * Accessor to the real type.
     *
     * This accessor is intended to be used by implementations in this class
     * and derivated MetaElement specializations to obtain a reference to the
     * Element instance with its most derivated type.
     */
    Element<S, T>& self();
    const Element<S, T>& self() const;
    /** @} */

  protected:

    /** @{ */
    /// Protected constructor for class abstraction 
    SyntacticDecorator();
    SyntacticDecorator(const SyntacticDecorator& other);
    /** @} */
  };

  /** @} */

} // vcsn

# include <vaucanson/fundamental/syntactic_decorator.hxx>

#endif // VCSN_FUNDAMENTAL_SYNTACTIC_DECORATOR_HH
