// krat_exp_flatten_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_FLATTEN_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_FLATTEN_TEST_HH

# include <check/tester.hh>
# include <vaucanson/algorithms/krat_exp_flatten.hh>

template <class Expr>
bool krat_exp_flatten_test(tests::Tester& tg)
{
  typedef Expr					krat_exp_t;
  typedef typename krat_exp_t::value_t		kexp_t;
  typedef typename krat_exp_t::monoid_elt_t	monoid_elt_t;
  typedef typename monoid_elt_t::set_t		monoid_t;
  typedef typename krat_exp_t::semiring_elt_t	semiring_elt_t;
  typedef typename semiring_elt_t::value_t	semiring_elt_value_t;
  typedef typename semiring_elt_t::set_t	semiring_t;
  typedef typename krat_exp_t::set_t		series_t;
  typedef typename monoid_t::letter_t		letter_t;
  typedef typename monoid_t::alphabet_t		alphabet_t;

  tests::Tester t(tg.verbose());
  srand(time(0));
  alphabet_t	al;
  letter_t	a = al.random_letter();
  letter_t	b = al.random_letter();
  al.insert(a);
  al.insert(b);
  monoid_t	md(al);
  semiring_t	sg;
  series_t	ss(sg, md);

  // Equivalent to semiring_elt_t w = 2 (but we have no << 2 >>).
  //
  // FIXME: Why do the following statement give a parse error?
  //        semiring_elt_t w = identity_as<semiring_elt_value_t>::of(semiring);
  //
  semiring_elt_t w = sg.identity(SELECT(semiring_elt_value_t));
  w += w;

  letter_t larray[] = { a, b, letter_t () };

  struct
  {
    krat_exp_t	exp;
    int		len;
  }
  exps[] =
    {
      /* 0 */ { krat_exp_t (ss, a), 1 },
      /* 1 */ { krat_exp_t (ss, a) + krat_exp_t (ss, b), 2 },
      /* 2 */ { krat_exp_t (ss, a) * krat_exp_t (ss, b), 2 },
      /* 3 */ { krat_exp_t (ss, a).star(), 1 },
      /* 4 */ { w * krat_exp_t (ss, a), 1 },
      /* 5 */ { krat_exp_t (ss, a) * w, 1 },
      //
      // FIXME: Why do the two following lines give a parse error?
      //         { zero_as<kexp_t>::of(s), 0 },
      //         { identity_as<kexp_t>::of(s) 0 },
      //
      /* 6 */ { ss.zero(SELECT(kexp_t)), 0 },
      /* 7 */ { ss.identity(SELECT(kexp_t)), 0 },
      /* 8 */ { krat_exp_t (ss), 0 },
      /* 9 */ { krat_exp_t (ss, std::basic_string<letter_t> (larray)), 2 },
      /* 10 */ { krat_exp_t (ss), -1 }
    };

  unsigned int nb_tests = 0;
  unsigned int nb_succs = 0;

  for (unsigned int i = 0; exps[i].len >= 0; ++i)
    {
      ++nb_tests;
      std::list<letter_t> r = flatten(exps[i].exp);
      if (int (r.size()) == exps[i].len)
	{
	  bool success = true;
	  letter_t cur = a;
	  for (typename std::list<letter_t>::const_iterator it = r.begin();
	       success and (it != r.end());
	       ++it)
	    {
	      if (*it != cur)
		success = false;
	      cur = cur == a ? b : a;
	    }
	  if (success)
	    ++nb_succs;
	  else
	    {
	      std::cerr << "FAIL: [" << i <<  "] " << exps[i].exp
			<< " : bad letters in list." << std::endl;
	    }
	}
      else
	std::cerr << "FAIL: [" << i << "] " << exps[i].exp
		  << " : list has bad size " << r.size() << " instead of "
		  << exps[i].len << std::endl;
    }

  std::string rate;
  SUCCESS_RATE(rate, nb_succs, nb_tests);
  TEST(t, "Flatten on all kind of basic expressions " + rate,
       nb_tests == nb_succs);

  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_FLATTEN_TEST_HH
