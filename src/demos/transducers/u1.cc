// u1.cc: this file is part of the Vaucanson project.
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

/* @file u1.cc
 *
 * Build the right transducer of the example of composition presented
 * in the article Inside Vaucanson.
 *
 */

#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/tools/xml_dump.hh>

int main()
{
  using namespace vcsn;
  using namespace vcsn::fmp_transducer;

  first_alphabet_t A;
  A.insert('a');
  A.insert('b');

  automaton_t u1 = new_automaton(A, A);

  hstate_t s = u1.add_state();
  hstate_t t = u1.add_state();
  hstate_t u = u1.add_state();

  u1.set_initial(t);
  u1.set_final(s);
  u1.set_final(t);

  u1.add_weighted_edge(s, t, true, make_couple(A, A, "a", "1").value());
  u1.add_weighted_edge(t, s, true, make_couple(A, A, "1", "b").value());
  u1.add_weighted_edge(t, u, true, make_couple(A, A, "b", "1").value());
  u1.add_weighted_edge(u, t, true, make_couple(A, A, "1", "a").value());

  tools::xml_dump(std::cout, u1, "u1");
}
