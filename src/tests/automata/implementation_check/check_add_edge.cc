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

  TEST(t, "Initial Number of Edges (0)", automaton.edges().size() == 0);

  hedge_t h1 = automaton.add_edge(s1, s2, polynom<std::string, int>());

  TEST(t, "Number of Edges after 1 edge added", 
       automaton.edges().size() == 1);

  automaton.del_edge(h1);

  TEST(t, "Number of Edges after 1 edge deleted ", 
       automaton.edges().size() == 0);

  return 0;
}
