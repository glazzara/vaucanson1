// algorithms.cc: this file is part of the Vaucanson project.
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
 * @file algorithms.cc
 *
 * ./algorithms <algorithm> (<exp> | <file>)
 *
 * Run various algorithms on R automata with numerical semiring. Results are
 * dumped in a XML format on stdout.
 *
 * Valid algorithms are:
 *
 * standard_of
 * thompson_of
 * derivatives_automaton
 * aut_to_exp
 * quotient
 * product
 * closure
 * determinize
 * trim
 * display - not really an algorithm. Display the automaton using dotty.
 */

#include <fstream>
#include <cstdlib>

#include <vaucanson/r_automaton.hh>
#include <vaucanson/xml/static.hh>

#include <vaucanson/algorithms/derivatives_automaton.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/closure.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/algorithms/trim.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
#include <vaucanson/tools/dot_display.hh>

void
usage(int, char** argv)
{
  std::cerr << "Usage: " << argv[0] << " <algorithm> (<exp> | <file>)"
	    << std::endl;
  exit(1);
}

vcsn::r_automaton::alphabet_t
alphabet()
{
  vcsn::r_automaton::alphabet_t	a;
  a.insert('a');
  a.insert('b');
  a.insert('c');
  return a;
}

vcsn::r_automaton::rat_exp_t
get_exp(std::string s)
{
  using namespace vcsn::r_automaton;

  rat_exp_t r = new_rat_exp(alphabet());
  std::pair<bool, std::string> p = parse(s, r);
  if (p.first)
    {
      std::cerr << "FATAL: Invalid expression: " << p.second << "."
		<< std::endl;
      exit(1);
    }
  else
    return r;
}

vcsn::r_automaton::automaton_t
get_aut(std::string s)
{
  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str()));
  if (not is->fail())
    {
      using namespace vcsn::r_automaton;
      using namespace vcsn::io;
      using namespace vcsn::xml;

      automaton_t a = new_automaton(alphabet());
      *is >> automaton_loader(a, string_out (), xml_loader ());

      if (s != "-")
	delete is;
      return a;
    }
  else
    {
      std::cerr << "FATAL: Could not load automaton." << std::endl;
      exit(1);
    }
}

int
main(int argc, char** argv)
{
  using namespace vcsn::r_automaton;
  using namespace vcsn::io;
  using namespace vcsn::xml;

  std::string cmd;
  if (argc > 1)
    cmd = argv[1];
  if (argc != 3 and (argc != 4 or cmd != "product"))
    usage(argc, argv);

  XML_BEGIN;

  if (cmd == "standard_of")
    std::cout << automaton_saver(standard_of(get_exp(argv[2])),
				 string_out (),
				 xml_loader ());
  else if (cmd == "thompson_of")
    std::cout << automaton_saver(thompson_of(get_exp(argv[2])),
				 string_out (),
				 xml_loader ());
  else if (cmd == "derivatives_automaton")
    {
      rat_exp_t		e = get_exp(argv[2]);
      automaton_t	a = new_automaton(alphabet());
      derivatives_automaton(a, e);
      std::cout << automaton_saver(a, string_out (), xml_loader ());
    }
  else if (cmd == "aut_to_exp")
    std::cout << aut_to_exp(get_aut(argv[2])) << std::endl;
  else if (cmd == "quotient")
    std::cout << automaton_saver(quotient(get_aut(argv[2])),
					  string_out (),
					  xml_loader ());
  else if (cmd == "product")
    std::cout << automaton_saver(product(get_aut(argv[2]), get_aut(argv[3])),
				 string_out (),
				 xml_loader ());
  else if (cmd == "closure")
    std::cout << automaton_saver(backward_closure(get_aut(argv[2])),
				 string_out (),
				 xml_loader ());
  else if (cmd == "determinize")
    std::cout << automaton_saver(determinize(get_aut(argv[2])),
				 string_out (),
				 xml_loader ());
  else if (cmd == "trim")
    std::cout << automaton_saver(trim(get_aut(argv[2])),
				 string_out (),
				 xml_loader ());
  else if (cmd == "display")
    vcsn::tools::dot_display(get_aut(argv[2]), "A", true);
  else
    usage(argc, argv);

  XML_END;
}
