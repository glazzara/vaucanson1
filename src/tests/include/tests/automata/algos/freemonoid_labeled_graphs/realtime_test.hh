// realtime_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_REALTIME_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_REALTIME_TEST_HH

# include <vaucanson/algorithms/realtime.hh>

# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/tools/gen_random.hh>


template <class Auto>
unsigned realtime_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);

  tests::Tester t(tg);
  vcsn::tools::GenRandomAutomata<Auto> gen;

  const unsigned nb_ok_tests     = 20;
  const unsigned nb_non_ok_tests = 20;
  unsigned success               = 0;

  for (unsigned i = 0; i < nb_ok_tests; i++)
    {
      automaton_t a = gen.generate(50, 60);;
      if (is_realtime(a))
	++success;
    }
  std::string rate;
  SUCCESS_RATE(rate, success, nb_ok_tests);
  TEST(t, "is_realtime on realtime "+rate, success == nb_ok_tests);

  success = 0;
  for (unsigned i = 0; i < nb_non_ok_tests; i++)
    {
      automaton_t a = gen.generate_with_epsilon(50, 60, 1, 15);;
      if (!is_realtime(a))
	++success;
    }
  SUCCESS_RATE(rate, success, nb_non_ok_tests);
  TEST(t, "is_realtime on non-realtime "+rate, success == nb_non_ok_tests);

  unsigned nb_tests = t.test_num();
  unsigned nb_tests_done = 0;
  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t automata = gen.generate_with_epsilon(4, 8, 1, 2);
      try
	{
	  automaton_t non_epsilon = realtime(automata);
	  if (is_realtime(non_epsilon))
	    ++success;
	  ++nb_tests_done;
	}
      catch (std::logic_error&)
	{
	  ++nb_tests;
	}
    }
  SUCCESS_RATE(rate, success, nb_tests_done);
  TEST(t, "realtime on non-realtime "+rate, success == nb_tests_done);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_FREEMONOID_LABELED_GRAPHS_REALTIME_TEST_HH
