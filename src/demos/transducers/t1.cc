// t1.cc: this file is part of the Vaucanson project.
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

/* @file t1.cc
 *
 * Build the left transducer of the example of composition presented
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

  automaton_t t1 = new_automaton(A, A);


  hstate_t p = t1.add_state();
  hstate_t q = t1.add_state();
  hstate_t r = t1.add_state();

  t1.set_initial(q);
  t1.set_final(q);
  t1.set_final(p);

  t1.add_weighted_edge(p, q, true, make_couple(A, A, "1", "b").value());
  t1.add_weighted_edge(q, p, true, make_couple(A, A, "a", "1").value());
  t1.add_weighted_edge(q, r, true, make_couple(A, A, "1", "a").value());
  t1.add_weighted_edge(r, q, true, make_couple(A, A, "b", "1").value());

  std::ofstream file("t1.xml");

  tools::xml_dump(file, t1, "t1");

  std::cout << "File t1.xml has been created." << std::endl;
}
