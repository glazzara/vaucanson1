// check_init_final.cc
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
  automaton.set_initial(s1);

  TEST(t, "Is Initial State [set]", automaton.is_initial(s1));

  automaton.unset_initial(s1);

  TEST(t, "Is Initial State [unset]", !automaton.is_initial(s1));


  automaton.set_final(s1);

  TEST(t, "Is Final State [set]", automaton.is_final(s1));

  automaton.unset_final(s1);

  TEST(t, "Is Final State [unset]", !automaton.is_final(s1));

  return 0;
}
