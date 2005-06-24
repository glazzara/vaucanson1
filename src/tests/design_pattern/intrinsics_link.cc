// intrinsics_link.cc: this file is part of the Vaucanson project.
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

void test_link()
{
  TEST_GROUP("link to s. e.");

  vcsn_test::S	s0;
  vcsn_test::S	s1;
  s1.s_ = 1;
  t		e1 (s0);

  e1.attach(s1);
  TEST_ASSERT(& e1.structure(), "structural element is valid after construction from structure");
  TEST_ASSERT(e1.structure() == s1, "attach() propagates the s. e.");

  et ee1;
  vcsn_test::eS es1;
  ee1.attach(es1);
  TEST_ASSERT(ee1.structure() == es1, "attach() propagates singleton structure");


  vcsn_test::S s2;
  s2.s_ = 1;

  t e2(s2);
  TEST_ASSERT(& e2.structure(), "structural element is valid after construction from structure");
  TEST_ASSERT(e2.structure().s_ == 1, "construction from structure propagates structure");
  TEST_ASSERT(e2.structure() == e1.structure(), "propagation of equality between structures");
  TEST_ASSERT(& e2.structure() == & e1.structure(), "equality of references for equal structures");

  s2.s_ = 2;
  t e3(s2);
  TEST_ASSERT(& e3.structure(), "structural element is valid  after construction from structure");
  TEST_ASSERT(e3.structure().s_ == 2, "construction from structure propagates structure");
  TEST_ASSERT(e2.structure().s_ == 1, "enforced unicity of structures");
  TEST_ASSERT(& e3.structure() != & e2.structure(), "difference of references for different structures");

  t e4(e3);
  TEST_ASSERT(& e4.structure(), "structural element is valid after c. c.");
  TEST_ASSERT(e4.structure() == e3.structure(), "c. c. propagates structure");
  TEST_ASSERT(& e4.structure() == & e3.structure(), "c. c. propagates reference");

  et ee4(ee1);
  TEST_ASSERT(ee4.structure() == ee1.structure(), "c. c. propagates singleton structure");
  TEST_ASSERT(& ee4.structure() == & ee1.structure(),
	      "c. c. propagates reference to singleton structure");
}

int main()
{
  test_link();
}

