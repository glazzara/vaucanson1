// generalized_test.hh
//
// $Id$
// VCSN_HEADER
#ifndef GENERALIZED_TEST_HH
# define GENERALIZED_TEST_HH

# include <check/tests_stuff.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/automata/concrete/generalized.hh>

using namespace vcsn;

template <class Auto>
bool generalized_test(tests::Tester& t)
{
  AUTOMATON_TYPES(Auto);
  TEST_MSG("Basic test on a well-known automaton.");
  vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
  Auto	a = gen.generate(10,20);
  typename generalized_traits<Auto>::automaton_t a_ = 
    generalized(a);
  return true;
}

#endif // GENERALIZED_TEST_HH
