// determinist_test.hh
// 
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

# include <vaucanson/algorithms/determinize.hh>

# include <time.h>

template <class Auto>
unsigned determinist_test(tests::Tester& t)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;

  gen_auto_t gen(time(0x0));
  
  const unsigned nb_tests = 10;
  
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t afd = gen.generate_afd(50);;
      
      TEST(t, "Check routine is_determinist", is_deterministic(afd));
    } 

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t afd = determinize(gen.generate(30, 60));
      
      TEST(t, "Is determinist Automaton", is_deterministic(afd));
    } 

  return EXIT_SUCCESS;
}
