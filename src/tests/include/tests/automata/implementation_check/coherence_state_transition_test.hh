// coherence_state_transition_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_COHERENCE_STATE_TRANSITION_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_COHERENCE_STATE_TRANSITION_TEST_HH

# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>

template <class Auto>
unsigned coherence_state_transition_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;

  typedef GenRandomAutomata<Auto> gen_auto_t;
  gen_auto_t gen(time(0x0));
  typedef Auto automaton_t;
  automaton_t automaton(gen.generate_dfa(10).structure());

  hstate_t s1 = automaton.add_state();
  hstate_t s2 = automaton.add_state();

  htransition_t h1 = automaton.add_letter_transition(s1, s2,
						     automaton.structure().series().
						     monoid().alphabet().choose());

  EQTEST(t, "Check number of state.", automaton.states().size(), 2);
  EQTEST(t, "Check number of transition.", automaton.transitions().size(), 1);

  automaton.del_state(s1);
  automaton.del_state(s2);

  TEST(t, "Check for zombies transition.", automaton.transitions().size() == 0);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_COHERENCE_STATE_TRANSITION_TEST_HH
