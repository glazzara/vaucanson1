// extract.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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


#ifndef ALGORITHMS_EXTRACT_HXX
# define ALGORITHMS_EXTRACT_HXX

# include <queue>
# include <vaucanson/algorithms/extract.hh>

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*----------------------------------------.
  | SubAutomaton defined by a set of states |
  `----------------------------------------*/
 
  template<typename A, typename auto_t, typename list_t>
  void auto_do_extract(const AutomataBase<A>&, 
		       auto_t& a,
		       const list_t& selected, 
		       bool /* FIXME: useless argument */)
  {
    std::deque<hstate_t> to_be_removed;
    for (typename auto_t::state_iterator i = a.states().begin();
	 i != a.states().end(); ++i)
      if (selected.find(*i) == selected.end())
	to_be_removed.push_back(*i);

    while (!to_be_removed.empty())
      {
	a.del_state(to_be_removed.front());
	to_be_removed.pop_front();
      }
  }


  // wrapper:
  template<typename A, typename T, typename StatesSet>
  Element<A, T> 
  auto_extract(const Element<A, T>& a, const StatesSet& s, bool check_states)
  { 
    Element<A, T> ret(a);
    ret.emancipate();
    auto_do_extract(ret.set(), ret, s, check_states);
    return ret;
  }

  template<typename A, typename T, typename StatesSet>
  void auto_in_extract(Element<A, T>& a, const StatesSet& s, bool check_states)
  {
    auto_do_extract(a.set(), a, s, check_states);
  }
  
} // vcsn

#endif // ALGO_EXTRACT_HXX
