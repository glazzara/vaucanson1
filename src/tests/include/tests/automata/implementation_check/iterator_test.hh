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

  //
  // Construct the transposed view and the identity view.
  //

  // Type helpers
  typedef Element<typename automaton_t::set_t,
		  TransposeView<typename automaton_t::value_t> >
	tr_automaton_t;
  typedef typename tr_automaton_t::delta_iterator transpose_delta_iterator;
  typedef typename tr_automaton_t::rdelta_iterator transpose_rdelta_iterator;
  typedef Element<typename automaton_t::set_t,
		  IdentityView<typename automaton_t::value_t> >
	id_automaton_t;
  typedef typename id_automaton_t::delta_iterator identity_delta_iterator;
  typedef typename id_automaton_t::rdelta_iterator identity_rdelta_iterator;

  const tr_automaton_t& transpose_aut = tr_automaton_t(automaton.structure(), TransposeView<typename automaton_t::value_t>(automaton.value()));
  const id_automaton_t& identity_aut = id_automaton_t(automaton.structure(), IdentityView<typename automaton_t::value_t>(automaton.value()));

  /*---------------.
  | delta_iterator |
  `---------------*/

# define CHECK_VIEW_ITERATOR(view, src, dst, tt)		\
  std::cout << "Testing " #src "deltai (" #view "_view)"	\
  << std::endl;							\
  for (int i = 0; i < 10; ++i)					\
  {								\
    int count = 0;						\
    view##_##src##delta_iterator a(view##_aut.value(),		\
					    state_list[i]);	\
    dst##delta_iterator b(automaton.value(), state_list[i]);	\
    while (!a.done())						\
    {								\
      if (*a != *b)						\
	break;							\
      a.next();							\
      b.next();							\
      if (a.done() != b.done())					\
	break;							\
      ++count;							\
    }								\
    EQTEST(t, "Basic iterations (" #view "_view)", count, tt);	\
  }								\
  std::cout << std::endl

  //
  // Simple iterations over each transitions
  //

  // Checking if the accessed transitions are correct
  std::cout << "Testing deltai over transitions" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (delta_iterator s(automaton.value(), state_list[i]);
	 ! s.done(); s.next())
    {
      if (transition_map[state_list[i]][size_t(automaton.dst_of(*s))] == *s &&
	  automaton.src_of(*s) == state_list[i])
	++count;
    }
    EQTEST(t, "Basic iterations over transitions", count, i);
  }
  std::cout << std::endl;

  // Checking if the deltai type for transpose_view on transitions is correct
  CHECK_VIEW_ITERATOR(transpose, , r, 9 - i);
  // Checking if the deltai type for identity_view on transitions is correct
  CHECK_VIEW_ITERATOR(identity, , , i);

  /*----------------.
  | rdelta_iterator |
  `----------------*/

  //
  // Simple iterations over each transitions
  //

  // Checking if the accessed transitions are correct
  std::cout << "Testing rdeltai over transitions" << std::endl;
  for (int i = 0; i < 10; ++i)
  {
    int count = 0;
    for (rdelta_iterator s(automaton.value(), state_list[i]);
	 ! s.done(); s.next())
    {
      if (transition_map[automaton.src_of(*s)][size_t(state_list[i])] == *s &&
	  automaton.dst_of(*s) == state_list[i])
	++count;
    }
    EQTEST(t, "Basic iterations over transitions", count, 9 -i);
  }
  std::cout << std::endl;

  // Checking if the deltai type for transpose_view on transitions is correct
  CHECK_VIEW_ITERATOR(transpose, r, , i);
  // Checking if the deltai type for identity_view on transitions is correct
  CHECK_VIEW_ITERATOR(identity, r, r, 9 - i);

# undef CHECK_VIEW_ITERATOR

  return t.all_passed();
}

#endif // ! TESTS_AUTOMATA_IMPLEMENTATION_CHECK_ITERATOR_TEST_HH
