// fibonacci_rt_tdc_gen.cc: this file is part of the Vaucanson project.
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

/* @file fibonacci_demo.cc
 *
 * Build the cautious left sequential transducer, the cautious right
 * sequential transducer and the left transducer composed by right
 * transducer with transducers seen as automata in the semiring of
 * series. And propose to evaluate words on each of them.
 *
 */

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/boolean_transducer.hh>

#include <vaucanson/algorithms/evaluation.hh>
#include <vaucanson/algorithms/krat_exp_expand.hh>
#include <vaucanson/algorithms/realtime_composition.hh>

#include <vaucanson/tools/dot_display.hh>

void
eval_an_expression(const vcsn::boolean_transducer::automaton_t& t)
{
  using namespace vcsn::boolean_transducer;

  const alphabet_t&	alphabet = t.structure().series().monoid().alphabet();
  std::string		user_string;

  do
    {
      std::cout << "Enter your expression over " << alphabet
		<<" (\"next\", otherwise): ";
      std::getline(std::cin, user_string);
      if (user_string != "next")
	{
	  using namespace vcsn::boolean_automaton;
	  using namespace vcsn::rat; // For setpm and MODE_STAR.

	  rat_exp_t exp = new_rat_exp(alphabet, user_string);
	  std::cout << setpm (MODE_STAR) << expand(evaluation(t, exp))
		    << std::endl;
	}

    }
  while (user_string != "next");
}

int main()
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::boolean_transducer;

  /*-------------------------------.
  | Instanciation of the objects.  |
  `-------------------------------*/

  alphabet_t	A;
  A.insert('a');
  A.insert('b');

 /*----------------------.
  | Creation of fibleft.  |
  `----------------------*/

  automaton_t		fibleft = new_automaton(A, A);

  hstate_t p = fibleft.add_state();
  hstate_t q = fibleft.add_state();
  hstate_t r = fibleft.add_state();

  fibleft.add_io_edge(p, p, "b", "b");
  fibleft.add_io_edge(p, q, "a", "");
  fibleft.add_io_edge(q, q, "a", "a");
  fibleft.add_io_edge(q, r, "b", "");
  fibleft.add_io_edge(r, q, "a", "ab");
  fibleft.add_io_edge(r, q, "b", "ba");

  fibleft.set_o_final(q, "a");

  fibleft.set_o_final(r, "ab");

  fibleft.set_final(p);
  fibleft.set_initial(p);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fibleft, "fibleft", true);
  eval_an_expression(fibleft);


  /*-----------------------.
  | Creation of fibright.  |
  `-----------------------*/

  automaton_t fibright = new_automaton(A, A);

  hstate_t s = fibright.add_state();
  hstate_t t = fibright.add_state();
  hstate_t u = fibright.add_state();

  fibright.add_io_edge(s, s, "b", "b");
  fibright.add_io_edge(s, t, "b", "");
  fibright.add_io_edge(t, s, "a", "aa");
  fibright.add_io_edge(t, u, "b", "");
  fibright.add_io_edge(u, t, "a", "ab");
  fibright.add_io_edge(u, u, "a", "a");

  fibright.set_o_initial(s, "bb");

  fibright.set_o_initial(t, "b");

  fibright.set_initial(u);
  fibright.set_final(u);


  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fibright, "fibright", true);
  eval_an_expression(fibright);


  /*----------.
  | Compose.  |
  `----------*/

  automaton_t	fiblr = new_automaton(A, A);
  realtime_composition(fibleft, fibright, fiblr);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fiblr, "fiblr", true);
  eval_an_expression(fiblr);

}