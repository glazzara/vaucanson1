// intrinsics_default.cc
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
  
namespace vcsn {
  vcsn_test::T op_default(const vcsn_test::S& s, SELECTOR(vcsn_test::T))
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
  t e;
  TEST_ASSERT(tag == "default", "delegation to default without s. e.");
  e.bound(); // use var

  vcsn_test::S s;
  tag = "";
  t e2(s);
  TEST_ASSERT(tag == "setdefault", "delegation to default with s. e.");
  e2.bound(); // use var
}


int main()
{
  test_default();
}
