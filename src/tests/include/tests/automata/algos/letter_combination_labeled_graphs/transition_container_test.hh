// transition_container_test.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_TRANSITION_CONTAINER_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_TRANSITION_CONTAINER_TEST_HH

# include <list>
# include <set>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>

template <class Auto>
unsigned transition_container_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  typedef Auto automaton_t;
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::algebra;
  AUTOMATON_TYPES(automaton_t);
  AUTOMATON_FREEMONOID_TYPES(automaton_t);

  alphabet_t	a;
  letter_t	l1 = a.random_letter();
  letter_t	l2;
  do
    l2 = a.random_letter();
  while (l1 == l2);
  // The tests on the sets needs to have two different letters to work.
  assert(l1 != l2);
  a.insert(l1);
  a.insert(l2);
  monoid_t	monoid(a);
  semiring_t	semiring;
  series_set_t	series(semiring, monoid);
  automata_set_t	auto_set(series);
  GenRandomAutomata<Auto> gen;
  automaton_t aut = gen.empty(auto_set);

  hstate_t s1(aut.add_state());
  hstate_t s2(aut.add_state());

  htransition_t t1(aut.add_letter_transition(s1, s2, l1));
  htransition_t t2(aut.add_letter_transition(s1, s2, l2));

  EQTEST(t, "Testing operator< (Used in the sets)", (t1 < t1), false);
  EQTEST(t, "Testing operator< (Used in the sets)", (t2 < t2), false);
  EQTEST(t, "Testing operator< (Used in the sets)", ((t1 < t2) || (t2 < t1)), true);

  std::list<htransition_t> list;
  std::multiset<htransition_t> multiset;
  std::set<htransition_t> set;

  list.push_back(t1);
  list.push_back(t2);
  EQTEST(t, "Number of transition added to the list using manual insertion = 2.", list.size(), 2);
  list.clear();

  multiset.insert(t1);
  multiset.insert(t2);
  EQTEST(t, "Number of transition added to the multiset using manual insertion = 2.", multiset.size(), 2);
  multiset.clear();

  set.insert(t1);
  set.insert(t2);
  EQTEST(t, "Number of transition added to the set using manual insertion = 2.", set.size(), 2);
  set.clear();

  return t.all_passed();
}

#endif // !VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_TRANSITION_CONTAINER_TEST_HH
