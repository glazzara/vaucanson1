// intrinsics_orphanage.cc
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include "intrinsics.hh"

void test_orphanage()
{
  TEST_GROUP("construction with no s. e.");

  // default instanciation
  t e;
  TEST_ASSERT(!e.bound(), "orphan not bound");
  TEST_ASSERT(!& e.set(), "orphan has no s. e.");

  // default instanciation constructor check
  tag = "";
  et ee;
  TEST_ASSERT(tag.substr(0, 2) == "eT", "orphan value from default constructor");
  TEST_ASSERT(ee.bound(), "orphan singleton structure already bound");
  TEST_ASSERT(!& ee.set(), "orphan singleton structure has no reference");

  // value retrieval
  vcsn_test::T & t1 = e.value();
  TEST_ASSERT(e.value().t_ == 0, "orphan value retrievable");
  t1.t_ = 42;
  TEST_ASSERT(e.value().t_ == 42, "orphan value() returns correct reference");

  TEST_GROUP("copy-construction of orphan to const");
  const t e2(e);
  TEST_ASSERT(!e2.bound(), "const copy not bound");
  TEST_ASSERT(!& e2.set(), "const copy has no s. e.");

  // copy to const
  tag = "";
  const et ee2(ee);
  TEST_ASSERT(tag == "eTc", "orphan value from copy constructor");
  TEST_ASSERT(ee2.bound(), "orphan singleton structure already set");
  TEST_ASSERT(!& ee2.set(), "orphan singleton structure has no reference");

  // const value retrieval
  const vcsn_test::T & t2 = e2.value();
  TEST_ASSERT(t2.t_ == 42, "const copy value() returns correct reference");

}

int main()
{
  test_orphanage();
}
