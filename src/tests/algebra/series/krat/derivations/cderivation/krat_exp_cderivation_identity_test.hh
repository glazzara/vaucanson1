// krat_exp_cderivation_identity_test.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_IDENTITY_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_IDENTITY_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_cderivation.hh>

using namespace vcsn;

template <class Expr, class Derivation>
bool krat_exp_cderivation_identity_test(tests::Tester& tg)
{
  TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation);

  tests::Tester t(tg.verbose());
  srand(time(0));
  TEST_DERIVATION_USUAL_DECS(alphabet, a, b, monoid, semiring, series);

  int sucs = 0;
  int tsts = 0;
  TEST_DERIVATE(tsts, sucs,
		identity_as<kexp_t>::of(series), a, 
		zero_as<kexp_t>::of(series));
  TEST_DERIVATE(tsts, sucs,
		identity_as<kexp_t>::of(series), b, 
		zero_as<kexp_t>::of(series));

  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on identity. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_IDENTITY_TEST_HH
