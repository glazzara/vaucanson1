// algo_test.cc
//
// $Id$
// VCSN_HEADER

# include <check/tests_stuff.hh>

# include <vaucanson/tools/usual.hh>
# include <automata/algos/union_test.hh>
# include <automata/algos/determinist_test.hh>
# include <automata/algos/normalize_test.hh>
# include <automata/algos/reachable_test.hh>
# include <automata/algos/extract_test.hh>
# include <automata/algos/generalized_test.hh>
# include <automata/algos/elimination_test.hh>
# include <automata/algos/closure_test.hh>
# include <automata/algos/glushkov_test.hh>
# include <automata/algos/thompson_test.hh>
# include <automata/algos/realtime_test.hh>

int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  tests::verbose_level_e verbose;
  srand(time(0));

  if (argc > 1) 
    {
      if (argv[1] == std::string("--no-verbose"))
	verbose = tests::none;
      else if (argv[1] == std::string ("--high-verbose"))
	verbose = tests::high;
      else 
	verbose = tests::low;
    }

  tests::Tester t(verbose);

  TEST(t, "CHECK UNION ", union_test<usual_automaton_t>(t));
  TEST(t, "CHECK DETERMINIST ", determinist_test<usual_automaton_t>(t));
  TEST(t, "CHECK NORMALIZE ", normalize_test<usual_automaton_t>(t));
  TEST(t, "CHECK REACHABLE ", reachable_test<usual_automaton_t>(t));
  TEST(t, "CHECK EXTRACT ", extract_test<usual_automaton_t>(t));
  TEST(t, "CHECK GENERALIZED ", generalized_test<usual_automaton_t>(t));
  TEST(t, "CHECK ELIMINATION ", elimination_test<usual_automaton_t>(t));
  TEST(t, "CHECK CLOSURE ", closure_test<usual_automaton_t>(t));
  TEST(t, "CHECK GLUSHKOV ", glushkov_test<usual_automaton_t>(t));
  TEST(t, "CHECK THOMPSON ", thompson_test<usual_automaton_t>(t));
  TEST(t, "CHECK REALTIME ", realtime_test<usual_automaton_t>(t));

  return EXIT_SUCCESS;
}
