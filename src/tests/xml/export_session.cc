// export_session.cc: this file is part of the Vaucanson project.
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
#include <iostream>

#include <vaucanson/boolean_automaton.hh>

#define FAIL WITH_THROW
#include <vaucanson/xml/session.hh>

int
main(int argc, char** argv)
{
  using namespace vcsn::xml;

  typedef ATTACH_XML_INFOS(vcsn::boolean_automaton::automaton_t) automaton_t;
  AUTOMATON_TYPES_EXACT(automaton_t);

  XML_BEGIN;
  xml_session_t session;
  try
    {
      xml_automata_set_t	xs;
      xml_automaton_t		x (xs);
      std::cin >> x;
      automaton_t		a (x);
      session << a;
      for (int i = 1; i < argc; ++i)
	{
	  std::ifstream f (argv[i]);
	  f >> x;
	  a = x;
	  session << a;
	}
    }
  catch (const LoaderException& e)
    {
      std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
      return 1;
    }
  std::cout << session;
  XML_END;
}
