// union_test.hh
// 
// $Id$
// VCSN_HEADER
#ifndef UNION_TEST_HH
# define UNION_TEST_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/algorithms/union.hh>
# include <time.h>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned union_test(tests::Tester& tg)
{  
  typedef Auto automaton_t;

  tests::Tester t(tg.verbose());
  gen_auto_t    gen(time(0x0));
  unsigned      nb_tests       = 10;
  unsigned      success_states = 0;
  unsigned      success_edges  = 0;

  for (unsigned i = 0 ; i < nb_tests; i++) 
    {
      automaton_t a = gen.generate(20, 40);
      automaton_t b = gen.generate(10, 20);
      automaton_t c = auto_union(a, b);

      if (a.states().size() + b.states().size() == c.states().size())
	++success_states;
      if (a.edges().size() + b.edges().size() == c.edges().size())
	++success_edges;
    }
  std::string rate_states, rate_edges;
  SUCCESS_RATE(rate_states, success_states, nb_tests);
  SUCCESS_RATE(rate_edges, success_edges, nb_tests);
  TEST(t, "Union basic tests (edges: "+rate_edges+", states: "+rate_states+")", 
       ((nb_tests == success_edges) && (nb_tests == success_states)));
  return t.all_passed();
}

#endif // UNION_TEST_HH
