// determinization_aut_2n_bench.hh: this file is part of the Vaucanson project.
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
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/tools/fsm_dump.hh>

#include <iostream>

using namespace vcsn;
using namespace vcsn::boolean_automaton;
using namespace vcsn::tools;

#include <common/bench_constructs.hh>

void determinization_aut_2n_bench(int n)
{
  if (not n)
    return;

  automaton_t aut = aut_2n(n);

  BENCH_START("Vaucanson determinization",
	      "Automaton determinization benchmark using Vaucanson.\n"
	      "\n"
	      "Input has 2^n states when determinized\n"
	      "(see src/bench/common/README_AUTOMATA for aut_2n).\n"
	      "\n"
	      "Process:\n"
	      "\n"
	      "1. Generate the input automaton (with parameter _n_).\n"
	      "2* Run determinize on the input automaton.\n");

  automaton_t res = determinize(aut);

  BENCH_STOP();

  BENCH_PARAMETER("_n_", (long) n);
  BENCH_PARAMETER("program", "Vaucanson");
  BENCH_PARAMETER("input automaton", "aut_2n");
  BENCH_PARAMETER("states (input)", (long) aut.states ().size ());
  BENCH_RESULT("states (determinized)", (long) res.states ().size ());

  std::stringstream name;
  name << "aut_2n/bench_determinization_aut_2n_" << n;

  BENCH_VCSN_SAVE_AND_PRINT(name.str());
}

