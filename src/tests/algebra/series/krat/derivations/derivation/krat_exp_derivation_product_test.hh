// derivation_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003  Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef DERIVATION_PRODUCT_TEST_HH
# define DERIVATION_PRODUCT_TEST_HH

# include <check/tests_stuff.hh>
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
  TEST_DERIVATION_USUAL_DECS(alphabet, a, b, moinoid, semiring, series);

  const int nb_iter = 20;
  int sucs = 0;
  int tsts = 0;
  for (int i = 0; i < nb_iter; ++i)
    {
      krat_exp_t random = series.choose(SELECT(kexp_t));

      // 1/ LHS is non-cancelable
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
      // FIXME: TODO (will come soon !)
    }
  
  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a product. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // DERIVATION_PRODUCT_TEST_HH
