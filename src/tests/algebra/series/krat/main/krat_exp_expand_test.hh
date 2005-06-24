// krat_exp_expand_test.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_EXPAND_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_EXPAND_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_expand.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>

# include <sstream>
# include <string>

template <class Expr>
std::string test(tests::Tester& t,
		 Expr& e,
		 const std::string& input,
		 const std::string& expected)
{
  parse(input, e);
  std::stringstream s;
  s << vcsn::rat::setpm (vcsn::rat::MODE_ALL) << expand(e);
  EQTEST(t, input, s.str(), expected);
  return s.str();
}

template <typename T, typename Expr>
struct specialized_tests
{
  static void run(tests::Tester& t, Expr& e)
  {
    test(t, e, "0", "0");
    test(t, e, "1", "1");
    test(t, e, "a", "a");
    test(t, e, "(5 1)", "(5 1)");
    test(t, e, "(2 a)", "(2 a)");
    test(t, e, "(a+b)", "(a+b)");
    test(t, e, "a.(a+b)", "(aa+ab)");
    test(t, e, "(a+b).a", "(aa+ba)");
    test(t, e, "a+a", "(2 a)");
    test(t, e, "(2 a)+a", "(3 a)");
    test(t, e, "a+(2 a)", "(3 a)");
    test(t, e, "(a+(2 a+b))", "((3 a)+b)");
    test(t, e, "((a+b)+a))", "((2 a)+b)");
    test(t, e, "3 b.(a+2 b)", "((3 ba)+(6 bb))");
    test(t, e, "(a+2 b).(4 a)", "((4 aa)+(8 ba))");
    test(t, e, "(a+2 b).(a 4)", "((4 aa)+(8 ba))");
    test(t, e, "2 a.(a+b).3 b", "((6 aab)+(6 abb))");
    test(t, e, "a+(a+(a+(a+a))+a)", "(6 a)");
    test(t, e, "(1 2)", "(2 1)");
    test(t, e, "(a 3)", "(3 a)");
    test(t, e, "((3 a) 4)", "(12 a)");
    test(t, e, "(a 2)+a", "(3 a)");
    test(t, e, "a+(a 2)", "(3 a)");
    test(t, e, "(a+(a 2+b))", "((3 a)+b)");
    test(t, e, "b 3.(a+b 2)", "((3 ba)+(6 bb))");
    test(t, e, "(a+b 2).(a 4)", "((4 aa)+(8 ba))");
    test(t, e, "a 2.(a+b).b 3", "((6 aab)+(6 abb))");
    test(t, e, "a*+(a*+a*)", "(3 (a)*)");
    test(t, e, "3 a*+4 a*", "(7 (a)*)");
    test(t, e, "((a+b).a)*+((a+b).a)*", "(2 (aa+ba)*)");
    test(t, e, "(((a+b).a)*+(aa+ba)*)*", "(2 (aa+ba)*)*");
    test(t, e, "(a*+b*).a*", "(((a)*.(a)*)+((b)*.(a)*))");
  }
};

template <typename Expr>
struct specialized_tests<bool, Expr>
{
  static void run(tests::Tester& t, Expr& e)
  {
    test(t, e, "0", "0");
    test(t, e, "1", "1");
    test(t, e, "a", "a");
    test(t, e, "(a+b)", "(a+b)");
    test(t, e, "a.(a+b)", "(aa+ab)");
    test(t, e, "(a+b).a", "(aa+ba)");
    test(t, e, "a+a", "a");
    test(t, e, "(a+(a+b))", "(a+b)");
    test(t, e, "((a+b)+a))", "(a+b)");
    test(t, e, "a.(a+b).b", "(aab+abb)");
    test(t, e, "a+(a+(a+(a+a))+a)", "a");
    test(t, e, "(a+b).(a+b)", "(((aa+ab)+ba)+bb)");
    test(t, e, "a*+(a*+a*)", "(a)*");
    test(t, e, "((a+b).a)*+((a+b).a)*", "(aa+ba)*");
    test(t, e, "(((a+b).a)*+(aa+ba)*)*", "((aa+ba)*)*");
    test(t, e, "(a*+b*).a*", "(((a)*.(a)*)+((b)*.(a)*))");
  }
};

template <class Expr>
bool krat_exp_expand_test(tests::Tester& tg)
{
  typedef Expr				      krat_exp_t;
  typedef typename krat_exp_t::value_t	      kexp_t;
  typedef typename krat_exp_t::monoid_elt_t   monoid_elt_t;
  typedef typename monoid_elt_t::set_t        monoid_t;

  typedef typename krat_exp_t::semiring_elt_t   semiring_elt_t;
  typedef typename semiring_elt_t::set_t	  semiring_t;
  typedef typename krat_exp_t::set_t 	  series_set_t;
  typedef typename monoid_t::letter_t     letter_t;
  typedef typename monoid_t::alphabet_t   alphabet_t;

  tests::Tester t(tg.verbose());
  srand(time(0));
  alphabet_t alphabet;
  letter_t a = 'a';
  letter_t b = 'b';
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_set_t s(semiring, monoid);

  krat_exp_t e(s);
  specialized_tests<typename semiring_elt_t::value_t, Expr>::run(t, e);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_EXPAND_TEST_HH
