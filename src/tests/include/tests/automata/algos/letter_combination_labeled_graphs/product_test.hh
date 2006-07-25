// product_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_PRODUCT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_PRODUCT_TEST_HH

# include <time.h>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/product.hh>
# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/algorithms/complement.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/trim.hh>

# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/automata/implementation/generalized.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned product_test(tests::Tester& tg)
{
  typedef Auto automaton_t;
  GenRandomAutomata<automaton_t> gen(time(0x0));
  tests::Tester t(tg.verbose());

  // Battery 1.
  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_t;
  AUTOMATON_TYPES_(generalized_t, g_);

  unsigned nb_test_product = 20;
  unsigned nb_test_product_done = 0;
  unsigned success_product = 0;

  for (unsigned cpt = 0; cpt < nb_test_product; ++cpt)
  {
    automaton_t auto_lhs = gen.generate(3, 6, 1, 2, 2);
    automaton_t auto_rhs = gen.generate(auto_lhs.structure(),
					3, 6, 1, 2);
    automaton_t p = product(auto_lhs, auto_rhs);
    // if the intersection is empty, regenerate a test.
    if (p.final().size() == 0)
    {
      ++nb_test_product;
      continue;
    }

    generalized_t g_p = generalized(p);
    g_series_set_elt_t exp_p(g_p.structure().series());
    exp_p = aut_to_exp(g_p);

    monoid_elt_t word_prod = exp_p.choose_from_supp();
    const semiring_elt_t wzero = auto_lhs.series().semiring().wzero_;

    if (eval(auto_lhs, word_prod) == wzero or
        eval(auto_rhs, word_prod) == wzero)
    {
      // Print the failing expressions.
      generalized_t g_auto_lhs = generalized(auto_lhs);
      generalized_t g_auto_rhs = generalized(auto_rhs);
      g_series_set_elt_t exp_lhs(g_auto_lhs.structure().series());
      g_series_set_elt_t exp_rhs(g_auto_rhs.structure().series());
      exp_lhs = aut_to_exp(g_auto_lhs);
      exp_rhs = aut_to_exp(g_auto_rhs);
      TEST_MSG("Automata saved in /tmp.");
      SAVE_AUTOMATON_XML("/tmp", "rhs", auto_rhs, cpt);
      SAVE_AUTOMATON_XML("/tmp", "lhs", auto_lhs, cpt);
      SAVE_AUTOMATON_XML("/tmp", "prod", p, cpt);
      TEST_FAIL_SAVE("product",
		     cpt,
		     "product of automata corresponding"
		     << " to following expressions failed."
		     << std::endl
		     << exp_lhs << " and " << exp_rhs
		     << std::endl
		     << "This word is not recognized by one of the automata "
		     << word_prod
		     << std::endl
		     );
    }
    else
      ++success_product;
    ++nb_test_product_done;
  }

  std::string rate_product;
  SUCCESS_RATE(rate_product, success_product, nb_test_product_done);
  TEST(t,"Product of automata." + rate_product,
       success_product == nb_test_product_done);


  // Battery 2.
  const unsigned nb_test    = 30;
  unsigned success_identity = 0;
  unsigned success_null	    = 0;

  for (unsigned i = 0 ; i < nb_test; i++)
  {
    automaton_t a = gen.generate(10, 20);

    complete_here(a);
    a = determinize(a);
    automaton_t ac = complement(a);
    automaton_t squared = product(a,a);

    if ((squared.states().size() == a.states().size()) &&
	(squared.transitions().size() == a.transitions().size()))
      success_identity++;

    if (trim(product(a, ac)).states().size() == 0)
      success_null++;
  }

  std::string rate_identity;
  std::string rate_null;
  SUCCESS_RATE(rate_identity, success_identity, nb_test);
  TEST(t,"Square of a complete deterministic automaton." + rate_identity,
       success_identity == nb_test);
  SUCCESS_RATE(rate_null, success_null, nb_test);
  TEST(t, "Product of complete automaton and its complementary." +
       rate_null,
       success_null == nb_test);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_PRODUCT_TEST_HH
