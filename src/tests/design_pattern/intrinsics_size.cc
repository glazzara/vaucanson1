// intrinsics_size.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#include "intrinsics.hh"

void test_sizes()
{
  TEST_GROUP("sizes of Element instances w.r.t. S.E. and value type");

  vcsn_test::S S;
  vcsn::Element<vcsn_test::S, vcsn_test::T> e(S);
  TEST_MSG("sizeof(S) == " << sizeof(vcsn_test::S));
  TEST_MSG("sizeof(Sna) == " << sizeof(vcsn_test::Sna));
  TEST_MSG("sizeof(T) == " << sizeof(vcsn_test::T));
  TEST_MSG("sizeof(Element<S,T>) == " << sizeof(e));


  vcsn_test::Sna Sna;
  vcsn::Element<vcsn_test::Sna, vcsn_test::T> e2(Sna);
  TEST_MSG("sizeof(Element<Sna,T>) == " << sizeof(vcsn::Element<vcsn_test::Sna, vcsn_test::T>));
  static const size_t size_of_element = sizeof(e2);
  static const size_t size_of_value = sizeof(vcsn_test::T);
  TEST_ASSERT(size_of_element == size_of_value,
	      "empty base-class eliminisation");

}


int main()
{
  test_sizes();
}

