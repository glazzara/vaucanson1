// add_edge_test.hh
//
// $Id$
// VCSN_HEADER

#ifndef ADD_EDGE_TEST_HH
# define ADD_EDGE_TEST_HH

#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>


# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>

# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/tags.hh>

# include <vaucanson/automata/concrete/manylinks.hh>

# include <check/tests_stuff.hh>
# include <map>

# include <vaucanson/misc/ref.hh>
# include <vaucanson/tools/usual.hh>

# include <vaucanson/automata/concept/handlers.hh>

template <class Auto> 
unsigned add_edge_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  automaton_t automaton;

  automaton.create();
  
  hstate_t s1 = automaton.add_state();
  hstate_t s2 = automaton.add_state();

  TEST(t, "Initial Number of Edges (0)", automaton.edges().size() == 0);

  hedge_t h1 = automaton.add_edge(s1, s2, series_elt_t());

  TEST(t, "Number of Edges after 1 edge added", 
       automaton.edges().size() == 1);

  automaton.del_edge(h1);

  TEST(t, "Number of Edges after 1 edge deleted ", 
       automaton.edges().size() == 0);

  return t.all_passed();
}

#endif
