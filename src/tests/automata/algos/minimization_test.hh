// minimization_test.hh
// 
// $Id$
// VCSN_HEADER
#ifndef MINIMIZATION_TEST_HH
# define MINIMIZATION_TEST_HH

# include <map>
# include <algorithm>
# include <list>
# include <time.h>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/transpose_impl.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/hopcroft.hh>
# include <vaucanson/algorithms/moore.hh>
# include <vaucanson/algorithms/trim.hh>
# include <check/tests_stuff.hh>

template <class Auto>
unsigned minimization_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;

  typedef GenRandomAutomata<Auto>  gen_auto_t;
  typedef Auto			   automaton_t;

  tests::Tester t(tg.verbose());
  gen_auto_t    gen(time(0x0));

  const unsigned nb_test    = 10;
  unsigned success_hopcroft = 0;
  unsigned success_moore    = 0;

  for (unsigned i = 0; i < nb_test; i++)
    {
      automaton_t work = gen.generate_dfa(5, 10);

      if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp", "minimization_initial", work, i);
	}
      
      typedef transpose_traits<automaton_t>::transpose_t transpose_t;
      typedef transpose_traits<transpose_t>::transpose_t tranpose_transpose_t;
      
      tranpose_transpose_t minimize = 
	determinize(transpose_view(trim(determinize(transpose_view(work)))));
      
      automaton_t hopcroft = hopcroft_minimization_det(work);
      automaton_t moore = moore_minimization(work);

      if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp", "minimization_hopcroft", hopcroft, i);
	}

      if (t.verbose() == tests::high)
	{
	  TEST_MSG("Automaton saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp", "minimization_moore", moore, i);
	}
      
      if ((minimize.states().size() == hopcroft.states().size()) &&
	  (minimize.edges().size() ==  hopcroft.edges().size()))
	++success_hopcroft;

      if ((minimize.states().size() == moore.states().size()) &&
	  (minimize.edges().size() ==  moore.edges().size()))
	++success_moore;
    }

  std::string rate_hopcroft;
  SUCCESS_RATE(rate_hopcroft, success_hopcroft, nb_test);
  std::string rate_moore;
  SUCCESS_RATE(rate_moore, success_moore, nb_test);
  TEST(t, "Hopcroft minimization "+rate_hopcroft, success_hopcroft == nb_test);
  TEST(t, "Moore minimization    "+rate_moore,    success_moore    == nb_test);

  return t.all_passed();
}
#endif // MINIMIZATION_TEST_HH
