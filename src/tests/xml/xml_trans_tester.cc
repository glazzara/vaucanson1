// xml_trans_tester.cc: this file is part of the Vaucanson project.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#include <iostream>
#include <string.h>
#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/xml/XML.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::xml;

  if (argc > 1 && ! strcmp(argv[1], "output"))
    {
      using namespace vcsn::boolean_transducer;

      alphabet_t alpha1; alpha1.insert('a'); alpha1.insert('b');
      alphabet_t alpha2; alpha2.insert('x'); alpha2.insert('y');

      automaton_t a = new_automaton(alpha1, alpha2);

      hstate_t s0 = a.add_state();
      hstate_t s1 = a.add_state();
      hstate_t s2 = a.add_state();

      a.set_initial(s0);
      a.set_o_final(s1, "x");

      a.add_io_edge(s0, s1, "a", "x");
      a.add_io_edge(s0, s1, "a", "y");
      a.add_io_edge(s1, s2, "b", "x");

      std::cout << automaton_saver(a, io::string_out(), xml::XML());
    }
  else
    {
      using namespace vcsn::boolean_transducer;

      alphabet_t alpha1;
      alphabet_t alpha2;

      automaton_t a = new_automaton(alpha1, alpha2);

      std::cin >> automaton_loader(a, io::string_out(), xml::XML());
      vcsn::tools::dot_dump(std::cout, a, "T");
    }
}