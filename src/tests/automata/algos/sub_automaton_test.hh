// sub_automaton_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_SUB_AUTOMATON_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_SUB_AUTOMATON_TEST_HH

#include <vaucanson/automata/concept/handlers.hh>
#include <vaucanson/algorithms/sub_automaton.hh>

#include <set>

template <class Auto>
unsigned sub_automaton_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);
  
  // Algebraic structures.
  alphabet_t		alphabet;
  letter_t		a (alphabet.random_letter());
  letter_t		b (alphabet.random_letter());
  while (a == b)
    b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t		monoid(alphabet);
  semiring_t 		semiring;
  series_t		series(semiring, monoid);
  automata_set_t	automata(series);
  automaton_t		automaton(automata);

  // States.
  vcsn::hstate_t s1 = automaton.add_state();
  vcsn::hstate_t s2 = automaton.add_state();
  vcsn::hstate_t s3 = automaton.add_state();
  automaton.set_initial(s1);
  automaton.set_initial(s3);
  automaton.set_final(s2);
  automaton.set_final(s3);

  // Show me the bug!
  std::set<vcsn::hstate_t> to_be_kept;
  to_be_kept.insert(s1);
  to_be_kept.insert(s2);
  automaton_t r = sub_automaton(automaton, to_be_kept);

  TEST(t, "r seems consistent. ",
       r.has_state(s1) && r.has_state(s2) && !r.has_state(s3));

  TEST(t, "r has a consistent max. ", r.states().max() == s2);

  TEST(t, "r has the right number of states. ", r.states().size() == 2);

  TEST(t, "r has the right number of initial states. ",
       r.initial().size() == 1);
  
  TEST(t, "r has the right number of final states. ", r.final().size() == 1);

  TEST(t, "r has consistant initial states. ",
       r.initial().max() <= r.states().max());
  
  TEST(t, "r has consistant final states. ",
       r.final().max() <= r.states().max());

  for_each_state(s, r)
    TEST(t, "r has the right states. ", *s <= r.states().max());

  for_each_state(s, r)
    TEST(t, "r has the right initial states. ", *s <= r.states().max());

  for_each_state(s, r)
    TEST(t, "r has the right final states. ", *s <= r.states().max());

  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_SUB_AUTOMATON_TEST_HH
