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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

/* @file b1.cc
 *
 * Build the automaton which recognizes the words containing a 'b'.
 *
 */

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

  std::ofstream file("b1.xml");
  tools::xml_dump(file, b1, "b1");

  std::cout << "File b1.xml has been created." << std::endl;
}

