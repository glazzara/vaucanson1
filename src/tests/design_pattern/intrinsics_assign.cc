// intrinsics_assign.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#include "intrinsics.hh"

namespace vcsn
{
  template <class S>
  void op_assign(const S& s1,
		 vcsn_test::T& dst,
		 const vcsn_test::T& org)
  {
    if (&s1)
      tag += "set";
    tag += "assign1";
    dst = org;
  }
}

void test_assign()
{
  TEST_GROUP("assignment");

  vcsn::Element<vcsn_test::eS, vcsn_test::T> e;
  vcsn::Element<vcsn_test::eS, vcsn_test::T> e2;
  e.value().t_ = 42;
  e2.value().t_ = 0;
  tag = "";
  e2 = e;
  TEST_ASSERT(tag == "assign1",
	      "delegation of assignment of orphan uses no structural element");
  TEST_ASSERT(!& e2.set(), "assignment preserves orphanness");
  TEST_ASSERT(e2.value().t_ == 42, "assignment of orphan propagates value");

  et ee;
  et ee2;
  tag = "";
  ee2 = ee;
  TEST_ASSERT(tag == "eTa", "delegation to intrinsics assign");
  ee = ee; ee2 = ee2; // use var

  vcsn_test::S s;
  t e3 (s);
  t e4 (s);
  e3.value().t_ = 51;
  tag = "";
  e4 = e3;
  TEST_ASSERT(tag == "setassign1",
	      "delegation of assignment with s.e. passes s.e. correctly");
  TEST_ASSERT(& e3.set() == & e4.set(),
	      "assignment propagates s.e.");
  TEST_ASSERT(e4.value().t_ == 51, "assignment with s.e. propagates value");
}

namespace vcsn
{

  template <class S1, class S2>
  void op_assign(const S1& s1,
		 const S2& s2,
		 vcsn_test::T& dst,
		 const int& org)
  {
    if (&s1)
      tag += "set1";
    if (&s2)
      tag += "set2";
    tag += "assign2";
    dst = org;
  }

  template <class S>
  void op_assign(const S& s,
		 vcsn_test::T& dst,
		 const int& org)
  {
    if (&s)
      tag += "set";
    tag += "assign3";
    dst = org;
  }

}


void test_foreign_assign()
{
  TEST_GROUP("foreign assignment");
  vcsn::Element<vcsn_test::eS, vcsn_test::T>	e;
  vcsn::Element<vcsn_test::Sna, int>		e2;
  tag = "";
  e = e2;
  TEST_ASSERT(tag == "assign2",
	      "delegation of foreign assignment to orphan uses no s.e.");
  TEST_ASSERT(!& e.set(), "assignment preserves orphanness");

  tag = "";
  e = 42;
  TEST_ASSERT(tag == "assign3",
	      "delegation of foreign value assignment to orphan uses no s.e.");
  TEST_ASSERT(!& e.set(), "assignment of foreign value preserves orphanness");

  vcsn_test::S	s;
  t		e3 (s);
  tag = "";
  e3 = 51;
  TEST_ASSERT(tag == "setassign3",
	      "delegation of foreign value assignment with s.e. passes s.e.");
  TEST_ASSERT(e3.set() == s,
	      "assignment of foreign value keeps s.e.");

  et ee;
  tag = "";
  ee = 42;
  TEST_ASSERT(tag == std::string("eTa") + typeid(int).name(),
	      "delegation to intrinsics foreign assignment");

}

int main()
{
  test_assign();
  test_foreign_assign();
}

