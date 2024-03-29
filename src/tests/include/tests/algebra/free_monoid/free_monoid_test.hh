// free_monoid_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_FREE_MONOID_FREE_MONOID_TEST_HH
# define VCSN_TESTS_ALGEBRA_FREE_MONOID_FREE_MONOID_TEST_HH

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <tests/design_pattern/design_pattern-test.hh>

# include <sstream>

template <typename S, typename T>
bool free_monoid_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T>					element_t;
  typedef typename element_t::set_t			freemonoid_t;
  typedef typename freemonoid_t::alphabets_elt_t	alphabet_t;
  typedef typename freemonoid_t::letter_t		letter_t;

  // Basic test for the monoid_elt_constructor.
  alphabet_t at;
  letter_t l1 = at.random_letter();
  letter_t l2 = at.random_letter();
  while (l1 == l2) l2 = at.random_letter();
  at.insert(l1);
  at.insert(l2);

  // When building the monoid without representation, a good epsilon
  // representation should be selected.
  freemonoid_t M(at);

  // There should be a problem is the concat representation is empty.
  if (M.representation()->concat == "")
  {
    std::string ambiguous_word;
    ambiguous_word += algebra::letter_traits<letter_t>::letter_to_literal(l1);
    ambiguous_word += M.representation()->concat;
    ambiguous_word += algebra::letter_traits<letter_t>::letter_to_literal(l2);

    // Now we use this ambiguous word as the epsilon representation.
    typename freemonoid_t::monoid_rep_t rep;
    rep.empty = ambiguous_word;

    // Now we build a new monoid.
    freemonoid_t N(at, rep);

    // And two monoid elements of interest.
    element_t m1(N, ambiguous_word);
    T mref;
    mref += l1;
    mref += l2;
    element_t m2(N);
    parse_word(m2, ambiguous_word);

    // The first construct MUST NOT call parse_word, ie m1 must be the word
    // with two letters, l1 and l2.
    TEST(t, "Basic test (no parse_word from CTOR).", m1.value() == mref);

    // On the contrary, if calling parse_word on ambiguous_word, it should
    // return the empty word, as ambiguous_word is the epsilon representation.
    TEST(t, "Basic test (parse_word gives epsilon).", m2.value().size() == 0);
  }

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
      for (size_t j = 0; j < test_sizes[i]; ++j)
	{
	  letter_t l;
	  do
	    l = alpha.random_letter();
	  while (alpha.contains(l));
	  alpha.insert(l);
	}
      std::ostringstream os;
      os << alpha.size();
      TEST_MSG("Alphabet has " + os.str() + " characters.");

      freemonoid_t		freemonoid (alpha);
      const freemonoid_t	const_freemonoid (alpha);

      TEST(t, "alphabet() (non-const).", freemonoid.alphabet() == alpha);
      TEST(t, "alphabet() (const).", const_freemonoid.alphabet() == alpha);

      // Create a word and its mirror.
      element_t ab (freemonoid);
      if (alpha.size())
	ab = freemonoid.choose(SELECT(T));
      element_t ba (ab);
      ba.mirror();

      // Do the tests.
      int l = ab.length() + ba.length();
      int m = l;
      TEST(t, "mirror() and length().", ab.length() == ba.length());

      bool						allright = true;
      typename element_t::const_iterator		abi = ab.begin();
      typename element_t::const_reverse_iterator	bai = ba.rbegin();
      while (allright and (abi != ab.end()) and
	     (bai != const_cast<const element_t&> (ba).rend()))
	{
	  if (*abi != *bai)
	    allright = false;
	  ++abi; --l;
	  ++bai; --l;
	}
      TEST(t, "const iterators.", not l);
      TEST(t, "mirror() [1].", (allright));
      TEST(t, "mirror() [2].", (abi == ab.end()) and
	   (bai == const_cast<const element_t&> (ba).rend()));

      element_t					old_ab = ab;
      element_t					old_ba = ba;
      typename element_t::iterator		abi2 = ab.begin();
      typename element_t::reverse_iterator	bai2 = ba.rbegin();
      for (typename element_t::const_iterator i = old_ba.begin();
	   i != old_ba.end();
	   ++i)
	{
	  *abi2 = *i;
	  abi2++; ++l;
	}
      for (typename element_t::const_reverse_iterator i = old_ab.rbegin();
	   i != const_cast<const element_t&> (old_ab).rend();
	   ++i)
	{
	  *bai2 = *i;
	  bai2++; ++l;
	}

      TEST(t, "iterators [1].", l == m);
      TEST(t, "iterators [2].", (abi2 == ab.end()) and (bai2 == ba.rend()));
      TEST(t, "iterators [3].", (ab == old_ba) and (ba == old_ab));


      TEST_MSG("Get the neutral element of this free monoid.");
      element_t e = freemonoid.identity(SELECT(T));

      test_design_pattern<S, T>(const_freemonoid);
      TEST(t, "Neutral element on the right.", (ab * e) == ab);
      TEST(t, "Neutral element on the left." , (e * ba) == ba);
      TEST(t, "Mirror is idempotent.", mirror(mirror(ab)) == ab);
    }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_FREE_MONOID_FREE_MONOID_TEST_HH
