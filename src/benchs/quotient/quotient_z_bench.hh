// quotient_z_bench.hh: this file is part of the Vaucanson project.
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
#include <vaucanson/z_automaton.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <iostream>
#include <fstream>

using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::z_automaton;

void binary(automaton_t& an)
{
  std::vector<hstate_t>        c(2);

  c[0] = an.add_state();
  c[1] = an.add_state();

  an.set_initial(c[0]);
  an.set_final(c[1]);

  an.add_letter_edge(c[0], c[0], 'a');
  an.add_letter_edge(c[0], c[0], 'b');

  an.add_letter_edge(c[0], c[1], 'b');

  an.add_weighted_edge(c[1], c[1], 2, "a");
  an.add_weighted_edge(c[1], c[1], 2, "b");
}

void quotient_z_bench(int n_power)
{
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t a = new_automaton(alpha);
  binary(a);
  automaton_t an = a;

  n_power--;
  while (n_power--)
    a = product(a, an);

  std::cout << "Product has " << a.states ().size () << " states and " 
	    << a.edges ().size () << "edges." << std::endl;
  VCSN_BENCH_START;
  automaton_t b = quotient(a);
  VCSN_BENCH_STOP_AND_PRINT;
  std::cout << "Quotient has " << b.states ().size () << " states and " 
	    << b.edges ().size () << "edges." << std::endl;
}

