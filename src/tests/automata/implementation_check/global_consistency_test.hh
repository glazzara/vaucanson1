// global_consistency_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_GLOBAL_CONSISTENCY_TEST_HH
# define VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_GLOBAL_CONSISTENCY_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/automaton_tools.hh>

# include <map>
# include <stack>
# include <time.h>

template <class Auto>
unsigned global_consistency_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;

  GenRandomAutomata<Auto> gen(time(0x0));

  automaton_t automaton = gen.generate(12, 20);

  std::deque<hstate_t> sc = choose_n_states(automaton, 3);
  hstate_t s1 = sc.front();
  sc.pop_front();
  hstate_t s2 = sc.front();
  sc.pop_front();
  hstate_t s3 = sc.front();
  sc.pop_front();

  automaton.del_state(s1);
  automaton.del_state(s2);
  automaton.del_state(s3);

  // call our function to check consistency of the automaton.

  bool final = true;
  for (typename automaton_t::edge_iterator i = automaton.edges().begin();
       i != automaton.edges().end();
       i++)
    {
      hstate_t aim  = automaton.aim_of(*i);
      hstate_t from = automaton.origin_of(*i);
      bool res  = false;
      bool res2 = false;

      for (typename automaton_t::state_iterator j =
	     automaton.states().begin();
	   j != automaton.states().end();
	   j++)
	{
	  if (*j == aim)
	    res = true;
	  if (*j == from)
	    res2 = true;
	}
      final = final && res && res2;
    }

  TEST(t, "All edges are well defined.", final);

  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_GLOBAL_CONSISTENCY_TEST_HH
