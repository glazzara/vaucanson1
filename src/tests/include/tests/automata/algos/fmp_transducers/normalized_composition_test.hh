// normalized_composition_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_NORMALIZED_COMPOSITION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_NORMALIZED_COMPOSITION_TEST_HH

# include <vaucanson/algorithms/normalized_composition.hh>
# include <vaucanson/algorithms/fmp_to_realtime.hh>
# include <vaucanson/algorithms/internal/evaluation.hh>
# include <vaucanson/boolean_transducer.hh>
# include <vaucanson/boolean_automaton.hh>

template <class Automaton>
bool
normalized_composition_test(tests::Tester& t)
{
  using namespace vcsn;

  AUTOMATON_TYPES(Automaton);

  typedef typename monoid_t::first_monoid_t	first_monoid_t;
  typedef typename monoid_t::second_monoid_t	second_monoid_t;
  typedef typename first_monoid_t::alphabet_t	first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t	second_alphabet_t;

  first_alphabet_t first_at;
  first_at.insert('a');
  first_at.insert('b');

  second_alphabet_t second_at;
  second_at.insert('x');
  second_at.insert('y');

  second_alphabet_t third_at;
  third_at.insert('u');
  third_at.insert('v');

  first_monoid_t  first_md (first_at);
  second_monoid_t second_md (second_at);
  second_monoid_t third_md (third_at);

  monoid_t fmp(first_md, second_md);
  monoid_t fmp2(second_md, third_md);
  monoid_t fmp3(first_md, third_md);

  semiring_t sg;

  series_set_t ss (sg, fmp);
  series_set_t ss2 (sg, fmp2);
  series_set_t ss3 (sg, fmp3);

  automata_set_t aa (ss);
  automata_set_t aa2 (ss2);
  automata_set_t aa3 (ss3);

  automaton_t t1(aa);
  automaton_t t2(aa2);
  automaton_t t3(aa3);

  series_set_elt_t series_elt1(ss);
  series_set_elt_t series_elt2(ss);
  series_set_elt_t series_elt3(ss);
  series_set_elt_t series_elt4(ss);

  series_set_elt_t series_elt21(ss);
  series_set_elt_t series_elt22(ss);
  series_set_elt_t series_elt23(ss);
  series_set_elt_t series_elt24(ss);

  monoid_elt_value_t fmp_elt1 ("a", "");
  monoid_elt_value_t fmp_elt2 ("b", "");
  monoid_elt_value_t fmp_elt3 ("", "y");
  monoid_elt_value_t fmp_elt4 ("", "x");

  monoid_elt_value_t fmp_elt21 ("", "u");
  monoid_elt_value_t fmp_elt22 ("x", "");
  monoid_elt_value_t fmp_elt23 ("y", "");
  monoid_elt_value_t fmp_elt24 ("", "v");

  semiring_elt_value_t	semi_elt =
    algebra::identity_as<semiring_elt_value_t>::of(sg).value();

  series_elt1.assoc(fmp_elt1, semi_elt);
  series_elt2.assoc(fmp_elt2, semi_elt);
  series_elt3.assoc(fmp_elt3, semi_elt);
  series_elt4.assoc(fmp_elt4, semi_elt);

  series_elt21.assoc(fmp_elt21, semi_elt);
  series_elt22.assoc(fmp_elt22, semi_elt);
  series_elt23.assoc(fmp_elt23, semi_elt);
  series_elt24.assoc(fmp_elt24, semi_elt);

  hstate_t st1 = t1.add_state();
  hstate_t st2 = t1.add_state();
  hstate_t st3 = t1.add_state();

  hstate_t st21 = t2.add_state();
  hstate_t st22 = t2.add_state();
  hstate_t st23 = t2.add_state();


  t1.set_initial(st1);
  t1.set_final(st2);
  t1.set_final(st1);

  t2.set_initial(st21);
  t2.set_initial(st23);
  t2.set_final(st21);

  htransition_t h1 = t1.add_series_transition(st1, st2, series_elt1);
  htransition_t h2 = t1.add_series_transition(st2, st1, series_elt3);
  htransition_t h3 = t1.add_series_transition(st1, st3, series_elt4);
  htransition_t h4 = t1.add_series_transition(st3, st1, series_elt2);

  htransition_t h21 = t2.add_series_transition(st21, st22, series_elt23);
  htransition_t h22 = t2.add_series_transition(st22, st21, series_elt21);
  htransition_t h23 = t2.add_series_transition(st21, st23, series_elt24);
  htransition_t h24 = t2.add_series_transition(st23, st21, series_elt22);

  t3 = compose(t1, t2);

  boolean_transducer::automaton_t trans1 =
    boolean_transducer::make_automaton(first_at, second_at);

  boolean_transducer::automaton_t trans2 =
    boolean_transducer::make_automaton(second_at, third_at);

  boolean_transducer::automaton_t trans3 =
    boolean_transducer::make_automaton(first_at, third_at);

  fmp_to_realtime(t1, trans1);
  realtime_here(trans1);
  fmp_to_realtime(t2, trans2);
  realtime_here(trans2);
  fmp_to_realtime(t3, trans3);
  realtime_here(trans3);

  boolean_automaton::rat_exp_t exp =
    boolean_automaton::make_rat_exp(first_at, "abbababa");

  TEST(t, "Normalized composition works.",
       (boolean_transducer::evaluation(trans3, exp) ==
	boolean_transducer::evaluation(trans2,
				       boolean_transducer::evaluation(trans1,
								      exp))));

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_NORMALIZED_COMPOSITION_TEST_HH
