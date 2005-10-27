// rdelta_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_RDELTA_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_RDELTA_TEST_HH

#include <vaucanson/automata/concept/handlers.hh>
#include <vaucanson/tools/dot_dump.hh>

#include <list>
#include <iostream>

template <class Auto>
unsigned rdelta_test(tests::Tester& tg)
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
  semiring_t 		semiring = semiring_t(CREATE_SEMIRING(monoid));
  series_set_t		series(semiring, monoid);
  automata_set_t	automata(series);
  automaton_t		automaton(automata);

  // States.
  vcsn::hstate_t s1 = automaton.add_state();
  vcsn::hstate_t s2 = automaton.add_state();

  // Edges.
  automaton.add_letter_edge(s1, s2, a);
  automaton.add_letter_edge(s2, s1, b);

  // Show me the bug!
  std::list<int> r;
  automaton.rdelta(inserter(r, r.begin()), s2, vcsn::delta_kind::edges());
  TEST(t, "rdelta returns consistent results (1/4). ",
       !r.empty() && (automaton.origin_of(r.front()) == s1));

  r.clear();
  automaton.rdelta(inserter(r, r.begin()), s2, vcsn::delta_kind::states());
  TEST(t, "rdelta returns consistent results (2/4). ",
      	!r.empty() && r.front() == s1);

  r.clear();
  automaton.rdelta(inserter(r, r.begin()), s1, vcsn::delta_kind::edges());
  TEST(t, "rdelta returns consistent results (3/4). ",
       !r.empty() && (automaton.origin_of(r.front()) == s2));

  r.clear();
  automaton.rdelta(inserter(r, r.begin()), s1, vcsn::delta_kind::states());
  TEST(t, "rdelta returns consistent results (4/4). ",
      	!r.empty() && r.front() == s2);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_RDELTA_TEST_HH
