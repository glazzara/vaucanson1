// sum_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_SUM_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_SUM_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/sum.hh>
# include <time.h>

# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/automata/implementation/generalized.hh>


using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned sum_test(tests::Tester& tg)
{
  typedef Auto automaton_t;
  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_t;
  AUTOMATON_TYPES_(generalized_t, g_);

  tests::Tester t(tg.verbose());

  GenRandomAutomata<automaton_t> gen(time(0x0));

  unsigned	nb_tests       = 10;
  unsigned	success_states = 0;
  unsigned	success_transitions  = 0;

  unsigned	nb_tests_sum = 10;
  unsigned	nb_tests_sum_done = 0;
  unsigned	success_sum = 0;
  unsigned	iter;

  for (unsigned j = 0; j < nb_tests_sum; ++j)
  {
    iter = 0;
    automaton_t auto_lhs = gen.generate_with_epsilon(5, 10, 1, 3);
    automaton_t auto_rhs = gen.generate_with_epsilon(auto_lhs.structure(),
						     5, 10, 1, 3);
    generalized_t g_auto_lhs = generalized(auto_lhs);
    generalized_t g_auto_rhs = generalized(auto_rhs);
    g_series_set_elt_t exp_lhs(g_auto_lhs.structure().series());
    g_series_set_elt_t exp_rhs(g_auto_rhs.structure().series());
    exp_lhs = aut_to_exp(g_auto_lhs);
    exp_rhs = aut_to_exp(g_auto_rhs);

    try
    {
      generalized_t g_rhs_r = realtime(g_auto_rhs);
      semiring_elt_t semiring_zero =
	zero_as<semiring_elt_value_t>::of(g_rhs_r.structure().series().semiring());

      automaton_t s = sum(auto_lhs, auto_rhs);

      monoid_elt_t word_lhs_unknown = exp_lhs.choose_from_supp();

      // Regenerate automata if 20 choose_from_supp didn't gave a valid test
      // word (auto_lhs can be equal to auto_rhs).
      while (++iter < 20 &&
	     eval(g_rhs_r, word_lhs_unknown) != semiring_zero)
	word_lhs_unknown = exp_lhs.choose_from_supp();

      if (iter < 20)
      {
	if (eval(realtime(s), word_lhs_unknown) != semiring_zero)
	  ++success_sum;
	else
	{
	  TEST_FAIL_SAVE("sum",
			 j,
			 "in union of "
			 << exp_lhs
			 << " and "
			 << exp_rhs
			 << std::endl);
	}
	++nb_tests_sum_done;
      }
      else
	++nb_tests_sum;
    }
    catch (std::logic_error&)
    {
      ++nb_tests_sum;
    }
  }
  std::string rate_sum;
  SUCCESS_RATE(rate_sum, success_sum, nb_tests_sum_done);
  TEST(t, "Union of automata " + rate_sum, nb_tests_sum_done == success_sum);

  for (unsigned i = 0 ; i < nb_tests; i++)
  {
    automaton_t a = gen.generate(20, 40);
    automaton_t b = gen.generate(10, 20);
    automaton_t c = sum(a, b);

    if (a.states().size() + b.states().size() == c.states().size())
      ++success_states;
    if (a.transitions().size() + b.transitions().size() == c.transitions().size())
      ++success_transitions;
  }
  std::string rate_states, rate_transitions;
  SUCCESS_RATE(rate_states, success_states, nb_tests);
  SUCCESS_RATE(rate_transitions, success_transitions, nb_tests);
  TEST(t, "Union basic tests (transitions: " + rate_transitions
       + ", states: " + rate_states + ")",
       ((nb_tests == success_transitions) && (nb_tests == success_states)));
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_SUM_TEST_HH
