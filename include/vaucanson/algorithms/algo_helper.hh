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
  namespace constructor
  {

    template <typename T_auto, typename Etiq, typename T>
    class IncAutomataConstructor : public T
    {
    public:
      // Usefull types :))
      typedef T_auto*						T_auto_p;
      AUTOMATON_TYPES(T_auto);
      // Types for the list -> used a hash_map with function defined in T
      typedef std::pair<hstate_t, bool>				StateMarked;
      typedef std::map<Etiq, StateMarked, T>			StateMap;
      typedef typename StateMap::iterator			Iterator;

      // The constructor
      IncAutomataConstructor(const series_t& series, const Etiq& etiq);
      // To run the algorithm
      void	run();
      // To get the result
      T_auto_p	get() const;
      // Add a link from current state to indicated state
      void	link2(const Etiq& etiq, const letter_t& l);
      // To make the current state final
      void	setfinal();
    protected:
      // Method to add properly a state
      hstate_t	add_state(const Etiq& etiq);
      // Attributes
      int				unvisited;
      T_auto_p				auto_p;
      StateMap				states_map;
      Iterator				current_state;
    };

    template <typename T_auto, typename Etiq, typename T>
    class MathAutomataConstructor : public T
    {
      // TODO
    };

  }
}

#include <vaucanson/algorithms/algo_helper.hxx>

#endif /* ! VCSN_ALGORITHMS_ALGO_HELPER_HH */
