// minimization_debruijn_moore_bench.hh: this file is part of the Vaucanson project.
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

void minimization_debruijn_moore_bench(int n_value)
{
  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t an = make_automaton(alpha);
  debruijn(n_value, an);

  VCSN_BENCH_START;
  minimization_moore(an);
  VCSN_BENCH_STOP_AND_PRINT;
}

