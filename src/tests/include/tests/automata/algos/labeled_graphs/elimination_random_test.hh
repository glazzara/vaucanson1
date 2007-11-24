// elimination_random_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_ELIMINATION_RANDOM_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_ELIMINATION_RANDOM_TEST_HH

# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/implementation/generalized.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/algorithms/eval.hh>

using namespace vcsn;
using namespace vcsn::tools;

template <class Auto>
bool elimination_random_test(tests::Tester& tg)
{
  tests::Tester t(tg);
  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_automaton_t;
  AUTOMATON_TYPES_(generalized_automaton_t, g);

  GenRandomAutomata<Auto> gen;
  unsigned success      = 0;
  unsigned nb_word_test = 100;

  for (unsigned nb = 0; nb < t.test_num(); ++nb)
    {
      Auto	a = gen.generate(5,10, 2, 2);
      generalized_automaton_t a_ = generalized(a);
      gseries_set_elt_t language (a_.structure().series());
      language = aut_to_exp(a_, RandomChooser());
      if (t.verbose(tests::Tester::high))
	SAVE_AUTOMATON_XML("/tmp", "aut_to_exp_random", a, nb);
      unsigned i = 0;
      for (; i < nb_word_test; ++i)
	{
	  monoid_elt_t w = language.choose_from_supp();
	  if (t.verbose(tests::Tester::high))
	    std::cerr << "TEST: aut_to_exp_random " << nb << " : test "
		      << w << std::endl;
	  if (eval(a, w) ==
	      zero_as<semiring_elt_value_t>::of(a.structure().series().semiring()))
	    {
	      break;
	      if (t.verbose(tests::Tester::high))
		std::cerr << "TEST: aut_to_exp_random " << nb
			  << " failed." << std::endl;
	    }
	}
      if (i == nb_word_test)
	++success;
    }
  std::string rate;
  SUCCESS_RATE(rate, success, t.test_num());
  TEST(t, "aut_to_exp, with random chooser, basic test " + rate, success == t.test_num());
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABELED_GRAPHS_ELIMINATION_RANDOM_TEST_HH
