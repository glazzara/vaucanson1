// random.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2005, 2006 The Vaucanson Group.
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
#include <tests/check/tester.hh>
#include <vaucanson/misc/random.hh>
#include <cassert>
#include <climits>
#include <iostream>

#define MAXITER 1000

int main()
{
  using vcsn::misc::random::generate;

#define TEST_TYPE(Type, MAX)				\
  for (int i = 0; i < MAXITER; ++i)			\
  {							\
    Type c = generate< Type >();			\
    Type min = generate< Type >(0, MAX);		\
    Type max = generate< Type >(min, MAX);		\
    c = generate< Type >(min, max);			\
    if (!(min <= c && max >= c))			\
    {							\
      TEST_FAIL_SAVE("random", i,			\
		     "random failed: min = " << min	\
		     << ", max = " << max		\
		     << ", val = " << c << std::endl);	\
      exit(1);						\
    }							\
  }
  TEST_TYPE(char, CHAR_MAX);
  TEST_TYPE(int, INT_MAX);
  for (int i = 0; i < MAXITER; ++i)
  {
    bool b = generate<bool>();
    assert(b || !b);
  }
  for (int i = 0; i < MAXITER; ++i)
  {
    float f = generate<float>();
    assert(f >= -2. && f <= 2.);
  }
}

