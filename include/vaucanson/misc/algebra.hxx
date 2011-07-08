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


    inline
    unsigned long long
    gcd (unsigned long long a, unsigned long long b)
    {
      if (0 == a)
	return b;
      unsigned long long r;
      while (0 != b)
	{
	  r = a % b;
	  a = b;
	  b = r;
	}
      return a;
    }

    inline
    unsigned long
    lcm (unsigned long long a, unsigned long b)
    {
      unsigned long long res = gcd (a, b);
      if (res)
	return a * b / res;
      return a * b;
    }

    inline
    bool
    is_coprime (unsigned long long a, unsigned long long b)
    {
      return 1 == gcd (a, b);
    }

    inline
    unsigned long long abs (long long a)
    {
      return a > 0 ? a : -a;
    }
  } // !misc

} // !vcsn
#endif // !INCLUDE_VAUCANSON_MISC_ALGEBRA_HXX
