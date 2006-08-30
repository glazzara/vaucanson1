// concat_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CONCAT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CONCAT_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/concatenate.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/automata/implementation/generalized.hh>

template <class Auto>
bool concat_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;

  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_t;
  AUTOMATON_TYPES_(generalized_t, g_);

  unsigned int nb_test_done = 0;
  unsigned int size    = 0;
  tests::Tester t(tg);
  unsigned test_num = t.test_num();

  GenRandomAutomata<Auto> gen;
  for (unsigned i = 0; i < test_num; ++i)
    {
      automaton_t auto_lhs = gen.generate_with_epsilon(5, 10, 3, 7);
      automaton_t auto_rhs = gen.generate_with_epsilon(auto_lhs.structure(),
						       5, 10, 3, 7);
      generalized_t g_auto_lhs = generalized(auto_lhs);
      generalized_t g_auto_rhs = generalized(auto_rhs);
      g_series_set_elt_t exp_lhs(g_auto_lhs.structure().series());
      g_series_set_elt_t exp_rhs(g_auto_rhs.structure().series());
      exp_lhs = aut_to_exp(g_auto_lhs);
      exp_rhs = aut_to_exp(g_auto_rhs);
      monoid_elt_t word_1 = exp_lhs.choose_from_supp();
      monoid_elt_t word_2 = exp_rhs.choose_from_supp();
      monoid_elt_t word = word_1 * word_2;

      try
	{
	  automaton_t ret = concatenate(auto_lhs, auto_rhs);
	  semiring_elt_t val =
	    eval(determinize(realtime(auto_lhs)), word_1) *
	    eval(determinize(realtime(auto_rhs)), word_2);
	  if (ret.states().size() ==
	      auto_lhs.states().size() + auto_rhs.states().size() &&
	      eval(determinize(realtime(ret)), word) == val)
	    ++size;
	  else
	    {
	      TEST_FAIL_SAVE("concat",
			     i,
			     "concatenation of automata corresponding"
			     << "to following expressions failed."
			     << std::endl
			     << exp_lhs << " and " << exp_rhs
			     << std::endl);
	    }
	  ++nb_test_done;
	}
      catch (std::logic_error&)
	{
	  ++test_num;
	}
    }

  std::string size_rate;
  SUCCESS_RATE(size_rate, size, nb_test_done);
  TEST(t, "Concatenation of two automata." + size_rate,
       size == nb_test_done);
  // FIXME: add tests based on samples from the languages.
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CONCAT_TEST_HH
