// global_consistency_test.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_TESTS_CONTEXT_HEADERS_FMP_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH
# define VCSN_TESTS_CONTEXT_HEADERS_FMP_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH

# include <vaucanson/misc/static.hh>

bool
operator == (const automaton_t& a, const automaton_t& b)
{
  return
    a.states().size() == b.states().size() and
    a.edges().size() == b.edges().size() and
    a.initial().size() == b.initial().size() and
    a.final().size() == b.final().size();
}

# define TYPE_OK(T1, T2) utility::static_eq<T1, typename Automaton::T2>::value
# define TEST_TYPE(T1, T2) \
TEST(t, #T1 " is consistent.", TYPE_OK(T1, T2))

template <class Automaton>
bool
global_consistency_test(tests::Tester& t)
{
  TEST_TYPE(first_alphabet_t, monoid_t::first_monoid_t::alphabet_t);
  TEST_TYPE(second_alphabet_t, monoid_t::second_monoid_t::alphabet_t);
  TEST_TYPE(first_monoid_t, monoid_t::first_monoid_t);
  TEST_TYPE(second_monoid_t, monoid_t::second_monoid_t);
  TEST_TYPE(monoid_t, monoid_t);
  TEST_TYPE(semiring_t, semiring_t);
  TEST_TYPE(series_set_t, series_set_t);
  TEST_TYPE(automata_set_t, set_t);

  bool			test_done = false;

  first_alphabet_t	first_at;
  first_at.insert('a');
  first_at.insert('b');

  second_alphabet_t	second_at;
  second_at.insert('x');
  second_at.insert('y');

  first_alphabet_t	other_first_at;
  first_at.insert('c');
  first_at.insert('d');

  second_alphabet_t	other_second_at;
  second_at.insert('z');
  second_at.insert('t');

  first_monoid_t	first_md (first_at);
  second_monoid_t	second_md (second_at);

  monoid_t		fmp(first_md, second_md);

  semiring_t		sg;
  series_set_t		ss (sg, fmp);
  automata_set_t	aa (ss);


  monoid_elt_value_t	fmp_elt ("aa", "yx");

  monoid_elt_t	couple = make_couple(first_at, second_at, "aa", "yx");

  TEST(t, "make_couple works.", fmp_elt == couple.value());

  while (not test_done)
    try
      {
	automaton_t		a1 = new_automaton(first_at, second_at);
	automaton_t		a2 = new_automaton(first_at.begin(),
						   first_at.end(),
						   second_at.begin(),
						   second_at.end());
	automaton_t		a3 (aa);
	automaton_t		a4 = new_automaton(other_first_at,
						   other_second_at);

	TEST(t, "new_automaton is consistent.", a1 == a2);
	TEST(t, "new_automaton gives a correct alphabet.",
	     a1.structure().series().monoid().first_monoid().alphabet()
	     == first_at
	     and
	     a1.structure().series().monoid().second_monoid().alphabet()
	     == second_at);
	TEST(t, "new automaton alphabet is consistent.",
	     a1.structure().series().monoid().first_monoid().alphabet()
	     != other_first_at
	     and
	     a1.structure().series().monoid().second_monoid().alphabet()
	     != other_second_at);
	TEST(t, "new_automaton gives a correct monoid.",
	     a1.structure().series().monoid() == fmp);
	TEST(t, "new_automaton gives a correct semiring.",
	     a1.structure().series().semiring() == sg);
	TEST(t, "new_automaton gives a correct automata set.",
	     a1.structure() == aa);
	TEST(t, "new automata set is consistent.",
	     a1.structure() != a4.structure());

	test_done = true;
      }
    catch (...)
      {
	test_done = false;
      }
  return t.all_passed();

}

#endif // !VCSN_TESTS_CONTEXT_HEADERS_FMP_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH
