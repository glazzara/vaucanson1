// intrinsics_binops.cc: this file is part of the Vaucanson project.
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

void test_link()
{
  TEST_GROUP("link to s. e.");

  t e1;
  vcsn_test::S s1;
  s1.s_ = 1;

  e1.attach(s1);
  TEST_ASSERT(e1.bound(), "bound() after attach()");
  TEST_ASSERT(e1.set() == s1, "attach() propagates the s. e.");
  
  et ee1;
  vcsn_test::eS es1;
  ee1.attach(es1);
  TEST_ASSERT(ee1.bound(), "bound() after attach() of singleton structure");
  TEST_ASSERT(ee1.set() == es1, "attach() propagates singleton structure");


  vcsn_test::S s2;
  s2.s_ = 1;

  t e2(s2);
  TEST_ASSERT(e2.bound(), "bound() after construction from structure");
  TEST_ASSERT(e2.set().s_ == 1, "construction from structure propagates structure");
  TEST_ASSERT(e2.set() == e1.set(), "propagation of equality between structures");
  TEST_ASSERT(& e2.set() == & e1.set(), "equality of references for equal structures");

  s2.s_ = 2;
  t e3(s2);
  TEST_ASSERT(e3.bound(), "bound() after construction from structure");
  TEST_ASSERT(e3.set().s_ == 2, "construction from structure propagates structure");
  TEST_ASSERT(e2.set().s_ == 1, "enforced unicity of structures");
  TEST_ASSERT(& e3.set() != & e2.set(), "difference of references for different structures");

  t e4(e3);
  TEST_ASSERT(e4.bound(), "bound() after c. c.");
  TEST_ASSERT(e4.set() == e3.set(), "c. c. propagates structure");
  TEST_ASSERT(& e4.set() == & e3.set(), "c. c. propagates reference");

  et ee4(ee1);
  TEST_ASSERT(ee4.bound(), "bound() after c. c. with singleton structure");
  TEST_ASSERT(ee4.set() == ee1.set(), "c. c. propagates singleton structure");
  TEST_ASSERT(& ee4.set() == & ee1.set(), 
	      "c. c. propagates reference to singleton structure");
}  

int main()
{
  test_link();
}

