// intrinsics_default.cc: this file is part of the Vaucanson project.
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

