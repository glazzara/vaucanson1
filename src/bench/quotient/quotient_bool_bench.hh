// quotient_bool_bench.hh: this file is part of the Vaucanson project.
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
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::boolean_automaton;

void binary(automaton_t& an)
{
  std::vector<hstate_t>	       c(2);

  c[0] = an.add_state();
  c[1] = an.add_state();

  an.set_initial(c[0]);
  an.set_final(c[1]);

  an.add_letter_transition(c[0], c[0], 'a');
  an.add_letter_transition(c[0], c[0], 'b');

  an.add_letter_transition(c[0], c[1], 'b');

  an.add_letter_transition(c[1], c[1], 'a');
  an.add_letter_transition(c[1], c[1], 'b');
  an.add_letter_transition(c[1], c[1], 'a');
  an.add_letter_transition(c[1], c[1], 'b');
}

void quotient_bool_bench(int n_power)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t a = make_automaton(alpha);
  binary(a);
  automaton_t an = a;

  std::stringstream n_power_str;
  n_power_str << n_power;

  n_power--;
  while (n_power--)
    a = product(a, an);

  BENCH_START("quotient", "Vaucanson - quotient (over B).");

  automaton_t b = quotient(a);

  BENCH_STOP();

  // Set extra parameters/results
  BENCH_PARAMETER("over", "B");
  BENCH_PARAMETER("n_power", n_power_str.str());
  BENCH_PARAMETER("product states", (long) a.states ().size ());
  BENCH_PARAMETER("product transitions", (long) a.transitions ().size ());

  BENCH_RESULT("quotient states", (long) b.states ().size ());
  BENCH_RESULT("quotient transitions", (long) b.transitions ().size ());

  std::string name = "bench_quotient_bool_" + n_power_str.str();

  // Save and print
  BENCH_VCSN_SAVE_AND_PRINT(name);

}

