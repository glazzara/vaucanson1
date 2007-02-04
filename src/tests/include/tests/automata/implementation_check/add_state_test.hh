// add_state_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_STATE_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_STATE_TEST_HH

# include <map>
# include <algorithm>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/gen_random.hh>
# include <tests/check/tester.hh>

template <class Auto>
unsigned add_state_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  AUTOMATON_TYPES(Auto);


  using namespace vcsn;
  using namespace vcsn::algebra;

  typedef Auto automaton_t;
  GenRandomAutomata<Auto> gen;

  automaton_t automaton = gen.empty();

  EQTEST(t, "Initial number of state = 0.", automaton.states().size(), 0);

  hstate_t s1 = automaton.add_state();

  EQTEST(t, "Number of state after one state addition = 1.",
       automaton.states().size(), 1);

  automaton.del_state(s1);

  EQTEST(t, "Number of state after one state deletion = 0.",
	 automaton.states().size(), 0);

  std::set<hstate_t> s;
  const std::set<hstate_t>& sc = s;
  for (unsigned i = 0; i < 3; ++i)
    s.insert(automaton.add_state());
  EQTEST(t, "Number of state after three state additions = 3.",
	 automaton.states().size(), 3);
  for (std::set<hstate_t>::const_iterator i = sc.begin();
       i != sc.end(); ++i)
    automaton.del_state(*i);
  EQTEST(t, "Number of state after total deletion in growing order = 0.",
	 automaton.states().size(), 0);

  for (unsigned i = 0; i < 3; ++i)
    s.insert(automaton.add_state());
  EQTEST(t, "Number of state after three state additions = 3.",
	 automaton.states().size(), 3);
  for (std::set<hstate_t>::const_reverse_iterator i = sc.rbegin();
       i != sc.rend(); ++i)
    automaton.del_state(*i);
  EQTEST(t, "Number of state after total deletion in decreasing order = 0.",
	 automaton.states().size(), 0);

  std::vector<hstate_t> vs;
  for (unsigned i = 0; i < 100; ++i)
    vs.push_back(automaton.add_state());
  std::random_shuffle(vs.begin(), vs.end());
  EQTEST(t, "Number of state after 100 state additions = 100.",
	 automaton.states().size(), 100);
  for (std::vector<hstate_t>::const_iterator i = vs.begin();
       i != vs.end(); ++i)
    automaton.del_state(*i);
  EQTEST(t, "Number of state after total deletion in random order = 0.",
	 automaton.states().size(), 0);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_STATE_TEST_HH
