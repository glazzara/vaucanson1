// elimination_test.hh
//
// $Id$
// VCSN_HEADER
#ifndef ELIMINATION_TEST_HH
# define ELIMINATION_TEST_HH

# include <check/tests_stuff.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/automata/concrete/generalized.hh>
# include <vaucanson/algorithms/elimination.hh>
# include <vaucanson/algorithms/compute.hh>

using namespace vcsn;

template <class Auto>
bool elimination_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());
  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_automaton_t;
  AUTOMATON_TYPES_(generalized_automaton_t, g);

  vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
  unsigned success      = 0;
  unsigned nb_test      = 50;
  unsigned nb_word_test = 100;

  for (unsigned nb = 0; nb < nb_test; ++nb)
    {
      Auto	a = gen.generate(5,10, 2, 2);
      generalized_automaton_t a_ = generalized(a);
      gseries_elt_t language;
      language = elimination(a_);
      if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp", "elimination", a, nb);
	}
      unsigned i = 0;
      for (; i < nb_word_test; ++i)
	{
	  monoid_elt_t w = language.choose_from_supp();
	  if (t.verbose() == tests::high)
	    std::cout << "TEST: elimination " << nb << " : test " << w << std::endl;
	  if (compute(a, w) == a.series().zero_)
	    {
	      break;
	      if (t.verbose() == tests::high)
		std::cout << "TEST: elimination " << nb << " failed." << std::endl;
	    }
	}
      if (i == nb_word_test)
	++success;
    }
  std::string rate;
  SUCCESS_RATE(rate, success, nb_test);
  TEST(t, "elimination basic test " + rate, success == nb_test);
  return t.all_passed();
}

#endif // ELIMINATION_TEST_HH
