// numerical_semiring_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_NUMERICAL_SEMIRING_NUMERICAL_SEMIRING_TEST_HH
# define VCSN_TESTS_ALGEBRA_NUMERICAL_SEMIRING_NUMERICAL_SEMIRING_TEST_HH

# include <tests/check/tester.hh>
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
  catch(std::logic_error& e)
    {
      TEST_MSG("Exception:" << e.what());
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
