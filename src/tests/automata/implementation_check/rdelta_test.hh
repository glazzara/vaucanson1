// rdelta_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_RDELTA_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_RDELTA_TEST_HH

#include <vaucanson/automata/concept/handlers.hh>
#include <vaucanson/tools/usual.hh>
#include <vaucanson/tools/dot_dump.hh>

#include <list>
#include <iostream>

template <class Auto>
unsigned rdelta_test(tests::Tester& tg)
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

  // Edges.
  automaton.add_letter_edge(s1, s2, a);
  automaton.add_letter_edge(s2, s1, b);

  // Show me the bug!
  std::list<int> r;
  automaton.rdelta(inserter(r, r.begin()), s2, vcsn::delta_kind::edges());
  TEST(t, "rdelta returns consistent results (1/4). ",
       !r.empty() && (automaton.origin_of(r.front()) == s1));

  r.clear();
  automaton.rdelta(inserter(r, r.begin()), s2, vcsn::delta_kind::states());
  TEST(t, "rdelta returns consistent results (2/4). ",
      	!r.empty() && r.front() == s1);

  r.clear();
  automaton.rdelta(inserter(r, r.begin()), s1, vcsn::delta_kind::edges());
  TEST(t, "rdelta returns consistent results (3/4). ",
       !r.empty() && (automaton.origin_of(r.front()) == s2));

  r.clear();
  automaton.rdelta(inserter(r, r.begin()), s1, vcsn::delta_kind::states());
  TEST(t, "rdelta returns consistent results (4/4). ",
      	!r.empty() && r.front() == s2);

  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_RDELTA_TEST_HH
