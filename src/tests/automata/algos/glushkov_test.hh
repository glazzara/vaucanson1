// glushkov_test.hh
//
// $Id$
// VCSN_HEADER
#ifndef GLUSHKOV_TEST_HH
# define GLUSHKOV_TEST_HH

# include <check/tests_stuff.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/automata/concrete/generalized.hh>
# include <vaucanson/algorithms/glushkov.hh>
# include <vaucanson/algorithms/realtime.hh>

using namespace vcsn;

template <class Auto>
bool glushkov_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  typedef rat::exp<monoid_elt_value_t, weight_value_t>	exp_t;
  typedef Element<series_t, exp_t>		krat_t;
  tests::Tester t(tg.verbose());

  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  weights_t semiring;
  series_t s(semiring, monoid);

  unsigned nb_word_test = 100;
  unsigned nb_test = 40;

  {
    TEST_MSG("Basic test on a well known expression.");
    krat_t exp(s);
    krat_t a_e = monoid_elt_t(b);
    exp = monoid_elt_t(a);
    exp = (a_e + exp).star();
    exp = exp * a_e * exp;
    vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
    Auto	au = gen.empty();
    glushkov(au, exp.value());
    in_realtime(au);
    unsigned i = 0;
    for (; i < nb_word_test; ++i)
      {
	monoid_elt_t w = exp.choose_from_supp();
	if (t.verbose() == tests::high)
	  std::cout << "TEST: glushkov " << i << " : test " << w << std::endl;
	if (compute(au, w) == s.zero_)
	  {
	    break;
	    if (t.verbose() == tests::high)
	      std::cout << "TEST: glushkov " << i << " failed." << std::endl;
	  }
      }
    TEST(t, "Basic test ", nb_word_test == i);
  }
  
  {
    TEST_MSG("Tests on random expressions.");
    unsigned success = 0;

    for (unsigned nb = 0; nb < nb_test; ++nb)
      {
	krat_t exp = s.choose(SELECT(exp_t));
	vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
	Auto	au = gen.empty();
	glushkov(au, exp.value());
	in_realtime(au);
	if (t.verbose() == tests::high)
	  {
	    TEST_MSG("Automaton saved in /tmp.");
	    SAVE_AUTOMATON_DOT("/tmp", "glushkov", au, nb);
	  }
	unsigned i = 0;
	if (exp != s.zero(SELECT(exp_t)))
	  for (; i < nb_word_test; ++i)
	    {
	      monoid_elt_t w = exp.choose_from_supp();
	      if (t.verbose() == tests::high)
		std::cout << "TEST: glushkov " << i << " : test " << w << std::endl;
	      if (compute(au, w) == s.zero_)
		{
		  if (t.verbose() == tests::high)
		    std::cout << "TEST: glushkov " << i << " failed." << std::endl;
		  break;
		}
	    }
	if ((nb_word_test == i) || (exp == s.zero(SELECT(exp_t))))
	  ++success;
      }
    std::string rate;
    SUCCESS_RATE(rate, success, nb_test);
    TEST(t, "Random test " + rate, success == nb_test);
  }
  return t.all_passed();
}

#endif // GLUSHKOV_TEST_HH
