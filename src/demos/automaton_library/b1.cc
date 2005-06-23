// b1.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
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
