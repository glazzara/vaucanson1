// semiring_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SEMIRING_SEMIRING_TEST_HH
# define VCSN_TESTS_ALGEBRA_SEMIRING_SEMIRING_TEST_HH

# include <check/tester.hh>
# include <vaucanson/algebra/concept/semiring_base.hh>
// from test battery:
# include <fundamental/design_pattern-test.hh>

template <class S, class T>
bool semiring_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T> element_t;
  element_t e1;
  element_t z = e1.set().zero(SELECT(T));
  element_t o = e1.set().identity(SELECT(T));
  element_t e2;
  element_t e3(o);

  test_design_pattern<S, T>();

  TEST(t, "Commutativity of plus.", (e1 + e2) == (e2 + e1));
  TEST(t, "Distributivity of mult with plus.", 
       (e1 + e2) * e3 == e2 * e3 + e1 * e3);
  TEST(t, "0 is a zero for mult.", 
       (e1 * z == z));
  TEST(t, "stareable works. (1)", z.stareable() ? true  : false);
  // FIXME: add some other tests.
  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_SEMIRING_SEMIRING_TEST_HH
