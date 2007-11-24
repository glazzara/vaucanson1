// add_transition_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_TRANSITION_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_TRANSITION_TEST_HH

# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/handlers.hh>

template <class Auto>
unsigned add_transition_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::algebra;

  typedef Auto automaton_t;
  GenRandomAutomata<Auto> gen;

  automaton_t automaton = gen.empty();

  hstate_t s1 = automaton.add_state();
  hstate_t s2 = automaton.add_state();

  TEST(t, "Initial number of transition = 0.", automaton.transitions().size() == 0);

  htransition_t h1 = automaton.add_series_transition(s1, s2, series_set_elt_t(automaton.structure().series()));

  TEST(t, "Number of transition after one add_transition = 1.",
       automaton.transitions().size() == 1);

  automaton.del_transition(h1);

  TEST(t, "Number of transition after one deletion = 0.",
       automaton.transitions().size() == 0);

  std::set<htransition_t> s;
  const std::set<htransition_t>& sc = s;
  for (unsigned i = 0; i < 3; ++i)
  {
    hstate_t p1 = automaton.add_state();
    hstate_t p2 = automaton.add_state();
    s.insert(automaton.add_series_transition(p1, p2,
					     series_set_elt_t(automaton.structure().series())));
  }
  EQTEST(t, "Number of transition after three transition additions = 3.",
	 automaton.transitions().size(), 3);
  for (typename std::set<htransition_t>::const_iterator i = sc.begin();
       i != sc.end(); ++i)
    automaton.del_transition(*i);
  EQTEST(t, "Number of transition after total deletion in growing order = 0.",
	 automaton.transitions().size(), 0);

  s.clear();

  for (unsigned i = 0; i < 3; ++i)
  {
    hstate_t p1 = automaton.add_state();
    hstate_t p2 = automaton.add_state();
    s.insert(automaton.add_series_transition(p1, p2,
					     series_set_elt_t(automaton.structure().series())));
  }

  EQTEST(t, "Number of transition after three transition additions = 3.",
	 automaton.transitions().size(), 3);
  for (typename std::set<htransition_t>::const_reverse_iterator i = sc.rbegin();
       i != sc.rend(); ++i)
    automaton.del_transition(*i);
  EQTEST(t, "Number of transition after total deletion in decreasing order = 0.",
	 automaton.transitions().size(), 0);

  std::vector<htransition_t> vs;
  for (unsigned i = 0; i < 100; ++i)
  {
    hstate_t p1 = automaton.add_state();
    hstate_t p2 = automaton.add_state();
    vs.push_back(automaton.add_series_transition(p1, p2,
						 series_set_elt_t(automaton.structure().series())));
  }
  std::random_shuffle(vs.begin(), vs.end());
  EQTEST(t, "Number of transition after 100 transition additions = 100.",
	 automaton.transitions().size(), 100);
  for (typename std::vector<htransition_t>::const_iterator i = vs.begin();
       i != vs.end(); ++i)
    automaton.del_transition(*i);
  EQTEST(t, "Number of transition after total deletion in random order = 0.",
	 automaton.transitions().size(), 0);


  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ADD_TRANSITION_TEST_HH
