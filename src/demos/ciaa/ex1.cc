// ex1.cc: this file is part of the Vaucanson project.
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

/*
 * @file ex1.cc
 *
 * Build an automaton "An" with  "n" states whose determinized has 2^n
 * states.
 */

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/tools/dot_display.hh>

#include <ostream>
#include <sstream>

int main(int argc, char** argv)
{
  if (argc != 2)
    {
      std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
      return 1;
    }

  unsigned n;
  {
    std::istringstream is (argv[1]);
    is >> n;
  }

  using vcsn::boolean_automaton::alphabet_t;
  using vcsn::boolean_automaton::automaton_t;

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t an = vcsn::boolean_automaton::new_automaton(alpha);

  vcsn::hstate_t p = an.add_state();
  vcsn::hstate_t x = p;
  for(unsigned i = 1; i < n; ++i)
    {
      vcsn::hstate_t y = an.add_state();
      an.add_letter_edge(x, y, 'a');an.add_letter_edge(y, y, 'b');
      an.add_letter_edge(y, y, 'c');an.add_letter_edge(y, p, 'c');
      x = y;
    }
  an.add_letter_edge(x, p, 'a');
  an.set_initial(p); an.set_final(p);
  vcsn::tools::dot_display(an, "A", "dotty", true);

  automaton_t dn = determinize(an);
  if (n and dn.states().size() != unsigned (1 <<  n))
    std::cerr << "Invalid determinization of A_" << n << std::endl;
  vcsn::tools::dot_display(dn, "D");
}
