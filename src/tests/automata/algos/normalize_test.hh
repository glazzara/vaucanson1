// normalize_test.hh
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

# include <automata/implementation_check/gen_random.hh>

# include <vaucanson/algorithms/normalized.hh>

template <class Auto>
unsigned normalize_test(const tests::Tester& t)
{
  using namespace vcsn;
  using namespace vcsn::algebra;

  typedef Auto automaton_t;
  
  const unsigned nb_tests = 10;
  
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t normalized = gen.generate_normalized(30);;
      
      TEST(t, "Check routine is_normalized", is_normalized(normalized));
    } 

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t normalized = gen.generate(30, 60);
      normalize(normalized);
      
      TEST(t, "Is normalized automaton", is_normalized(normalized));
    } 

  return EXIT_SUCCESS;
}
