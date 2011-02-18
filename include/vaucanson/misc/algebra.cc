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

unsigned int
gcd (unsigned int a, unsigned int b)
{
  if (a)
    {
      int r;
      while (true)
	{
	  r = a % b;
	  if (! (r))
	    return b;
	  a = b;
	  b = r;
	}
    }
  return b;
}

unsigned int
lcm (unsigned int a, unsigned int b)
{
  unsigned int res = gcd (a, b);
  if (res)
    return a * b / res;
  return a * b;
}

bool
is_coprime (unsigned int a, unsigned int b)
{
  return 1 == gcd (a, b);
}

