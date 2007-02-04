// semiring_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SEMIRING_SEMIRING_TEST_HH
# define VCSN_TESTS_ALGEBRA_SEMIRING_SEMIRING_TEST_HH

# include <tests/check/tester.hh>
# include <vaucanson/algebra/concept/semiring_base.hh>

template <class S, class T>
bool semiring_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T> element_t;
  element_t e1;
  element_t z = e1.structure().zero(SELECT(T));
  element_t o = e1.structure().identity(SELECT(T));
  element_t e2;
  element_t e3(o);

  TEST(t, "Commutativity of plus.", (e1 + e2) == (e2 + e1));
  TEST(t, "Distributivity of mult with plus.", 
       (e1 + e2) * e3 == e2 * e3 + e1 * e3);
  TEST(t, "0 is a zero for mult.", 
       (e1 * z == z));
  TEST(t, "starable works. (1)", z.starable() ? true  : false);
  // FIXME: add some other tests.
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SEMIRING_SEMIRING_TEST_HH
