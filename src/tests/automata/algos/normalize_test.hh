// normalize_test.hh
// 
// $Id$
// VCSN_HEADER
#ifndef NORMALIZE_TEST_HH
# define NORMALIZE_TEST_HH

# include <time.h>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/algorithms/normalized.hh>

template <class Auto>
unsigned normalize_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  typedef Auto automaton_t;
 
  tests::Tester     t(tg.verbose());
  gen_auto_t        gen(time(0x0));
  const unsigned    nb_tests = 10;
  unsigned	    success = 0;
  std::string	    rate;

  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t normalized = gen.generate_normalized(30);;
      if (is_normalized(normalized))
	success++;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "is_normalized on random normalized automaton "+rate, 
       nb_tests == success);

  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {
      automaton_t normalized = gen.generate(30, 60);
      normalize(normalized);
      if (is_normalized(normalized))
	success++;
    } 
  SUCCESS_RATE(rate, success, nb_tests);
  TEST(t, "normalized on randomly generated automaton "+rate, nb_tests == success);

  return t.all_passed();
}

#endif // NORMALIZE_TEST_HH
