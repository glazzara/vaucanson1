// derivation_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef CDERIVATION_LINEAR_TEST_HH
# define CDERIVATION_LINEAR__TEST_HH

# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
// FIXME: Code krat_exp_linearize.hh !
//# include <vaucanson/algorithms/krat_exp_linearize.hh>
# include <vaucanson/algorithms/krat_exp_derivation.hh>
# include <vaucanson/algorithms/krat_exp_cderivation.hh>
# include <vaucanson/misc/selectors.hh>

// FIXME: Works only when derivation and linearize do ! So need to be completed
// with other tests.

template <class Expr>
bool krat_exp_cderivation_linear_test(tests::Tester& tg)
{
  typedef Expr				      krat_exp_t;
  typedef typename krat_exp_t::value_t	      kexp_t;
  typedef typename krat_exp_t::monoid_elt_t   monoid_elt_t;
  typedef typename monoid_elt_t::set_t        monoid_t;
  
  typedef typename krat_exp_t::weight_t   weight_t;
  typedef typename weight_t::set_t	  weights_t;
  typedef typename krat_exp_t::set_t 	  series_t;
  typedef typename monoid_t::letter_t     letter_t;
  typedef typename monoid_t::alphabet_t   alphabet_t;

  // FIXME: Finish this test and remove following line !
  return true;

  tests::Tester t(tg.verbose());
  srand(time(0));

  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);

  monoid_t monoid(alphabet);
  weights_t semiring;
  series_t series(semiring, monoid);

  const unsigned int tests_num = 20;
  unsigned int success = 0;

  for (unsigned int i = 0; i < tests_num; i++)
    {
      krat_exp_t exp = series.choose(SELECT(kexp_t));
      // FIXME: Code linearize !
      // exp = linearize(exp);
      for (typename alphabet_t::iterator it = alphabet.begin();
	   it != alphabet.end();
	   ++it)
	{
	  std::pair<krat_exp_t, bool> dexp = derivate(exp, *it);
	  krat_exp_t cdexp = cderivate(exp, *it);
	  if (dexp.second && (dexp.first == cdexp))
	    success++;
	  else
	    std::cerr << "TEST FAILED !" << std::endl <<
	      "exp was \"" << exp << "\"." << std::endl <<
	      "derivate says \"" << dexp.first << "\"." << std::endl <<
	      "cderivate says \"" << cdexp << "\"." << std::endl;
	}
    }
  std::string rate;
  SUCCESS_RATE(rate, success, tests_num * alphabet.size());
  TEST(t, "c-derivation is equivalent to derivation on linear exp. " +
       rate, success == tests_num * alphabet.size());
  return t.all_passed();
}

#endif // CDERIVATION_LINEAR_TEST_HH
