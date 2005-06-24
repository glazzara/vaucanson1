// free_monoid_product_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_ALGEBRA_FREE_MONOID_PRODUCT_FREE_MONOID_PRODUCT_TEST_HH
# define VCSN_TESTS_ALGEBRA_FREE_MONOID_PRODUCT_FREE_MONOID_PRODUCT_TEST_HH

#include <vaucanson/misc/functors.hh>

template <typename S, typename T>
bool free_monoid_product_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T>					element_t;
  typedef S						freemonoid_product_t;
  typedef typename freemonoid_product_t::first_monoid_t	first_monoid_t;
  typedef typename freemonoid_product_t::second_monoid_t
							second_monoid_t;
  typedef typename first_monoid_t::alphabet_t		first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t		second_alphabet_t;

  first_alphabet_t	first_base;
  second_alphabet_t	second_base;
  size_t		test_sizes[] =
    {
      0,
      1,
      first_base.max_size() >= 2 ? 2 : 1,
      first_base.max_size() <= 256 ? first_base.max_size() / 2 : 128,
      first_base.max_size() <= 256 ? first_base.max_size() : 256
    };

  bool monoid_error = false;
  bool neutral_error = false;
  bool mirror_error = false;
  bool length_error = false;

  for (size_t i = 0; i < sizeof (test_sizes) / sizeof (size_t); ++i)
    {
      first_alphabet_t first_alpha (first_base);
      second_alphabet_t second_alpha (second_base);
      for (size_t j = 0; j < test_sizes[i]; ++j)
	{
	  typename first_alphabet_t::letter_t l1;
	  typename second_alphabet_t::letter_t l2;
	  do
	    {
	      l1 = first_alpha.random_letter();
	      l2 = second_alpha.random_letter();
	    }
	  while (first_alpha.contains(l1) or second_alpha.contains(l2));
	  first_alpha.insert(l1);
	  second_alpha.insert(l2);
	}

      first_monoid_t		first_monoid (first_alpha);
      second_monoid_t		second_monoid(second_alpha);

      freemonoid_product_t	freemonoid_product(first_monoid,
						   second_monoid);

      if ((freemonoid_product.first_monoid() != first_monoid) or
	  (freemonoid_product.second_monoid() != second_monoid))
	monoid_error = true;

      element_t ab (freemonoid_product);
      if (first_alpha.size() and second_alpha.size())
	ab = freemonoid_product.choose(SELECT(T));
      element_t ba (ab);
      ba.mirror();

      element_t e = freemonoid_product.identity(SELECT(T));


      if (((ab * e) != ab) or ((e * ba) != ba))
	neutral_error = true;

      if (mirror(mirror(ab)) != ab)
	mirror_error = true;

      if (test_sizes[i])
	{
	  std::pair<int, int>			pair_len;
	  std::pair<int, int>			discr_len;
	  std::pair<int, int>			len;
	  std::pair<int, int>			len2;
	  int					add_len;
	  int					n = test_sizes[i];

	  // Size 0.
	  std::string				first_word_0;
	  std::string				second_word_0;

	  // Size 1.
	  std::string				first_word_1;
	  std::string				second_word_1;

	  first_word_1 += first_alpha.choose();
	  second_word_1 += second_alpha.choose();

	  // Size n.
	  std::string				first_word_n;
	  std::string				second_word_n;

	  for (int j = 1; j <= n; ++j)
	    {
	      first_word_n += first_alpha.choose();
	      second_word_n += second_alpha.choose();
	    }

	  // Test 0,0.

	  std::pair<std::string, std::string>	p0;
	  p0 = std::make_pair(first_word_0, second_word_0);
	  element_t w0(freemonoid_product, p0);

	  pair_len = w0.length(utility::pair<int>());
	  discr_len = w0.length(utility::discrepancy<int>());
	  add_len = w0.length(std::plus<int>());
	  len = std::make_pair(0, 0);

	  if ((pair_len != len) or (discr_len != len) or (add_len != 0))
	    length_error = true;

	  // Test 0,n.

	  std::pair<std::string, std::string>	p0n;
	  p0n = std::make_pair(first_word_0, second_word_n);
	  element_t w0n(freemonoid_product, p0n);

	  pair_len = w0n.length(utility::pair<int>());
	  discr_len = w0n.length(utility::discrepancy<int>());
	  add_len = w0n.length(std::plus<int>());

	  len = std::make_pair(0, n);

	  if ((pair_len != len) or (discr_len != len) or (add_len != n))
	    length_error = true;

	  // Test n,0.

	  std::pair<std::string, std::string>	pn0;
	  pn0 = std::make_pair(first_word_n, second_word_0);
	  element_t wn0(freemonoid_product, pn0);

	  pair_len = wn0.length(utility::pair<int>());
	  discr_len = wn0.length(utility::discrepancy<int>());
	  add_len = wn0.length(std::plus<int>());

	  len = std::make_pair(n, 0);

	  if ((pair_len != len) or (discr_len != len) or (add_len != n))
	    length_error = true;

	  // Test n,1.

	  std::pair<std::string, std::string>	pn1;
	  pn1 = std::make_pair(first_word_n, second_word_1);
	  element_t wn1(freemonoid_product, pn1);

	  pair_len = wn1.length(utility::pair<int>());
	  discr_len = wn1.length(utility::discrepancy<int>());
	  add_len = wn1.length(std::plus<int>());

	  len = std::make_pair(n, 1);
	  len2 = std::make_pair(n - 1, 0);

	  if ((pair_len != len) or (discr_len != len2) or (add_len != n + 1))
	    length_error = true;

	  // Test 1,n.

	  std::pair<std::string, std::string>	p1n;
	  p1n = std::make_pair(first_word_1, second_word_n);
	  element_t w1n(freemonoid_product, p1n);

	  pair_len = w1n.length(utility::pair<int>());
	  discr_len = w1n.length(utility::discrepancy<int>());
	  add_len = w1n.length(std::plus<int>());

	  len = std::make_pair(1, n);
	  len2 = std::make_pair(0, n - 1);

	  if ((pair_len != len) or (discr_len != len2) or (add_len != n + 1))
	    length_error = true;
	}

    }


  TEST(t, "Monoid accessors are correct.", not monoid_error);
  TEST(t, "Neutral element is correct.", not neutral_error);
  TEST(t, "Mirror is idempotent.", not mirror_error);
  TEST(t, "Length is correct.", not length_error)

  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_FREE_MONOID_PRODUCT_FREE_MONOID_PRODUCT_TEST_HH
