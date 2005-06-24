// elimination_dmheuristic_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_ELIMINATION_DMHEURISTIC_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_ELIMINATION_DMHEURISTIC_TEST_HH

# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/implementation/generalized.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/algorithms/eval.hh>

using namespace vcsn;

template <class Auto>
bool elimination_dmheuristic_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());
  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_automaton_t;
  AUTOMATON_TYPES_(generalized_automaton_t, g);

  GenRandomAutomata<Auto> gen(time(0));
  unsigned success      = 0;
  unsigned nb_test      = 50;
  unsigned nb_word_test = 100;

  for (unsigned nb = 0; nb < nb_test; ++nb)
    {
      Auto	a = gen.generate(5,10, 2, 2);
      generalized_automaton_t a_ = generalized(a);
      gseries_set_elt_t language (a_.structure().series());
      language = aut_to_exp(a_, DMChooser());
      if (t.verbose() == tests::high)
      {
	TEST_MSG("Automaton saved in /tmp.");
	SAVE_AUTOMATON_DOT("/tmp", "aut_to_exp_DMheuristic", a, nb);
      }
      unsigned i = 0;
      for (; i < nb_word_test; ++i)
      {
	monoid_elt_t w = language.choose_from_supp();
	if (t.verbose() == tests::high)
	  std::cout << "TEST: aut_to_exp_DMheuristic " << nb << " : test "
		    << w << std::endl;
	if (eval(a, w) ==
	    zero_as<semiring_elt_value_t>::of(a.structure().series().semiring()))
	{
	  break;
	  if (t.verbose() == tests::high)
	    std::cout << "TEST: aut_to_exp_DMheuristic " << nb
		      << " failed." << std::endl;
	}
      }
      if (i == nb_word_test)
	++success;
    }
  std::string rate;
  SUCCESS_RATE(rate, success, nb_test);
  TEST(t, "aut_to_exp, Delgado-Morais heuristic, basic test " + rate, success == nb_test);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_ELIMINATION_DMHEURISTIC_TEST_HH
