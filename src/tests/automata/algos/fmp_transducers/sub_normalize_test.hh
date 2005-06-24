// sub_normalize_test.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_SUB_NORMALIZE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_SUB_NORMALIZE_TEST_HH

# include <vaucanson/algorithms/sub_normalize.hh>

using namespace vcsn;


template <class Automaton>
bool
sub_normalize_test(tests::Tester& t)
{

  AUTOMATON_TYPES(Automaton);

  typedef typename monoid_t::first_monoid_t	first_monoid_t;
  typedef typename monoid_t::second_monoid_t	second_monoid_t;
  typedef typename first_monoid_t::alphabet_t	first_alphabet_t;
  typedef typename second_monoid_t::alphabet_t	second_alphabet_t;

  first_alphabet_t	alpha1;
  alpha1.insert('a');
  alpha1.insert('b');

  second_alphabet_t	alpha2;
  alpha2.insert('x');
  alpha2.insert('y');

  first_monoid_t	first_md(alpha1);
  second_monoid_t	second_md(alpha2);

  monoid_t		fmp(first_md, second_md);
  semiring_t		sg;

  series_set_t		ss(sg, fmp);

  automata_set_t	aa(ss);

  automaton_t		t1(aa);
  automaton_t		t2(aa);

  series_set_elt_t	series_elt1(ss);
  series_set_elt_t	series_elt2(ss);
  series_set_elt_t	series_elt3(ss);
  series_set_elt_t	series_elt4(ss);
  series_set_elt_t	series_elt5(ss);

  monoid_elt_value_t	fmp_elt1("aba", "");
  monoid_elt_value_t	fmp_elt2("baba", "xyxy");
  monoid_elt_value_t	fmp_elt3("bab", "yxxy");
  monoid_elt_value_t	fmp_elt4("", "xy");
  monoid_elt_value_t	fmp_elt5("aa", "xx");

  semiring_elt_value_t	semi_elt =
    algebra::identity_as<semiring_elt_value_t>::of(sg).value();

  series_elt1.assoc(fmp_elt1, semi_elt);
  series_elt2.assoc(fmp_elt2, semi_elt);
  series_elt3.assoc(fmp_elt3, semi_elt);
  series_elt4.assoc(fmp_elt4, semi_elt);
  series_elt5.assoc(fmp_elt5, semi_elt);

  hstate_t	s0 = t1.add_state();
  hstate_t	s1 = t1.add_state();
  hstate_t	s2 = t1.add_state();

  t1.set_initial(s0, series_elt1);
  t1.set_final(s2, series_elt4);

  t1.add_series_edge(s0, s1, series_elt2);
  t1.add_series_edge(s0, s0, series_elt5);
  t1.add_series_edge(s1, s2, series_elt3);
  t1.add_series_edge(s1, s1, series_elt5);
  t1.add_series_edge(s2, s2, series_elt5);
  t1.add_series_edge(s2, s0, series_elt2);

  t2 = sub_normalize(t1);

  TEST(t, "Sub-normalization of FMP transducers",
       (! is_sub_normalized(t1)) && is_sub_normalized(t2)
       && t2.states().size() == 18 && t2.edges().size() == 21);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_FMP_TRANSDUCERS_SUB_NORMALIZE_TEST_HH
