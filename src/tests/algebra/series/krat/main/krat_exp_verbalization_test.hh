// krat_exp_verbalization_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_VERBALIZATION_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_VERBALIZATION_TEST_HH

# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_verbalization.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
# include <vaucanson/misc/selectors.hh>
# include <sstream>
# include <string>

template <class Expr>
std::string test(tests::Tester& t,
		 Expr& e, 
		 const std::string& input,
		 const std::string& expected)
{
  parse(input, e);
  std::stringstream s;
  s << verbalize(e);
  EQTEST(t, input, s.str(), expected);
  return s.str();
}

template <class Expr>
bool krat_exp_verbalization_test(tests::Tester& tg)
{
  typedef Expr				      krat_exp_t;
  typedef typename krat_exp_t::value_t	      kexp_t;
  typedef typename krat_exp_t::monoid_elt_t   monoid_elt_t;
  typedef typename monoid_elt_t::set_t        monoid_t;
  
  typedef typename krat_exp_t::semiring_elt_t   semiring_elt_t;
  typedef typename semiring_elt_t::set_t	  semiring_t;
  typedef typename krat_exp_t::set_t 	  series_t;
  typedef typename monoid_t::letter_t     letter_t;
  typedef typename monoid_t::alphabet_t   alphabet_t;

  tests::Tester t(tg.verbose());
  srand(time(0));
  alphabet_t alphabet;
  letter_t a = 'a';
  letter_t b = 'b';
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_t s(semiring, monoid);

  krat_exp_t e(s);

  test(t, e, "(a+b)", "(a+b)");
  test(t, e, "a.(a+b)", "(aa+ab)");
  test(t, e, "b.(a+b)", "(ba+bb)");
  test(t, e, "(a+b).a", "(aa+ba)");
  test(t, e, "a+a", "(2 a)");  
  test(t, e, "a+2 a", "(3 a)");
  test(t, e, "3 b.(a+2 b)", "((3 ba)+(6 bb))");
  test(t, e, "(a+2 b).(4 a)", "((4 aa)+(8 ba))");
  test(t, e, "(a+2 b).(a 4)", "((4 aa)+(8 ba))");

  return t.all_passed();

}

#endif // VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_REALTIME_TEST_HH
