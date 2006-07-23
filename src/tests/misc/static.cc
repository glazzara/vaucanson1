// static.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2006 The Vaucanson Group.
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
#include <vaucanson/config/system.hh>
#include <vaucanson/misc/static.hh>
#include <cassert>

using namespace vcsn::misc;

void xassert(bool b)
{
  assert(b == true);
}

struct v {};

int main()
{
  int a = -1;
  const int b = -2;
  remove_reference<int>::t x = 0;
  remove_reference<int&>::t y = 1;
  xassert(remove_reference<const int&>::t(2) == 2);

  xassert(static_if<false, int, int>::choose(x, y) == y);
  xassert(static_if<true, int, int>::choose(x, y) == x);
  xassert(static_if<false, int, int>::choose(a, b) == b);
  xassert(static_if<false, int, int>::choose(a, x) == x);

  xassert(static_if<true, int, v>::t(3) == 3);
  xassert(static_if<false, v, int>::t(4) == 4);

  xassert(static_eq<int, int>::value);
  xassert(! static_eq<int, v>::value);

  xassert(static_pow<0, 10>::value == 0);
  xassert(static_pow<1, 10>::value == 1);
  xassert(static_pow<2, 16>::value == 1 << 16);
  xassert(static_pow<3, 3>::value == 27);

  xassert(static_pow_minus_one<1, 10>::value == 0);
  xassert(static_pow_minus_one<2, 16>::value == (1 << 16) - 1);
  xassert(static_pow_minus_one<3, 3>::value == 26);

  return 0;
}

