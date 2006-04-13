// minimization_debruijn_hopcroft_bench.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#include <common/bench_automaton.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::bench_automaton;

#include <common/algorithm.hh>
#include <common/bench_constructs.hh>

void minimization_debruijn_hopcroft_bench(int n_value)
{
  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t an = make_automaton(alpha);

  debruijn(n_value, an);

  std::ofstream tmp_o_file("init_o_tmp.fsm");
  fsm_dump(tmp_o_file, an);
  tmp_o_file.close();

  VCSN_BENCH_START;
  automaton_t dn = minimization_hopcroft(an);
  VCSN_BENCH_STOP_AND_PRINT;
}

