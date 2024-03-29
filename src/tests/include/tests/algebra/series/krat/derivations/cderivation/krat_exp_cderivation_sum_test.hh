// krat_exp_cderivation_sum_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_SUM_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_SUM_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_cderivation.hh>

using namespace vcsn;
using namespace vcsn::tools;

template <class Expr, class Derivation>
bool krat_exp_cderivation_sum_test(tests::Tester& tg)
{
  TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation);

  tests::Tester t(tg);
  TEST_DERIVATION_USUAL_DECS(alphabet, a, b, monoid, semiring, series);

  const int nb_iter = 20;
  int sucs = 0;
  int tsts = 0;
  for (int i = 0; i < nb_iter; ++i)
    {
      std::pair<krat_exp_t, krat_exp_t> lhs_a =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, krat_exp_t> lhs_b =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, b);
      std::pair<krat_exp_t, krat_exp_t> rhs_a =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, krat_exp_t> rhs_b =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, b);
      TEST_DERIVATE(tsts, sucs,
		    lhs_a.first + rhs_a.first, a,
		    lhs_a.second != zero_as<typename Expr::value_t>::of(series) ?
		      lhs_a.second : rhs_a.second);
      TEST_DERIVATE(tsts, sucs,
		    lhs_b.first + rhs_b.first, b,
		    lhs_b.second != zero_as<typename Expr::value_t>::of(series) ?
  		      lhs_b.second : rhs_b.second);
    }
  
  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a sum. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_SUM_TEST_HH
