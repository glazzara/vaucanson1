// gen_random.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TOOLS_GEN_RANDOM_HH
# define VCSN_TOOLS_GEN_RANDOM_HH

#include <vaucanson/misc/selectors.hh>
#include <vaucanson/automata/concept/transducer.hh>

namespace vcsn {

  /*---------------------.
  | GenRandomAutomataSet |
  `---------------------*/

  class GenRandomAutomataSet
  {
  public:

    template <class AutoSet>
    static AutoSet generate(SELECTOR(AutomataBase<AutoSet>),
			    unsigned nb_letter = 0);

    template <class AutoSet>
    static AutoSet generate(SELECTOR(TransducerBase<AutoSet>),
			    unsigned input_nb_letter = 0,
			    unsigned output_nb_letter = 0);
  };


  /*------------------.
  | GenRandomAutomata |
  `------------------*/

  template <class TAutomata, class AutomataSetGenerator = GenRandomAutomataSet>
  class GenRandomAutomata
  {
  public:
    typedef typename TAutomata::set_t	automata_set_t;

  public:
    GenRandomAutomata();
    GenRandomAutomata(unsigned init);

    TAutomata empty(unsigned nb_letter = 0);
    TAutomata empty(const automata_set_t& set);

    TAutomata generate(unsigned nb_state, unsigned nb_edge,
		       unsigned istate = 1, unsigned fstate = 1,
		       unsigned nb_letter = 0);
    TAutomata generate(const automata_set_t& set,
		       unsigned nb_state, unsigned nb_edge,
		       unsigned istate = 1, unsigned fstate = 1);

    TAutomata generate_dfa(unsigned nb_state,
			   unsigned size_alphabet = 0,
			   unsigned fstate = 1);
    TAutomata generate_dfa(const automata_set_t& set,
			   unsigned nb_state,
			   unsigned fstate = 1);

    TAutomata generate_with_epsilon(unsigned nb_state, unsigned nb_edge,
				    unsigned nb_epsilon_min,
				    unsigned nb_epsilon_max);
    TAutomata generate_with_epsilon(const automata_set_t& set,
				    unsigned nb_state, unsigned nb_edge,
				    unsigned nb_epsilon_min,
				    unsigned nb_epsilon_max);

    TAutomata generate_normalized(unsigned nb_state, unsigned density = 3);
    TAutomata generate_normalized(const automata_set_t& set,
				  unsigned nb_state, unsigned density = 3);


  private:

    unsigned nb_edge_circle(TAutomata work, hstate_t state);
    void     del_edge_circle(TAutomata& work, hstate_t state);

  };

  static unsigned alea(unsigned max);

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/tools/gen_random.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_TOOLS_GEN_RANDOM_HH
