// import_session.cc: this file is part of the Vaucanson project.
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


int main()
{
  using namespace vcsn::io;
  using namespace vcsn::xml;

  typedef ATTACH_XML_INFOS(vcsn::boolean_automaton::automaton_t) automaton_t;
  AUTOMATON_TYPES_EXACT(automaton_t);

  alphabet_t		at;
  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  XML_BEGIN;
  xml_session_t		session;
  std::cin >> session;

  for (unsigned i = 0; i < 2; ++i)
    {
      automaton_t	a (aa);

      try
	{
	  session >> a;
	}
      catch (const LoaderException& e)
	{
	  std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
	  return 1;
	}

      std::cout << "Letters:";
      for_each_letter(i, a.structure().series().monoid().alphabet())
	std::cout << " " << *i;
      std::cout << std::endl;

      std::cout << "States:" << std::endl;
      for_each_state(i, a)
	{
	  std::cout << *i << " ";
	  std::cout << a.tag().get_states().get_name()[*i] << std::endl;
	}

      std::cout << "Edges:" << std::endl;
      for_each_edge(i, a)
	{
	  std::cout << *i << " ";
	  std::cout << a.aim_of(*i) << " ";
	  std::cout << a.origin_of(*i) << " ";
	  std::cout << a.label_of(*i) << std::endl;
	}

      std::cout << "Initials:" << std::endl;
      for_each_initial_state(i, a)
	{
	  std::cout << *i << " ";
	  std::cout << a.get_initial(*i) << std::endl;
	}

      std::cout << "Finals:" << std::endl;
      for_each_final_state(i, a)
	{
	  std::cout << *i << " ";
	  std::cout << a.get_final(*i) << std::endl;
	}
    }
  XML_END;
}
