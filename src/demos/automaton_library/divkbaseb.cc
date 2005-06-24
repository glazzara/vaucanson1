// divkbaseb.cc: this file is part of the Vaucanson project.
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
 * @file divkbaseb.cc
 *
 * Build an automaton which divides by "k" a number in base "b".
 *
 */

#include <sstream>

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/xml_dump.hh>

int
main(int argc, char** argv)
{
  if (argc != 3)
    {
      std::cerr << "Usage:" << std::endl
		<< "\t" << argv[0] << " <divisor> <base>" << std::endl;
      return 1;
    }

  int			divisor;
  {
    std::istringstream	is (argv[1]);
    is >> divisor;
  }

  int			base;
  {
    std::istringstream	is (argv[2]);
    is >> base;
  }

  std::string div (argv[1]);
  std::string b (argv[2]);

  using namespace vcsn::boolean_automaton;

  alphabet_t	alpha;
  for (int i = 0; i < base; ++i)
    alpha.insert(i < 10 ? '0' + i : 'A' + i);

  automaton_t	a = new_automaton(alpha);

  for (int i = 0; i < divisor; ++i)
    a.add_state();
  a.set_initial(0);
  a.set_final(0);

  int d = 0;
  for (int i = 0; i < divisor; ++i)
    for_each_letter(l, alpha)
    {
      a.add_letter_edge(i, d, *l);
      d = (d + 1) % divisor;
    }

  std::string name = "div" + div + "base" + b + ".xml";
  std::ofstream file(name.c_str());
  vcsn::tools::xml_dump(file, a, "divkbaseb");

  std::cout << "File " << name << " has been created." << std::endl;
}
