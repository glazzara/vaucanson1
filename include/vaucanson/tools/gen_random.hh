// gen_random.hh
// 
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef GEN_RANDOM_HH
# define GEN_RANDOM_HH

# include <vaucanson/config/system.hh>
# include <vaucanson/fundamental/fundamental.hh>

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/misc/ref.hh>

namespace vcsn {

  using namespace algebra;

  template <class TAutomata> 
  class GenRandomAutomata
  {
  public:
    GenRandomAutomata();
    GenRandomAutomata(unsigned init);

    TAutomata empty(unsigned nb_letter = 2); 

    TAutomata generate(unsigned nb_state, unsigned nb_edge, 
		       unsigned istate = 1, unsigned fstate = 1,
		       unsigned nb_letter = 2);
    TAutomata generate_dfa(unsigned nb_state, 
			   unsigned size_alphabet = 2, 
			   unsigned fstate = 1);
    TAutomata generate_with_epsilon(unsigned nb_state, unsigned nb_edge, 
				    unsigned nb_epsilon_min, 
				    unsigned nb_epsilon_max);

    TAutomata generate_normalized(unsigned nb_state, unsigned density = 3);

  private:

    unsigned alea(unsigned max);
    unsigned nb_edge_circle(TAutomata work, hstate_t state);
    void     del_edge_circle(TAutomata& work, hstate_t state);
   
  };

  namespace tools {

    typedef GenRandomAutomata<usual_automaton_t> gen_auto_t;

  } // tools

} // vcsn

# include <vaucanson/tools/gen_random.hxx>

#endif
