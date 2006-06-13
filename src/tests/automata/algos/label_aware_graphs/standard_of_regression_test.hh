// standard_of_regression_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_STANDARD_OF_REGRESSION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_STANDARD_OF_REGRESSION_TEST_HH

# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/algorithms/eval.hh>
# include <vaucanson/tools/usual_macros.hh>

template <class Auto>
bool
standard_of_regression_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester t (tg.verbose());

  alphabet_t		at;
  letter_t		la = at.random_letter();
  at.insert(la);
  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  using vcsn::algebra::identity_as;
  using vcsn::algebra::zero_as;

  monoid_elt_t		ma (md, la);
  krat_t		a (ss, ma);
  semiring_elt_t	w (sg);
  do
    w = sg.choose(SELECT(semiring_elt_value_t));
  while (w == zero_as<semiring_elt_value_t>::of(sg)) ;

  krat_t e = a.star() * w; // WARNING: star() has side effects on a!

  automaton_t		au (aa);
  standard_of(au, e.value());

  TEST_MSG("Tests on \"a* w\".");
  TEST(t, "Number of states", au.states().size() == 2);
  TEST(t, "Number of initial states", au.initial().size() == 1);
  TEST(t, "Number of final states", au.final().size() == 2);
  TEST(t, "Number of transitions", au.transitions().size() == 2);

  bool b (true);
  for_all_initial_states(i, au)
    b = b and
    au.get_initial(*i) == identity_as<series_set_elt_value_t>::of(ss);
  TEST(t, "Weight of initials", b);

  b = true;
  for_all_transitions(e, au)
    b = b and au.series_of(*e) == series_set_elt_t (ss, ma);
  TEST(t, "Weight of transitions", b);

  b = true;
  for_all_final_states(f, au)
    b = b and au.get_final(*f) == series_set_elt_t (ss, w);
  TEST(t, "Weight of finals", b);

  TEST_MSG("Tests on \"(w a*)(w a*)\".");

  e = (w * a) * (w * a);
  standard_of(au, e.value());

  TEST(t, "Evaluation of 1 gives w * w.",
       eval(au, monoid_elt_t (md)) == w * w);

  TEST(t, "Evaluation of a gives w * w + w * w.",
       eval(au, ma) == w * w + w * w);

  TEST(t, "Evaluation of aa gives w * w + w * w + w * w.",
       eval(au, ma * ma) == w * w + w * w + w * w);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_STANDARD_OF_REGRESSION_TEST_HH
