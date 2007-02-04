// krat_exp_realtime_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_REALTIME_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_REALTIME_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_realtime.hh>

template <class Expr>
bool krat_exp_realtime_test(tests::Tester& tg)
{
  typedef Expr					krat_exp_t;
  typedef typename krat_exp_t::value_t		kexp_t;
  typedef typename krat_exp_t::monoid_elt_t	monoid_elt_t;
  typedef typename monoid_elt_t::set_t		monoid_t;

  typedef typename krat_exp_t::semiring_elt_t	semiring_elt_t;
  typedef typename semiring_elt_t::set_t	semiring_t;
  typedef typename krat_exp_t::set_t		series_set_t;
  typedef typename monoid_t::letter_t		letter_t;
  typedef typename monoid_t::alphabet_t		alphabet_t;

  tests::Tester t(tg);
  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_set_t s(semiring, monoid);

  bool error = false;
  for (int i = 0; i < 100; ++i)
    {
      krat_exp_t exp = s.choose(SELECT(kexp_t));
      krat_exp_t lin = realtime(exp);
      if (!is_realtime(lin))
	error = true;
    }
  TEST(t, "Realtime works.", not error);
  return t.all_passed();

}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_REALTIME_TEST_HH
