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

namespace algebra
{
  /** @addgroup algebra */
  /// @{
  /// @name Prime Number Operator
  // @{
  /// @todo FIXME: We might prefer to define gcd and lcm somewhere else.
  /// Greatest common divisor.
  unsigned int gcd (unsigned int a, unsigned int b);

  /// Least common multiple.
  unsigned int lpcm (unsigned int a, unsigned int b);

  /// Coprime between to int.
  inline bool is_coprime (unsigned int a, unsigned int b);

  /// @}
  /// @}
}

#endif // !INCLUDE_VAUCANSON_MISC_ALGEBRA_HH

