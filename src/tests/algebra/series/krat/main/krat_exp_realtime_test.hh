// krat_exp_realtime_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_REALTIME_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_REALTIME_TEST_HH

# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/algorithms/krat_exp_realtime.hh>
# include <vaucanson/misc/selectors.hh>

template <class Expr>
bool krat_exp_realtime_test(tests::Tester& tg)
{
  typedef Expr					krat_exp_t;
  typedef typename krat_exp_t::value_t		kexp_t;
  typedef typename krat_exp_t::monoid_elt_t	monoid_elt_t;
  typedef typename monoid_elt_t::set_t		monoid_t;

  typedef typename krat_exp_t::semiring_elt_t	semiring_elt_t;
  typedef typename semiring_elt_t::set_t	semiring_t;
  typedef typename krat_exp_t::set_t		series_set_t;
  typedef typename monoid_t::letter_t		letter_t;
  typedef typename monoid_t::alphabet_t		alphabet_t;

  tests::Tester t(tg.verbose());
  srand(time(0));
  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_set_t s(semiring, monoid);

  bool error = false;
  for (int i = 0; i < 100; ++i)
    {
      krat_exp_t exp = s.choose(SELECT(kexp_t));
      krat_exp_t lin = realtime(exp);
      if (!is_realtime(lin))
	error = true;
    }
  TEST(t, "Realtime works.", not error);
  return t.all_passed();

}

#endif // VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_REALTIME_TEST_HH
