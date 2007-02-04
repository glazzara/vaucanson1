// intrinsics_convert.cc: this file is part of the Vaucanson project.
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


namespace vcsn {
  template <class S>
  vcsn_test::T
  op_convert(const S& s,
	     SELECTOR(vcsn_test::T),
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

  vcsn::Element<vcsn_test::eS, int> e;
  tag = "";
  vcsn::Element<vcsn_test::eS, vcsn_test::T> e2(e);
  TEST_ASSERT(tag == "convert1", "delegation to convert with no s. e.");
  e = e; e2 = e2; // use var

  vcsn::Element<vcsn_test::eS, float> ee;
  ee.value() = 3.14;
  tag = "";
  vcsn::Element<vcsn_test::eS, vcsn_test::eT> ee2(ee);
  TEST_ASSERT(tag.substr(0,4) == (std::string("eTc") + typeid(float).name()).substr(0,4),
	      "delegation to intrinsics convert");
  ee2 = ee2; // use var

  vcsn_test::S	s;
  vcsn::Element<vcsn_test::S, int> u (s);
  tag = "";
  t e3(u);
  TEST_ASSERT(tag == "setconvert1", "delegation to convert when c. c. with s. e.");
  e3 = e3; u = u; // use var

  tag = "";
  t e4(s, 123);
  TEST_ASSERT(tag == "setconvert1", "delegation to convert when explicit construction with s. e.");
  e4 = e4; // use var

  tag = "";
  vcsn_test::eS es;
  et ee4(es, 123);
  TEST_ASSERT(tag.substr(0,4) == (std::string("eTc") + typeid(int).name()).substr(0,4),
	      "delegation to intrinsics convert when explicit construction with s. e.");
  ee4 = ee4; // use var
}

namespace vcsn
{
  template <class S>
  vcsn_test::T op_convert(const S& s1,
			  SELECTOR(vcsn_test::T),
			  const vcsn_test::Sna&,
			  const int& v)
  {
    if (&s1)
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
  vcsn::Element<vcsn_test::eS, vcsn_test::T> e2(e);
  TEST_ASSERT(tag == "convert2",
	      "delegation to convert on foreign c. c. with no s. e.");
  e = e; e2 = e2; // use var

  vcsn_test::S s1;
  tag = "";
  t e4(s1, e);
  TEST_ASSERT(tag == "setconvert2",
	      "delegation to convert on explicit foreign element c. c.");
  e4 = e4; // use var
}

namespace vcsn
{
  template <class S>
  vcsn_test::T
  op_convert(const S& s,
	     SELECTOR(vcsn_test::T),
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
  vcsn::Element<vcsn_test::eS, vcsn_test::T> e(v);
  TEST_ASSERT(tag == "convert3",
	      "delegation to convert on construction from value");
  e = e; // use var

  tag = "";
  vcsn::Element<vcsn_test::eS, vcsn_test::T> e2(123);
  TEST_ASSERT(tag == "convert1",
	      "delegation to convert on construction from foreign value");
  e2 = e2; // use var

  vcsn_test::S s;
  tag = "";
  t e3(s, vcsn_test::T());
  TEST_ASSERT(tag == "setconvert3",
	      "delegation to convert on explicit construction from value");
  e3 = e3; // use var
}

int main()
{
  test_convert1();
  test_convert2();
  test_convertv();
}

