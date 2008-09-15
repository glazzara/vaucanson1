// transition_coherence_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef TESTS_AUTOMATA_IMPLEMENTATION_CHECK_TRANSITION_COHERENCE_TEST_HH
# define TESTS_AUTOMATA_IMPLEMENTATION_CHECK_TRANSITION_COHERENCE_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <tests/check/tester.hh>

template <typename Auto>
void transition_coherence_test_on_label(tests::Tester& t)
{
  using namespace vcsn;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  AUTOMATON_TYPES(automaton_t);
  AUTOMATON_FREEMONOID_TYPES(automaton_t);

  GenRandomAutomata<automaton_t> gen;

  automaton_t a = gen.empty();
  hstate_t s1 = a.add_state();
  hstate_t s2 = a.add_state();
  EQTEST(t, "Number of states = 2.", a.states().size(), 2);

  letter_t l  = a.structure().series().monoid().alphabet().choose();
  a.add_letter_transition(s1, s2, l);
  EQTEST(t, "Add one transition, expected number of transition = 1.",
            a.transitions().size(), 1);

  /* FIXME Activate when implemented
  htransition_t e = a.add_letter_transition(s1, s2, l);
  EQTEST(t, "Add the same transition, expected number of transition = 1.",
            a.transitions().size(), 1);

  monoid_elt_t m(a.structure().series().monoid(), l);
  EQTEST(t, "Checking if the weights are correctly updated",
	    a.series_of(e).get(m),
	    a.series().semiring().wone_ + a.series().semiring().wone_);
	    */

  /* FIXME add a third transition */
  /* FIXME use different labels */
}

template <class Auto>
unsigned transition_coherence_test(tests::Tester& tg)
{
  tests::Tester t(tg);

#if 1
  TEST_MSG("on_letters");
  transition_coherence_test_on_label<typename vcsn::on_letters<Auto>::type>(t);
#endif
#if 1
  TEST_GROUP("on_series");
  transition_coherence_test_on_label<typename vcsn::on_series<Auto>::type>(t);
#endif
  return t.all_passed();
}

#endif // ! TESTS_AUTOMATA_IMPLEMENTATION_CHECK_TRANSITION_COHERENCE_TEST_HH
