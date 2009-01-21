// partial_evaluation_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_PARTIAL_EVALUATION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_PARTIAL_EVALUATION_TEST_HH

# include <tests/check/tester.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algorithms/internal/evaluation.hh>

template <class Auto>
bool partial_evaluation_test(tests::Tester& tg)
{
  using namespace vcsn;

  tests::Tester t(tg);

  unsigned nb_succeed = 0;
  unsigned test_num = 8;

  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);

  //
  // Build the test automaton.
  //

  alphabet_t A;

  A.insert(static_cast<letter_t>('a'));
  A.insert(static_cast<letter_t>('b'));

  automaton_t S = rw_transducer::make_automaton(A, A);

  monoid_elt_t in_e(S.series().monoid());
  monoid_elt_t in_a(S.series().monoid(), static_cast<letter_t>('a'));
  monoid_elt_t in_b(S.series().monoid(), static_cast<letter_t>('b'));

  monoid_elt_t out_e(S.series().monoid());
  monoid_elt_t out_a(S.series().semiring().monoid(), static_cast<letter_t>('a'));
  monoid_elt_t out_b(S.series().semiring().monoid(), static_cast<letter_t>('b'));

  hstate_t s0 = S.add_state();
  hstate_t s1 = S.add_state();
  hstate_t s2 = S.add_state();
  hstate_t s3 = S.add_state();

  S.set_initial(s0);
  S.set_o_initial(s1, out_b);
  S.set_final(s0);
  S.set_o_final(s2, out_a);

  S.add_io_transition(s0, s2, in_a, out_e);
  S.add_io_transition(s3, s2, in_b, out_e);
  S.add_io_transition(s1, s0, in_b, out_e);
  S.add_io_transition(s1, s3, in_a, out_e);

  S.add_io_transition(s1, s1, in_b, out_b);
  S.add_io_transition(s2, s2, in_a, out_a);
  S.add_io_transition(s3, s3, in_a, out_a);
  S.add_io_transition(s3, s3, in_b, out_b);

  //
  // Run the tests.
  //

  // Type helpers.
  typedef series_set_elt_t exp_t;
  typedef typename series_set_elt_t::semiring_elt_t output_exp_t;
  typedef std::set<std::pair<hstate_t, output_exp_t> > state_exp_pair_set_t;

  output_exp_t ser_e(S.series().semiring());
  ser_e.assoc(in_e, true);
  output_exp_t ser_a(S.series().semiring());
  ser_a.assoc(in_a, true);
  output_exp_t ser_b(S.series().semiring());
  ser_b.assoc(in_b, true);

  state_exp_pair_set_t sep_set;

  for (int j = 0; j < 2; ++j)
  {
    monoid_elt_t x(S.series().monoid(), static_cast<letter_t>('a' + j));
    output_exp_t E(S.series().semiring());
    E.assoc(x, true);
    for (int i = 0; i < 4; ++i)
    {
      hstate_t p = S.get_state(i);
      // Run partial evaluation.
      sep_set.clear();
      partial_evaluation(E, S, p, sep_set);

      // Check against reference.

# define CHECK_LINE(idx, st, exp) (((*(idx(sep_set.begin()))).first == S.get_state(st)) && ((*(idx(sep_set.begin()))).second == ser_##exp))

      if (j == 0)
      {
	if (i == 0 && sep_set.size() == 1 && CHECK_LINE(, 2, e))
	  nb_succeed++;
	else if (i == 1 && sep_set.size() == 1 && CHECK_LINE(, 3, e))
	  nb_succeed++;
	else if (i == 2 && sep_set.size() == 1 && CHECK_LINE(, 2, a))
	  nb_succeed++;
	else if (i == 3 && sep_set.size() == 1 && CHECK_LINE(, 3, a))
	  nb_succeed++;
      }
      else if (j == 1)
      {
	if (i == 0 && sep_set.size() == 0)
	  nb_succeed++;
	else if (i == 1 && sep_set.size() == 2 && (CHECK_LINE(, 1, b) || CHECK_LINE(++, 1, b))
		 && (CHECK_LINE(++, 0, e) || CHECK_LINE(, 0, e)))
	  nb_succeed++;
	else if (i == 2 && sep_set.size() == 0)
	  nb_succeed++;
	else if (i == 3 && sep_set.size() == 2 && (CHECK_LINE(, 3, b) || CHECK_LINE(++, 3, b))
		 && (CHECK_LINE(++, 2, e) || CHECK_LINE(, 2, e)))
	  nb_succeed++;
      }

# undef CHECK_LINE

    }
  }

  // Status.
  std::string rate;
  SUCCESS_RATE(rate, nb_succeed, test_num);
  TEST(t, "Partial evaluation on RW transducers. " + rate, nb_succeed == test_num);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_PARTIAL_EVALUATION_TEST_HH
