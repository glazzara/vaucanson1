// derivatives_automaton.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/tools/usual.hh>
#include <vaucanson/algebra/concrete/series/rat/exp.hh>
#include <vaucanson/algebra/concrete/series/krat.hh>
#include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <string>
#include <vaucanson/algorithms/derivatives_automaton.hh>
#include <vaucanson/misc/unique.hcc>

int main(int argc, char **argv)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;
  
  // Tha automaton type we are working on
  AUTOMATON_TYPES_EXACT(numerical_automaton_t);
 
  // The first argument is the rational expression.
  if (argc != 2)
  {
    std::cout << "Usage:" << std::endl << "deriv <expression>" << std::endl;
    return 1;
  }
  std::string exp = argv[1];

  // Declare and initialize serie
  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  monoid_t freemonoid(alpha);
  weights_t semiring;
  series_t series(semiring, freemonoid);

  // Set krat value
  Element<series_t, rat::exp<monoid_elt_value_t, weight_value_t> >
    krat_exp(series);
  parse(exp, krat_exp);

  // Display krat value
  std::cout << "Expression to transform: " << krat_exp << std::endl;
  
  // Initialize automaton
  automata_set_t a_set(series);
  automaton_t automaton(a_set);

  // Build automaton
  derivatives_automaton(automaton, krat_exp);
  
  // If the automaton is valide, save it !
  if (automaton.states().end() == automaton.states().begin())
    std::cout << "Empty automaton!" << std::endl;
  else
  {
    SAVE_AUTOMATON_DOT_SIMPLE("out", automaton);
    std::cout << "Automaton saved!" << std::endl;
  }
}

