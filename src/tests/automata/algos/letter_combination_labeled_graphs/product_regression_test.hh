// product_regression_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_PRODUCT_REGRESSION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_PRODUCT_REGRESSION_TEST_HH

# include <vaucanson/algorithms/product.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <ostream>

template <class Auto>
unsigned
product_regression_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);
  using vcsn::hstate_t;

  tests::Tester t(tg.verbose());

  alphabet_t	at;
  letter_t	l1 = at.random_letter();
  letter_t	l2;
  do
    l2 = at.random_letter();
  while (l1 == l2) ;
  at.insert(l1);
  at.insert(l2);

  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  automaton_t	lhs (aa);
  hstate_t	s1 = lhs.add_state();
  hstate_t	s2 = lhs.add_state();
  lhs.add_letter_edge(s1, s2, l1);
  lhs.set_initial(s1);
  lhs.set_final(s2);

  automaton_t	rhs (aa);
  s1 = rhs.add_state();
  s2 = rhs.add_state();
  rhs.add_letter_edge(s1, s2, l2);
  rhs.set_initial(s1);
  rhs.set_final(s2);

  automaton_t prod = product(lhs, rhs);

  TEST(t,"Regression test for product() [1/4].", prod.states().size() == 1);
  TEST(t,"Regression test for product() [2/4].", prod.initial().size() == 1);
  TEST(t,"Regression test for product() [3/4].", prod.final().size() == 0);
  TEST(t,"Regression test for product() [4/4].", prod.edges().size() == 0);

  if (not t.all_passed())
    {
      TEST_MSG("Automaton saved in /tmp.");
      SAVE_AUTOMATON_DOT("/tmp", "product_regression_test", prod, 0);
    }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_PRODUCT_REGRESSION_TEST_HH
