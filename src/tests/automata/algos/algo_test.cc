// algo_test.cc
//
// VCSN_HEADER

# include <check/tests_stuff.hh>

# include <vaucanson/tools/usual.hh>

# include <automata/algos/union_test.hh>
# include <automata/algos/determinist_test.hh>
# include <automata/algos/normalize_test.hh>
# include <automata/algos/reachable_test.hh>
# include <automata/algos/extract_test.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
    using namespace vcsn::tools;

  unsigned verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = 0;
  else
    verbose = 1;
  tests::Tester t(verbose);

  TEST(t, "CHECK UNION : ", !union_test<usual_automaton_t>(t));
  TEST(t, "CHECK DETERMINIST : ", !determinist_test<usual_automaton_t>(t));
  TEST(t, "CHECK NORMALIZE : ", !normalize_test<usual_automaton_t>(t));
  TEST(t, "CHECK REACHABLE : ", !reachable_test<usual_automaton_t>(t));
  TEST(t, "CHECK EXTRACT : ", !extract_test<usual_automaton_t>(t));

  return EXIT_SUCCESS;
}
