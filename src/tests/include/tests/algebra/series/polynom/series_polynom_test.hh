// series_polynom_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_POLYNOM_SERIES_POLYNOM_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_POLYNOM_SERIES_POLYNOM_TEST_HH

# include <vaucanson/config/system.hh>
# include <tests/check/tester.hh>
# include <vaucanson/design_pattern/design_pattern.hh>

# include <vaucanson/algebra/implementation/series/polynoms.hh>


using namespace vcsn;

template <class SeriesElt>
bool series_polynom_test(tests::Tester& t)
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

  typedef typename series_set_elt_t::monoid_elt_t	monoid_elt_t;
  typedef typename series_set_elt_t::semiring_elt_t	semiring_elt_t;
  typedef typename semiring_elt_t::value_t		semiring_elt_value_t;

  alphabet_t	alphabet;
  letter_t	a = alphabet.random_letter();
  letter_t	b;
  do
    b = alphabet.random_letter();
  while (a == b);
  alphabet.insert(a);
  alphabet.insert(b);

  monoid_t		monoid (alphabet);
  semiring_t		semiring;
  series_set_t		series (semiring, monoid);
  monoid_elt_t		w1 (monoid, a);
  monoid_elt_t		w2 (monoid, b);
  series_set_elt_t	s1 (series, w1);
  series_set_elt_t	s2 (series, w2);
  series_set_elt_t	s3 (series,
			    series.identity(SELECT(series_set_elt_value_t)));
  series_set_elt_t	s4 (series,
			    series.zero(SELECT(series_set_elt_value_t)));
  semiring_elt_t	zero = semiring.zero(SELECT(semiring_elt_value_t));

  TEST(t, "get of series.", s1.get(w1) != zero);
  TEST(t, "set of series.", s1.get(w2) == zero);
  TEST(t, "choose from the support.", s1.choose_from_supp() == w1);

  return t.all_passed();
}


#endif // ! VCSN_TESTS_ALGEBRA_SERIES_POLYNOM_SERIES_POLYNOM_TEST_HH
