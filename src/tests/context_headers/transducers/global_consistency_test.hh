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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_TESTS_CONTEXT_HEADERS_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH
# define VCSN_TESTS_CONTEXT_HEADERS_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH

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
  TEST_TYPE(output_series_set_t, semiring_t);

  alphabet_t				in_at;
  in_at.insert('a');
  in_at.insert('b');
  alphabet_t				out_at;
  out_at.insert('c');
  out_at.insert('d');

  monoid_t				out_md (out_at);
  monoid_t				in_md(in_at);
  output_series_set_t::semiring_t	out_sg;
  output_series_set_t			out_ss(out_sg, out_md);
  series_set_t				ss (out_ss, in_md);
  automata_set_t			aa (ss);


  automaton_t		a1 = new_automaton(in_at, out_at);
  automaton_t		a2 = new_automaton(in_at.begin(), in_at.end(),
					   out_at.begin(), out_at.end());

  TEST(t, "new_automaton is consistent.", a1 == a2);
  TEST(t, "new_automaton gives a correct alphabet.",
       a1.structure().series().monoid().alphabet() == in_at);
  TEST(t, "new_automaton gives a correct monoid.",
       a1.structure().series().monoid() == in_md);
  TEST(t, "new_automaton gives a correct semiring.",
       a1.structure().series().semiring() == out_ss);
  TEST(t, "new_automaton gives a correct automata set.", a1.structure() == aa);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_CONTEXT_HEADERS_TRANSDUCERS_GLOBAL_CONSISTENCY_TEST_HH