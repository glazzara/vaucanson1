// iterator_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ITERATOR_TEST_HH
# define TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ITERATOR_TEST_HH

# include <algorithm>
# include <vector>
# include <vaucanson/tools/gen_random.hh>
# include <tests/check/tester.hh>

template <class Auto>
unsigned iterator_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  AUTOMATON_TYPES(Auto);


  using namespace vcsn;
  using namespace vcsn::tools;
//  using namespace vcsn::algebra;

  typedef Auto automaton_t;
  typedef std::vector<hstate_t> state_list_t;
  typedef std::vector<htransition_t> transition_list_t;
  typedef std::map<hstate_t, transition_list_t> transition_map_t;


  GenRandomAutomata<Auto> gen;

  automaton_t automaton = gen.empty();
  state_list_t state_list;
  transition_map_t transition_map;

  // state at index i in state_list has i transitions
  //  -> 1 to each states with a lower id in the list.
  std::cout << "Creating automaton:" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    hstate_t s = automaton.add_state();
    state_list.push_back(s);
    transition_map.insert(std::make_pair(s, transition_list_t()));
    for (int j = 0; j < i; ++j)
      transition_map[s].push_back(automaton.add_spontaneous(s, state_list[j]));
    std::cout << "  step " << i << ": " << automaton << std::endl;
  }
  std::cout << std::endl;

  // Simple iterations over each states
  //  Checking if the accessed states are correct
  std::cout << "Testing deltai over states" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (delta_state_iterator s(automaton.value(), state_list[i]);
	 ! s.done(); s.next())
    {
      if (state_list[size_t(automaton.get_state(*s))] == *s)
	++count;
    }
    EQTEST(t, "Basic iterations over states", count, i);
  }
  std::cout << std::endl;

  // Simple iterations over each transitions
  //  Checking if the accessed transitions are correct
  std::cout << "Testing deltai over transitions" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (delta_transition_iterator s(automaton.value(), state_list[i]);
	 ! s.done(); s.next())
    {
      if (transition_map[state_list[i]][size_t(automaton.dst_of(*s))] == *s &&
	  automaton.src_of(*s) == state_list[i])
	++count;
    }
    EQTEST(t, "Basic iterations over transitions", count, i);
  }
  std::cout << std::endl;

  // Simple iterations over each states
  //  Checking if the accessed states are correct
  std::cout << "Testing rdeltai over states" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (rdelta_state_iterator s(automaton.value(), state_list[i]);
	 ! s.done(); s.next())
    {
      if (state_list[size_t(automaton.get_state(*s))] == *s)
	++count;
    }
    EQTEST(t, "Basic iterations over states", count, 9 - i);
  }
  std::cout << std::endl;

  // Simple iterations over each transitions
  //  Checking if the accessed transitions are correct
  std::cout << "Testing rdeltai over transitions" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (rdelta_transition_iterator s(automaton.value(), state_list[i]);
	 ! s.done(); s.next())
    {
      if (transition_map[automaton.src_of(*s)][size_t(state_list[i])] == *s &&
	  automaton.dst_of(*s) == state_list[i])
	++count;
    }
    EQTEST(t, "Basic iterations over transitions", count, 9 -i);
  }
  std::cout << std::endl;



#if 0
  // Simple iterations over each states
  //  Checking if the accessed states are correct
  std::cout << "Testing deltai over states" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (delta_state_iterator s = automaton.deltai(state_list[i], delta_kind::states());
	 ! s.done(); ++s)
    {
      if (state_list[size_t(automaton.get_state(*s))] == *s)
	++count;
    }
    EQTEST(t, "Basic iterations over states", count, i);
  }
  std::cout << std::endl;

  // Simple iterations over each transitions
  //  Checking if the accessed transitions are correct
  std::cout << "Testing deltai over transitions" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (delta_transition_iterator s = automaton.deltai(state_list[i], delta_kind::transitions());
	 ! s.done(); ++s)
    {
      if (transition_map[state_list[i]][size_t(automaton.dst_of(*s))] == *s &&
	  automaton.src_of(*s) == state_list[i])
	++count;
    }
    EQTEST(t, "Basic iterations over transitions", count, i);
  }
  std::cout << std::endl;

  // Simple iterations over each states
  //  Checking if the accessed states are correct
  std::cout << "Testing rdeltai over states" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (delta_state_iterator s = automaton.rdeltai(state_list[i], delta_kind::states());
	 ! s.done(); ++s)
    {
      if (state_list[size_t(automaton.get_state(*s))] == *s)
	++count;
    }
    EQTEST(t, "Basic iterations over states", count, i);
  }
  std::cout << std::endl;
#endif

  /* FIXME Enable test when erase is functionnal.
  int j = 0;
  for (delta_state_iterator s = automaton.deltai(state_list[9], delta_kind::states());
       ! s.done(); ++s)
  {
    std::cout << j << std::endl;
    ++j;
    s.erase();
  }
  EQTEST(t, "Basic state deletion", 1, automaton.states().size());
  */

  return t.all_passed();
}

#endif // ! TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ITERATOR_TEST_HH
