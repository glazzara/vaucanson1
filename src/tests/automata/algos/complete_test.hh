// complete_test.hh
//
// $Id$
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

# include <vaucanson/algorithms/product.hh>

# include <time.h>

# include <vaucanson/misc/dot_dump.hh>

# include <vaucanson/algorithms/complementary.hh>
# include <vaucanson/algorithms/complete.hh>

# include <vaucanson/algorithms/trim.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned complete_test(tests::Tester& tg)
{  
//   std::filebuf fb;
//   std::ostream os(&fb);
//   fb.open ("automaton.dot", std::ios::out);
  tests::Tester t(tg.verbose());
  typedef Auto automaton_t;

  gen_auto_t gen(time(0x0));

  const unsigned nb_test = 10;

  for (unsigned i = 0 ; i < nb_test; i++) 
    {
      automaton_t a = gen.generate_afd(20);
      
      auto_in_complete(a);

      TEST(t, "Check Identity for square product", 
	   (a.edges().size() == a.states().size() * 
	    a.series().monoid().alphabet().size()) && is_deterministic(a)
	   );
      
     }
  
  //  misc::dot_dump(os, trim(d), "Product"); 

  return t.all_passed();
}
