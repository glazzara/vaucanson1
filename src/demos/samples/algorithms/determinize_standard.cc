// determinize_standard.cc: this file is part of the Vaucanson project.
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
//
#include <vaucanson/boolean_automaton.hh>

#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/trim.hh>
#include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>

#include <string>

int main(int argc, char **argv)
{
  using namespace vcsn::boolean_automaton;

  // The first argument is the rational expression.
  if (argc != 2)
  {
    std::cerr << "Usage:" << std::endl
	      << '\t' << argv[0] <<" <expression>" << std::endl;
    return 1;
  }

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t	automaton = new_automaton(alpha);
  krat_exp_t	krat_exp (automaton.structure().series());

  parse(argv[1], krat_exp);
  std::cout << "Expression to transform: " << krat_exp << std::endl;

  automaton = trim(determinize(standard_of(krat_exp)));


  // If the automaton is valid, save it !
  if (automaton.states().size())
    {
      SAVE_AUTOMATON_DOT_SIMPLE("out", automaton);
      std::cout << "Automaton saved in out.dot." << std::endl;
    }
  else
    std::cout << "Empty automaton." << std::endl;
}
