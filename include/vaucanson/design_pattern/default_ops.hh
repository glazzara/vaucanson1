// default_ops.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_FUNDAMENTAL_DEFAULT_OPS_HH
# define VCSN_FUNDAMENTAL_DEFAULT_OPS_HH

/** @addtogroup design_pattern *//** @{ */
/** @addtogroup operators   *//** @{ */
/**
 * @file default_ops.hh
 * @brief Default implementations for standard @c Element operations.
 */
/** @} */
/** @} */

# include <vaucanson/design_pattern/predecls.hh>
# include <vaucanson/misc/selectors.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */
  /** @addtogroup operators   *//** @{ */

  /*--------------------.
  | Structure::contains |
  `--------------------*/

  /**
   * Check whether a value is contained in a set.
   *
   * @c op_contains is an  operator appliable on every structure; this
   * is the "is in" relation.
   */
  template<typename S, typename T>
  bool op_contains(const Structure<S>& set, const T& value);

  /*---------------------.
  | Standard comparisons |
  `---------------------*/

  /// Equality between two structured values.
  template<typename S, typename T, typename U>
  bool op_eq(const Structure<S>&,
	     const T& v1,
	     const U& v2);

  /// Equality between two structured values.
  template<typename S, typename V, typename T, typename U>
  bool op_eq(const Structure<S>&,
	     const Structure<V>&,
	     const T& v1,
	     const U& v2);

  /// Ordered comparison between two structured values.
  template<typename S, typename T, typename U>
  bool op_lt(const Structure<S>&,
	     const T& v1,
	     const U& v2);

  /// Ordered comparison between two structured values.
  template<typename S, typename V, typename T, typename U>
  bool op_lt(const Structure<S>&,
	     const Structure<V>&,
	     const T& v1,
	     const U& v2);

  /*------------.
  | Conversions |
  `------------*/

  /// Default conversion between value types with computation
  template<typename S, typename R, typename T>
  R op_convert(const Structure<S> &se,
	       SELECTOR(R), const T& data);

  /// Pass-through conversion
  template<typename S, typename T>
  const T& op_convert(const Structure<S>& se,
		      SELECTOR(T), const T& from_data);

  /// Pass-through conversion between compatible structures
  template<typename S, typename T>
  const T& op_convert(const Structure<S>& se, SELECTOR(T),
		      const Structure<S>& from_se, const T& from_data);

  /*---------------------.
  | Default construction |
  `---------------------*/

  /// Default construction of values using @c Structure.
  template<typename S, typename T>
  T op_default(const Structure<S>& se, SELECTOR(T));


  /*-----.
  | Swap |
  `-----*/

  /// Default swap operator.
  template<typename S, typename T>
  void op_swap(const Structure<S>& se, T& v1, T& v2);

  /*-----------.
  | Assignment |
  `-----------*/

  /// Assignement operator between two implementations of a Structure<S>.
  template<typename S, typename T, typename U>
  void op_assign(const Structure<S>& s,
		 T& dst, const U& src);

  /**
   * @brief Assignement operator between two implementations of two
   *        differents structures.
   */
  template<typename S, typename T, typename U>
  void op_assign(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst,
		 const U& src);

  /// Addition in place operator between two different elements.
  template<typename S, typename T, typename U>
  void op_in_add(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst,
		 const U& arg);

  /// Substraction in place operator between two different elements.
  template<typename S, typename T, typename U>
  void op_in_sub(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst,
		 const U& arg);

  /// Multiplication in place operator between two different elements.
  template<typename S, typename T, typename U>
  void op_in_mul(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst,
		 const U& arg);

  /// Division in place operator between two different elements.
  template<typename S, typename T, typename U>
  void op_in_div(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst,
		 const U& arg);

  /// Modulo in place operator between two different elements.
  template<typename S, typename T, typename U>
  void op_in_mod(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst,
		 const U& arg);

  /// Addition operator between two different elements.
  template<typename S, typename T, typename U>
  T op_add(const Structure<S>& s1,
	   const Structure<S>& s2,
	   const T& v1,
	   const U& v2);

  /// Substraction operator between two different elements.
  template<typename S, typename T, typename U>
  T op_sub(const Structure<S>& s1,
	   const Structure<S>& s2,
	   const T& v1,
	   const U& v2);

  /// Multiplication operator between two different elements.
  template<typename S, typename T, typename U>
  T op_mul(const Structure<S>& s1,
	   const Structure<S>& s2,
	   const T& v1,
	   const U& v2);

  /// Division operator between two different elements.
  template<typename S, typename T, typename U>
  T op_div(const Structure<S>& s1,
	   const Structure<S>& s2,
	   const T& v1,
	   const U& v2);

  /// Modulo operator between two different elements.
  template<typename S, typename T, typename U>
  T op_mod(const Structure<S>& s1,
	   const Structure<S>& s2,
	   const T& v1,
	   const U& v2);

  /// Input stream operator.
  template<typename S, typename St, typename T>
  St& op_rin(const Structure<S>& s, St& st, const T& v);

  /// Output stream operator.
  template<typename S, typename St, typename T>
  St& op_rout(const Structure<S>& s, St& st, const T& v);

  /** @} */
  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/design_pattern/default_ops.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_FUNDAMENTAL_DEFAULT_OPS_HH
