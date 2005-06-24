// normalize_test.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_NORMALIZE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_NORMALIZE_TEST_HH

# include <time.h>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/normalized.hh>

template <class Auto>
unsigned normalize_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  typedef Auto automaton_t;
 
  tests::Tester				t(tg.verbose());
  GenRandomAutomata<automaton_t>	gen(time(0x0));
  const unsigned			nb_tests = 10;
  unsigned				success = 0;
  std::string				rate;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t normalized = gen.generate_normalized(30);;
      if (is_normalized(normalized))
	success++;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "is_normalized on random normalized automaton "+rate, 
       nb_tests == success);

  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t normalized = gen.generate(30, 60);
      normalize_here(normalized);
      if (is_normalized(normalized))
	success++;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "normalized on randomly generated automaton "+rate, nb_tests == success);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_NORMALIZE_TEST_HH
