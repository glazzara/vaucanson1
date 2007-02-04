// alphabet_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TEST_HH
# define VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TEST_HH

#include <vaucanson/config/system.hh>
#include <tests/design_pattern/design_pattern-test.hh>
#include <tests/check/tester.hh>
#include <vaucanson/design_pattern/design_pattern.hh>

using namespace vcsn;

template <typename S, typename T>
bool alphabet_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  typedef Element<S, T> element_t;
  typedef typename element_t::letter_t letter_t;

  TEST_MSG("Instantiate an alphabet A.");
  element_t A;
  TEST_MSG("Check A is empty");
  for (typename element_t::const_iterator i = A.begin(); i != A.end(); ++i)
    TEST(t, "A is not empty", false);

  TEST_MSG("Insert a random letter a in A.");
  letter_t a = A.random_letter();
  A.insert(a);

  letter_t b;
  int timeout = 0;
  do
    {
      b = A.random_letter();
      ++timeout;
    }
  while ((b == a) and timeout < 100);
  TEST(t, "A.random_letter() produces different letters.", timeout < 100);

  bool error = false;
  for (int i = 0; i < 100; ++i)
    if (A.choose() != a)
      error = true;
  TEST(t, "A.choose() gives good values.", not error);

  TEST(t, "a is in A.", A.contains(a));
  TEST(t, "b is not in A.", !A.contains(b));
  TEST(t, "A is finite and its cardinal is one.",
       (A.is_finite()) && (A.size() == 1));

  TEST(t, "A.begin() is correct.", *A.begin() == a);
  TEST(t, "A.end() is correct.", ++A.begin() == A.end());
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TEST_HH
