// series-test.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef SERIES_TEST_HH
# define SERIES_TEST_HH

# include <check/tests_stuff.hh>
# include <fundamental/design_pattern-test.hh>
# include <vaucanson/fundamental/fundamental.hh>

using namespace vcsn;

template <typename S, typename T> 
bool test_series(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef S					series_t;
  typedef typename S::monoid_t			monoid_t;
  typedef typename monoid_t::alphabet_t		alphabet_t;
  typedef typename S::weights_t			weights_t;
  typedef Element<S, T>				element_t;
  typedef typename element_t::monoid_elt_t      monoid_elt_t;
  typedef typename element_t::weight_t		semiring_elt_t;

  // In the future, the alphabet will be define more generally than in
  // this test.
  alphabet_t	alphabet;
  alphabet.insert('a');
  alphabet.insert('b');

  monoid_t	monoid(alphabet);
  weights_t	weights;
  series_t	series(weights, monoid);
  element_t     a(series);
  element_t     b(series.identity(SELECT(T)));
  element_t     c(series.zero(SELECT(T)));
  semiring_elt_t one;
  semiring_elt_t two = one + one;
  monoid_elt_t  w(*alphabet.begin());
  element_t	e = monoid_elt_t(w);

  test_design_pattern<S, T>();

  element_t	d = a * b;

  TEST(t, "get of series.", d.get(w) == one);
  d.assoc(w, two);
  TEST(t, "set of series.", d.get(w) == two);

  return t.all_passed(); 
}


#endif // SERIES_TEST_HH
