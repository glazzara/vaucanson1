// closure_test.hh
//
// $Id$
// VCSN_HEADER

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

# include <vaucanson/tools/gen_random.hh>

# include <vaucanson/algorithms/closure.hh>


template <class Auto>
bool closure_test(tests::Tester& t)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  
  typedef Auto automaton_t;
  AUTOMATON_TYPES(Auto);
  
  gen_auto_t gen(time(0x0));
  
  automaton_t auto_epsilon = gen.generate_with_epsilon(30, 50, 10, 20);
  
  automaton_t cauto = closure(auto_epsilon);
  TEST(t, "Increase of edges number.",  
       cauto.edges().size() >= auto_epsilon.edges().size());
  TEST(t, "Idempotence.", 
       closure(cauto).edges().size() == cauto.edges().size());

  return true;
}
