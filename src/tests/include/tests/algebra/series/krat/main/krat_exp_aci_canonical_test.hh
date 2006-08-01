// krat_exp_aci_canonical_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_ACI_CANONICAL_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_ACI_CANONICAL_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
# include <vaucanson/algorithms/aci_canonical.hh>

# include <sstream>

static struct { char* fst; char* snd; } samples[] =
{
  { "0", "0" },
  { "1", "1" },
  { "a", "a" },
  { "a.b", "a.b" },
  { "a+b", "a+b" },
  { "b+a", "a+b" },
  { "a+(b+c)", "(a+b)+c" },
  { "a+a", "a" },
  { "a+c+a", "c+a" },
  { "a+(c+a)", "a+c" },
  { "(a.b)+c+a", "a+(a.b)+c" },
  { "a.(b+c+b)", "a.(c+b)" },
  { "(a.(b+a+b))+(a.(a+b+a))", "a.(b+a)" },
  { "(a+c.b)+(a+c.b+a)", "a+c.b" },
  { NULL, NULL }
};

template <class Expr>
bool krat_exp_aci_canonical_test(tests::Tester& tg)
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
  alphabet.insert('a');
  alphabet.insert('b');
  alphabet.insert('c');
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_set_t s(semiring, monoid);

  unsigned int nb_success = 0;
  unsigned int nb_tests;

  for (nb_tests = 0; samples[nb_tests].fst != NULL; ++nb_tests)
  {
    krat_exp_t exp1(s);
    krat_exp_t exp2(s);
    parse(samples[nb_tests].fst, exp1);
    parse(samples[nb_tests].snd, exp2);
    if (canonical(exp1) == canonical(exp2))
      nb_success++;
    else
      TEST_FAIL_SAVE("krat_exp_aci_canonical", nb_tests,
		     "canonical(" << samples[nb_tests].fst
		     << ") != canonical("
		     << samples[nb_tests].snd << ")" << std::endl);
  }

  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_tests);
  TEST(t, "Building aci-canonical form of rational expression " + rate,
       nb_success == nb_tests);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_ACI_CANONICAL_TEST_HH
