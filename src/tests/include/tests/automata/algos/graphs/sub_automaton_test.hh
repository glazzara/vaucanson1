// sub_automaton_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_SUB_AUTOMATON_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_SUB_AUTOMATON_TEST_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/algorithms/sub_automaton.hh>

# include <set>

template <class Auto>
unsigned sub_automaton_test(tests::Tester& tg)
{
  tests::Tester t(tg);

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
  hstate_t s1 = automaton.add_state();
  hstate_t s2 = automaton.add_state();
  hstate_t s3 = automaton.add_state();
  automaton.set_initial(s1);
  automaton.set_initial(s3);
  automaton.set_final(s2);
  automaton.set_final(s3);

  // Show me the bug!
  std::set<hstate_t> to_be_kept;
  to_be_kept.insert(s1);
  to_be_kept.insert(s2);
  sub_automaton_here(automaton, to_be_kept);

  TEST(t, "automaton seems consistent. ",
       automaton.has_state(s1) && automaton.has_state(s2) && !automaton.has_state(s3));

// FIXME what does "has a consistent max" means
//  TEST(t, "r has a consistent max. ", r.states().back() == s2);

  TEST(t, "automaton has the right number of states. ", automaton.states().size() == 2);

  TEST(t, "automaton has the right number of initial states. ",
       automaton.initial().size() == 1);

  TEST(t, "automaton has the right number of final states. ", automaton.final().size() == 1);

  TEST(t, "automaton has consistant initial states. ",
       automaton.initial().size() <= automaton.states().size());

  TEST(t, "automaton has consistant final states. ",
       automaton.final().size() <= automaton.states().size());

  for_all_states(s, automaton)
    TEST(t, "automaton has the right states. ", automaton.has_state(*s));

// FIXME: understand what was intended and write a correct test
//  for_all_states(s, automaton)
//    TEST(t, "automaton has the right initial states. ", *s <= automaton.states().back());
//
//  for_all_states(s, automaton)
//    TEST(t, "automaton has the right final states. ", *s <= automaton.states().back());

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_GRAPHS_SUB_AUTOMATON_TEST_HH
