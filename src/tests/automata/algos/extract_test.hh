// extract_test.hh
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

# include <vaucanson/algorithms/reachable.hh>

# include <vaucanson/algorithms/moore.hh>
# include <vaucanson/misc/dot_dump.hh>

# include <vaucanson/tools/usual.hh>


template <class Auto>
unsigned extract_test(tests::Tester& t)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
 
  AUTOMATON_TYPES(Auto);
  typedef Auto automaton_t;
  
  gen_auto_t gen(time(0x0));
  
  const unsigned nb_tests = 10;
  
//   std::filebuf fb;
//   fb.open ("automaton.dot", std::ios::out);
//   std::ostream os(&fb);
  

  for (unsigned i = 0; i < nb_tests; i++)
    {
      unsigned nb_state = 5;
      unsigned nb_edge = 10;
      automaton_t a = gen.generate(nb_state, nb_edge);
      
      a = auto_extract(a, a.states());
      
      // misc::dot_dump(os, a, "test");

      TEST(t, "Check Extract ok", (a.states().size() == nb_state) &&
	   (a.edges().size() == nb_edge));
    }

  return EXIT_SUCCESS;
}
    
