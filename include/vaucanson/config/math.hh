// math.hh: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_CONFIG_MATH_HH
# define VCSN_CONFIG_MATH_HH

/** @addtogroup conf *//** @{ */
/**
 * @file math.hh
 * @brief Wrapper about the math library for Vaucanson
 *
 * This file includes the standard @c cmath header and attempts
 * to fix the standard math library by adding the following
 * functions if needed:
 * <ul>
 * <li> @c sqrtf if @c NEED_SQRTF is defined
 * <li> @c floorf if @c NEED_FLOORF is defined
 * <li> @c round if @c NEED_ROUND is defined
 * <li> @c roundf if @c NEED_ROUNDF is defined
 * </ul>
 *
 * Additionnally, it defines @c USE_CXX_LIMITS if the macro @c
 * USE_C_LIMITS is not defined and the standard header @c limits
 * was detected available (@c HAVE_LIMITS is defined).
 */
/** @} */

# include <vaucanson/config/system.hh>

# include <cmath>

# ifndef USE_C_LIMITS
#  ifdef HAVE_LIMITS
#   define USE_CXX_LIMITS
#  endif
# endif

# ifdef NEED_SQRTF
static inline float sqrtf(float f)
{
  return (float)sqrt((double)f);
}
# endif

# ifdef NEED_FLOORF
static inline float floorf(float f)
{
  return (float)floor((double)f);
}
# endif

# ifdef NEED_ROUND
static inline double round(double f)
{
  return (f < 0.) ? -floor(-f + 0.5) : floor(f + 0.5);
}
# endif
# ifdef NEED_ROUNDF
static inline float roundf(float f)
{
  return (f < 0.f) ? -floorf(-f + 0.5f) : floorf(f + 0.5f);
}
# endif

#endif // ! VCSN_CONFIG_MATH_HH
