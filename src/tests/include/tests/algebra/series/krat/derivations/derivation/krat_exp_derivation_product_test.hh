// krat_exp_derivation_product_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_PRODUCT_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_PRODUCT_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_derivation.hh>

using namespace vcsn;

template <class Expr, class Derivation>
bool krat_exp_derivation_product_test(tests::Tester& tg)
{
  TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation);

  tests::Tester t(tg);
  TEST_DERIVATION_USUAL_DECS(alphabet, a, b, monoid, semiring, series);

  const int nb_iter = 20;
  int sucs = 0;
  int tsts = 0;
  for (int i = 0; i < nb_iter; ++i)
    {
      // 1/ LHS is non-cancelable

      krat_exp_t random = series.choose(SELECT(kexp_t));
      krat_exp_t krat_a (series, a);
      krat_exp_t krat_b (series, b);
      // 0.xyz
      TEST_DERIVATE(tsts, sucs, zero_as<kexp_t>::of(series) * random, a,
		    zero_as<kexp_t>::of(series));
      // a.xyz
      TEST_DERIVATE(tsts, sucs, krat_a * random, a, random);
      TEST_DERIVATE(tsts, sucs, krat_a * random, b,
		    zero_as<kexp_t>::of(series));
      // (a+b).xyz
      TEST_DERIVATE(tsts, sucs, (krat_a + krat_b) * random, a, random);
      TEST_DERIVATE(tsts, sucs, (krat_a + krat_b) * random, b, random);
      // (a.b).xyz
      TEST_DERIVATE(tsts, sucs, krat_a * krat_b * random, a, krat_b * random);
      TEST_DERIVATE(tsts, sucs, krat_a * krat_b * random, b,
		    zero_as<kexp_t>::of(series));

      // 2/ LHS *is* cancelable

      std::pair<krat_exp_t, krat_exp_t> random_a =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, krat_exp_t> random_b =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, b);
      std::pair<krat_exp_t, krat_exp_t> cancel_a =
       choose_cancelable_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, krat_exp_t> cancel_b =
       choose_cancelable_exp_and_derivate<derivation_t, krat_exp_t>(series, b);
      // cancelable * random
      TEST_DERIVATE(tsts, sucs,
		    cancel_a.first * random_a.first, a,
		    cancel_a.second * random_a.first + random_a.second);
      TEST_DERIVATE(tsts, sucs,
		    cancel_b.first * random_b.first, b,
		    cancel_b.second * random_b.first + random_b.second);
    }
  
  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a product. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_PRODUCT_TEST_HH
