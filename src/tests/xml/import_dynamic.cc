// import_dynamic.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/z_automaton.hh>

#define FAIL WITH_THROW
#include <vaucanson/xml/dynamic.hh>


template <typename T>
void
print_out(T a)
{
  AUTOMATON_TYPES(T);

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

void
error_not_dealt(int& rval)
{
  std::cerr << "Automaton type not dealt" << std::endl;
  rval = 1;
}

int
main()
{
  using namespace vcsn::xml;

  typedef
    ATTACH_XML_INFOS(vcsn::boolean_automaton::automaton_t)
    tagged_boolean_automaton_t;

  typedef
    ATTACH_XML_INFOS(vcsn::z_automaton::automaton_t)
    tagged_z_automaton_t;

  XML_BEGIN;
  xml_automata_set_t	xs;
  xml_automaton_t	x (xs);
  try
    {
      std::cin >> x;
    }
  catch (const LoaderException& e)
    {
      std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
      return 1;
    }

  int rval (0);

  switch (x.structure().semiring_value())
    {
    case xml_automata_set_t::Z:
      if (x.structure().semiring_structure() == xml_automata_set_t::NUMERICAL)
	print_out<tagged_z_automaton_t>(x);
      else
	error_not_dealt(rval);
      break ;
    case xml_automata_set_t::B:
      print_out<tagged_boolean_automaton_t>(x);
      break ;
    default:
      error_not_dealt(rval);
      break ;
    }
  XML_END;
  return rval;
}
