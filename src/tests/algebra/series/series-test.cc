// series-test.cc
//
// VCSN_HEADER

// Goal: 
// - to instantiate all services of element parameterized by empty classes.
//

#include <set>
#include <check/tests_stuff.hh>
#include <fundamental/design_pattern-test.hh>
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>

using namespace vcsn;


template <typename S, typename T> 
bool test_series(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef Element<S, T> element_t;
  element_t a;

  test_design_pattern<S, T>();

  return t.all_passed(); 
}



int main(int argc, char **argv)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  unsigned verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = 0;
  else
    verbose = 1;
  tests::Tester t(verbose);

 if (test_series<Series<NumericalSemiring, Words>, polynom<int,std::string> >(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

