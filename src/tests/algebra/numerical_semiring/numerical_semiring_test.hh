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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
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
# include <stdexcept>

template <class S, class T>
bool numerical_semiring_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef S numerical_semiring_t;
  typedef Element<S, T> element_t;

  numerical_semiring_t semiring;
  int timeout = 0;
  bool result_test = true;
  element_t nb = semiring.choose_starable(SELECT(T));
  T average_value(0);

  try
    {
      do
	{
	  result_test = result_test &&
	    (-T(1) < nb.value() and nb.value() < T(1));
	  ++timeout;
	  nb = semiring.choose_starable(SELECT(T));
	  average_value += nb.value();
	}
      while (timeout < 2000);
      average_value = average_value < T(0) ? -average_value : average_value;
      TEST(t,
	   "starable distribution is correct",
	   (average_value / T(2000)) <= (T(1) / T(10)) 
	   );

    }
  catch(std::overflow_error&)
    {
      std::cerr << "Integer overflow in rational calculus."
		<< std::endl;
    }
  TEST(t, "starable works. (2)", result_test);  
  nb = semiring.choose_non_starable(SELECT(T));
  timeout = 0;
  result_test = true;
  do
    {
      result_test = result_test and
	(-T(1) >= nb.value() or nb.value() >= T(1));
      ++timeout;
      nb = semiring.choose_non_starable(SELECT(T));
    }
  while (timeout < 1000);
  TEST(t, "starable works. (3)", result_test);
  // FIXME: add some other tests.
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_NUMERICAL_SEMIRING_NUMERICAL_SEMIRING_TEST_HH
