// b1.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/boolean_automaton.hh>

using namespace vcsn;
using namespace vcsn::boolean_automaton;
#include "dumper.hcc"


int
main(int argc, char **argv)
{

  alphabet_t	A;
  A.insert('a');
  A.insert('b');

  /*------------------------------.
  | Creation of the automaton A_1 |
  `------------------------------*/

  automaton_t b1 = new_automaton(A);

  hstate_t p = b1.add_state();
  hstate_t q = b1.add_state();

  b1.add_letter_edge(p, p, 'a');
  b1.add_letter_edge(p, p, 'b');

  b1.add_letter_edge(p, q, 'b');

  b1.add_letter_edge(q, q, 'a');
  b1.add_letter_edge(q, q, 'b');

  b1.set_initial(p);
  b1.set_final(q);

  dumper(argc, argv)(std::cout, b1, "b1");
}

