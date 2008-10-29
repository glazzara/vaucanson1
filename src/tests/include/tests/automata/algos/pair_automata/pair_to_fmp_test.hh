// pair_to_fmp_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_PAIR_AUTOMATA_PAIR_TO_FMP_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_PAIR_AUTOMATA_PAIR_TO_FMP_TEST_HH

# include <vaucanson/algorithms/pair_to_fmp.hh>
# include <vaucanson/algorithms/is_ltl.hh>
# include <vaucanson/algorithms/realtime.hh>

template <class Automaton>
bool
pair_to_fmp_test(tests::Tester& t)
{
  using namespace vcsn;

  // Type helpers.
  AUTOMATON_TYPES(Automaton);
  typedef typename automaton_t::series_set_t::monoid_t::alphabet_t
	alphabet_t;

  // Construct our test alphabet.
  alphabet_t A;

  // FIXME: be more generic w.r.t. letter type.
  A.insert("(3,4)");
  A.insert("(5,7)");

  // Construct our test automaton.
  automaton_t aut = automaton::make_automaton(A);

  hstate_t p = aut.add_state();
  hstate_t q = aut.add_state();

  // Monoid structures.
  monoid_t M(aut.structure().series().monoid());

  // Construct the series.
# define MAKE_SERIES(str, a) \
  monoid_elt_t x##str (M, a); \
  series_set_elt_t s##str (aut.structure().series()); \
  s##str .assoc( x##str , true)

  MAKE_SERIES(0, "");
  MAKE_SERIES(1, "(3,4)");
  MAKE_SERIES(2, "(3,4)(3,4)");

# undef MAKE_SERIES

  // First dummy transition.
  htransition_t h = aut.add_series_transition(p, q, s0);

# define CHECK_CASE(i, e, f, res1, res2) \
  aut.del_transition(h); \
  aut.set_initial(p, s##i); \
  h = aut.add_series_transition(p, q, s##e); \
  aut.set_final(q, s##f); \
  EQTEST(t, "is_realtime(" #i "," #e "," #f ")", \
  is_realtime(aut), res1) \
  EQTEST(t, "is_ltl(pair_to_fmp(" #i "," #e "," #f "))", \
  is_ltl(pair_to_fmp(aut)), res2)

  // Test initial transitions.
  CHECK_CASE(0, 1, 1, true,  true);
  CHECK_CASE(1, 1, 1, true,  true);
  // FIXME: is_realtime ignores initial transitions
  //CHECK_CASE(2, 1, 1, false, false);

  // Test normal transitions.
  // FIXME: this case induces that is_realtime is not equivalent to is_ltl
  // (epsilon transitions...)
  CHECK_CASE(1, 0, 1, false,  true);
  CHECK_CASE(1, 1, 1, true,  true);
  CHECK_CASE(1, 2, 1, false, false);

  // Test final transitions.
  CHECK_CASE(1, 1, 0, true,  true);
  CHECK_CASE(1, 1, 1, true,  true);
  // FIXME: is_realtime ignores final transitions
  //CHECK_CASE(1, 1, 2, false, false);

# undef UPDATE_TRANSITION

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_PAIR_AUTOMATA_PAIR_TO_FMP_TEST_HH
