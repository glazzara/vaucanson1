// union_test.cc
// 
// VCSN_HEADER


#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>

# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/tags.hh>

# include <vaucanson/automata/concrete/manylinks.hh>

# include <check/tests_stuff.hh>

# include <vaucanson/misc/ref.hh>
# include <vaucanson/misc/dot_dump.hh>

# include <vaucanson/tools/gen_random.hh>

# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/transpose_impl.hh>

# include <vaucanson/algorithms/union.hh>

# include <time.h>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;


template <class Auto>
unsigned union_test(tests::Tester& t)
{  
  std::filebuf fb;
  std::ostream os(&fb);
  fb.open ("automaton.dot", std::ios::out);
  
  typedef Auto automaton_t;

  gen_auto_t gen(time(0x0));

  for (unsigned i = 0 ; i < 10; i++) 
    {
      automaton_t a = gen.generate(20, 40);
      automaton_t b = gen.generate(10, 20);
      automaton_t c = auto_union(a, b);
      
      TEST(t, "Check Union automata [states]", a.states().size() + 
	   b.states().size() == c.states().size());
      
      TEST(t, "Check Union automata [edges]", a.edges().size() + 
	   b.edges().size() == c.edges().size());
    }

  return EXIT_SUCCESS;
}
