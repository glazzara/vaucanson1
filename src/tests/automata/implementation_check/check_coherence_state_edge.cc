// check_add_state.cc
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


  Element<Automata, 
    AutomatonImpl<labels_are_series, 
    Series<NumericalSemiring, Words>,
    polynom<std::string, int>,
    ManyLinks<polynom<std::string, int>, NoTag, NoTag>,
    NoTag,
    std::map> 
    > automaton;
  
  hstate_t s1 = automaton.add_state();
  hstate_t s2 = automaton.add_state();

  hedge_t h1 = automaton.add_edge(s1, s2, polynom<std::string, int>());

  TEST(t, "Check Number of States", automaton.states().size() == 2);

  TEST(t, "Check Number of Edges", automaton.edges().size() == 1);

  automaton.del_state(s1);

  TEST(t, "Check for zombies edges", automaton.edges().size() == 0);

  return 0;
}
