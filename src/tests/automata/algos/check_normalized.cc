// check_normalized.cc
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

int main(int argc, char **argv)
{
  using namespace vcsn;
  using namespace vcsn::algebra;

  unsigned verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = 0;
  else
    verbose = 1;
  tests::Tester t(verbose);

  gen_auto_t gen(42);
  
 
  const unsigned nb_tests = 10;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      usual_automaton_t normalized = gen.generate_normalized(30);;
      
      TEST(t, "Check routine is_normalized", is_normalized(normalized));
    } 

  for (unsigned i = 0; i < nb_tests; i++)
    {
      usual_automaton_t normalized = gen.generate(30, 60);
      normalize(normalized);
      
      TEST(t, "Is Nomalized Automaton", is_normalized(normalized));
    } 

  return 0;
}
