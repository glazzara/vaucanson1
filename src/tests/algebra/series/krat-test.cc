// krat-test.cc
//
//
// $Id$
// VCSN_HEADER

#include <set>
#include <check/tests_stuff.hh>
#include <fundamental/design_pattern-test.hh>
#include <algebra/series/series-test.hh>
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
#include <vaucanson/algebra/concrete/series/krat.hh>
#include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>

using namespace vcsn;

template <class S, class T>
bool test_krat(tests::Tester& t)
{
  bool series_test = test_series(t);
}

int main(int argc, char **argv)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  tests::verbose_level_e verbose;

  if ((argc > 1) && (argv[1] == std::string("--noverbose")))
    verbose = tests::none;
  else
    verbose = tests::low;
  tests::Tester t(verbose);

 if (test_series<Series<NumericalSemiring, Words>, rat::exp<std::string, int> >(t))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

