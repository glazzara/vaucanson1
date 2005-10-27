// alphabet_torture_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TORTURE_TEST_HH
# define VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TORTURE_TEST_HH

# include <vaucanson/config/system.hh>
# include <design_pattern/design_pattern-test.hh>
# include <check/tester.hh>
# include <vaucanson/design_pattern/design_pattern.hh>

# include <set>

using namespace vcsn;

template <typename S, typename T>
bool alphabet_torture_test(tests::Tester& t)
{
  using namespace vcsn::algebra;

  typedef Element<S, T>			alphabet_t;
  typedef typename alphabet_t::letter_t	letter_t;

  std::set<letter_t>	alphaset;
  alphabet_t		base;
  size_t		test_sizes[] =
    {
      0,
      1,
      base.max_size() >= 2 ? 2 : 1,
      base.max_size() <= 256 ? base.max_size() / 2 : 128,
      base.max_size() <= 256 ? base.max_size() : 256
    };

  for (size_t i = 0; i < sizeof (test_sizes) / sizeof (size_t); ++i)
    {
      alphabet_t alpha (base);
      letter_t l;
      alphaset.clear();
      for (size_t j = 0; j < test_sizes[i]; ++j)
	{
	  do
	    l = alpha.random_letter();
	  while (alpha.contains(l));
	  alphaset.insert(l);
	  alpha.insert(l);
	}

      bool error = false;
      for (size_t k = 0; k < test_sizes[i]; ++k)
	{
	  l = alpha.choose();
	  if (alphaset.find(l) == alphaset.end())
	    error = true;
	}
      TEST(t, "Choose gives correct letters.", not error);

      error = false;
      for (typename std::set<letter_t>::const_iterator  it = alphaset.begin();
	   it != alphaset.end(); ++it)
	{
	  if (not alpha.contains(*it))
	    error = true;
	}
      TEST(t, "Contains gives correct letters.", not error);
    }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_ALPHABETS_ALPHABET_TORTURE_TEST_HH
