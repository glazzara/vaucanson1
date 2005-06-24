// intrinsics_default.cc: this file is part of the Vaucanson project.
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

namespace vcsn {
  template <class S>
  vcsn_test::T
  op_default(const S& s, SELECTOR(vcsn_test::T))
  {
    if (&s)
      tag += "set";
    tag += "default";
    return vcsn_test::T();
  }
}

void test_default()
{
  TEST_GROUP("delegation for default construction");

  tag = "";
  vcsn::Element<vcsn_test::eS, vcsn_test::T> e;
  TEST_ASSERT(tag == "default", "delegation to default without s. e.");
  e = e; // use var

  vcsn_test::S s;
  tag = "";
  t e2(s);
  TEST_ASSERT(tag == "setdefault", "delegation to default with s. e.");
  e = e; // use var
}


int main()
{
  test_default();
}

