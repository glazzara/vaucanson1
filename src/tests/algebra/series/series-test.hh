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
# include <vaucanson/tools/usual.hh>

using namespace vcsn;

template <typename S, typename T> 
bool test_series(tests::Tester& t)
{
  using namespace vcsn::algebra;
  using namespace vcsn;

  typedef S					series_t;
  typedef typename S::monoid_t			monoid_t;
  typedef typename monoid_t::alphabet_t		alphabet_t;
  typedef typename alphabet_t::letter_t		letter_t;
  typedef typename S::weights_t			weights_t;
  typedef Element<S, T>				series_elt_t;
  typedef typename series_elt_t::monoid_elt_t   monoid_elt_t;
  typedef typename series_elt_t::weight_t	semiring_elt_t;
  typedef typename semiring_elt_t::value_t	semiring_value_t;

  alphabet_t	alphabet;
  letter_t	a = alphabet.random_letter();
  letter_t	b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);

  monoid_t	monoid(alphabet);
  weights_t	weights;
  series_t	series(weights, monoid);
  monoid_elt_t  w1(a);
  monoid_elt_t  w2(b);
  series_elt_t     s1(series, w1);
  series_elt_t     s2(series, w2);
  series_elt_t     s3(series, series.identity(SELECT(T)));
  series_elt_t     s4(series, series.zero(SELECT(T)));
  semiring_elt_t   zero = weights.zero(SELECT(semiring_value_t));

  // FIXME: add element operators to krat to permit this static test.
  // test_design_pattern<S, T>();

  TEST(t, "get of series.", s1.get(w1) != zero);
  TEST(t, "set of series.", s1.get(w2) == zero);
  TEST(t, "choose from the support.", s1.choose_from_supp() == w1);
  return t.all_passed(); 
}


#endif // SERIES_TEST_HH
