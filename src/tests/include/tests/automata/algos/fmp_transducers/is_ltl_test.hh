// is_ltl_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_IS_LTL_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_IS_LTL_TEST_HH

# include <vaucanson/algorithms/is_ltl.hh>

template <class Automaton>
bool
is_ltl_test(tests::Tester& t)
{
  using namespace vcsn;

  // Type helpers.
  AUTOMATON_TYPES(Automaton);
  typedef typename monoid_t::first_monoid_t	first_monoid_t;
  typedef typename monoid_t::second_monoid_t	second_monoid_t;
  typedef typename first_monoid_t::alphabet_t	first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t	second_alphabet_t;
  typedef typename first_alphabet_t::set_t::letter_t	first_letter_t;
  typedef typename second_alphabet_t::set_t::letter_t	second_letter_t;

  first_alphabet_t		first_at;
  first_letter_t a = first_at.random_letter();
  first_letter_t b = first_at.random_letter();
  while (a == b) b = first_at.random_letter();
  first_at.insert(a);
  first_at.insert(b);

  second_alphabet_t		second_at;
  second_letter_t x = second_at.random_letter();
  second_letter_t y = second_at.random_letter();
  while (x == y) y = second_at.random_letter();
  second_at.insert(x);
  second_at.insert(y);

  typedef std::basic_string<first_letter_t> first_word_t;
  typedef std::basic_string<second_letter_t> second_word_t;

  first_word_t word1_a;
  word1_a += a;
  first_word_t word1_ab(word1_a);
  word1_ab += b;
  first_word_t word1_empty;
  second_word_t word2_x;
  word2_x += x;
  second_word_t word2_xy(word2_x);
  word2_xy += y;
  second_word_t word2_empty;

  // Construct our test automaton.
  fmp::automaton_t aut = fmp::make_automaton(first_at, second_at);

  hstate_t p = aut.add_state();
  hstate_t q = aut.add_state();

  // Monoid structures.
  monoid_t M(aut.structure().series().monoid());

  // Construct the series.
# define MAKE_SERIES(str, a, b) \
  monoid_elt_t x##str (M, std::make_pair(a, b)); \
  series_set_elt_t s##str (aut.structure().series()); \
  s##str .assoc( x##str , true)

  MAKE_SERIES(00, word1_empty, word2_empty);
  MAKE_SERIES(01, word1_empty, word2_x);
  MAKE_SERIES(02, word1_empty, word2_xy);
  MAKE_SERIES(10, word1_a, word2_empty);
  MAKE_SERIES(11, word1_a, word2_x);
  MAKE_SERIES(12, word1_a, word2_xy);
  MAKE_SERIES(20, word1_ab, word2_empty);
  MAKE_SERIES(21, word1_ab, word2_x);
  MAKE_SERIES(22, word1_ab, word2_xy);

# undef MAKE_SERIES

  // First dummy transition.
  htransition_t h = aut.add_series_transition(p, q, s00);

# define CHECK_CASE(i, e, f, res) \
  aut.del_transition(h); \
  aut.set_initial(p, s##i); \
  h = aut.add_series_transition(p, q, s##e); \
  aut.set_final(q, s##f); \
  EQTEST(t, "is_ltl(" #i "," #e "," #f ")", \
  is_ltl(aut), res)

  // We have to be carefull that final, initial, first and second are really
  // handled separately.
  // is_ltl must be true iff `11'.

  // Test initial transitions.
  CHECK_CASE(00, 11, 00, true);
  CHECK_CASE(01, 11, 00, false);
  CHECK_CASE(02, 11, 00, false);
  CHECK_CASE(10, 11, 00, false);
  CHECK_CASE(11, 11, 00, false);
  CHECK_CASE(12, 11, 00, false);
  CHECK_CASE(20, 11, 00, false);
  CHECK_CASE(21, 11, 00, false);
  CHECK_CASE(22, 11, 00, false);

  // Test normal transitions.
  CHECK_CASE(00, 00, 00, false);
  CHECK_CASE(00, 01, 00, false);
  CHECK_CASE(00, 02, 00, false);
  CHECK_CASE(00, 10, 00, false);
  CHECK_CASE(00, 11, 00, true);
  CHECK_CASE(00, 12, 00, false);
  CHECK_CASE(00, 20, 00, false);
  CHECK_CASE(00, 21, 00, false);
  CHECK_CASE(00, 22, 00, false);

  // Test final transitions.
  CHECK_CASE(00, 11, 00, true);
  CHECK_CASE(00, 11, 01, false);
  CHECK_CASE(00, 11, 02, false);
  CHECK_CASE(00, 11, 10, false);
  CHECK_CASE(00, 11, 11, false);
  CHECK_CASE(00, 11, 12, false);
  CHECK_CASE(00, 11, 20, false);
  CHECK_CASE(00, 11, 21, false);
  CHECK_CASE(00, 11, 22, false);

# undef UPDATE_TRANSITION

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_IS_LTL_TEST_HH
