// elimination_test.hh
//
// $Id$
// VCSN_HEADER
#ifndef ELIMINATION_TEST_HH
# define ELIMINATION_TEST_HH

# include <check/tests_stuff.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/automata/concrete/generalized.hh>
# include <vaucanson/algorithms/elimination.hh>

using namespace vcsn;

template <class Auto>
bool elimination_test(tests::Tester& t)
{
  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_automaton_t;
  AUTOMATON_TYPES_(generalized_automaton_t, g);

  TEST_MSG("Basic test on a well-known automaton.");
  vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
  Auto	a = gen.generate(10,20);
  generalized_automaton_t a_ = generalized(a);
  gseries_elt_t language;
  language = elimination(a_);
  return true;
}

#endif // GENERALIZED_TEST_HH
