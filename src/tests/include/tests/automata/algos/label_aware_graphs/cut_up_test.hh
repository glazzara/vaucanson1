// cut_up_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CUT_UP_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CUT_UP_TEST_HH

# include <vaucanson/algorithms/cut_up.hh>

template <class Auto>
bool cut_up_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester t(tg);

  alphabet_t		at;
  letter_t		la = at.random_letter();
  at.insert(la);
  letter_t		lb = at.random_letter();
  while (at.contains(lb))
    lb = at.random_letter();
  at.insert(lb);
  letter_t		lc = at.random_letter();
  while (at.contains(lc))
    lc = at.random_letter();
  at.insert(lc);

  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);
  automaton_t		a (aa);

  hstate_t s0 = a.add_state();
  hstate_t s1 = a.add_state();
  hstate_t s2 = a.add_state();

  automaton_t a1(a.structure());
  automaton_t a2(a.structure());
  automaton_t a3(a.structure());

  series_set_elt_t ss0(a.structure().series());
  series_set_elt_t ss1(a.structure().series());
  series_set_elt_t ss2(a.structure().series());
  series_set_elt_t ss3(a.structure().series());

  using vcsn::algebra::identity_as;

  semiring_elt_t w(a.structure().series().semiring(),
		   identity_as<semiring_elt_value_t>::of(sg));

  monoid_elt_t m0(a.structure().series().monoid(), la);
  monoid_elt_t m1(a.structure().series().monoid(), lb);
  monoid_elt_t m2(a.structure().series().monoid(), lc);

  // Series ss0 has 2 elements.
  ss0.assoc(m0, w);
  ss0.assoc(m1, w);

  // Series ss1 has 2 elements.
  ss1.assoc(m0, w);
  ss1.assoc(m1, w);

  // Series ss2 has 3 elements.
  ss2.assoc(m0, w);
  ss2.assoc(m1, w);
  ss2.assoc(m2, w);

  // Series ss3 has 1 elements.
  ss3.assoc(m0, w);

  // Create transitions.
  a.add_series_transition(s0, s1, ss0);
  a.add_series_transition(s1, s2, ss1);
  a1 = cut_up(a);

  a.add_series_transition(s1, s2, ss2);
  a2 = cut_up(a);

  a.add_series_transition(s0, s1, ss3);
  a3 = cut_up(a);

  TEST(t, "Cut-up (Polynomial series labeled graph) (1/3)",
       is_cut_up(a1) 
       && a1.states().size() == 3
       && a1.transitions().size() == 4);

  TEST(t, "Cut-up (Polynomial series labeled graph) (2/3)",
       is_cut_up(a2)
       && a2.states().size() == 3
       && a2.transitions().size() == 7);
  TEST(t, "Cut-up (Polynomial series labeled graph) (3/3)",
       is_cut_up(a3)
       && a3.states().size() == 3
       && a3.transitions().size() == 8);

  typedef typename vcsn::generalized_traits<automaton_t>::automaton_t
    gen_automaton_t;

  gen_automaton_t gena(a.structure());
  gen_automaton_t gena1(gena.structure());

  typename gen_automaton_t::hstate_t gs0 = gena.add_state();
  typename gen_automaton_t::hstate_t gs1 = gena.add_state();
  typename gen_automaton_t::hstate_t gs2 = gena.add_state();

  gena.add_series_transition(gs0, gs1, ss1);
  gena.add_series_transition(gs0, gs1, ss2);
  gena.add_series_transition(gs1, gs2, ss3);

  gena1 = cut_up(gena);

  TEST(t, "Cut-up (Rational series labeled graph)   (1/1)",
       is_cut_up(gena1)
       && gena1.states().size() == 10
       && gena1.transitions().size() == 13);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CUT_UP_TEST_HH
