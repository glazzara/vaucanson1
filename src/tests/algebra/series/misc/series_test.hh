// series-test.hh
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef SERIES_TEST_HH
# define SERIES_TEST_HH

# include <vaucanson/config/system.hh>
# include <check/tests_stuff.hh>
# include <fundamental/design_pattern-test.hh>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/tools/usual.hh>

using namespace vcsn;

template <typename S, typename T> 
bool series_test(tests::Tester& t)
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
  letter_t	b;
  do
    b = alphabet.random_letter();
  while (a == b);
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
