// series-test.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef SERIES_TEST_HH
# define SERIES_TEST_HH

#include <check/tests_stuff.hh>
#include <fundamental/design_pattern-test.hh>
#include <vaucanson/fundamental/fundamental.hh>

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


#endif // SERIES_TEST_HH
