// krat_exp_partial_derivation_letter_test.hh: this file is part of the Vaucanson project.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_LETTER_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_LETTER_TEST_HH

# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_partial_derivation.hh>
# include <krat_exp_partial_derivation_common.hh>

using namespace vcsn;

template <class Expr, class Derivation>
bool krat_exp_partial_derivation_letter_test(tests::Tester& tg)
{
  TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation);

  tests::Tester t(tg.verbose());
  srand(time(0));
  TEST_DERIVATION_USUAL_DECS(al, a, b, md, sg, ss);

  std::set<Expr>	id_set;
  id_set.insert(identity_as<kexp_t>::of(ss));

  int sucs = 0;
  int tsts = 0;
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, a), a, id_set);
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, b), a, std::set<Expr>());
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, a), b, std::set<Expr>());
  TEST_DERIVATE(tsts, sucs,
		krat_exp_t (ss, b), b, id_set);

  std::string rate;
  SUCCESS_RATE(rate, sucs, tsts);
  TEST(t, "Various derivation tests on a letter. " + rate, sucs == tsts);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_DERIVATIONS_PARTIAL_DERIVATION_KRAT_EXP_PARTIAL_DERIVATION_LETTER_TEST_HH
