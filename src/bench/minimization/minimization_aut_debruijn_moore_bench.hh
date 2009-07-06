// minimization_aut_debruijn_moore_bench.hh: this file is part of the Vaucanson project.
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
#include <vaucanson/algorithms/minimization_moore.hh>

#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>

void minimization_aut_debruijn_moore_bench(int n)
{
  automaton_t a = aut_debruijn(n);

  BENCH_START("Vaucanson minimization (moore)",
	      "FIXME.");
  automaton_t d = minimization_moore(a);
  BENCH_STOP();

  BENCH_PARAMETER("_n_", (long) n);
  BENCH_PARAMETER("program", "Vaucanson");
  BENCH_PARAMETER("algorithm", "moore");
  BENCH_PARAMETER("input automaton", "aut_debruijn");

  std::stringstream name;
  name << "aut_debruijn_moore/bench_minimization_aut_debruijn_moore_" << n;
  BENCH_VCSN_SAVE_AND_PRINT(name.str());
}
