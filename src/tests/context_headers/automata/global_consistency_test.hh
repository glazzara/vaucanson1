// global_consistency_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_CONTEXT_HEADERS_AUTOMATA_GLOBAL_CONSISTENCY_TEST_HH
# define VCSN_TESTS_CONTEXT_HEADERS_AUTOMATA_GLOBAL_CONSISTENCY_TEST_HH

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
  TEST_TYPE(alphabet_t, monoid_t::alphabet_t);
  TEST_TYPE(monoid_t, monoid_t);
  TEST_TYPE(semiring_t, semiring_t);
  TEST_TYPE(series_set_t, series_set_t);
  TEST_TYPE(automata_set_t, set_t);

  bool			test_done = false;
  
  alphabet_t		at;
  at.insert('a');
  at.insert('b');

  alphabet_t		other_at;
  at.insert('c');
  at.insert('d');

  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  rat_exp_t		e (ss);
  rat_exp_t		f = new_rat_exp(at);
  rat_exp_t		g = new_rat_exp(at, "a+b");
  TEST(t, "new_rat_exp works. [1/3]", e == f);
  TEST(t, "new_rat_exp works. [2/3]", g != f);

  rat_exp_t::support_t			s = g.supp();
  rat_exp_t::support_t::const_iterator	i = s.begin();
  TEST(t, "new_rat_exp works. [3/3]",
       s.size() == 2 and *i == "a" and *(++i) == "b");

  while (not test_done)
    try
      {
	do
	  e = ss.choose(SELECT(rat_exp_impl_t));
	while (e == zero_as<rat_exp_impl_t>::of(ss));

	automaton_t		a1 = new_automaton(at);
	automaton_t		a2 = new_automaton(at.begin(), at.end());
	automaton_t		a3 (aa);
	automaton_t		a4 = standard_of(e);
	automaton_t		a5 = thompson_of(e);
	automaton_t		a6 = new_automaton(other_at);

	TEST(t, "new_automaton is consistent.", a1 == a2);
	TEST(t, "new_automaton gives a correct alphabet.",
	     a1.structure().series().monoid().alphabet() == at);
	TEST(t, "new automaton alphabet is consistent.",
	     a1.structure().series().monoid().alphabet() != other_at);
	TEST(t, "new_automaton gives a correct monoid.",
	     a1.structure().series().monoid() == md);
	TEST(t, "new_automaton gives a correct semiring.",
	     a1.structure().series().semiring() == sg);
	TEST(t, "new_automaton gives a correct automata set.",
	     a1.structure() == aa);
	TEST(t, "new automata set is consistent.",
	     a1.structure() != a6.structure());

	standard_of(a3, e.value());
	TEST(t, "standard_of is consistent.", a3 == a4);

	thompson_of(a3, e.value());
	TEST(t, "thompson_of is consistent.", a3 == a5);
	test_done = true;
      }
    catch (...)
      {
	test_done = false;
      }
  return t.all_passed();
}

#endif // ! VCSN_TESTS_CONTEXT_HEADERS_AUTOMATA_GLOBAL_CONSISTENCY_TEST_HH
