// lomb2.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#include <ostream>

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/xml/XML.hh>

int
main()
{
  using namespace vcsn::boolean_automaton;
  using vcsn::io::string_out;
  using vcsn::xml::XML;

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');

  automaton_t a = new_automaton(alpha);

  a.add_state();
  a.add_state();
  a.add_state();

  a.set_initial(0);
  a.set_final(1);

  a.add_letter_edge(0, 1, 'a');
  a.add_letter_edge(0, 2, 'b');

  a.add_letter_edge(1, 1, 'a');
  a.add_letter_edge(1, 1, 'b');

  a.add_letter_edge(2, 2, 'a');
  a.add_letter_edge(2, 2, 'b');

  std::cout << automaton_saver(a, string_out (), XML ());
}
