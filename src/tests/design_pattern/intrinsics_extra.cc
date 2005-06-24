// intrinsics_extra.cc: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include "intrinsics.hh"


void test_extra()
{
  TEST_GROUP("additional services via MetaElement");

  vcsn::Element<vcsn_test::eS, vcsn_test::T> e1;

  tag = ""; e1.foo();
  TEST_ASSERT(tag == "foo", "call delegation operator without s. e.");

  vcsn_test::S	s;
  t		e2 (s);
  tag = ""; e2.foo();
  TEST_ASSERT(tag == "setfoo", "call delegation with s. e.");
}

int main()
{
  test_extra();
}

