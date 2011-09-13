// q_number.hh: this file is part of the Vaucanson project.
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

#ifndef INCLUDE_VAUCANSON_MISC_ALGEBRA_HXX
# define INCLUDE_VAUCANSON_MISC_ALGEBRA_HXX

# include <vaucanson/misc/algebra.hh>

namespace vcsn {

  namespace misc {


    template<typename T>
    inline
    T
    gcd (T a, T b)
    {
      if (0 == a)
		return b;
    	T s=1;
    	if(b < 0){
    		s=-1;
    		b=-b;
    	}
    	if(a<0)
    	  a=-a;
      T r;
      while (0 != b)
	{
	  r = a % b;
	  a = b;
	  b = r;
	}
      return a*s;
    }

    template<typename T>
    inline
	T
    lcm (T a, T b)
    {
      T res = gcd (a, b);
      if (res)
	    return a /res * b;
      return T(0);
    }

    template<typename T>
    inline
    bool
    is_coprime (T a, T b)
    {
      T g=gcd (a, b);
      return 1 == g || -1 == g;
    }

    template<typename T>
    inline
    T abs (T a)
    {
      return a > 0 ? a : -a;
    }
  } // !misc

} // !vcsn
#endif // !INCLUDE_VAUCANSON_MISC_ALGEBRA_HXX
