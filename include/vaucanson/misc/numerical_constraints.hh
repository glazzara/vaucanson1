// numerical_constraints.hh
//
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

#ifndef UTILITY_NUMERICAL_CONSTRAINTS_HH
# define UTILITY_NUMERICAL_CONSTRAINTS_HH

# include <vaucanson/config/system.hh>
# ifdef USE_CXX_LIMITS
#  include <limits>
# else
#  include <vaucanson/misc/limits.hh>
# endif // USE_CXX_LIMITS
# include <vaucanson/misc/misc_constraints.hh>

namespace utility {

  namespace concepts {

    /*----------------------.
    | number types concepts |
    `----------------------*/

    template <typename T>
    struct HasLimits
    {
      void constraints() 
      {
	function_requires<SameValue<bool, 
	  std::numeric_limits<T>::is_specialized,
	  true > >();
      }
    };

    template <typename T>
    struct IntegerType
    {
      void constraints()
      {
	function_requires<HasLimits<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::is_integer, true> >();
      }
    };

    template <typename T>
    struct UnsignedType
    {
      void constraints()
      {
	function_requires<IntegerType<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::is_signed, false> >();
      }
    };
	

    template <typename T>
    struct HasInfinity
    {
      void constraints() 
      {
	function_requires<HasLimits<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::has_infinity,
	  true > >();
      }
    };

    template <typename T>
    struct BoundedType
    {
      void constraints() 
      {
	function_requires<HasLimits<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::is_bounded,
	  true > >();
      }
    };

    template <typename T>
    struct IsSigned
    {
      void constraints() 
      {
	function_requires<HasLimits<T> >();
	function_requires<SameValue<bool,
	  std::numeric_limits<T>::is_signed,
	  true > >();
      }
    };

  } // concepts

} // utility

#endif // UTILITY_NUMERICAL_CONSTRAINTS_HH
