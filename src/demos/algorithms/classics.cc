// classics.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004, 2005 The Vaucanson Group.
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

#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/eval.hh>

#include <iostream>

using namespace vcsn;
using namespace vcsn::boolean_automaton;

void
ask_and_eval(const automaton_t& x)
{
  std::string user_string;
  do
    {
      std::cout << "Enter a word over "
		<< x.structure().series().monoid().alphabet()
		<< " (\"next\", otherwise): ";
      std::cin >> user_string;

      if (user_string != "next")
	{
	  monoid_elt_t w (x.structure().series().monoid(), user_string);

	  std::cout << w << std::endl;
	  std::cout << eval(x, w) << std::endl;
	}
    }
  while (user_string != "next") ;
}

int
main()
{
  alphabet_t alpha;

  alpha.insert('a');
  alpha.insert('b');

  automaton_t a = new_automaton(alpha);

  hstate_t p = a.add_state();
  hstate_t q = a.add_state();
  a.add_letter_edge(p, p, 'a');
  a.add_letter_edge(p, p, 'b');
  a.add_letter_edge(p, q, 'b');
  a.add_letter_edge(q, q, 'a');
  a.add_letter_edge(q, q, 'b');
  a.set_initial(p);
  a.set_final(q);

  SAVE_AUTOMATON_DOT_SIMPLE("a", a);
  std::cout << "`a' saved in a.dot" << std::endl;

  automaton_t a_q = quotient(a);
  SAVE_AUTOMATON_DOT_SIMPLE("a_quotient", a_q);
  std::cout << "`a' quotient saved in a_quotient.dot" << std::endl;

  automaton_t a_d = determinize(a);
  SAVE_AUTOMATON_DOT_SIMPLE("a_determinize", a_d);
  std::cout << "`a' determinized saved in a_determinize.dot" << std::endl;

  automaton_t a_p = product(a, a);
  SAVE_AUTOMATON_DOT_SIMPLE("a_product", a_p);
  std::cout << "`a' product saved in a_product.dot" << std::endl;

  automaton_t a_pq = quotient(a_p);
  SAVE_AUTOMATON_DOT_SIMPLE("a_product_quotient", a_pq);
  std::cout << "`a' product's quotient saved in a_product_quotient.dot"
	    << std::endl;

  std::cout << "Evaluating `a' product's quotient." << std::endl;
  ask_and_eval(a_pq);
}
