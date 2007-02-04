// krat_exp_partial_derivation_product_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_PRODUCT_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_PRODUCT_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_partial_derivation.hh>
# include <tests/algebra/series/krat/derivations/partial_derivation/krat_exp_partial_derivation_common.hh>

using namespace vcsn;

template <class Expr, class Derivation>
bool krat_exp_partial_derivation_product_test(tests::Tester& tg)
{
  TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation);

  tests::Tester t(tg);
  TEST_DERIVATION_USUAL_DECS(alphabet, a, b, monoid, semiring, series);

  const int nb_iter = 20;
  int sucs = 0;
  int tsts = 0;
  for (int i = 0; i < nb_iter; ++i)
    {
      std::pair<krat_exp_t, std::set<krat_exp_t> > lhs_a =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, std::set<krat_exp_t> > lhs_b =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, b);
      std::pair<krat_exp_t, std::set<krat_exp_t> > rhs_a =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, std::set<krat_exp_t> > rhs_b =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, b);

      std::set<krat_exp_t> deriv_a =
	(rhs_a.first == zero_as<typename Expr::value_t>::of(series)) ?
	std::set<krat_exp_t>() : lhs_a.second ^ rhs_a.first;
      std::set<krat_exp_t> deriv_b =
	(rhs_b.first == zero_as<typename Expr::value_t>::of(series)) ?
	std::set<krat_exp_t>() : lhs_b.second ^ rhs_b.first;

      std::pair<typename krat_exp_t::semiring_elt_t, bool> c =
        constant_term(lhs_a.first);
      if (c.second && c.first != semiring.zero(SELECT(kexp_semiring_elt_value_t)))
	deriv_a = deriv_a + rhs_a.second;
      c = constant_term(lhs_b.first);
      if (c.second && c.first != semiring.zero(SELECT(kexp_semiring_elt_value_t)))
	deriv_b = deriv_b + rhs_b.second;

      TEST_DERIVATE(tsts, sucs, lhs_a.first * rhs_a.first, a, deriv_a);
      TEST_DERIVATE(tsts, sucs, lhs_b.first * rhs_b.first, b, deriv_b);
    }

  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a product. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_PRODUCT_TEST_HH
