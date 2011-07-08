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
  inline
  unsigned long long gcd (unsigned long long a, unsigned long long b);

  /// Least common multiple.
  inline
  unsigned long long lcm (unsigned long long a, unsigned long long b);

  /// Coprime between to int.
  inline
  bool is_coprime (unsigned long long a, unsigned long long b);

  inline
  unsigned long long abs (long long a);

  ///   @}
  ///  @}
} // !misc
  /// @}
} // !vcsn
# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/algebra.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !INCLUDE_VAUCANSON_MISC_ALGEBRA_HH
