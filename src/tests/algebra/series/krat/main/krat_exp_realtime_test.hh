// krat_exp_linearize_test.hh
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

#ifndef KRAT_EXP_REALTIME_TEST_HH
# define KRAT_EXP_REALTIME_TEST_HH

# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algorithms/krat_exp_realtime.hh>
# include <vaucanson/misc/selectors.hh>

template <class Expr>
bool krat_exp_realtime_test(tests::Tester& tg)
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

  tests::Tester t(tg.verbose());
  srand(time(0));
  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  weights_t semiring;
  series_t s(semiring, monoid);
  monoid_elt_t w(monoid);
  w = a;
  w = w * w * w;
  krat_exp_t exp(w);
  krat_exp_t lin = realtime(exp);
  return t.all_passed();

}

#endif // KRAT_EXP_REALTIME_TEST_HH
