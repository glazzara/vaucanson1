// accessible_bench.hh: this file is part of the Vaucanson project.
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
#ifndef BENCHS_ITERATORS_ITERATOR_BENCH_HH
# define BENCHS_ITERATORS_ITERATOR_BENCH_HH

# define CONTEXT boolean_automaton

# define CONTEXT_HEADER <vaucanson/CONTEXT.hh>

# include CONTEXT_HEADER
# include <iostream>
# include <list>
# include <vector>

using namespace vcsn;
using namespace vcsn::CONTEXT;

# include <common/bench_constructs.hh>

static void run_through_using_deltai(const automaton_t& a)
{
  AUTOMATON_TYPES_EXACT(automaton_t);
  for_all_states(s, a)
    for (delta_iterator i(a.value(), *s); ! i.done(); i.next());
}

void iterator_bench(int n_states)
{
  if (not n_states)
    return;

  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');

  automaton_t a = make_automaton(alpha);
  std::vector<hstate_t>	state_list;

  {
    BENCH_START("iterator building process",
		"Vaucanson - iterator.\n"
		"Complete automaton building process.");

    for (int i = 0; i < n_states; ++i)
      state_list.push_back(a.add_state());
    for (std::vector<hstate_t>::iterator i = state_list.begin(); i != state_list.end(); ++i)
      for (std::vector<hstate_t>::iterator j = state_list.begin(); j != state_list.end(); ++j)
	a.add_spontaneous(*i, *j);

    BENCH_STOP();

    BENCH_PARAMETER("n_states", (long) n_states);
    std::stringstream name;
    name << "bench_iterator_building_process_" << n_states;
    BENCH_VCSN_SAVE_AND_PRINT(name.str());
  }

  {
    BENCH_START("iterator deltai",
		"Vaucanson - iterator.\n"
		"Deltai.");

    run_through_using_deltai(a);

    BENCH_STOP();

    BENCH_PARAMETER("n_states", (long) n_states);
    std::stringstream name;
    name << "bench_iterator_deltai_" << n_states;
    BENCH_VCSN_SAVE_AND_PRINT(name.str());
  }
}

#endif // ! BENCHS_ITERATORS_ITERATOR_BENCH_HH
