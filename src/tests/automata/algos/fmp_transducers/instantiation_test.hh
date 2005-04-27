// instantiation_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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

#ifndef VCSN_TESTS_FMP_TRANSDUCERS_INSTANTIATION_TEST_HH
# define VCSN_TESTS_FMP_TRANSDUCERS_INSTANTIATION_TEST_HH

# include <vaucanson/misc/static.hh>
# include <vaucanson/algebra/implementation/free_monoid_product/freemonoid_product_pair_str.hh>

using namespace vcsn;
using namespace vcsn::fmp_transducer;

# define TYPE_OK(T1, T2) utility::static_eq<T1, typename Automaton::T2>::value
# define TEST_TYPE(T1, T2) \
TEST(t, #T1 " is consistent.", TYPE_OK(T1, T2))


template <class Automaton>
bool
instantiation_test(tests::Tester& t)
{
  TEST_TYPE(first_alphabet_t, monoid_t::first_monoid_t::alphabet_t);
  TEST_TYPE(second_alphabet_t, monoid_t::second_monoid_t::alphabet_t);
  TEST_TYPE(first_monoid_t, monoid_t::first_monoid_t);
  TEST_TYPE(second_monoid_t, monoid_t::second_monoid_t);
  TEST_TYPE(monoid_t, monoid_t);
  TEST_TYPE(semiring_t, semiring_t);
  TEST_TYPE(series_set_t, series_set_t);
  TEST_TYPE(automata_set_t, set_t);


  bool				test_done = false;

  first_alphabet_t		first_at;
  first_at.insert('a');
  first_at.insert('b');

  second_alphabet_t		second_at;
  second_at.insert('x');
  second_at.insert('y');

  first_monoid_t		first_md (first_at);
  second_monoid_t		second_md (second_at);

  monoid_t			fmp(first_md, second_md);

  semiring_t			sg;
  series_set_t			ss (sg, fmp);
  automata_set_t		aa (ss);

  while (not test_done)
    try
      {
	automaton_t		t1(aa);

	series_set_elt_t	series_elt1(ss);
	series_set_elt_t	series_elt2(ss);

	monoid_elt_value_t	fmp_elt1 =
	  fmp.choose(SELECT(monoid_elt_value_t)).value();
	monoid_elt_value_t	fmp_elt2 =
	  fmp.choose(SELECT(monoid_elt_value_t)).value();

	semiring_elt_value_t	semi_elt = true;
	series_elt1.assoc(fmp_elt1, semi_elt);
	series_elt2.assoc(fmp_elt2, semi_elt);

	hstate_t		s = t1.add_state();
	hstate_t		t = t1.add_state();
	hstate_t		u = t1.add_state();

	t1.set_initial(s);
	t1.set_final(u);

	hedge_t			h1 = t1.add_series_edge(s, t, series_elt1);
	hedge_t			h2 = t1.add_series_edge(t, u, series_elt2);

	test_done = true;
      }
    catch (...)
      {
	test_done = false;
      }


  return t.all_passed();
}

#endif // ! VCSN_TESTS_FMP_TRANSDUCERS_INSTANTIATION_TEST_HH
