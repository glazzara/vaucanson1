// add_state_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef ADD_STATE_TEST_HH
# define ADD_STATE_TEST_HH

# include <map>
# include <algorithm>
# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/gen_random.hh>
# include <check/tests_stuff.hh>

template <class Auto> 
unsigned add_state_test(tests::Tester& tg)
{
  tests::Tester t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  srand(time(0));

  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  tools::GenRandomAutomata<Auto> gen(time(0x0));

  automaton_t automaton = gen.empty();

  EQTEST(t, "Initial number of state = 0.", automaton.states().size(), 0);

  hstate_t s1 = automaton.add_state();

  EQTEST(t, "Number of state after one state addition = 1.",
       automaton.states().size(), 1);

  automaton.del_state(s1);

  EQTEST(t, "Number of state after one state deletion = 0.",
	 automaton.states().size(), 0);  

  std::set<hstate_t> s;
  for (unsigned i = 0; i < 3; ++i)
    s.insert(automaton.add_state());
  EQTEST(t, "Number of state after three state additions = 3.", 
	 automaton.states().size(), 3);
  for (std::set<hstate_t>::const_iterator i = s.begin();
       i != s.end(); ++i)
    automaton.del_state(*i);
  EQTEST(t, "Number of state after total deletion in growing order = 0.",
	 automaton.states().size(), 0);  

  for (unsigned i = 0; i < 3; ++i)
    s.insert(automaton.add_state());
  EQTEST(t, "Number of state after three state additions = 3.", 
	 automaton.states().size(), 3);
  for (std::set<hstate_t>::const_reverse_iterator i = s.rbegin();
       i != s.rend(); ++i)
    automaton.del_state(*i);
  EQTEST(t, "Number of state after total deletion in decreasing order = 0.",
	 automaton.states().size(), 0);  

  std::vector<hstate_t> vs;
  for (unsigned i = 0; i < 100; ++i)
    vs.push_back(automaton.add_state());
  std::random_shuffle(vs.begin(), vs.end());
  EQTEST(t, "Number of state after 100 state additions = 100.", 
	 automaton.states().size(), 100);
  for (std::vector<hstate_t>::const_iterator i = vs.begin(); 
       i != vs.end(); ++i)
    automaton.del_state(*i);
  EQTEST(t, "Number of state after total deletion in random order = 0.",
	 automaton.states().size(), 0);  
  
  return t.all_passed();
}

#endif // ADD_STATE_TEST_HH
