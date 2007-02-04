// extract_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_EXTRACT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_EXTRACT_TEST_HH

# include <time.h>
# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/accessible.hh>
# include <vaucanson/tools/xml_dump.hh>

template <class Auto>
unsigned extract_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  AUTOMATON_TYPES(Auto);
  typedef Auto automaton_t;

  tests::Tester t(tg);
  GenRandomAutomata<automaton_t> gen;

  unsigned	 success  = 0;

  for (unsigned i = 0; i < t.test_num(); i++)
  {
    unsigned nb_state = 5;
    unsigned nb_transition = 10;
    automaton_t a = gen.generate(nb_state, nb_transition);
    automaton_t b = sub_automaton(a, a.states());
    if ((a.states().size() == b.states().size()) &&
	(a.transitions().size() == b.transitions().size()))
      ++success;
  }
  std::string rate;
  SUCCESS_RATE(rate, success, t.test_num());
  TEST(t, "sub automaton "+rate, success == t.test_num());
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_EXTRACT_TEST_HH
