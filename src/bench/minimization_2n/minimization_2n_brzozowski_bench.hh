// minimization_2n_brzozowski_bench.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/fsm_dump.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>

void minimization_2n_brzozowski_bench(int n_states)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t a = make_automaton(alpha);
  aut_2n(n_states, a);
  a = determinize(a);

  BENCH_START("minimization 2n brzozowski",
	      "Vaucanson - minimization 2n brzozowski.");
  determinize(transpose(determinize(transpose(a))));
  BENCH_STOP();

  BENCH_PARAMETER("n_states", (long) n_states);

  std::stringstream name;
  name << "bench_minimization_2n_brzozowski_" << n_states;
  BENCH_VCSN_SAVE_AND_PRINT(name.str());
}

