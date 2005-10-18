// contains_factor.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//

/**
 * @file contains_factor.cc
 *
 * Generates a program that checks if a factor is recognized by
 * an automaton.
 *
 */

#include "equivalent_functions.hh"

int
main(int argc, char** argv)
{
  if (argc != 3)
    {
      std::cerr << "Usage: " << argv[0] << " <automaton> <factor>" << std::endl;
      return 1;
    }


  rat_exp_t exp = get_exp(argv[2]);
  automaton_t a = standard_of(exp);
  alphabet_t alpha = a.structure().series().monoid().alphabet();

  for_each_initial_state(s, a)
    for_each_letter(l, alpha)
    {
      a.add_letter_edge(*s, *s, *l);
    }

  for_each_final_state(s, a)
    for_each_letter(l, alpha)
    {
      a.add_letter_edge(*s, *s, *l);
    }

  automaton_t b = get_aut(argv[1]);

  a = trim(product(a, b));

  if (a.states().size() != 0)
    {
      std::cout << "The factor \"" << argv[2]
		<< "\" is recognized by the automaton " << argv[1]
		<< "." << std::endl;
      return 0;
    }
  std::cout << "The factor \"" << argv[2]
	    << "\" is NOT recognized by the automaton " << argv[1]
	    << "." << std::endl;
  return 1;
}
