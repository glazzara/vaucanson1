// krat_exp_derivation_zero_test.hh
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

#ifndef DERIVATION_ZERO_TEST_HH
# define DERIVATION_ZERO_TEST_HH

# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algorithms/krat_exp_derivation.hh>
# include <vaucanson/misc/selectors.hh>

using namespace vcsn;

template <class Expr, class Derivation>
bool krat_exp_derivation_zero_test(tests::Tester& tg)
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
      krat_exp_t random = series.choose(SELECT(kexp_t));
      TEST_DERIVATE(tsts, sucs,
		    zero_as<kexp_t>::of(series), a, 
		    zero_as<kexp_t>::of(series));
      TEST_DERIVATE(tsts, sucs,
		    zero_as<kexp_t>::of(series), b, 
		    zero_as<kexp_t>::of(series));
    }
  
  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a zero. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // DERIVATION_ZERO_TEST_HH
