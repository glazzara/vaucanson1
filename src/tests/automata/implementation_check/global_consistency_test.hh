// global_consistency_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef GLOBAL_CONSISTENCY_TEST_HH
# define GLOBAL_CONSISTENCY_TEST_HH

# include <map>
# include <set>
# include <time.h>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tests_stuff.hh>
# include <vaucanson/misc/ref.hh>
# include <vaucanson/tools/gen_random.hh>

template <class Auto>
unsigned global_consistency_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
 
  gen_auto_t gen(time(0x0));

  automaton_t automaton = gen.generate(12, 20);

  hstate_t 
    s1 = automaton.select_state(2), 
    s2 = automaton.select_state(7),
    s3 = automaton.select_state(4);
  
  automaton.del_state(s1);
  automaton.del_state(s2);
  automaton.del_state(s3);

  // call our function to check consistency of the automaton.

  bool final = true;
  for (tools::usual_automaton_t::edge_iterator i = automaton.edges().begin(); 
       i != automaton.edges().end();
       i++)
    {
      hstate_t aim  = automaton.aim_of(*i);
      hstate_t from = automaton.origin_of(*i);
      bool res  = false;
      bool res2 = false;

      for (tools::usual_automaton_t::state_iterator j = 
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

#endif // GLOBAL_CONSISTENCY_TEST_HH
