// algo_helper.hh
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

#ifndef VCSN_ALGORITHMS_ALGO_HELPER_HH
# define VCSN_ALGORITHMS_ALGO_HELPER_HH

# include <map>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {
  namespace algorithm_patterns
  {

    // This is a pattern for algorithm which build automaton in
    // an incremental way :
    // it start with one state, and with this state, it build
    // other states. New states are used to build more and
    // more states.
    // It needs the function applied on each state,
    // and the order used by the map.
    template <typename T_auto, typename Etiq, typename T>
    class IncAutomataConstructor : public T
    {
    public:
      // Useful types :))
      typedef T_auto*						T_auto_p;
      AUTOMATON_TYPES(T_auto);
      // Types for the list -> used a hash_map with function defined in T
      typedef std::pair<hstate_t, bool>				StateMarked;
      typedef std::map<Etiq, StateMarked, T>			StateMap;
      typedef typename StateMap::iterator			iterator;

      // The constructor
      IncAutomataConstructor(const series_t& series, const Etiq& etiq);
      // To run the algorithm
      void	run();
      // To get the result
      T_auto_p	get() const;
      // Add a link from current state to indicated state
      void	link_to(const Etiq& etiq, const letter_t& l);
      // To make the current state final
      void	set_final();
    protected:
      // Method to add properly a state
      hstate_t	add_state(const Etiq& etiq);
      // Attributes
      int				unvisited;
      T_auto_p				auto_p;
      StateMap				states_map;
      iterator				current_state;
    };

    template <typename T_auto, typename Etiq, typename T>
    class MathAutomataConstructor : public T
    {
      // FIXME : Write it !
      // This  Algorithm builder takes a struture
      // which contains different functions (like IncAutomataConstructor)
      // but the functions needed are mathematical definitions
      // of the automaton, i.e. :
      // function which return the set of final state,
      // etc.
    };

  }
}

#include <vaucanson/algorithms/algo_helper.hxx>

#endif /* ! VCSN_ALGORITHMS_ALGO_HELPER_HH */
