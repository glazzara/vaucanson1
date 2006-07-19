// static.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_STATIC_HH
# define VCSN_MISC_STATIC_HH

/**
 * @file misc/static.hh
 * Definition of metaprogrammation helpers.
 */

# include <cstddef>

namespace utility {

  /** @addtogroup utility *//** @{ */


  /*-----------------.
  | remove_reference |
  `-----------------*/

  /// Turn a reference type into its corresponding plain type.
  /** @{ */
  template<typename T>
  struct remove_reference
  {
      typedef T t;
  };

  template<typename T>
  struct remove_reference<T&>
  {
      typedef T t;
  };

  template<typename T>
  struct remove_reference<const T&>
  {
      typedef const T t;
  };
  /** @} */

  /*-------------.
  | remove_const |
  `-------------*/

  /// Turn a const type into its corresponding mutable type.
  /** @{ */
  template<typename T>
  struct remove_const
  {
      typedef T t;
  };

  template<typename T>
  struct remove_const<const T>
  {
      typedef T t;
  };
  /** @} */

  /*----------.
  | static_if |
  `----------*/

  /**
   * Choose between two types or values depending on a constant Boolean.
   *
   * @author Raphael Poss <raph@lrde.epita.fr>
   * @see static_if_simple
   */
  /** @{ */
  template<bool b, typename T, typename U>
  struct static_if
  {
      typedef T t;

      typedef typename remove_const<typename remove_reference<T>::t>::t bare_t1;
      typedef typename remove_const<typename remove_reference<U>::t>::t bare_t2;

      static bare_t1&
      choose(bare_t1& p1,
	     bare_t2& )
      { return p1; }
      static const bare_t1&
      choose(const bare_t1& p1,
	     const bare_t2& )
      { return p1; }
  };

  template<typename T, typename U>
  struct static_if<false, T, U>
  {
      typedef U t;

      typedef typename remove_const<typename remove_reference<T>::t>::t bare_t1;
      typedef typename remove_const<typename remove_reference<U>::t>::t bare_t2;

      static bare_t2&
      choose(bare_t1& ,
	     bare_t2& p2)
      { return p2; }
      static const bare_t2&
      choose(const bare_t1& ,
	     const bare_t2& p2)
      { return p2; }
  };
  /** @} */

  /*----------------.
  | Static Booleans |
  `----------------*/
  /**
   * Static Booleans, for type matching use of Booleans.
   */
  struct true_t {};
  struct false_t {};

  template <bool B>
  struct bool_to_type_helper
  {
      typedef true_t ret;
  };

  template <>
  struct bool_to_type_helper<false>
  {
      typedef false_t ret;
  };

# define bool_to_type(Bool) typename utility::bool_to_type_helper<(Bool)>::ret

  /*-----------------.
  | static_if_simple |
  `-----------------*/

  /**
   * Choose between two types or values depending on a constant Boolean.
   *
   * The classical static_if  cannot choose between a type  T and void
   * because of	 its choose() methods which take  references. This one
   * is much simpler  and require no conditions on  types. However, it
   * has no choose method.
   *
   * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
   * @see static_if
   */
  /** @{ */
  template<bool b, typename T, typename U>
  struct static_if_simple
  {
      typedef T t;
  };

  template<typename T, typename U>
  struct static_if_simple<false, T, U>
  {
      typedef U t;
  };
  /** @} */

  /*----------.
  | static_eq |
  `----------*/

  /// Test for equality between two types.
  /** @{ */
  template<typename T, typename U>
  struct static_eq
  {
      static const bool value = false;
  };

  template<typename T>
  struct static_eq<T, T>
  {
      static const bool value = true;
  };
  /** @} */

  /*-----------.
  | static_pow |
  `-----------*/

  /// These are auxilliary functions for static_pow.
  /** @{ */
  template<size_t N, size_t P, bool pair_p = false>
  struct static_pow_compute
  {
      static const size_t value =
	N * static_pow_compute<N, P-1, (((P-1) % 2) == 0)>::value ;
  };

  template<size_t N, size_t P>
  struct static_pow_compute<N, P, true>
  {
      static const size_t temp =
	static_pow_compute<N, P/2, (((P/2) % 2) == 0)>::value;
      static const size_t value = temp * temp;
  };

  template<size_t N>
  struct static_pow_compute<N, 0, true>
  {
      static const size_t value = 1;
  };
  /** @} */

  /** Static exponentiation.
   * It uses the fast exponentiation algorithm to save
   * template recursion depth.
   */
  template<size_t N, size_t P>
  struct static_pow
  {
      static const size_t value =
	static_pow_compute<N, P, ((P % 2) == 0)>::value ;
  };

  /*---------------------.
  | static_pow_minus_one |
  `---------------------*/

  /** Static exponentiation, result minus one. @see @c static_pow */
  template<size_t N, size_t P>
  struct static_pow_minus_one
  {
      static const size_t value =
	static_pow_compute<N, P, ((P % 2) == 0)>::value - 1;
  };

  /** @} */

} // utility

#endif // ! VCSN_MISC_STATIC_HH
