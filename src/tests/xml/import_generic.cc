// import_generic.cc: this file is part of the Vaucanson project.
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
#define FAIL WITH_THROW
#define VCSN_XML_GENRERIC_WEIGHTED 1

#include <vaucanson/algebra/implementation/semiring/numerical_semiring.hh>
#include <vaucanson/algebra/implementation/semiring/tropical_semiring.hh>
#include <vaucanson/xml/generic.hh>

#include <iostream>

struct MyData
{
  MyData(int c, char** v) : argc(c), argv(v)
  {
  }

  int		argc;
  char**	argv;
};

template <typename Auto>
struct MyCallBack
{
  int
  operator () (Auto& a, MyData&)
  {
    AUTOMATON_TYPES(Auto);

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
	using vcsn::rat::setpm;
	using vcsn::rat::MODE_WEIGHT;

	std::cout << *i << " ";
	std::cout << a.aim_of(*i) << " ";
	std::cout << a.origin_of(*i) << " ";
	std::cout << setpm (MODE_WEIGHT)
		  << a.label_of(*i) << std::endl;
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

    return 0;
  }
};

int
main(int argc, char *argv[])
{
  using namespace vcsn::xml;

  XML_BEGIN;
  try
    {
      MyData data(argc, argv);
      return apply<MyCallBack, MyData>(std::cin, data);
    }
  catch (const LoaderException& e)
    {
      std::cerr << "error ?!?" << std::endl << e.get_msg() << std::endl;
      return 1;
    }
  XML_END;
}
