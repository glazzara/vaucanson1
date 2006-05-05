// deterministic_test.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_DETERMINISTIC_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_DETERMINISTIC_TEST_HH

# include <time.h>
# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/tools/dot_dump.hh>

template <class Auto>
unsigned deterministic_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  typedef Auto automaton_t;

  
  tests::Tester t(tg.verbose());
  GenRandomAutomata<automaton_t> gen(time(0x0));
  
  const unsigned nb_tests = 1;
  unsigned success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t dfa = gen.generate_dfa(50);;
      if (is_deterministic (dfa))
	++success;
    } 
  std::string rate;
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "is_deterministic on randomly generated dfa " + rate, success == nb_tests);


  // add my test mettre a jour t

  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {     
      automaton_t automata = gen.generate(4, 8);
      automaton_t dfa      = determinize(automata);
      if (is_deterministic(dfa))
	++success;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "determinize on randomly generated automaton " + rate, success == nb_tests);
  
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_DETERMINISTIC_TEST_HH
