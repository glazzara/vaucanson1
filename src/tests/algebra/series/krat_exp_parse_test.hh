// krat_exp_parse_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef KRAT_EXP_PARSE_TEST_HH
# define KRAT_EXP_PARSE_TEST_HH

# include <check/tests_stuff.hh>
# include <sstream>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
# include <vaucanson/misc/selectors.hh>

template <class Expr>
bool krat_exp_parse_test(tests::Tester& tg)
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
  alphabet.insert('a');
  monoid_t monoid(alphabet);
  weights_t semiring;
  series_t s(semiring, monoid);
  // FIXME: !!!
  const unsigned nb_test = 100;
  unsigned nb_success    = 0;
  for (unsigned i = 0; i < 100; ++i)
    {
      krat_exp_t exp = s.choose(SELECT(kexp_t));
      std::ostringstream sstr;
      sstr << exp;
      krat_exp_t out(s);
      std::pair<bool, std::string> ret = parse(sstr.str(), out);
      std::ostringstream ostr;
      ostr << out;
      if ((ostr.str() != sstr.str()) || (ret.first == true))
	{
	  std::cout << "parser:" << ret.second << std::endl;
	  std::cout << "input :" << sstr.str() << std::endl;
	  std::cout << "output:" << ostr.str() << std::endl;
	}
      else 
	++nb_success;
    }
  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_test);
  TEST(t, "parsing random rational expression " + rate, nb_success == nb_test);
  return t.all_passed();

}

#endif // KRAT_EXP_PARSE_TEST_HH
