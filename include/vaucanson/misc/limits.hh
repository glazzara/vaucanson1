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

#ifndef VCSN_CONFIG_LIMITS_HH
# define VCSN_CONFIG_LIMITS_HH

/** @addtogroup utility *//** @{ */
/**
 * @file limits.hh
 * @brief Wrapper about the numeric limits for Vaucanson
 *
 * This file defines the utility trait @c vcsn::limits, by using
 * standard C++ @c std::numeric_limits if available, or the
 * standard C limits if @c USE_C_LIMITS is defined.
 */
/** @} */

# include <vaucanson/config/math.hh>

# ifdef USE_C_LIMITS
#  include <climits>
# else
#  include <limits>
# endif

namespace utility
{
  template<typename T>
  struct limits 
# ifndef USE_C_LIMITS
    : std::numeric_limits<T>
  { };
# else
  {
    static const bool is_specialized = false;
  };

  template<>
  struct limits<bool>
  { 
    static const int digits = sizeof(bool)*8;
    static const int digits10 = 1;
    static const bool is_specialized = true;
    static bool min() throw() { return false; }
    static bool max() throw() { return false; }   
    static const bool has_infinity = false;
    static bool infinity() throw() { return false; }
    static const bool has_quiet_NaN = false;
    static bool quiet_NaN() throw() 
    { return static_cast<bool>(0); }
    static const bool is_signed = false;
    static const bool is_integer = true;
    static const bool is_exact = true;
    static const int radix = 2;
    static const bool is_iec559 = true;
    static const bool is_bounded = true;
    static const bool is_modulo = true;
  };

  template<>
  struct limits<signed char>
  {
    static const int digits = sizeof(signed char)*8 - 1;
    static const int digits10 = 3;
    static const bool is_specialized = true;
    static char min() throw()   { return SCHAR_MIN; }
    static char max() throw() { return SCHAR_MAX; }
    static const bool is_signed = true;
    static const bool is_integer = true;
    static const bool is_exact = true;
    static const int radix = 2;
    static const bool has_infinity = false;
    static signed char infinity() throw() 
    { return static_cast<signed char>(0); }
    static const bool has_quiet_NaN = false;
    static signed char quiet_NaN() throw() 
    { return static_cast<signed char>(0); }
    static const bool is_iec559 = false;
    static const bool is_bounded = true;
    static const bool is_modulo = false;
  };

  template<>
  struct limits<unsigned char>
  {
    static const int digits = sizeof(unsigned char)*8;
    static const int digits10 = 3;
    static const bool is_specialized = true;
    static char min() throw()   { return 0; }
    static char max() throw() { return UCHAR_MAX; }
    static const bool is_signed = false;
    static const bool is_integer = true;
    static const bool is_exact = true;
    static const int radix = 2;
    static const bool has_infinity = false;
    static unsigned char infinity() throw() 
    { return static_cast<unsigned char>(0); }
    static const bool has_quiet_NaN = false;
    static unsigned char quiet_NaN() throw() 
    { return static_cast<unsigned char>(0); }
    static const bool is_iec559 = false;
    static const bool is_bounded = true;
    static const bool is_modulo = true;
  };
  
  template<>
  struct limits<int>
  {
    static const int digits = sizeof(int)*8 - 1;
    static const int digits10 = 19;
    static const bool is_specialized = true;
    static int min() throw()   { return INT_MIN; }
    static int max() throw() { return INT_MAX; }
    static const bool is_signed = true;
    static const bool is_integer = true;
    static const bool is_exact = true;
    static const int radix = 2;
    static const bool has_infinity = false;
    static int infinity() throw() 
    { return static_cast<int>(0); }
    static const bool has_quiet_NaN = false;
    static int quiet_NaN() throw() 
    { return static_cast<int>(0); }
    static const bool is_iec559 = true;
    static const bool is_bounded = true;
    static const bool is_modulo = false;
  };

  template<>
  struct limits<unsigned int>
  {
    static const int digits = sizeof(unsigned int)*8;
    static const int digits10 = 19;
    static const bool is_specialized = true;
    static unsigned int min() throw()   { return 0; }
    static unsigned int max() throw() { return UINT_MAX; }
    static const bool is_signed = false;
    static const bool is_integer = true;
    static const bool is_exact = true;
    static const int radix = 2;
    static const bool has_infinity = false;
    static unsigned int infinity() throw() 
    { return static_cast<unsigned int>(0); }
    static const bool has_quiet_NaN = false;
    static unsigned int quiet_NaN() throw() 
    { return static_cast<unsigned int>(0); }
    static const bool is_iec559 = true;
    static const bool is_bounded = true;
    static const bool is_modulo = true;
  };

  template<>
  struct limits<float>
  {
    static const int digits = sizeof(float)*8;
    static const int digits10 = 33;
    static const bool is_specialized = true;
    static float min() throw()   { return -HUGE_VAL; }
    static float max() throw() { return HUGE_VAL; }
    static const bool is_signed = true;
    static const bool is_integer = false;
    static const bool is_exact = false;
    static const int radix = 2;
    static const bool has_infinity = true;
    static float infinity() throw() 
    { return HUGE_VAL; }
    static const bool has_quiet_NaN = true;
    static float quiet_NaN() throw()
    { return NAN; }
    static const bool is_iec559 = false;
    static const bool is_bounded = false;
    static const bool is_modulo = false;
  };

# endif

}


#endif

