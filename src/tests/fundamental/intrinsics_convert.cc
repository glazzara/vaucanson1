// intrinsics_convert.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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


namespace vcsn {
  vcsn_test::T op_convert(const vcsn_test::S& s, SELECTOR(vcsn_test::T), 
			  const int& other)
  {
    if (&s)
      tag += "set";
    tag += "convert1";
    vcsn_test::T t;
    t.t_ = other;
    return t;
  }
}

void test_convert1()
{
  TEST_GROUP("simple conversions");
  
  vcsn::Element<vcsn_test::S, int> e;
  tag = "";
  vcsn::Element<vcsn_test::S, vcsn_test::T> e2(e);
  TEST_ASSERT(tag == "convert1", "delegation to convert with no s. e.");
  e.bound(); e2.bound(); // use var

  vcsn::Element<vcsn_test::eS, float> ee;
  ee.value() = 3.14;
  tag = "";
  vcsn::Element<vcsn_test::eS, vcsn_test::eT> ee2(ee);
  TEST_ASSERT(tag.substr(0,4) == (std::string("eTc") + typeid(float).name()).substr(0,4),
	      "delegation to intrinsics convert");
  ee2.bound(); // use var

  vcsn_test::S s;
  e.attach(s);
  tag = "";
  t e3(e);
  TEST_ASSERT(tag == "setconvert1", "delegation to convert when c. c. with s. e.");
  e3.bound(); // use var

  tag = "";
  t e4(s, 123);
  TEST_ASSERT(tag == "setconvert1", "delegation to convert when explicit construction with s. e.");
  e4.bound(); // use var

  tag = "";
  vcsn_test::eS es;
  et ee4(es, 123);
  TEST_ASSERT(tag.substr(0,4) == (std::string("eTc") + typeid(int).name()).substr(0,4), 
	      "delegation to intrinsics convert when explicit construction with s. e.");
  ee4.bound(); // use var
}

namespace vcsn
{
  vcsn_test::T op_convert(SELECTOR(vcsn_test::S),
			  SELECTOR(vcsn_test::T),
			  const vcsn_test::Sna& s,
			  const int& v)
  {
    if (&s)
      tag += "set";
    tag += "convert2";
    vcsn_test::T t;
    t.t_ = v;
    return t;
  }
}

void test_convert2()
{
  TEST_GROUP("foreign conversion");

  vcsn::Element<vcsn_test::Sna, int> e;
  tag = "";
  t e2(e);
  TEST_ASSERT(tag == "convert2", 
	      "delegation to convert on foreign c. c. with no s. e.");
  e.bound(); e2.bound(); // use var

  vcsn_test::Sna s;
  e.attach(s);
  tag = "";
  t e3(e);
  TEST_ASSERT(tag == "setconvert2", 
	      "delegation to convert on foreign c. c. with s. e.");
  e3.bound(); // use var

  vcsn_test::S s1;
  tag = "";
  t e4(s1, e);
  TEST_ASSERT(tag == "setconvert2",
	      "delegation to convert on explicit foreign element c. c.");
  e4.bound(); // use var
}

namespace vcsn
{
  vcsn_test::T op_convert(const vcsn_test::S& s, SELECTOR(vcsn_test::T),
			  const vcsn_test::T& other)
  {
    if (&s)
      tag += "set";
    tag += "convert3";
    return other;
  }
}

void test_convertv()
{
  TEST_GROUP("delegation for construction from value");

  vcsn_test::T v;
  
  tag = "";
  t e(v);
  TEST_ASSERT(tag == "convert3",
	      "delegation to convert on construction from value");
  e.bound(); // use var
  
  tag = "";
  t e2(123);
  TEST_ASSERT(tag == "convert1",
	      "delegation to convert on construction from foreign value");
  e2.bound(); // use var

  vcsn_test::S s;
  tag = "";
  t e3(s, vcsn_test::T());
  TEST_ASSERT(tag == "setconvert3",
	      "delegation to convert on explicit construction from value");
  e3.bound(); // use var
}

int main()
{
  test_convert1();
  test_convert2();
  test_convertv();
}

