// ex3.cc: this file is part of the Vaucanson project.
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

/* @file ex3.cc
 *
 * Build  the  Z-automaton "C_1"  which  computes  for  each word  its
 * "binary value".
 *
 * Build  the   n-th  power  "C_n"  of  "C_1"   and  test  aut_to_exp,
 * standard_of, thompson_of, backward_closure and quotient on it.
 *
 * Reference: ETA exer. III.2.17, III.3.12
 */

#include <vaucanson/z_automaton.hh>

#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/eval.hh>
#include <vaucanson/algorithms/aut_to_exp.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/algorithms/backward_closure.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/tools/dot_display.hh>

#include <ostream>
#include <sstream>

int
main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::z_automaton;

  alphabet_t	A;
  A.insert('a');
  A.insert('b');
  monoid_t	Astar (A);
  monoid_elt_t	a (Astar, "a");
  monoid_elt_t	b (Astar, "b");

  /*------------------------------.
  | Creation of the automaton C_1 |
  `------------------------------*/

  automaton_t c1 = new_automaton(A);

  hstate_t p = c1.add_state();
  hstate_t q = c1.add_state();

  series_set_elt_t sp (c1.structure().series());
  sp.assoc(a, 1);
  sp.assoc(b, 1);

  series_set_elt_t sq (c1.structure().series());
  sq.assoc(a, 2);
  sq.assoc(b, 2);

  c1.add_letter_edge(p, q, 'b');
  c1.add_series_edge(q, q, sq);
  c1.add_series_edge(p, p, sp);
  c1.set_initial(p);
  c1.set_final(q);

  std::cout << "evaluation on baba: "
	    << eval(c1, monoid_elt_t (Astar, "baba")) << std::endl;
  tools::dot_display(c1, "C_1");

  if (argc == 2)
    {
      unsigned n;
      {
	std::istringstream is (argv[1]);
	is >> n;
      }

      /*------------------------------.
      | Creation of the automaton C_n |
      `------------------------------*/

      automaton_t cn = c1;
      for (unsigned i = 1; i < n; ++i)
	cn = product(cn, c1);

      std::cout << "n = "<< n << std::endl
		<< "evaluation on baba: "
		<< eval(cn, monoid_elt_t (Astar, "baba")) << std::endl;
      tools::dot_display(cn, "C_n", true);

      /*--------------------------.
      | Work on the automaton C_n |
      `--------------------------*/

     krat_exp_t e = aut_to_exp(generalized(cn));
     std::cout << e << std::endl;

     automaton_t sn = standard_of(e);
     std::cout << "S_n = " << sn << std::endl;
     tools::dot_display(sn, "S_n", true);

     automaton_t tn = thompson_of(e);
     std::cout << "T_n = " << tn << std::endl;
     tools::dot_display(tn, "T_n", true);

     automaton_t un = backward_closure(tn);
     std::cout << "U_n = " << un << std::endl;
     tools::dot_display(un, "U_n", true);

     automaton_t vn = quotient(cn);
     std::cout << "V_n = " << vn << std::endl;
     tools::dot_display(vn, "V_n");
    }
}
