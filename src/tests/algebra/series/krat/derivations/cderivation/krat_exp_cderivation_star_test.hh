// krat_exp_cderivation_star_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_STAR_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_STAR_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_cderivation.hh>

using namespace vcsn;

template <class Expr, class Derivation>
bool krat_exp_cderivation_star_test(tests::Tester& tg)
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
      std::pair<krat_exp_t, krat_exp_t> rnd_a =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, a);
      std::pair<krat_exp_t, krat_exp_t> rnd_b =
	choose_exp_and_derivate<derivation_t, krat_exp_t>(series, b);
      krat_exp_t rnd_star_a = rnd_a.first;
      rnd_star_a.star();
      krat_exp_t rnd_star_b = rnd_b.first;
      rnd_star_b.star();
      TEST_DERIVATE(tsts, sucs,
		    rnd_star_a, a,
		    rnd_a.second * rnd_star_a);
      TEST_DERIVATE(tsts, sucs,
		    rnd_star_b, b,
		    rnd_b.second * rnd_star_b);
    }
  
  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a star. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_DERIVATION_KRAT_EXP_DERIVATION_STAR_TEST_HH
