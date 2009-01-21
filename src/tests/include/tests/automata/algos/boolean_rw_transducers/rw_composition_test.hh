// rw_composition_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_RW_COMPOSITION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_RW_COMPOSITION_TEST_HH

# include <tests/check/tester.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algorithms/rw_composition.hh>

template <class Auto>
bool rw_composition_test(tests::Tester& tg)
{
  using namespace vcsn;

  tests::Tester t(tg);

  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);

  //
  // Build the two automaton.
  //

  // Type helpers.
  typedef series_set_elt_t exp_t;
  typedef typename series_set_elt_t::semiring_elt_t output_exp_t;
  typedef std::set<std::pair<hstate_t, output_exp_t> > state_exp_pair_set_t;

  alphabet_t A;

  A.insert(static_cast<letter_t>('a'));
  A.insert(static_cast<letter_t>('b'));

  automaton_t R = rw_transducer::make_automaton(A, A);

  monoid_elt_t in_e(R.series().monoid());
  monoid_elt_t in_a(R.series().monoid(), static_cast<letter_t>('a'));
  monoid_elt_t in_b(R.series().monoid(), static_cast<letter_t>('b'));

  monoid_elt_t out_e(R.series().monoid());
  monoid_elt_t out_a(R.series().semiring().monoid(), static_cast<letter_t>('a'));
  monoid_elt_t out_b(R.series().semiring().monoid(), static_cast<letter_t>('b'));

  output_exp_t ser_e(R.series().semiring());
  ser_e.assoc(in_e, true);
  output_exp_t ser_a(R.series().semiring());
  ser_a.assoc(in_a, true);
  output_exp_t ser_b(R.series().semiring());
  ser_b.assoc(in_b, true);

  hstate_t p = R.add_state();
  hstate_t q = R.add_state();

  R.set_initial(p);
  R.set_final(q);

  series_set_elt_t x(R.series());
  x.assoc(in_a, ser_b);
  x.assoc(in_b, ser_a);

  /**
   * The following line must give the same result in the composition
   * as the two following.
   *
   * R.add_io_transition(p, q, "a", "b");
   * R.add_io_transition(p, q, "b", "a");
   */

  R.add_series_transition(p, q, x);

  automaton_t S = rw_transducer::make_automaton(A, A);

  hstate_t u = S.add_state();
  hstate_t v = S.add_state();

  S.set_initial(u);
  S.set_final(v);

  S.add_io_transition(u, v, in_b, out_a);
  S.add_io_transition(u, v, in_a, out_b);

  //
  // Run the tests.
  //

  automaton_t res = rw_transducer::make_automaton(A, A);
  rw_composition(R, S, res);

  TEST(t, "Number of states in the result transducer.", res.states().size() == 2);
  TEST(t, "Number of transitions in the result transducer.", res.transitions().size() == 2);

  {
    hstate_t p = res.get_state(0);
    TEST(t, "p is the initial state.", res.is_initial(p));

    hstate_t q = res.get_state(1);
    TEST(t, "q is the final state.", res.is_final(q));

    series_set_elt_t u(res.series());
    u.assoc(in_a, out_a);
    series_set_elt_t v(res.series());
    v.assoc(in_b, out_b);

    series_set_elt_t k = res.series_of(*(res.transitions().begin()));
    series_set_elt_t l = res.series_of(*(++(res.transitions().begin())));

    TEST(t, "The two transitions are ({a} a) and ({b} b).", (k != l)
	 && ((k == u) || k == v) && ((l == u) || (l == v)));
  }

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_RW_COMPOSITION_TEST_HH
