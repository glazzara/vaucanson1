// element_ops.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_DESIGN_PATTERN_ELEMENT_OPS_HH
# define VCSN_DESIGN_PATTERN_ELEMENT_OPS_HH

/** @addtogroup design_pattern *//** @{ */
/** @addtogroup operators   *//** @{ */
/**
 * @file element_ops.hh
 * @brief Declarations of standard external operator delegations for @c Element
 */
/** @} */
/** @} */

# include <vaucanson/design_pattern/element_op_traits.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */
  /** @addtogroup operators   *//** @{ */

  /*-------------------.
  | Ordered comparison |
  `-------------------*/

  /// Comparison between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  bool operator<(const vcsn::Element<S1, T1>& e1,
		 const vcsn::Element<S2, T2>& e2);

  /// Comparison between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  bool operator>(const vcsn::Element<S1, T1>& e1,
		 const vcsn::Element<S2, T2>& e2);

  /// Comparison between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  bool operator<=(const vcsn::Element<S1, T1>& e1,
		  const vcsn::Element<S2, T2>& e2);

  /// Comparison between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  bool operator>=(const vcsn::Element<S1, T1>& e1,
		  const vcsn::Element<S2, T2>& e2);

  /// Comparison between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static
  bool operator <(const vcsn::Element<S, T>& e,
		  const U& v);

  /// Comparison between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static
  bool operator >(const vcsn::Element<S, T>& e,
		  const U& v);

  /// Comparison between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static
  bool operator >=(const vcsn::Element<S, T>& e,
		   const U& v);

  /// Comparison between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static
  bool operator <=(const vcsn::Element<S, T>& e,
		   const U& v);

  /// Comparison between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static
  bool operator <(const U& v,
		  const vcsn::Element<S, T>& e);

  /// Comparison between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static
  bool operator >(const U& v,
		  const vcsn::Element<S, T>& e);

  /// Comparison between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static
  bool operator >=(const U& v,
		   const vcsn::Element<S, T>& e);

  /// Comparison between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static
  bool operator <=(const U& v,
		   const vcsn::Element<S, T>& e);

  /*---------.
  | Equality |
  `---------*/

  /// Equality between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  bool operator ==(const vcsn::Element<S1, T1>& e1,
		  const vcsn::Element<S2, T2>& e2);

  /// Equality between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static
  bool operator ==(const vcsn::Element<S, T>& e,
		   const U& v);

  /// Equality between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static
  bool operator ==(const U& v,
		   const vcsn::Element<S, T>& e);

  /*-----------.
  | Difference |
  `-----------*/

  /// Difference between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  bool operator !=(const vcsn::Element<S1, T1>& e1,
		  const vcsn::Element<S2, T2>& e2);

  /// Difference between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static
  bool operator !=(const vcsn::Element<S, T>& e,
		   const U& v);

  /// Difference between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static
  bool operator !=(const U& v,
		   const vcsn::Element<S, T>& e);

  /*---------.
  | Addition |
  `---------*/

  /// Addition between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  typename vcsn::op_add_traits<S1, S2, T1, T2>::ret_t
  operator+(const vcsn::Element<S1, T1>& e1,
	    const vcsn::Element<S2, T2>& e2);

  /// Addition between Element and foreign values (left)
  template<typename S, typename T, typename U>
  static vcsn::Element<S, T>
  operator +(const vcsn::Element<S, T>& e,
	     const U& v);

  /// Addition between Element and foreign values (right)
  template<typename U, typename S, typename T>
  static vcsn::Element<S, T>
  operator +(const U& v,
	     const vcsn::Element<S, T>& e);

  /*-------------.
  | Substraction |
  `-------------*/

  /// Substraction between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  typename vcsn::op_sub_traits<S1, S2, T1, T2>::ret_t
  operator-(const vcsn::Element<S1, T1>& e1,
	    const vcsn::Element<S2, T2>& e2);

  /// Substraction between Element and foreign values (left)
  template<typename S, typename T, typename U>
  static vcsn::Element<S, T>
  operator-(const vcsn::Element<S, T>& e,
	    const U& v);

  /// Substraction between Element and foreign values (right)
  template<typename U, typename S, typename T>
  static vcsn::Element<S, T>
  operator-(const U& v,
	    const vcsn::Element<S, T>& e);

  /*---------------.
  | Multiplication |
  `---------------*/

  /// Multiplication between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  typename vcsn::op_mul_traits<S1, S2, T1, T2>::ret_t
  operator*(const vcsn::Element<S1, T1>& e1,
	    const vcsn::Element<S2, T2>& e2);

  /// Multiplication between Element and foreign values (left)
  template<typename S, typename T, typename U>
  static vcsn::Element<S, T>
  operator*(const vcsn::Element<S, T>& e,
	    const U& v);

  /// Multiplication between Element and foreign values (right)
  template<typename U, typename S, typename T>
  static vcsn::Element<S, T>
  operator*(const U& v,
	    const vcsn::Element<S, T>& e);

  /*---------.
  | Division |
  `---------*/

  /// Division between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  typename vcsn::op_div_traits<S1, S2, T1, T2>::ret_t
  operator/(const vcsn::Element<S1, T1>& e1,
	    const vcsn::Element<S2, T2>& e2);

  /// Division between Element and foreign values (left)
  template<typename S, typename T, typename U>
  static vcsn::Element<S, T>
  operator/(const vcsn::Element<S, T>& e,
	    const U& v);

  /// Division between Element and foreign values (right)
  template<typename U, typename S, typename T>
  static vcsn::Element<S, T>
  operator/(const U& v,
	    const vcsn::Element<S, T>& e);

  /*--------.
  | Modulus |
  `--------*/

  /// Modulus between Element instances
  template<typename S1, typename T1, typename S2, typename T2>
  static
  typename vcsn::op_mod_traits<S1, S2, T1, T2>::ret_t
  operator%(const vcsn::Element<S1, T1>& e1,
	    const vcsn::Element<S2, T2>& e2);

  /// Modulus between Element and foreign values (left)
  template<typename S, typename T, typename U>
  static vcsn::Element<S, T>
  operator%(const vcsn::Element<S, T>& e,
	    const U& v);

  /// Modulus between Element and foreign values (right
  template<typename U, typename S, typename T>
  static vcsn::Element<S, T>
  operator%(const U& v,
	    const vcsn::Element<S, T>& e);

  /*---------------.
  | Unary negation |
  `---------------*/

  /// Unary negation of Element instances
  template<typename S, typename T>
  static vcsn::Element<S, T>
  operator -(const vcsn::Element<S, T>&);

  /*-----------------.
  | Input and Output |
  `-----------------*/

  /// Output to stream
  template<typename St, typename S, typename T>
  static St&
  operator <<(St& s, const vcsn::Element<S, T>& e);

  /// Input from stream
  template<typename St, typename S, typename T>
  static St&
  operator >>(St& s, const vcsn::Element<S, T>& e);

  // This operator does not exist.

//   template<typename S1, typename T1, typename S2, typename T2>
//   static void /* do not use or specialize */
//   operator <<(const vcsn::Element<S1, T1>& e1,
// 	      const vcsn::Element<S2, T2>& e2);


  /** @} */
  /** @} */

} // vcsn

namespace std {

  /** @addtogroup design_pattern *//** @{ */
  /** @addtogroup operators   *//** @{ */

  /*-----.
  | Swap |
  `-----*/

  /** Swap to Element instances with the same structure.
   * Calling this operators is valid only if the structural elements
   * of the two Element instances are equal.
   */
  template<typename S, typename T1, typename T2>
  void swap(vcsn::Element<S, T1>& e1,
	    vcsn::Element<S, T2>& e2);

  /// Swap between Element and foreign values (left)
  template<typename S, typename T>
  void swap(vcsn::Element<S, T>& e1, T& v2);

  /// Swap between Element and foreign values (right)
  template<typename T, typename S>
  void swap(T& v1, vcsn::Element<S, T>& e2);

  /** @} */
  /** @} */

} // std

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/design_pattern/element_ops.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_DESIGN_PATTERN_ELEMENT_OPS_HH
