// check_tranpose.cc
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

# include <vaucanson/algorithms/transpose.hh>

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
  
  usual_automaton_t a = gen.generate(12, 20);
//   usual_automaton_t work = auto_transpose(a);
  
  

 //  TEST(t, "Initial Number of States (0)", automaton.states().size() == 0);

//   hstate_t s1 = automaton.add_state();

//   TEST(t, "Number of States after 1 state added", 
//        automaton.states().size() == 1);

//   automaton.del_state(s1);
 
//  TEST(t, "Number of States after state deleted", 
//        automaton.states().size() == 0);  

  return 0;
}
