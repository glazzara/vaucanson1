// design_pattern-test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_DESIGN_PATTERN_DESIGN_PATTERN_TEST_HH
# define VCSN_TESTS_DESIGN_PATTERN_DESIGN_PATTERN_TEST_HH

# include <vaucanson/design_pattern/element.hh>

template <class Tset, class Tvalue>
void test_design_pattern(const Tset& s)
{
  vcsn::Element<Tset, Tvalue> a (s);
  vcsn::Element<Tset, Tvalue> b (s);
  Tvalue		      sample;

  // Comparison operators.
  a == b;
  a != b;
  a < b;
  a > b;
  a <= b;
  a >= b;

  // Comparison operators with implementation.
  a == sample;
  sample == a;
  a != sample;
  sample != a;
  a < sample;
  sample < a;
  a > sample;
  sample > a;
  a <= sample;
  sample <= a;
  a >= sample;
  sample >= a;

  //FIXME: swap(a,a) is ambiguous.
}

#endif // ! VCSN_TESTS_DESIGN_PATTERN_DESIGN_PATTERN_TEST_HH
