// evaluation_fmp_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_EVALUATION_FMP_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_EVALUATION_FMP_TEST_HH

# include <vaucanson/algorithms/evaluation_fmp.hh>
# include <vaucanson/algorithms/fmp_to_realtime.hh>
# include <vaucanson/algorithms/evaluation.hh>
# include <vaucanson/boolean_transducer.hh>
# include <vaucanson/boolean_automaton.hh>


template <class Automaton>
bool
evaluation_fmp_test(tests::Tester& t)
{
  using namespace vcsn;
  AUTOMATON_TYPES(Automaton);

  typedef typename monoid_t::first_monoid_t	first_monoid_t;
  typedef typename monoid_t::second_monoid_t	second_monoid_t;
  typedef typename first_monoid_t::alphabet_t	first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t	second_alphabet_t;

  first_alphabet_t		first_at;
  first_at.insert('a');
  first_at.insert('b');

  second_alphabet_t		second_at;
  second_at.insert('x');
  second_at.insert('y');

  first_monoid_t		first_md (first_at);
  second_monoid_t		second_md (second_at);

  monoid_t			fmp(first_md, second_md);

  semiring_t			sg;

  series_set_t			ss (sg, fmp);

  automata_set_t		aa (ss);

  automaton_t			t1(aa);

  series_set_elt_t		series_elt1(ss);
  series_set_elt_t		series_elt2(ss);
  series_set_elt_t		series_elt3(ss);
  series_set_elt_t		series_elt4(ss);

  monoid_elt_value_t	fmp_elt1 ("a", "");
  monoid_elt_value_t	fmp_elt2 ("b", "x");
  monoid_elt_value_t	fmp_elt3 ("a", "y");
  monoid_elt_value_t	fmp_elt4 ("", "x");

  semiring_elt_value_t	semi_elt =
    algebra::identity_as<semiring_elt_value_t>::of(sg).value();

  series_elt1.assoc(fmp_elt1, semi_elt);
  series_elt2.assoc(fmp_elt2, semi_elt);
  series_elt3.assoc(fmp_elt3, semi_elt);
  series_elt4.assoc(fmp_elt4, semi_elt);

  hstate_t	st1 = t1.add_state();
  hstate_t	st2 = t1.add_state();
  hstate_t	st3 = t1.add_state();

  t1.set_initial(st1);
  t1.set_final(st3);

  htransition_t	h1 = t1.add_series_transition(st1, st2, series_elt1);
  htransition_t	h2 = t1.add_series_transition(st2, st3, series_elt2);
  htransition_t	h3 = t1.add_series_transition(st1, st2, series_elt3);
  htransition_t	h4 = t1.add_series_transition(st1, st3, series_elt4);


  boolean_transducer::automaton_t trans1 =
    boolean_transducer::make_automaton(first_at, second_at);

  fmp_to_realtime(t1, trans1);

  boolean_automaton::rat_exp_t exp =
    boolean_automaton::make_rat_exp(first_at, "abbababa");

  boolean_automaton::automaton_t res_aut =
    boolean_automaton::make_automaton(second_at);

  evaluation_fmp(t1, boolean_automaton::standard_of(exp), res_aut);

  boolean_automaton::rat_exp_t exp_res1 =
    boolean_transducer::evaluation(trans1, exp);
  boolean_automaton::rat_exp_t exp_res2 = aut_to_exp(res_aut);


  TEST(t, "Fmp evaluation works.", (exp_res1 == exp_res2));

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_EVALUATION_FMP_TEST_HH
