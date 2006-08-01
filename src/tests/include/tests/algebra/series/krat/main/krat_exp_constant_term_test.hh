// krat_exp_constant_term_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_CONSTANT_TERM_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_CONSTANT_TERM_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algebra/concept/semiring_base.hh>

template <class Expr>
bool krat_exp_constant_term_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  typedef Expr					krat_exp_t;
  typedef typename krat_exp_t::value_t		kexp_t;
  typedef typename krat_exp_t::monoid_elt_t	monoid_elt_t;
  typedef typename monoid_elt_t::set_t		monoid_t;
  typedef typename monoid_elt_t::value_t	monoid_elt_value_t;

  typedef typename krat_exp_t::semiring_elt_t	semiring_elt_t;
  typedef typename semiring_elt_t::value_t	semiring_elt_value_t;
  typedef typename semiring_elt_t::set_t	semiring_t;
  typedef typename krat_exp_t::set_t		series_set_t;
  typedef typename monoid_t::letter_t		letter_t;
  typedef typename monoid_t::alphabet_t		alphabet_t;

  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_set_t s(semiring, monoid);
  krat_exp_t exp = s.choose(SELECT(kexp_t));

  semiring_elt_t s_identity = semiring.identity(SELECT(semiring_elt_value_t));
  semiring_elt_t s_zero = semiring.zero(SELECT(semiring_elt_value_t));

  monoid_elt_t m_identity = monoid.identity(SELECT(monoid_elt_value_t));

  semiring_elt_t s_2identity = s_identity + s_identity;
  bool s_identity_computable =
    (semiring.identity(SELECT(semiring_elt_value_t))).starable();

  letter_t larray[] = { a, b, letter_t () };

  unsigned int nb_tests = 0;
  unsigned int nb_succs = 0;

  for (int cpt = 0; cpt < 100; ++cpt)
  {
    semiring_elt_t w = semiring.choose(SELECT(semiring_elt_value_t));
    semiring_elt_t w_star = w;
    semiring_elt_t s_identity_star = s_identity;
    if (s_identity.starable())
      s_identity_star = s_identity_star.star();
    if (w.starable())
      w_star = w_star.star();

    struct s_check
      {
	krat_exp_t	exp;
	semiring_elt_t	res;
	bool		computable;
      }
      exps[] =
      {
	{ // 0
	  s.zero(SELECT(kexp_t)),
	  s_zero,
	  true
	},
	{ // 1
	  s.identity(SELECT(kexp_t)),
	  s_identity,
	  true
	},
	{ // a
	  krat_exp_t (s, a),
	  s_zero,
	  true
	},
	{ // ab
	  krat_exp_t (s, std::basic_string<letter_t>(larray)),
	  s_zero,
	  true
	},
	{ // a+b
	  krat_exp_t (s, a) + krat_exp_t (s, b),
	  s_zero,
	  true
	},
	{ // a.b
	  krat_exp_t (s, a) * krat_exp_t (s, b),
	  s_zero,
	  true
	},
	{ // a*
	  krat_exp_t (s, a).star(),
	  s_identity,
	  true
	},
	{ // 1*
	  (s.identity(SELECT(kexp_t))).star(),
	  s_identity_star,
	  s_identity_computable
	},
	{ // (2 a)*
	  (s_2identity * krat_exp_t (s, a)).star(),
	  s_identity,
	  true
	},
	{ // w a
	  w * krat_exp_t (s, a),
	  s_zero,
	  true
	},
	{ // a w
	  krat_exp_t (s, a) * w,
	  s_zero,
	  true
	},
	{ // a w+a
	  krat_exp_t (s, a) * w + krat_exp_t (s, a),
	  s_zero,
	  true
	},
	{ // a w+a*
	  krat_exp_t (s, a) * w + krat_exp_t (s, a).star(),
	  s_identity,
	  true
	},
	{// w 1
	  w * krat_exp_t (s, m_identity),
	  w,
	  true
	},
	{// 1 w
	  krat_exp_t (s, m_identity) * w,
	  w,
	  true
	},
	{// (w 1)*
	  (w * krat_exp_t (s, m_identity)).star(),
	  w_star,
	  w.starable()
	},
	{// (1 w)*
	  (krat_exp_t (s, m_identity) * w).star(),
	  w_star,
	  w.starable()
	},
	{// a+1
	  krat_exp_t (s, a) + krat_exp_t (s, m_identity),
	  s_identity,
	  true
	},
	{// (a+1)*
	  (krat_exp_t (s, a) + krat_exp_t (s, m_identity)).star(),
	  s_identity_star,
	  s_identity_computable
	},
	{// 0.a
	  s.zero(SELECT(kexp_t)) * krat_exp_t (s, a),
	  s_zero,
	  true
	},
	{// a.0
	  krat_exp_t (s, a) * s.zero(SELECT(kexp_t)),
	  s_zero,
	  true
	},
	{// 0*
	  (s.zero(SELECT(kexp_t))).star(),
	  s_identity,
	  true
	}
      };

    for (unsigned int i = 0; i < sizeof(exps) / sizeof(struct s_check); ++i)
      {
	std::pair<semiring_elt_t, bool> ret = constant_term(exps[i].exp);
	if (exps[i].computable != ret.second)
	  {
	    if (exps[i].computable)
	    {
	      TEST_FAIL_SAVE("krat_exp_constant_term",
			     i,
			     "Constant term should be computed in "
			     << exps[i].exp
			     << std::endl);
	    }
	    else
	      TEST_FAIL_SAVE("krat_exp_constant_term",
			     i,
			     "Constant term shouldn't be computed in "
			     << exps[i].exp
			     << std::endl);
	  }
	else
	  if (exps[i].computable)
	    {
	      if (ret.first == exps[i].res)
		++nb_succs;
	      else
		TEST_FAIL_SAVE("krat_exp_constant_term",
			       i,
			       "Expression "
			       << exps[i].exp
			       << " returned "
			       << ret.first
			       << " as constant term, instead of "
			       << exps[i].res
			       << std::endl);
	    }
	  else
	    ++nb_succs;
	++nb_tests;
      }
  }

  std::string rate;
  SUCCESS_RATE(rate, nb_succs, nb_tests);
  TEST(t, "Constant term on all kind of basic expressions " + rate,
       nb_tests == nb_succs);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_CONSTANT_TERM_TEST_HH
