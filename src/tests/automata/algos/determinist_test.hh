// determinist_test.hh
// 
// $Id$
// VCSN_HEADER
#ifndef DETERMINIST_TEST_HH
# define DETERMINIST_TEST_HH

# include <time.h>
# include <map>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/misc/dot_dump.hh>

template <class Auto>
unsigned determinist_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  typedef Auto automaton_t;

  tests::Tester t(tg.verbose());
  gen_auto_t gen(time(0x0));
  
  const unsigned nb_tests = 20;
  unsigned success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t dfa = gen.generate_dfa(50);;
      if (is_deterministic(dfa))
	++success;
    } 
  std::string rate;
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "is_determinist on randomly generated dfa " + rate, success == nb_tests);

  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {     
      automaton_t automata = gen.generate(40, 80);
      automaton_t dfa      = determinize(automata);
      if (is_deterministic(dfa))
	++success;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "determinize on randomly generated dfa " + rate, success == nb_tests);
  
  return t.all_passed();
}

#endif // DETERMINIST_TEST_HH
