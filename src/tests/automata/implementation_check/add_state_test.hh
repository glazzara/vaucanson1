// add_state_test.hh
//
// $Id$
// VCSN_HEADER

#ifndef ADD_STATE_TEST_HH
# define ADD_STATE_TEST_HH

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



template <class Auto> 
unsigned add_state_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  automaton_t automaton;

  automaton.create();

  TEST(t, "Initial Number of States (0)", automaton.states().size() == 0);

  hstate_t s1 = automaton.add_state();

  TEST(t, "Number of States after 1 state added", 
       automaton.states().size() == 1);

  automaton.del_state(s1);
 
 TEST(t, "Number of States after state deleted", 
       automaton.states().size() == 0);  

  return t.all_passed();
}

#endif
