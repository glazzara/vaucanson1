// series-test.cc
//
//
// $Id$
// VCSN_HEADER

// Goal: 
// - to instantiate all services of element parameterized by empty classes.
//

#include <set>
#include <check/tests_stuff.hh>
#include <fundamental/design_pattern-test.hh>
#include <algebra/series/series-test.hh>
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/polynoms.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>

using namespace vcsn;

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

  if (test_series<Series<NumericalSemiring, Words>, polynom<std::string, int> >(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

