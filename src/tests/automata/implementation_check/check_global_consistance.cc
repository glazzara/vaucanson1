// check_global_consistance.cc
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
# include <set>

# include <vaucanson/misc/ref.hh>

# include <vaucanson/tools/gen_random.hh>

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

  tools::gen_auto_t gen(42);

  tools::usual_automaton_t automaton = gen.generate(12, 20);

  hstate_t 
    s1 = automaton.select_state(2), 
    s2 = automaton.select_state(7),
    s3 = automaton.select_state(4);
  
  automaton.del_state(s1);
  automaton.del_state(s2);
  automaton.del_state(s3);

  // call our function to check consistency of the automaton.

  bool final = true;
  for (tools::usual_automaton_t::edge_iterator i = automaton.edges().begin(); 
       i != automaton.edges().end();
       i++)
    {
      hstate_t tmp = automaton.aim_of(*i);
      bool res = false;

      for (tools::usual_automaton_t::state_iterator j = 
	     automaton.states().begin();
	   j != automaton.states().end();
	   j++)
	if (*j == tmp)
	  res = true;
      final = final && res;
    }

  TEST(t, "All edges are well defined.", final);
  
  TEST_RETURN(t);
}
