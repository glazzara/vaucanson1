// krat_exp_cderivation_letter_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_LETTER_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_LETTER_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_cderivation.hh>

using namespace vcsn;
using namespace vcsn::tools;

template <class Expr, class Derivation>
bool krat_exp_cderivation_letter_test(tests::Tester& tg)
{
  TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation);

  tests::Tester t(tg);
  TEST_DERIVATION_USUAL_DECS(al, a, b, md, sg, ss);

  int sucs = 0;
  int tsts = 0;
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, a), a, identity_as<kexp_t>::of(ss));
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, b), a, zero_as<kexp_t>::of(ss));
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, a), b, zero_as<kexp_t>::of(ss));
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, b), b, identity_as<kexp_t>::of(ss));

  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a letter. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_CDERIVATION_KRAT_EXP_CDERIVATION_LETTER_TEST_HH
