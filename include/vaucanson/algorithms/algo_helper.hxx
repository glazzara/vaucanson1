// algo_helper.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_ALGO_HELPER_HXX
# define VCSN_ALGORITHMS_ALGO_HELPER_HXX

namespace vcsn
{
  namespace constructor 
  {

    // The constructor
    template <typename T_auto, typename Etiq, typename T>
    IncAutomataConstructor<T_auto, Etiq, T>::IncAutomataConstructor
    (
      const series_t& series, const Etiq& etiq
    )
    {
      auto_p = new T_auto();
      auto_p->create();
      auto_p->series() = series;
      unvisited = 0;
      auto_p->set_initial(add_state(etiq));
      current_state = states_map.end();
    }

    // To get the result
    template <typename T_auto, typename Etiq, typename T>
    T_auto*
    IncAutomataConstructor<T_auto, Etiq, T>::get() const
    {
      return auto_p;
    }

    // To run the algorithm
    template <typename T_auto, typename Etiq, typename T>
    void
    IncAutomataConstructor<T_auto, Etiq, T>::run()
    {
      while (unvisited > 0)
      {
	for (current_state = states_map.begin();
	     current_state != states_map.end();
	     ++current_state)
	{
	  if (!(current_state->second.second))
	  {
	    on_state(*this, current_state->first);
	    unvisited -= 1;
	    current_state->second.second = true;
	  }
	}
      }
    }
    
    // Link current state to an other, which can be created
    template <typename T_auto, typename Etiq, typename T>
    void
    IncAutomataConstructor<T_auto, Etiq, T>::link2
    (
      const Etiq& etiq, const letter_t& l
    )
    {
      hstate_t	s;
      Iterator	i = states_map.find(etiq);
      
      if (i == states_map.end())
	s = add_state(etiq);
      else
	s = i->second.first;
      auto_p->add_letter_edge(current_state->second.first, s, l);
    }
    
    // A tool to add a state in the set and the automaton
    template <typename T_auto, typename Etiq, typename T>
    hstate_t
    IncAutomataConstructor<T_auto, Etiq, T>::add_state(const Etiq& etiq)
    {
      std::cout << "Ajout de: " << etiq << std::endl;
      hstate_t	res = auto_p->add_state();
      states_map[etiq] = std::pair<hstate_t, bool>(res, false);
      unvisited += 1;
      return res;
    }

    // To make the current state final
    template <typename T_auto, typename Etiq, typename T>
    void
    IncAutomataConstructor<T_auto, Etiq, T>::setfinal()
    {
      auto_p->set_final(current_state->second.first);
    }

  }
}

#endif /* ! VCSN_ALGORITHMS_ALGO_HELPER_HXX */
