// global_consistency_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
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
  tests::Tester t(tg);

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::algebra;

  GenRandomAutomata<Auto> gen;

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
  for (typename automaton_t::transition_iterator i = automaton.transitions().begin();
       i != automaton.transitions().end();
       i++)
  {
    hstate_t dst  = automaton.dst_of(*i);
    hstate_t src = automaton.src_of(*i);
    bool res  = false;
    bool res2 = false;

    for (typename automaton_t::state_iterator j =
	   automaton.states().begin();
	 j != automaton.states().end();
	 j++)
    {
      if (*j == dst)
	res = true;
      if (*j == src)
	res2 = true;
    }
    final = final && res && res2;
  }

  TEST(t, "All transitions are well defined.", final);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_IMPLEMENTATION_CHECK_GLOBAL_CONSISTENCY_TEST_HH
