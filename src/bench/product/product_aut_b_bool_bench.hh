// product_aut_b_bench.hh: this file is part of the Vaucanson project.
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
#include <vaucanson/algorithms/product.hh>

#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::boolean_automaton;

#include <common/bench_constructs.hh>

void product_aut_b_bool_bench(int n)
{
  automaton_t a = aut_b();
  automaton_t b = a;

  std::stringstream n_str;
  n_str << n;

  BENCH_START("Vaucanson product (over B)",
	      "Automaton product benchmark using Vaucanson.\n"
	      "\n"
	      "Input automaton is aut_b.\n"
	      "(see src/bench/common/README_AUTOMATA for aut_b).\n"
	      "\n"
	      "Process:\n"
	      "\n"
	      "1. Generate a and b, both aut_b.\n"
	      "2* Do a = product(a, b) n times.\n");

  n--;
  while (n--)
    a = product(a, b);

  BENCH_STOP();

  // Set extra parameters/results
  BENCH_PARAMETER("_n_", n_str.str());
  BENCH_PARAMETER("over", "B");

  BENCH_RESULT("product states", (long) a.states().size());
  BENCH_RESULT("product transitions", (long) a.transitions().size());

  std::string name = "aut_b_bool/bench_product_aut_b_bool_" + n_str.str();

  // Save and print
  BENCH_VCSN_SAVE_AND_PRINT(name);
}

