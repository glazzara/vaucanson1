// krat_exp_constant_term_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2204 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_CONSTANT_TERM_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_CONSTANT_TERM_TEST_HH

# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/concept/semiring_base.hh>

template <class Expr>
bool krat_exp_constant_term_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  typedef Expr				      krat_exp_t;
  typedef typename krat_exp_t::value_t	      kexp_t;
  typedef typename krat_exp_t::monoid_elt_t   monoid_elt_t;
  typedef typename monoid_elt_t::set_t        monoid_t;
  
  typedef typename krat_exp_t::semiring_elt_t   semiring_elt_t;
  typedef typename semiring_elt_t::value_t	semiring_elt_value_t;
  typedef typename semiring_elt_t::set_t	  semiring_t;
  typedef typename krat_exp_t::set_t 	  series_t;
  typedef typename monoid_t::letter_t     letter_t;
  typedef typename monoid_t::alphabet_t   alphabet_t;

  typedef typename kexp_t::semiring_elt_value_t	impl_t;
  
  srand(time(0));
  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_t s(semiring, monoid);
  krat_exp_t exp = s.choose(SELECT(kexp_t));

  semiring_elt_t s_identity = semiring.identity(SELECT(semiring_elt_value_t));
  semiring_elt_t s_zero = semiring.zero(SELECT(semiring_elt_value_t));
  semiring_elt_t s_2identity = s_identity + s_identity;

  letter_t larray[] = { a, b, letter_t () };

  unsigned int nb_tests = 0;
  unsigned int nb_succs = 0;
  
  for (int cpt = 0; cpt < 5; ++cpt)
  {
    semiring_elt_t w = semiring.choose(SELECT(semiring_elt_value_t));

    struct
    {
      krat_exp_t		exp;
      semiring_elt_t	res;
    }
    exps[] =
      {
	{ s.zero(SELECT(kexp_t)), s_zero },
	{ s.identity(SELECT(kexp_t)), s_identity },
	{ krat_exp_t (s), s_zero },
	{ krat_exp_t (s, a), s_zero },
	{ krat_exp_t (s, a) + krat_exp_t (s, b), s_zero },
	{ krat_exp_t (s, a) * krat_exp_t (s, b), s_zero },
	{ krat_exp_t (s, std::basic_string<letter_t> (larray)), s_zero },
	{ krat_exp_t (s, a).star(), s_identity },
	{ (s.identity(SELECT(kexp_t))).star(), s_identity },
	{ (s_2identity * krat_exp_t (s, a)).star(), s_identity },
	{ w * krat_exp_t (s, a), s_zero },
	{ krat_exp_t (s, a) * w, s_zero },
	{ krat_exp_t (s, a) * w + krat_exp_t (s, a), s_zero },
	{ krat_exp_t (s, a) * w + krat_exp_t (s, a).star(), s_identity }
      };

    for (unsigned int i = 0; i < 14; ++i)
      {
	std::pair<semiring_elt_t, bool> ret = constant_term(exps[i].exp);

	// Tests with w are after test #9
	if (i > 9)
	  if (w.starable())
	    {
	      if (ret.second)
		std::cerr << "Fail: Constant term shouldn't be computed"
			  << std::endl;
	      else
		++nb_succs;
	      continue;
	    }
	if (ret.first.value() == exps[i].res.value())
	  ++nb_succs;
	else
	  std::cerr << "FAIL: Expression "
		    << exps[i].exp
		    << " returned "
		    << ret.first
		    << " as constant term, instead of "
		    << exps[i].res
		    << std::endl;
	++nb_tests;
      }
  }
  
  std::string rate;
  SUCCESS_RATE(rate, nb_succs, nb_tests);
  TEST(t, "Constant term on all kind of basic expressions " + rate,
       nb_tests == nb_succs);
  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_CONSTANT_TERM_TEST_HH
