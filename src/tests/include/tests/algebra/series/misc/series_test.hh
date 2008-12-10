// series_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_MISC_SERIES_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_MISC_SERIES_TEST_HH

using namespace vcsn;

template <class SeriesElt>
bool series_test(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef SeriesElt					series_set_elt_t;
  typedef typename series_set_elt_t::set_t		series_set_t;
  typedef typename series_set_elt_t::value_t		series_set_elt_value_t;

  typedef typename series_set_t::monoid_t		monoid_t;
  typedef typename monoid_t::alphabet_t			alphabet_t;
  typedef typename alphabet_t::letter_t			letter_t;

  typedef typename series_set_t::semiring_t		semiring_t;
  typedef typename series_set_elt_t::semiring_elt_t	semiring_elt_t;
  typedef typename semiring_elt_t::value_t		semiring_value_t;

  typedef typename series_set_elt_t::monoid_elt_t	monoid_elt_t;
  typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
  typedef typename series_set_elt_t::support_t		support_t;

  int			n_test = 0;
  alphabet_t		base;
  size_t		test_sizes[] =
    {
      1,
      base.max_size() >= 2 ? 2 : 1,
      base.max_size() <= 256 ? base.max_size() / 2 : 128,
      base.max_size() <= 256 ? base.max_size() : 256
    };

  for (size_t i = 0; i < sizeof (test_sizes) / sizeof (size_t); ++i, ++n_test)
    {
      alphabet_t alphabet (base);
      for (size_t j = 0; j < test_sizes[i]; ++j)
	{
	  letter_t l;
	  do
	    l = alphabet.random_letter();
	  while (alphabet.contains(l));
	  alphabet.insert(l);
	}
      std::ostringstream os;
      os << alphabet.size();
      TEST_MSG("Alphabet is " + os.str() + " characters.");

      monoid_t		monoid(alphabet);
      semiring_t	semiring;
      series_set_t		series(semiring, monoid);

      // Check that assoc on the empty word value is ok.
      monoid_elt_t empty_word(monoid);
      series_set_elt_t basic_series(series);
      basic_series.assoc(empty_word.value(), semiring_elt_t().value());

      monoid_elt_t	w1 = monoid.choose(SELECT(monoid_elt_value_t));
      monoid_elt_t	w2 (monoid);
      do
	w2 = monoid.choose(SELECT(monoid_elt_value_t));
      while (w2 == w1);

      series_set_elt_t	s1(series, w1);
      series_set_elt_t	s2(series, w2);
      series_set_elt_t	s3 = identity_as<series_set_elt_value_t>::of(series);
      series_set_elt_t	s4 = zero_as<series_set_elt_value_t>::of(series);

      semiring_elt_t	zero = zero_as<semiring_value_t>::of(semiring);

      TEST(t, "series_set_t::monoid() (const).",
	   const_cast<const series_set_t&>(series).monoid() == monoid);
      TEST(t, "series_set_t::monoid() (non-const).", series.monoid() == monoid);

      TEST(t, "series_set_t::semiring() (const).",
	   const_cast<const series_set_t&>(series).semiring() == semiring);
      TEST(t, "series_set_t::semiring() (non-const).",
	   series.semiring() == semiring);


      TEST_GROUP("Basic tests.");
      TEST(t, "get of series (element) [1].", s1.get(w1) != zero);
      TEST(t, "get of series (element) [2].", s1.get(w2) == zero);
      TEST(t, "get of series (implementation) [1].",
	   s1.get(w1.value()) != zero.value());
      TEST(t, "get of series (implementation) [2].",
	   s1.get(w2.value()) == zero.value());

      TEST_GROUP("Advanced tests with structure().");
      std::map<monoid_elt_t, semiring_elt_t>	random_values;
      const size_t				max =
	misc::random::generate<unsigned>(0, op_choose_max_word_length);
      series_set_elt_t		s5 (series);
      bool			allright = true;
      for (size_t j = 0; j < max; ++j)
	{
	  monoid_elt_t		m (monoid);
	  do
	    m = monoid.choose(SELECT(monoid_elt_value_t));
	  while (s5.get(m) != zero);
	  semiring_elt_t	s (semiring);
	  do
	    s = semiring.choose(SELECT(semiring_value_t));
	  while (s == zero);
	  random_values.insert(std::make_pair(m, s));
	  if (j % 2)
	    s5.assoc(m, s);
	  else
	    s5.assoc(m.value(), s.value());
	  if ((s5.get(m) != s) or (s5.get(m.value()) != s.value()))
	    allright = false;
	}
      TEST(t, "assoc() and value_structure().", allright);
      TEST(t, "is_finite_app().", s5.is_finite_app());

      allright = true;
      for (size_t j = 0; j < 2 * max; ++j)
	{
	  monoid_elt_t m = s5.choose_from_supp();
	  typename std::map<monoid_elt_t, semiring_elt_t>::const_iterator i =
	    random_values.find(m);
	  if (i == random_values.end())
	    {
	      TEST_FAIL_SAVE("krat_series_choose",
			     j,
			     "m is " << m
			     << " and has not been found in random_values."
			     << std::endl);
	      allright = false;
	    }
	  else if (i->second != s5.get(m))
	    {
	      TEST_FAIL_SAVE("krat_series_choose",
			     j,
			     "get(" << m << ") is " << s5.get(m)
			     << " instead of " << i->second
			     << '.' << std::endl);
	      allright = false;
	    }
	}
      TEST(t, "choose_from_supp().", allright);

      support_t		supp = s5.supp();
      allright = true;
      for (typename support_t::const_iterator j = supp.begin();
	   j != supp.end();
	   ++j)
	{
	  if (random_values.find(monoid_elt_t(monoid, *j)) ==
	      random_values.end())
	    allright = false;
	}
      TEST(t, "supp() does not give extra values.", allright);
      allright = true;
      for (typename std::map<monoid_elt_t, semiring_elt_t>::const_iterator j =
	     random_values.begin();
	   j != random_values.end();
	   ++j)
	{
	  if (std::find(supp.begin(), supp.end(), j->first) == supp.end())
	    allright = false;
	}
      TEST(t, "supp() does not forget values.", allright);

      s5.transpose();
      allright = true;
      for (size_t j = 0; j < 2 * max; ++j)
	{
	  monoid_elt_t m = s5.choose_from_supp();
	  semiring_elt_t s = s5.get(m);
	  typename std::map<monoid_elt_t, semiring_elt_t>::const_iterator i =
	    random_values.find(mirror(m));
	  if (i == random_values.end())
	    {
	      TEST_FAIL_SAVE("krat_series_transpose",
			     j,
			     "mirror(m) is " << mirror(m)
			     << " and has not been found in random_values."
			     << std::endl);
	      allright = false;
	    }
	  else if (i->second != s5.get(m))
	    {
	      TEST_FAIL_SAVE("krat_series_transpose",
			     j,
			     "get(" << m << ") is " << s5.get(m)
			     << " instead of " << i->second
			     << '.' << std::endl);
	      allright = false;
	    }
	}
      TEST(t, "transpose().", allright);
    }
  return t.all_passed();
}


#endif // ! VCSN_TESTS_ALGEBRA_SERIES_MISC_SERIES_TEST_HH
