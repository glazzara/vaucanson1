// quotient_z_bench.hh: this file is part of the Vaucanson project.
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

#include <vaucanson/z_automaton.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>

#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::z_automaton;

#include <common/bench_constructs.hh>

void quotient_z_bench(int n)
{
  automaton_t a = aut_ab();
  automaton_t an = a;

  std::stringstream n_str;
  n_str << n;

  n--;
  while (n--)
    a = product(a, an);

  BENCH_START("Vaucanson quotient (over Z)", "FIXME.");

  automaton_t b = quotient(a);

  BENCH_STOP();

  // Set extra parameters/results
  BENCH_PARAMETER("_n_", n_str.str());
  BENCH_PARAMETER("over", "Z");
  BENCH_PARAMETER("input automaton", "aut_ab");
  BENCH_PARAMETER("product states", (long) a.states().size());
  BENCH_PARAMETER("product transitions", (long) a.transitions().size());

  BENCH_RESULT("quotient states", (long) b.states().size());
  BENCH_RESULT("quotient transitions", (long) b.transitions().size());

  std::string name = "z/bench_quotient_z_" + n_str.str();

  // Save and print
  BENCH_VCSN_SAVE_AND_PRINT(name);
}

