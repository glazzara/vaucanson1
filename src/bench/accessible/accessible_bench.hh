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

#ifndef BENCHS_ACCESSIBLE_ACCESSIBLE_BENCH_HH
# define BENCHS_ACCESSIBLE_ACCESSIBLE_BENCH_HH

# define CONTEXT boolean_automaton

# define CONTEXT_HEADER <vaucanson/CONTEXT.hh>

# include CONTEXT_HEADER
# include <vaucanson/algorithms/accessible.hh>

# include <iostream>
# include <vector>

using namespace vcsn;
using namespace vcsn::CONTEXT;

#include <common/bench_constructs.hh>

void accessible_bench(int n)
{
  if (not n)
    return;

  automaton_t a = aut_complete(n);

  BENCH_START("Vaucanson accessible",
	      "Benchmark for listing the accessible states of an automaton\n"
              "using Vaucanson.\n"
	      "\n"
	      "Input is a complete automaton with n states:\n"
	      "Between any two states, there exists a spontaneous transition.\n"
	      "(see src/bench/common/README_AUTOMATA for aut_complete).\n"
	      "\n"
	      "Process:\n"
	      "\n"
	      "1. Generate the input automaton (with parameter _n_).\n"
	      "2* Run accessible_states on the input automaton.\n");
  accessible_states(a);
  BENCH_STOP();

  BENCH_PARAMETER("_n_", (long) n);

  std::stringstream name;
  name << "default/bench_accessible_" << n;

  BENCH_VCSN_SAVE_AND_PRINT(name.str());
}

#endif // ! BENCHS_ACCESSIBLE_ACCESSIBLE_BENCH_HH
