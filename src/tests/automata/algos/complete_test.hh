// complete_test.hh
//
// $Id$
// VCSN_HEADER
#ifndef COMPLETE_TEST_HH
# define COMPLETE_TEST_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/complementary.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/determinize.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned complete_test(tests::Tester& tg)
{  
  tests::Tester t(tg.verbose());
  typedef Auto			  automaton_t;
  typedef GenRandomAutomata<Auto> gen_auto_t;
  
  gen_auto_t gen(time(0x0));

  const unsigned nb_test = 10;
  unsigned nb_success    = 0;

  for (unsigned i = 0 ; i < nb_test; i++) 
    {
      automaton_t a = gen.generate_dfa(20);
      
      auto_in_complete(a);
      
      if ((a.edges().size() == a.states().size() * 
	   a.series().monoid().alphabet().size()) && is_deterministic(a))
	++nb_success;
     }
  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_test);
  TEST(t, "complete on DFA." + rate, nb_success == nb_test);
  return t.all_passed();
}

#endif // COMPLETE_TEST_HH
