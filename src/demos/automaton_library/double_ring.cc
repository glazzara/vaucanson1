// double_ring.cc: this file is part of the Vaucanson project.
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

/*
 * @file double_ring.cc
 *
 * Build an automaton which forms a double ring.
 *
 */


#include <sstream>

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/xml_dump.hh>

int
main(int argc, char** argv)
{
  using namespace vcsn::boolean_automaton;
  using vcsn::io::string_out;
  using vcsn::xml::XML;

  if (argc < 2)
    {
      std::cerr << "Usage:" << std::endl
		<< "\t" << argv[0] << " <number of states>"
		<< " [list of final states...]" << std::endl;
      return 1;
    }

  int			n;
  {
    std::istringstream	is (argv[1]);
    is >> n;
  }

  std::string nstates (argv[1]);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');

  automaton_t	a = new_automaton(alpha);
  a.add_state();
  a.set_initial(0);

  for (int i = 1; i < n; ++i)
    {
      a.add_state();
      a.add_letter_edge(i - 1, i, 'a');
      a.add_letter_edge(i, i - 1, 'b');
    }
  a.add_letter_edge(n - 1, 0, 'a');
  a.add_letter_edge(0, n - 1, 'b');

  for (int i = 2; i < argc; ++i)
    {
      std::stringstream	is (argv[i]);
      int		s;

      is >> s;
      if (s >= 0 and s < n)
	a.set_final(s);
    }

  std::string name = "double_ring" + nstates + ".xml";
  std::ofstream file(name.c_str());
  vcsn::tools::xml_dump(file, a, "double_ring");

  std::cout << "File " << name << " has been created." << std::endl;
}
