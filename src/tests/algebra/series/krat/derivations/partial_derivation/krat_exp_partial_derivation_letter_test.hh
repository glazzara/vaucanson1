// krat_exp_partial_derivation_letter_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_LETTER_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_LETTER_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_partial_derivation.hh>
# include <krat_exp_partial_derivation_common.hh>

using namespace vcsn;

template <class Expr, class Derivation>
bool krat_exp_partial_derivation_letter_test(tests::Tester& tg)
{
  TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation);

  tests::Tester t(tg.verbose());
  srand(time(0));
  TEST_DERIVATION_USUAL_DECS(al, a, b, md, sg, ss);

  std::set<Expr>	id_set;
  id_set.insert(identity_as<kexp_t>::of(ss));

  int sucs = 0;
  int tsts = 0;
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, a), a, id_set);
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, b), a, std::set<Expr>());
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, a), b, std::set<Expr>());
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, b), b, id_set);

  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a letter. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_LETTER_TEST_HH
