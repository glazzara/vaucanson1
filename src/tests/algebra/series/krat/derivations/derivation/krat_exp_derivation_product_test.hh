// krat_exp_derivation_product_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_PRODUCT_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_PRODUCT_TEST_HH

# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algorithms/krat_exp_derivation.hh>
# include <vaucanson/misc/selectors.hh>

using namespace vcsn;

template <class Expr, class Derivation>
bool krat_exp_derivation_product_test(tests::Tester& tg)
{
  TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation);

  tests::Tester t(tg.verbose());
  srand(time(0));
  TEST_DERIVATION_USUAL_DECS(alphabet, a, b, monoid, semiring, series);

  const int nb_iter = 20;
  int sucs = 0;
  int tsts = 0;
  for (int i = 0; i < nb_iter; ++i)
    {
      // 1/ LHS is non-cancelable

      krat_exp_t random = series.choose(SELECT(kexp_t));
      // 0.xyz
      TEST_DERIVATE(tsts, sucs, zero_as<kexp_t>::of(series) * random, a,
		    zero_as<kexp_t>::of(series));
      // a.xyz
      TEST_DERIVATE(tsts, sucs, a * random, a, random);
      TEST_DERIVATE(tsts, sucs, a * random, b, zero_as<kexp_t>::of(series));
      // (a+b).xyz
      TEST_DERIVATE(tsts, sucs,
		    (krat_exp_t (a) + krat_exp_t (b)) * random, a, random);
      TEST_DERIVATE(tsts, sucs,
		    (krat_exp_t (a) + krat_exp_t (b)) * random, b, random);
      // (a.b).xyz
      TEST_DERIVATE(tsts, sucs,
		    (krat_exp_t (a) * krat_exp_t (b)) * random, a, b * random);
      TEST_DERIVATE(tsts, sucs,
		    (krat_exp_t (a) * krat_exp_t (b)) * random, b,
		    zero_as<kexp_t>::of(series));

      // 2/ LHS *is* cancelable

      std::pair<krat_exp_t, krat_exp_t> random_a =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, krat_exp_t> random_b =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, b);
      std::pair<krat_exp_t, krat_exp_t> cancel_a =
       choose_cancelable_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, krat_exp_t> cancel_b =
       choose_cancelable_exp_and_derivate<derivation_t, krat_exp_t>(series, b);
      // cancelable * random
      TEST_DERIVATE(tsts, sucs,
		    cancel_a.first * random_a.first, a,
		    cancel_a.second * random_a.first + random_a.second);
      TEST_DERIVATE(tsts, sucs,
		    cancel_b.first * random_b.first, b,
		    cancel_b.second * random_b.first + random_b.second);
    }
  
  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a product. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_PRODUCT_TEST_HH
