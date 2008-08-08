// empty_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_EMPTY_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_EMPTY_TEST_HH

# include <string>

# include <vaucanson/algorithms/is_empty.hh>
# include <vaucanson/algorithms/eval.hh>

// Test various algorithms on empty automata.
template <class Auto>
bool empty_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  tests::Tester t(tg);

  alphabet_t A;

  letter_t a = A.random_letter();
  letter_t b = A.random_letter();

  A.insert(a);
  A.insert(b);

  monoid_t M(A);
  semiring_t S;
  series_set_t SS(S, M);
  automata_set_t aut_set(SS);

  // Make an empty automaton.
  automaton_t aut(aut_set);

  TEST(t, "Check is_empty returns true on an empty automaton.",
       is_empty(aut));

  std::basic_string<letter_t> word;
  word += a;
  word += b;

  semiring_elt_t zero(aut.structure().series().semiring());

  TEST(t, "Check eval on an empty automaton returns zero.",
       eval(aut, word) == zero);

  // Finally we check a bit more is_empty.
  aut.add_state();

  TEST(t, "Check is_empty returns false on a non empty automaton.",
       !is_empty(aut));

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_TRANSPOSE_TEST_HH
