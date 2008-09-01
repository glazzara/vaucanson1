// in_concat_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_IN_CONCAT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_IN_CONCAT_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/concatenate.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/algorithms/realtime.hh>

template <class Auto>
bool in_concat_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::algebra;

  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_t;
  AUTOMATON_TYPES_(generalized_t, g_);

  unsigned int nb_test_done = 0;
  unsigned int size    = 0;
  tests::Tester t(tg);

  GenRandomAutomata<Auto> gen;
  unsigned test_num = t.test_num();
  for (unsigned i = 0; i < test_num; ++i)
    {
      automaton_t auto_lhs = gen.generate_with_epsilon(5, 10, 3, 7);
      automaton_t auto_rhs = gen.generate_with_epsilon(auto_lhs.structure(),
						       5, 10, 3, 7);
      int lhs_states_num = auto_lhs.states().size();
      generalized_t g_auto_lhs = generalized(auto_lhs);
      generalized_t g_auto_rhs = generalized(auto_rhs);
      g_series_set_elt_t exp_lhs(g_auto_lhs.structure().series());
      g_series_set_elt_t exp_rhs(g_auto_rhs.structure().series());
      exp_lhs = aut_to_exp(g_auto_lhs);
      exp_rhs = aut_to_exp(g_auto_rhs);

      monoid_elt_t word = (exp_lhs * exp_rhs).choose_from_supp();

      try
	{
	  concatenate_here(auto_lhs, auto_rhs);
	  if (auto_lhs.states().size() ==
	      lhs_states_num + auto_rhs.states().size() &&
	      eval(realtime(auto_lhs), word) !=
	      zero_as<semiring_elt_value_t>::of(auto_lhs.structure().series().semiring()))
	    ++size;
	  else
	    {
	      TEST_FAIL_SAVE("in_concat",
			     i,
			     "concatenation of automata corresponding"
			     << "to following expressions failed."
			     << std::endl
			     << exp_lhs << " and " << exp_rhs << std::endl);
	    }
	  ++nb_test_done;
	}
      catch (std::logic_error& e)
      {
	std::cout << e.what() << std::endl;
	std::cout << "Trying again..." << std::endl;
	++test_num;
      }
      catch (...)
      {
	std::cout << "Unexpected exception!" << std::endl;
	++nb_test_done;
      }
    }

  std::string size_rate;
  SUCCESS_RATE(size_rate, size, nb_test_done);
  TEST(t, "In place concatenation of two automata." + size_rate,
       size == nb_test_done);
  // FIXME: add tests based on samples from the languages.
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_IN_CONCAT_TEST_HH
