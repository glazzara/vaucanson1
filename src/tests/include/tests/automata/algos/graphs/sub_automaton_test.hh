// sub_automaton_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_SUB_AUTOMATON_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_SUB_AUTOMATON_TEST_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/algorithms/sub_automaton.hh>

# include <set>

template <class Auto>
unsigned sub_automaton_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);

  // Algebraic structures.
  alphabet_t		alphabet;
  letter_t		a (alphabet.random_letter());
  letter_t		b (alphabet.random_letter());
  while (a == b)
    b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t		monoid(alphabet);
  semiring_t		semiring = semiring_t(CREATE_SEMIRING(monoid));
  series_set_t		series(semiring, monoid);
  automata_set_t	automata(series);
  automaton_t		automaton(automata);

  // States.
  vcsn::hstate_t s1 = automaton.add_state();
  vcsn::hstate_t s2 = automaton.add_state();
  vcsn::hstate_t s3 = automaton.add_state();
  automaton.set_initial(s1);
  automaton.set_initial(s3);
  automaton.set_final(s2);
  automaton.set_final(s3);

  // Show me the bug!
  std::set<vcsn::hstate_t> to_be_kept;
  to_be_kept.insert(s1);
  to_be_kept.insert(s2);
  automaton_t r = sub_automaton(automaton, to_be_kept);

  TEST(t, "r seems consistent. ",
       r.has_state(s1) && r.has_state(s2) && !r.has_state(s3));

  TEST(t, "r has a consistent max. ", r.states().max() == s2);

  TEST(t, "r has the right number of states. ", r.states().size() == 2);

  TEST(t, "r has the right number of initial states. ",
       r.initial().size() == 1);

  TEST(t, "r has the right number of final states. ", r.final().size() == 1);

  TEST(t, "r has consistant initial states. ",
       r.initial().max() <= r.states().max());

  TEST(t, "r has consistant final states. ",
       r.final().max() <= r.states().max());

  for_all_states(s, r)
    TEST(t, "r has the right states. ", *s <= r.states().max());

  for_all_states(s, r)
    TEST(t, "r has the right initial states. ", *s <= r.states().max());

  for_all_states(s, r)
    TEST(t, "r has the right final states. ", *s <= r.states().max());

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_SUB_AUTOMATON_TEST_HH
