// coherence_state_edge_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_COHERENCE_STATE_EDGE_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_COHERENCE_STATE_EDGE_TEST_HH

# include <map>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>

template <class Auto>
unsigned coherence_state_edge_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef GenRandomAutomata<Auto> gen_auto_t;
  gen_auto_t gen(time(0x0));
  typedef Auto automaton_t;
  automaton_t automaton(gen.generate_dfa(10).structure());

  hstate_t s1 = automaton.add_state();
  hstate_t s2 = automaton.add_state();

  hedge_t h1 = automaton.add_letter_edge(s1, s2,
					 automaton.structure().series().
					 monoid().alphabet().choose());

  EQTEST(t, "Check number of state.", automaton.states().size(), 2);
  EQTEST(t, "Check number of edge.", automaton.edges().size(), 1);

  automaton.del_state(s1);
  automaton.del_state(s2);

  TEST(t, "Check for zombies edge.", automaton.edges().size() == 0);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_COHERENCE_STATE_EDGE_TEST_HH
