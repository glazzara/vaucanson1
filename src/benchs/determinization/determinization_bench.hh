// determinization_bench.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include <common/bench_automaton.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <iostream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::bench_automaton;

#include <common/bench_constructs.hh>

void determinization_bench(int n_states)
{
  if (not n_states)
    return;

  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  automaton_t a = new_automaton(alpha);
  aut_2n(n_states, a);
  VCSN_BENCH_START;
  automaton_t ret = determinize(a);
  VCSN_BENCH_STOP_AND_PRINT;
}

