// a1.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/tools/xml_dump.hh>


int
main()
{
  using namespace vcsn;
  using namespace vcsn::boolean_automaton;

  alphabet_t	A;
  A.insert('a');
  A.insert('b');

  /*------------------------------.
  | Creation of the automaton A_1 |
  `------------------------------*/

  automaton_t a1 = new_automaton(A);

  hstate_t p = a1.add_state();
  hstate_t q = a1.add_state();
  hstate_t r = a1.add_state();

  a1.add_letter_edge(p, p, 'a');
  a1.add_letter_edge(p, p, 'b');

  a1.add_letter_edge(p, q, 'a');
  a1.add_letter_edge(q, r, 'b');

  a1.add_letter_edge(r, r, 'a');
  a1.add_letter_edge(r, r, 'b');

  a1.set_initial(p);
  a1.set_final(r);

  tools::xml_dump(std::cout, a1, "a1");
}

