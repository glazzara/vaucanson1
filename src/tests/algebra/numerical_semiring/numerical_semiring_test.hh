// numerical_semiring_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_TESTS_ALGEBRA_NUMERICAL_SEMIRING_NUMERICAL_SEMIRING_TEST_HH
# define VCSN_TESTS_ALGEBRA_NUMERICAL_SEMIRING_NUMERICAL_SEMIRING_TEST_HH

# include <check/tester.hh>
# include <vaucanson/algebra/concept/semiring_base.hh>

template <class S, class T>
bool numerical_semiring_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef S numerical_semiring_t;
  typedef Element<S, T> element_t;

  numerical_semiring_t semiring;
  int timeout = 0;
  element_t nb = semiring.choose_starable(SELECT(T));
  do
    {
      TEST(t, "starable works. (2)", -T(1) < nb.value() and nb.value() < T(1));
      ++timeout;
      nb = semiring.choose_starable(SELECT(T));
    }
  while (timeout < 100);
  nb = semiring.choose_non_starable(SELECT(T));
  timeout = 0;
  do
    {
      TEST(t, "starable works. (3)", -T(1) > nb.value() or nb.value() > T(1));
      ++timeout;
      nb = semiring.choose_non_starable(SELECT(T));
    }
  while (timeout < 100);

  // FIXME: add some other tests.
  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_NUMERICAL_SEMIRING_NUMERICAL_SEMIRING_TEST_HH
