// intrinsics_default.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004,2005 The Vaucanson Group.
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

void test_sizes()
{
  TEST_GROUP("sizes of Element instances w.r.t. S.E. and value type");

  vcsn_test::S S;
  vcsn::Element<vcsn_test::S, vcsn_test::T> e(S);
  TEST_MSG("sizeof(S) == " << sizeof(vcsn_test::S));
  TEST_MSG("sizeof(Sna) == " << sizeof(vcsn_test::Sna));
  TEST_MSG("sizeof(T) == " << sizeof(vcsn_test::T));
  TEST_MSG("sizeof(Element<S,T>) == " << sizeof(e));


  vcsn_test::Sna Sna;
  vcsn::Element<vcsn_test::Sna, vcsn_test::T> e2(Sna);
  TEST_MSG("sizeof(Element<Sna,T>) == " << sizeof(vcsn::Element<vcsn_test::Sna, vcsn_test::T>));
  static const size_t size_of_element = sizeof(e2);
  static const size_t size_of_value = sizeof(vcsn_test::T);
  TEST_ASSERT(size_of_element == size_of_value,
	      "empty base-class eliminisation");

}


int main()
{
  test_sizes();
}
