// boolean.cc: this file is part of the Vaucanson project.
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
 * @file boolean.cc
 *
 * Takes two arguments: either "load" or "save" and then a file name.
 *
 * If "save" is given, the program builds a boolean automaton and save
 * it in the given file.
 *
 * If  "load" is given,  the boolean  automaton in  the given  file is
 * loaded and displayed.
 */

#include <fstream>

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/dot_display.hh>
#include <vaucanson/xml/static.hh>

int
usage(int, char** argv)
{
  std::cerr << "Usage: " << argv[0] << " load | save <file>" << std::endl;
  return 1;
}

int
main(int argc, char** argv)
{
  using namespace vcsn::boolean_automaton;
  using vcsn::io::string_out;
  using vcsn::xml::xml_loader;

  if (argc != 3)
    return usage(argc, argv);

  int		rval (0);

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');

  automaton_t a = new_automaton(alpha);

  XML_BEGIN;
  if (std::string (argv[1]) == "load")
    {
      std::ifstream in (argv[2]);
      if (not in.fail())
	{
	  in >> automaton_loader(a, string_out (), xml_loader ());
	  vcsn::tools::dot_display(a, argv[2]);
	}
      else
	rval = 2;
    }
  else if (std::string(argv[1]) == "save")
    {
      const int div = 7;

      for (int i = 0; i < div; ++i)
	a.add_state();
      a.set_initial(0);
      a.set_final(0);
      unsigned d (0);
      for (int i = 0; i < div; ++i)
	for_each_letter(l, alpha)
	  {
	    a.add_letter_edge(i, d, *l);
	    d = (d + 1) % div;
	  }

      std::ofstream out (argv[2]);
      if (not out.fail())
	out << automaton_saver(a, string_out (), xml_loader ());
      else
	rval = 2;
    }
  else
    rval = usage(argc, argv);
  XML_END;

  return rval;
}
