// intrinsics_orphanage.cc: this file is part of the Vaucanson project.
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

void test_orphanage()
{
  TEST_GROUP("construction with no s. e.");

  // default instanciation
  vcsn::Element<vcsn_test::eS, vcsn_test::T> e;
  TEST_ASSERT(!& e.structure(), "orphan has no s. e.");

  // default instanciation constructor check
  tag = "";
  et ee;
  TEST_ASSERT(tag.substr(0, 2) == "eT", "orphan value from default constructor");
  TEST_ASSERT(!& ee.structure(), "orphan singleton structure has no reference");

  // value retrieval
  vcsn_test::T & t1 = e.value();
  TEST_ASSERT(e.value().t_ == 0, "orphan value retrievable");
  t1.t_ = 42;
  TEST_ASSERT(e.value().t_ == 42, "orphan value() returns correct reference");

  TEST_GROUP("copy-construction of orphan to const");
  const vcsn::Element<vcsn_test::eS, vcsn_test::T> e2(e);
  TEST_ASSERT(!& e2.structure(), "const copy has no s. e.");

  // copy to const
  tag = "";
  const et ee2(ee);
  TEST_ASSERT(tag == "eTc", "orphan value from copy constructor");
  TEST_ASSERT(!& ee2.structure(), "orphan singleton structure has no reference");

  // const value retrieval
  const vcsn_test::T & t2 = e2.value();
  TEST_ASSERT(t2.t_ == 42, "const copy value() returns correct reference");

}

int main()
{
  test_orphanage();
}

