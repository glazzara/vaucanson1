// krat_exp_realtime_conflict_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_KRAT_EXP_REALTIME_CONFLICT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_KRAT_EXP_REALTIME_CONFLICT_TEST_HH

# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/algorithms/krat_exp_realtime.hh>

# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/tools/gen_random.hh>

template <class Auto>
unsigned krat_exp_realtime_conflict_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  // By  the  past  realtime()  in realtime.hh  was  conflicting  with
  // realtime()   in   krat_exp_realtime.hh.   The  following   is   a
  // corresponding regression test.
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  typedef
    vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>			krat_exp_t;

  bool out (false);
  while (not out)
    {
      // The goal is  to compile successfully. It is  not important if
      // an exception is thrown.
      try
	{
	  alphabet_t	at;
	  at.insert(at.random_letter());
	  monoid_t	md (at);
	  semiring_t	sg;
	  series_set_t	ss(sg, md);
	  krat_exp_t	e1 = ss.choose(SELECT(exp_t));
	  krat_exp_t	e2 = realtime(e1);
	  realtime_here(e1);
	  TEST(t,
	       "realtime(automaton) does not conflict with realtime(exp) [1].",
	       e1 == e2);
	  out = true;
	}
      catch (...)
	{
	}
    }

  vcsn::GenRandomAutomata<Auto> generator;
  try
    {
      automaton_t	a = realtime(generator.generate(50, 60));
    }
  catch (...)
    {
    }
  TEST(t, "realtime(automaton) does not conflict with realtime(exp) [2].",
       true);

  automaton_t	b = generator.generate_with_epsilon(50, 60, 1, 15);
  try
    {
      realtime_here(b);
    }
  catch (...)
    {
    }
  TEST(t, "realtime(automaton) does not conflict with realtime(exp) [3].",
       true);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_KRAT_EXP_REALTIME_CONFLICT_TEST_HH
