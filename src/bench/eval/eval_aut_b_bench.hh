// eval_aut_b_bench.hh: this file is part of the Vaucanson project.
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
#include <vaucanson/tools/fsm_dump.hh>

#include <iostream>

using namespace vcsn;
using namespace vcsn::boolean_automaton;
using namespace vcsn::tools;

#include <common/bench_constructs.hh>

void eval_aut_b_bench(int n)
{
  if (not n)
    return;

  automaton_t a = aut_b();
  automaton_t b = a;

  int np = n - 1;
  while (np--)
    a = product(a, b);

  std::string word;

  for (int i = 0; i < 10000; ++i)
  {
    if (i % 2 < i % 3)
      word += "a";
    else
      word += "b";
  }

  BENCH_START("Vaucanson eval",
	      "Automaton eval benchmark using Vaucanson.\n"
	      "\n"
	      "Input is the nth product of the aut_b automaton.\n"
	      "(see src/bench/common/README_AUTOMATA for aut_b).\n"
	      "\n"
	      "Process:\n"
	      "\n"
	      "1. Generate the input automaton.\n"
	      "2. Take the nth product of the input automaton (parameter _n_)."
	      "\n"
	      "3. Generate an input word of 10 000 symbols (fixed word).\n"
	      "2* Run eval on the input automaton and word.\n");

  bool res = eval(a, word).value();

  BENCH_STOP();

  BENCH_PARAMETER("_n_", (long) n);
  BENCH_PARAMETER("context", "boolean");
  BENCH_PARAMETER("program", "Vaucanson");
  BENCH_PARAMETER("input automaton", "aut_b");

  std::stringstream name;
  name << "aut_b/bench_eval_aut_b_" << n;

  BENCH_VCSN_SAVE_AND_PRINT(name.str());
}

