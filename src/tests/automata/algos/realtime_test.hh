// realtime_test.hh
// 
// $Id$
// VCSN_HEADER
#ifndef REALTIME_TEST_HH
# define REALTIME_TEST_HH

# include <map>
# include <time.h>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/misc/ref.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/misc/dot_dump.hh>


template <class Auto>
unsigned realtime_test(tests::Tester& t)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;

  gen_auto_t gen(time(0x0));
  
  const unsigned nb_ok_tests     = 20;
  const unsigned nb_non_ok_tests = 20;
  unsigned success = 0;

  for (unsigned i = 0; i < nb_ok_tests; i++)
    {
      automaton_t a = gen.generate(50, 60);;      
      if (is_realtime(a))
	++success;
    } 
  char buff[128];
  snprintf(buff, 128, "is_realtime on realtime (%d/%d)", success, nb_ok_tests);
  TEST(t, buff, success == nb_ok_tests);

  success = 0;
  for (unsigned i = 0; i < nb_non_ok_tests; i++)
    {
      automaton_t a = gen.generate_with_epsilon(50, 60, 1, 15);;      
      if (!is_realtime(a))
	++success;
    } 
  snprintf(buff, 128, "is_realtime on non-realtime (%d/%d)", success, nb_non_ok_tests);
  TEST(t, buff, success == nb_non_ok_tests);

  unsigned nb_tests = 20;
  success = 0;
  for (unsigned i = 0; i < nb_tests; i++)
    {     
      automaton_t automata = gen.generate_with_epsilon(40, 80, 1, 40);
      automaton_t non_epsilon = realtime(automata);
      if (is_realtime(non_epsilon))
	++success;
    } 
  snprintf(buff, 128, "realtime on non-realtime (%d/%d)", success, nb_tests);
  TEST(t, buff, success == nb_non_ok_tests);

  return t.all_passed();
}

#endif // REALTIME_TEST_HH
