// is_subnormalized_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_IS_SUBNORMALIZED_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_IS_SUBNORMALIZED_TEST_HH

# include <vaucanson/algorithms/sub_normalize.hh>

template <class Automaton>
bool
is_subnormalized_test(tests::Tester& t)
{
  using namespace vcsn;

  // Type helpers.
  AUTOMATON_TYPES(Automaton);
  typedef typename monoid_t::first_monoid_t	first_monoid_t;
  typedef typename monoid_t::second_monoid_t	second_monoid_t;
  typedef typename first_monoid_t::alphabet_t	first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t	second_alphabet_t;

  // First alphabet.
  first_alphabet_t A;

  A.insert('a');
  A.insert('b');

  // Second alphabet.
  second_alphabet_t B;

  B.insert('x');
  B.insert('y');

  // Construct our test automaton.
  fmp::automaton_t aut = fmp::make_automaton(A, B);

  hstate_t p = aut.add_state();
  hstate_t q = aut.add_state();

  // Monoid structures.
  monoid_t M(aut.structure().series().monoid());

  // Construct the series.
# define MAKE_SERIES(str, a, b) \
  monoid_elt_t x##str (M, std::make_pair(a, b)); \
  series_set_elt_t s##str (aut.structure().series()); \
  s##str .assoc( x##str , true)

  MAKE_SERIES(00, "", "");
  MAKE_SERIES(01, "", "x");
  MAKE_SERIES(02, "", "xy");
  MAKE_SERIES(10, "a", "");
  MAKE_SERIES(11, "a", "x");
  MAKE_SERIES(12, "a", "xy");
  MAKE_SERIES(20, "ab", "");
  MAKE_SERIES(21, "ab", "x");
  MAKE_SERIES(22, "ab", "xy");

# undef MAKE_SERIES

  // First dummy transition.
  htransition_t h = aut.add_series_transition(p, q, s00);

# define CHECK_CASE(i, e, f, res) \
  aut.del_transition(h); \
  aut.set_initial(p, s##i); \
  h = aut.add_series_transition(p, q, s##e); \
  aut.set_final(q, s##f); \
  EQTEST(t, "is_subnormalized(" #i "," #e "," #f ")", \
  is_sub_normalized(aut), res)

  // We have to be carefull that final, initial, first and second are really
  // handled separately.
  // is_subnormalized must be false each time there is a `2', true otherwise.

  // Test initial transitions.
  CHECK_CASE(00, 00, 00, true);
  CHECK_CASE(01, 00, 00, true);
  CHECK_CASE(02, 00, 00, false);
  CHECK_CASE(10, 00, 00, true);
  CHECK_CASE(11, 00, 00, true);
  CHECK_CASE(12, 00, 00, false);
  CHECK_CASE(20, 00, 00, false);
  CHECK_CASE(21, 00, 00, false);
  CHECK_CASE(22, 00, 00, false);

  // Test normal transitions.
  CHECK_CASE(00, 00, 00, true);
  CHECK_CASE(00, 01, 00, true);
  CHECK_CASE(00, 02, 00, false);
  CHECK_CASE(00, 10, 00, true);
  CHECK_CASE(00, 11, 00, true);
  CHECK_CASE(00, 12, 00, false);
  CHECK_CASE(00, 20, 00, false);
  CHECK_CASE(00, 21, 00, false);
  CHECK_CASE(00, 22, 00, false);

  // Test final transitions.
  CHECK_CASE(00, 00, 00, true);
  CHECK_CASE(00, 00, 01, true);
  CHECK_CASE(00, 00, 02, false);
  CHECK_CASE(00, 00, 10, true);
  CHECK_CASE(00, 00, 11, true);
  CHECK_CASE(00, 00, 12, false);
  CHECK_CASE(00, 00, 20, false);
  CHECK_CASE(00, 00, 21, false);
  CHECK_CASE(00, 00, 22, false);

# undef UPDATE_TRANSITION

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_IS_SUBNORMALIZED_TEST_HH
