// make_session.cc: this file is part of the Vaucanson project.
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

/*
 * @file make_session.cc
 *
 * ./make_session <session file> [XML automata...]
 *
 * Takes XML files  containing Boolean automata as input and stores them in a
 * single XML session file.
 */

#include <fstream>

#include <vaucanson/xml/XML.hh>
#include <vaucanson/xml/session.hh>
#include <vaucanson/boolean_automaton.hh>


int
usage(int, char** argv)
{
  std::cerr << "Usage: " << argv[0] << " <session file> [XML automata...]"
	    << std::endl;
  return 1;
}

int
main(int argc, char** argv)
{
  using namespace vcsn;
  using vcsn::xml::xml_session;

  if (argc < 2)
    return usage(argc, argv);

  int		rval (0);

  xml_session		session;
  for (int i = 2; i < argc; ++i)
    {
      std::ifstream in (argv[i]);
      if (not in.fail())
	{
	  using namespace vcsn::boolean_automaton;

	  automaton_t a = new_automaton(alphabet_t());

 	  in >> automaton_loader(a, io::string_out(), xml::XML());
	  session << a;
	}
      else
	{
	  std::cerr << "WARNING: Cannot open " << argv[i] << "." << std::endl;
	  ++rval;
	}

    }

  std::ofstream	out (argv[1]);
  if (not out.fail())
    out << session;
  else
    {
      std::cerr << "FATAL: Cannot write " << argv[1] << "." << std::endl;
      ++rval;
    }

  return rval;
}
