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

void eps_removal_bench(int n)
{
  if (not n)
    return;

  automaton_t a = aut_linear_eps(n);

  BENCH_START("Vaucanson epsilon removal", "FIXME.");
  automaton_t ret = eps_removal(a);
  BENCH_STOP();

  BENCH_PARAMETER("_n_", (long) n);

  std::stringstream name;
  name << "aut_linear_eps/bench_eps_removal_" << n;
  BENCH_VCSN_SAVE_AND_PRINT(name.str());
}
