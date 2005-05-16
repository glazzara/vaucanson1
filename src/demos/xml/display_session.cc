// display_session.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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

/*
 * @file display_session.cc
 *
 * ./make_session <session file>
 *
 * Display all automata from a session.
 *
 * Works only with boolean automata.
 */

#include <sstream>
#include <fstream>

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/usual_macros.hh>
#include <vaucanson/tools/dot_display.hh>

#include <vaucanson/xml/session.hh>

int
usage(int, char** argv)
{
  std::cerr << "Usage: " << argv[0] << " <session file>" << std::endl;
  return 1;
}

int
main(int argc, char** argv)
{
  if (argc != 2)
    return usage(argc, argv);

  std::ifstream		in (argv[1]);
  if (in.fail())
    {
      std::cerr << "FATAL: Cannot open session file." << std::endl;
      return 1;
    }
  using namespace vcsn;
  using vcsn::xml::xml_session;

  xml_session	session;
  in >> session;

  int		rval (0);
  int		i (0);

  while (true)
    {
      using namespace vcsn;
      using namespace vcsn::boolean_automaton;
      automaton_t a = new_automaton(alphabet_t());
      session >> a;
      std::ostringstream	os;
      os << "A" << i;
      vcsn::tools::dot_display(a, os.str(), true);

      ++i;
    }

  return rval;
}
