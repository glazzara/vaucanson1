// syntactic_decorator.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_DESIGN_PATTERN_SYNTACTIC_DECORATOR_HH
# define VCSN_DESIGN_PATTERN_SYNTACTIC_DECORATOR_HH

# include <vaucanson/design_pattern/predecls.hh>

/** @addtogroup design_pattern *//** @{ */
/**
 * @file syntactic_decorator.hh
 * @brief Declaration of the very base class of @c Element
 */
/** @} */

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */

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
    /// Attribute indicating whether the implementation type has run-time data.
    static const bool dynamic_value = true;

    /// Virtual accessor to the structural element.
    const S&	structure() const;

    //@{
    /// Virtual accessor to value data.
    T&		value();
    const T&	value() const;
    //@}

    /// Self addition between Element instances. Maps to @c op_in_add().
    template<typename OtherS, typename U>
    Element<S, T>& operator+=(const Element<OtherS, U>& other);

    /// @brief Self addition between Element and foreign values.
    ///        Maps to @c op_in_add().
    template<typename U>
    Element<S, T>& operator+=(const U& other);

    /// Self substraction between Element instances. Maps to @c op_in_sub().
    template<typename OtherS, typename U>
    Element<S, T>& operator-=(const Element<OtherS, U>& other);

    /// @brief Self substraction between Element and foreign values.
    ///        Maps to @c op_in_sub().
    template<typename U>
    Element<S, T>& operator-=(const U& other);

    /// Self division between Element instances. Maps to @c op_in_div().
    template<typename OtherS, typename U>
    Element<S, T>& operator/=(const Element<OtherS, U>& other);

    /// @brief Self division between Element and foreign values.
    ///        Maps to @c op_in_div().
    template<typename U>
    Element<S, T>& operator/=(const U& other);

    /// Self multiplication between Element instances. Maps to @c op_in_mul().
    template<typename OtherS, typename U>
    Element<S, T>& operator*=(const Element<OtherS, U>& other);

    /// @brief Self multiplication between Element and foreign values.
    ///        Maps to @c op_in_mul().
    template<typename U>
    Element<S, T>& operator*=(const U& other);

    /// Self modulus between Element instances. Maps to @c op_in_mod().
    template<typename OtherS, typename U>
    Element<S, T>& operator%=(const Element<OtherS, U>& other);

    /// @brief Self modulus between Element and foreign values.
    ///        Maps to @c op_in_mod().
    template<typename U>
    Element<S, T>& operator%=(const U& other);

    /// In-place, prefix incrementation. Maps to @c op_in_inc().
    Element<S, T>& operator++();

    /// Postfix incrementation. Maps to @c op_in_dec(), with Element copy.
    Element<S, T> operator++(int);

    /// In-place, prefix decrementation. Maps to @c op_in_dec().
    Element<S, T>& operator--();

    /// Postfix decrementation. Maps to @c op_in_dec(), with Element copy().
    Element<S, T> operator--(int);

    /// @brief Standard constant-time swap between Element instances.
    ///        Maps to @c op_swap().
    template<typename U>
    Element<S, T>& swap(Element<S, U>& other);

    //@{
    /**
     * Accessor to the real type.
     *
     * This accessor is intended to be used by implementations in this class
     * and derivated MetaElement specializations to obtain a reference to the
     * Element instance with its most derivated type.
     */
    Element<S, T>& self();
    const Element<S, T>& self() const;
    //@}

  protected:

    //@{
    /// @name Protected constructor for class abstraction
    SyntacticDecorator();
    SyntacticDecorator(const SyntacticDecorator& other);
    //@}
  };

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/design_pattern/syntactic_decorator.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_DESIGN_PATTERN_SYNTACTIC_DECORATOR_HH
