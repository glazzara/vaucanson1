// math.hh
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

#endif // !VCSN_CONFIG_MATH_HH
