// derivation_test.hh
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

#ifndef DERIVATION_TEST_HH
# define DERIVATION_TEST_HH

# include <check/tests_stuff.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algorithms/krat_exp_derivation.hh>
# include <vaucanson/misc/selectors.hh>

template <class Expr>
bool krat_exp_derivation_test(tests::Tester& tg)
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
  krat_exp_t exp = s.choose(SELECT(kexp_t));
  std::cout << exp << std::endl;
  std::pair<krat_exp_t, bool> dexp_a = derivate(exp, a);
  std::pair<krat_exp_t, bool> dexp_b = derivate(exp, b);
  monoid_elt_t w;
  w = a; w *= b;
  std::pair<krat_exp_t, bool> dexp_ab = word_derivate(exp, w);
  if (!dexp_a.second)
    std::cout << "undefined" << std::endl;
  else 
    std::cout <<  a << "/" << dexp_a.first << std::endl;
  if (!dexp_b.second)
    std::cout << "undefined" << std::endl;
  else 
    std::cout<< b << "/" << dexp_b.first << std::endl;
  return t.all_passed();

}

#endif // DERIVATION_TEST_HH
