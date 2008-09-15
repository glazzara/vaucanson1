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
#ifndef BENCHS_ITERATORS_ACCESSIBLE_BENCH_HH
# define BENCHS_ITERATORS_ACCESSIBLE_BENCH_HH

# define CONTEXT_HEADER <vaucanson/CONTEXT.hh>

# include CONTEXT_HEADER
# include <vaucanson/algorithms/accessible.hh>
# include <iostream>
# include <vector>

using namespace vcsn;
using namespace vcsn::CONTEXT;

# include <common/bench_constructs.hh>

void accessible_bench(int n_states)
{
  if (not n_states)
    return;

  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');

  automaton_t a = make_automaton(alpha);
  std::vector<hstate_t>	state_list;

  for (int i = 0; i < n_states; ++i)
    state_list.push_back(a.add_state());
  a.set_initial(a.get_state(0));
  a.set_final(a.get_state(0));

  for (std::vector<hstate_t>::iterator i = state_list.begin(); i != state_list.end(); ++i)
    for (std::vector<hstate_t>::iterator j = state_list.begin(); j != state_list.end(); ++j)
      a.add_spontaneous(*i, *j);

  VCSN_BENCH_START;
//automaton_t ret = accessible(a);
  accessible_states(a);
  VCSN_BENCH_STOP_AND_PRINT;
}

#endif // ! BENCHS_ITERATORS_ACCESSIBLE_BENCH_HH
