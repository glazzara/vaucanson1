#include <vaucanson/tools/usual.hh>
  #include <check/tests_stuff.hh>
  #include </home/lrde/stud/yann/work/vaucanson/vaucanson/src/tests//automata/algos/closure_test.hh>

  int main(int argc, char **argv)
  {
  using namespace vcsn;
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
    if (closure_test<usual_automaton_t>(t)) 
      return EXIT_SUCCESS;
    else
      return EXIT_FAILURE;
  }
  
