// minimization_aut_2n_hopcroft_bench.hh: this file is part of the Vaucanson project.
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
#include <vaucanson/algorithms/minimization_hopcroft.hh>

#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>

void minimization_aut_2n_hopcroft_bench(int n)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  automaton_t a = aut_2n(n);
  a = determinize(a);

  BENCH_START("Vaucanson minimization (hopcroft)",
	      "FIXME.");
  minimization_hopcroft(a);
  BENCH_STOP();

  BENCH_PARAMETER("_n_", (long) n);
  BENCH_PARAMETER("program", "Vaucanson");
  BENCH_PARAMETER("algorithm", "hopcroft");
  BENCH_PARAMETER("input automaton", "aut_2n");

  std::stringstream name;
  name << "aut_2n_hopcroft/bench_minimization_aut_2n_hopcroft_" << n;
  BENCH_VCSN_SAVE_AND_PRINT(name.str());
}

