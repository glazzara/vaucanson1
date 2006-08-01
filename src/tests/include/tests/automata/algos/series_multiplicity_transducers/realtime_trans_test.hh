// realtime_trans_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_SERIES_MULTIPLICITY_TRANSDUCERS_REALTIME_TRANS_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_SERIES_MULTIPLICITY_TRANSDUCERS_REALTIME_TRANS_TEST_HH

# include <vaucanson/algorithms/is_realtime.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/tools/gen_random.hh>


template <class Transducer>
unsigned realtime_trans_test(tests::Tester& tg)
{
  using namespace vcsn;
  AUTOMATON_TYPES(Transducer);

  tests::Tester t(tg);
  GenRandomAutomata<Transducer> gen(time(0x0));

  const unsigned nb_tests     = 20;
  bool error = false;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t t = gen.generate(50, 60);;
      if (!is_realtime(t))
	error = true;
    }
  TEST(t, "is_realtime on realtime ", not error);
  error = false;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t t = gen.generate_with_epsilon(50, 60, 1, 15);;
      if (is_realtime(t))
	error = true;
    }
  TEST(t, "is_realtime on non-realtime ", not error);

  error = false;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t automata = gen.generate_with_epsilon(4, 8, 1, 2);
      try
      	{
	  automaton_t non_epsilon = realtime(automata);
 	  if (!is_realtime(non_epsilon))
 	    error = true;
	}
      catch (std::logic_error&)
	{
	}
    }
  TEST(t, "realtime on non-realtime ", not error);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_SERIES_MULTIPLICITY_TRANSDUCERS_REALTIME_TRANS_TEST_HH
