// check_add_state.cc
//
// $Id$
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


int main(int argc, char **argv)
{
  using namespace vcsn;
  using namespace vcsn::algebra;

  tests::verbose_level_e verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = tests::none;
  else
    verbose = tests::low;
  tests::Tester t(verbose);


  Element<Automata, 
    utility::ref <AutomatonImpl<labels_are_series, 
    Series<NumericalSemiring, Words>,
    polynom<std::string, int>,
    ManyLinks<polynom<std::string, int>, NoTag, NoTag>,
    NoTag,
    std::map> >
    > automaton;
  
  automaton.create();

  TEST(t, "Initial Number of States (0)", automaton.states().size() == 0);

  hstate_t s1 = automaton.add_state();

  TEST(t, "Number of States after 1 state added", 
       automaton.states().size() == 1);

  automaton.del_state(s1);
 
 TEST(t, "Number of States after state deleted", 
       automaton.states().size() == 0);  

  return 0;
}
