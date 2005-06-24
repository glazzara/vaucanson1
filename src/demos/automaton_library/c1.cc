// c1.cc: this file is part of the Vaucanson project.
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
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//

/* @file c1.cc
 *
 * Build  the  Z-automaton "C_1"  which  computes  for  each word  its
 * "binary value".
 *
 */

#include <vaucanson/z_automaton.hh>
#include <vaucanson/tools/xml_dump.hh>


int
main()
{
  using namespace vcsn;
  using namespace vcsn::z_automaton;

  alphabet_t	A;
  A.insert('a');
  A.insert('b');
  monoid_t	Astar (A);
  monoid_elt_t	a (Astar, "a");
  monoid_elt_t	b (Astar, "b");

  /*------------------------------.
  | Creation of the automaton C_1 |
  `------------------------------*/

  automaton_t c1 = new_automaton(A);

  hstate_t p = c1.add_state();
  hstate_t q = c1.add_state();

  series_set_elt_t sp (c1.structure().series());
  sp.assoc(a, 1);
  sp.assoc(b, 1);

  series_set_elt_t sq (c1.structure().series());
  sq.assoc(a, 2);
  sq.assoc(b, 2);

  c1.add_letter_edge(p, q, 'b');
  c1.add_series_edge(q, q, sq);
  c1.add_series_edge(p, p, sp);
  c1.set_initial(p);
  c1.set_final(q);

  std::ofstream file("c1.xml");
  tools::xml_dump(file, c1, "c1");

  std::cout << "File c1.xml has been created." << std::endl;
}
