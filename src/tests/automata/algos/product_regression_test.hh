// product_regression_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_PRODUCT_REGRESSION_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_PRODUCT_REGRESSION_TEST_HH

# include <vaucanson/algorithms/product.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <ostream>

template <class Auto>
unsigned
product_regression_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  using vcsn::hstate_t;

  tests::Tester t(tg.verbose());

  alphabet_t	at;
  letter_t	l1 = at.random_letter();
  letter_t	l2;
  do
    l2 = at.random_letter();
  while (l1 == l2) ;
  at.insert(l1);
  at.insert(l2);

  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  automaton_t	lhs (aa);
  hstate_t	s1 = lhs.add_state();
  hstate_t	s2 = lhs.add_state();
  lhs.add_letter_edge(s1, s2, l1);
  lhs.set_initial(s1);
  lhs.set_final(s2);

  automaton_t	rhs (aa);
  s1 = rhs.add_state();
  s2 = rhs.add_state();
  rhs.add_letter_edge(s1, s2, l2);
  rhs.set_initial(s1);
  rhs.set_final(s2);

  automaton_t prod = product(lhs, rhs);

  TEST(t,"Regression test for product() [1/4].", prod.states().size() == 1);
  TEST(t,"Regression test for product() [2/4].", prod.initial().size() == 1);
  TEST(t,"Regression test for product() [3/4].", prod.final().size() == 0);
  TEST(t,"Regression test for product() [4/4].", prod.edges().size() == 0);

  if (not t.all_passed())
    {
      SAVE_AUTOMATON_DOT("/tmp", "product_regression_test", prod, 0);
      std::cerr << "Product saved in /tmp/product_regression_test_0.dot"
		<< std::endl;
    }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_PRODUCT_REGRESSION_TEST_HH
