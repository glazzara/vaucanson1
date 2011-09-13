// algebra.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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
#ifndef INCLUDE_VAUCANSON_MISC_ALGEBRA_HH
# define INCLUDE_VAUCANSON_MISC_ALGEBRA_HH

/** @addtogroup algebra */
/// @{
/**
 * @file algebra.hh
 *
 * Algebra Formula.
 *
 * @author David Moreira <david.moreiraa@epita.fr>
 *
 */
/// @}
namespace vcsn {
  namespace misc {
  /** @addgroup vcsn */
  /// @{
  /** @addgroup algebra */
  ///  @{
  /// @name Prime Number Operator
  ///   @{
  /// Greatest common divisor.
  /// Beware that gcd is not symmetric: the sign of the result is the sign of b
  template<typename T>
  inline
  T gcd (T a, T b);

  /// Least common multiple.
  template<typename T>
  inline
  T lcm (T a, T b);

  /// Coprime between to int.
  template<typename T>
  inline
  bool is_coprime (T a, T b);

  template<typename T>
  inline
  T abs (T a);

  ///   @}
  ///  @}
} // !misc
  /// @}
} // !vcsn
# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/algebra.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !INCLUDE_VAUCANSON_MISC_ALGEBRA_HH
