// product_test.hh: this file is part of the Vaucanson project.
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

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned product_test(tests::Tester& tg)
{
  typedef Auto automaton_t;
  GenRandomAutomata<automaton_t> gen;
  tests::Tester t(tg);

  /*-------------*
   | Battery 1.  |
   *-------------*/
  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_t;
  AUTOMATON_TYPES_(generalized_t, g_);

  unsigned nb_test_product = 20;
  unsigned nb_test_product_done = 0;
  unsigned success_product = 0;

  for (unsigned cpt = 0; cpt < nb_test_product; ++cpt)
  {
    automaton_t lhs = gen.generate(3, 6, 1, 2, 2);
    automaton_t rhs = gen.generate(lhs.structure(),
				   3, 6, 1, 2);
    automaton_t p = product(lhs, rhs);

    // If the intersection is empty, regenerate a test.
    if (p.final().size() == 0)
    {
      ++nb_test_product;
      continue;
    }

    /*-------------------------------------------*
     | Look for a word accepted by the product.  |
     *-------------------------------------------*/
    generalized_t g_p = generalized(p);
    g_series_set_elt_t exp_p(g_p.structure().series());
    exp_p = aut_to_exp(g_p);
    // This guy is  accepted by the automaton.
    monoid_elt_t word_prod = exp_p.choose_from_supp();

    // We have overflow problems when working on Z, so it does happen
    // that some evaluation lead to incorrect results, including `0',
    // on words that should be accepted.  In this case, there is no
    // chance we can actually test the product, so skip these cases.
    if (eval(p, word_prod) == p.series().semiring().wzero_)
      {
	TEST_MSG("This automata overflows the evaluation, it is saved in /tmp.");
	SAVE_AUTOMATON_XML("/tmp", "product_prod", p, cpt);
	SAVE_AUTOMATON_XML("/tmp", "product_generalized", g_p, cpt);
	TEST_FAIL_SAVE("product",
		       cpt,
		       "element of the support is eval'ed to 0"
		       << std::endl
		       << "word: " << word_prod << std::endl
		       );
	++nb_test_product;
	continue;
      }


    /*-------------------------------------------*
     | The word must accepted by both operands.  |
     *-------------------------------------------*/
    const semiring_elt_t wzero = lhs.series().semiring().wzero_;
    if (eval(lhs, word_prod) == wzero or
	     eval(rhs, word_prod) == wzero)
    {
      SAVE_AUTOMATON_XML("/tmp", "product_rhs", rhs, cpt);
      SAVE_AUTOMATON_XML("/tmp", "product_lhs", lhs, cpt);
      SAVE_AUTOMATON_XML("/tmp", "product_prod", p, cpt);
      TEST_FAIL_SAVE("product",
		     cpt,
		     "The following word is accepted by the product, but rejected by an"
		     " operand."
		     << std::endl
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


  /*-------------*
   | Battery 2.  |
   *-------------*/
  unsigned success_identity = 0;
  unsigned success_null	    = 0;

  for (unsigned i = 0 ; i < t.test_num(); i++)
  {
    automaton_t a = gen.generate(2, 4);

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
  SUCCESS_RATE(rate_identity, success_identity, t.test_num());
  TEST(t,"Square of a complete deterministic automaton." + rate_identity,
       success_identity == t.test_num());
  SUCCESS_RATE(rate_null, success_null, t.test_num());
  TEST(t, "Product of complete automaton and its complementary." +
       rate_null,
       success_null == t.test_num());
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LETTER_COMBINATION_LABELED_GRAPHS_PRODUCT_TEST_HH
