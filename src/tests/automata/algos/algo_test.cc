// algo_test.cc
//
// VCSN_HEADER

# include <check/tests_stuff.hh>

# include <automata/algos/type_test.hh>

# include <automata/algos/union_test.hh>
# include <automata/algos/determinist_test.hh>
# include <automata/algos/normalize_test.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::algebra;

  unsigned verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = 0;
  else
    verbose = 1;
  tests::Tester t(verbose);

//   TEST(t, "CHECK UNION : ", union_test<usual_automaton_t>(t));
//   TEST(t, "CHECK DETERMINIST : ", determinist_test<usual_automaton_t>(t));
//   TEST(t, "CHECK NORMALIZE : ", normalize_test<usual_automaton_t>(t));
  
}
