// check_minimisation.cc
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
# include <map>
# include <algorithm>
# include <list>

# include <vaucanson/misc/ref.hh>
# include <vaucanson/misc/dot_dump.hh>

# include <vaucanson/tools/gen_random.hh>

# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/automata/concept/kinds.hh>

# include <vaucanson/automata/concept/transpose_impl.hh>

# include <time.h>

# include <vaucanson/algorithms/hopcroft.hh>
# include <vaucanson/algorithms/moore.hh>

using namespace vcsn;
using namespace vcsn::algebra;


template <class Auto>
unsigned minimization_test(tests::Tester& tg)
{
  std::filebuf fb;
  std::ostream os(&fb);
  fb.open ("automaton.dot", std::ios::out);

  tests::Tester t(tg.verbose());
  typedef Auto automaton_t;
  typedef transpose_traits<automaton_t>::transpose_t transpose_t;
  typedef transpose_traits<transpose_t>::transpose_t tranpose_transpose_t;

  gen_auto_t gen(time(0x0));

  const unsigned nb_tests = 10;
  unsigned success = 0;
  std::string rate;
   
  for (unsigned i = 0; i < nb_tests; i++)
    {
      bool res;
      automaton_t work = gen.generate_dfa(5, 10);
            
      tranpose_transpose_t minimize = 
	determinize(transpose_view(trim(determinize(transpose_view(work)))));
      
      automaton_t hopcroft = hopcroft_minimization_det(work);
      
      if (res = ((minimize.states().size() == hopcroft.states().size()) &&
		 (minimize.edges().size() ==  hopcroft.edges().size())))
	++success;
    }
  
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "HopCroft Minimization Check" + rate, success == nb_tests);
  
  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      bool res;
      automaton_t work = gen.generate_dfa(5, 10);
            
      tranpose_transpose_t minimize = 
	determinize(transpose_view(trim(determinize(transpose_view(work)))));
      
      automaton_t moore = moore_minimization(work);
      
      if (res = ((minimize.states().size() == moore.states().size()) &&
		 (minimize.edges().size() ==  moore.edges().size())))
	++success;
    }
  rate.clear();
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "Moore Minimization Check" + rate, success == nb_tests);
      
  return t.all_passed();
}
