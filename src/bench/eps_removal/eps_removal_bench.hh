// eps_removal_bench.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#define CONTEXT boolean_automaton

#define CONTEXT_HEADER <vaucanson/CONTEXT.hh>

#include CONTEXT_HEADER
#include <vaucanson/algorithms/eps_removal.hh>
#include <iostream>

using namespace vcsn;
using namespace vcsn::CONTEXT;

#include <common/bench_constructs.hh>

void eps_removal_bench(int n_states)
{
  if (not n_states)
    return;

  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');

  automaton_t a = make_automaton(alpha);
  aut_linear_eps(n_states, a);

  BENCH_START("eps removal", "Vaucanson - eps removal.");
  automaton_t ret = eps_removal(a);
  BENCH_STOP();

  BENCH_PARAMETER("n_states", (long) n_states);

  std::stringstream name;
  name << "bench_eps_removal_" << n_states;
  BENCH_VCSN_SAVE_AND_PRINT(name.str());
}
