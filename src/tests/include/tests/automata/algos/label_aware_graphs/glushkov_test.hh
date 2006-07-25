// glushkov_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_GLUSHKOV_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_GLUSHKOV_TEST_HH

# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/algorithms/eval.hh>
# include <vaucanson/tools/xml_dump.hh>

# include <vaucanson/algebra/implementation/series/krat.hh>

# define TEST_ON(ExpStr, Exp, St, TrA, TrB)			\
  {								\
    TEST_MSG("Basic test on " ExpStr ".");			\
								\
    krat_t	e = Exp;					\
    automaton_t	au (aa);					\
								\
    standard_of(au, e.value());					\
    TEST(t, "a is a standard automaton.", is_standard(au) or	\
	 e == zero_as<exp_t>::of(ss));				\
								\
    TEST(t, "a has a consistent number of states.",		\
	 au.states().size() == St);				\
    int tr_a = 0;						\
    int tr_b = 0;						\
    int tr_X = 0;						\
    for_all_transitions(e, au)					\
    {								\
      if (au.series_of(*e) == series_set_elt_t (ss, ma))	\
	++tr_a;							\
      else if (au.series_of(*e) == series_set_elt_t (ss, mb))	\
	++tr_b;							\
      else							\
	++tr_X;							\
    }								\
    TEST(t, "a has consistent transitions.",			\
	 tr_a == TrA and tr_b == TrB and tr_X == 0);		\
								\
    realtime_here(au);						\
								\
    if (e != zero_as<exp_t>::of(ss))				\
    {								\
      unsigned i;						\
      for (i = 0; i < nb_word_test; ++i)			\
      {								\
	monoid_elt_t w = e.choose_from_supp();			\
	if (eval(au, w) ==					\
	    zero_as<semiring_elt_value_t>::of(ss.semiring()))	\
	{							\
	  TEST_FAIL_SAVE("glushkov", i,				\
			 "on " << e				\
			 << " : test " << w << std::endl);	\
	  break;						\
	}							\
      }								\
      TEST(t, "Basic test.", nb_word_test == i);		\
    }								\
    else							\
      TEST(t, "Basic test.", true);				\
  }


template <class Auto>
bool glushkov_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester t (tg.verbose());

  alphabet_t		at;
  letter_t		la = at.random_letter();
  at.insert(la);
  letter_t		lb = at.random_letter();
  while (at.contains(lb))
    lb = at.random_letter();
  at.insert(lb);
  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  unsigned nb_word_test = 100;
  unsigned nb_test = 40;
  unsigned nb_test_done = 0;

  letter_t	lalb[] = { la, lb, letter_t () };

  monoid_elt_t	ma (md, la);
  monoid_elt_t	mb (md, lb);
  monoid_elt_t	mamb (md, lalb);

  krat_t	a (ss, ma);
  krat_t	b (ss, mb);
  krat_t	ab (ss, mamb);

  using vcsn::algebra::zero_as;
  using vcsn::algebra::identity_as;

  TEST_ON("0", zero_as<exp_t>::of(ss), 0, 0, 0);
  TEST_ON("1", identity_as<exp_t>::of(ss), 1, 0, 0);
  TEST_ON("a", a, 2, 1, 0);
  TEST_ON("b", b, 2, 0, 1);
  TEST_ON("ab", ab, 3, 1, 1);
  TEST_ON("a.b", a * b, 3, 1, 1);
  TEST_ON("a+b", a + b, 3, 1, 1);
  TEST_ON("a*", krat_t (a).star(), 2, 2, 0);
  TEST_ON("(a+b)*a(a+b)*", (a + b).star() * a * (a + b).star(), 6, 9, 6);

  {
    TEST_MSG("Tests on random expressions.");
    unsigned success = 0;

    for (unsigned nb = 0; nb < nb_test; ++nb)
    {
      krat_t		exp = ss.choose(SELECT(exp_t));
      automaton_t	au (aa);

      try
      {
	standard_of(au, exp.value());
	bool standard = is_standard(au) or exp == zero_as<exp_t>::of(ss);
	realtime_here(au);

	if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_XML("/tmp", "glushkov", au, nb);
	}

	if (exp != ss.zero(SELECT(exp_t)))
	{
	  unsigned i;
	  for (i = 0; i < nb_word_test; ++i)
	  {
	    monoid_elt_t w = exp.choose_from_supp();
	    if (eval(au, w) ==
		zero_as<semiring_elt_value_t>::of(ss.semiring()))
	    {
	      TEST_FAIL_SAVE("glushkov", i,
			     "on " << exp
			     << " : test " << w << std::endl);
	      break;
	    }
	  }
	  if (standard and
	      ((nb_word_test == i) || (exp == ss.zero(SELECT(exp_t)))))
	    ++success;
	}
	else if (standard)
	  ++success;
	++nb_test_done;
      }
      catch (...)
      {
	++nb_test;
      }
    }
    std::string rate;
    SUCCESS_RATE(rate, success, nb_test_done);
    TEST(t, "Random test " + rate, success == nb_test_done);
  }

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_GLUSHKOV_TEST_HH
