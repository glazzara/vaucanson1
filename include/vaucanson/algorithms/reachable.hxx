// reachable.hxx
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

#ifndef ALGORITHMS_REACHABLE_HXX
# define ALGORITHMS_REACHABLE_HXX

# include <vaucanson/algorithms/reachable.hh>

# include <algorithm>
# include <set>
# include <queue>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algorithms/extract.hh>
# include <vaucanson/automata/concept/transpose_impl.hh>

namespace vcsn {

  /*--------------------------.
  | do_start_reachable_states |
  `--------------------------*/
  // preconditions :
  //
  //
  template <class A_, typename Auto_>
  std::set<hstate_t>
  do_start_reachable_states(const AutomataBase<A_>&,
			    const Auto_&		   a)
  {
    typedef Auto_				automaton_t;
    typedef std::set<hstate_t>	      		reachable_set_t;
    typedef std::set<hstate_t>		       	delta_ret_t;
    typedef std::queue<hstate_t>		queue_t;

    delta_ret_t			      delta_ret;
    hstate_t			      state;
    queue_t			      queue;
    reachable_set_t		      reachable_states;

    /*---------------.
    | Initialization |
    `---------------*/
    for (typename automaton_t::initial_iterator i = a.initial().begin();
	 i != a.initial().end();
	 ++i)
      {
	queue.push(*i);
	reachable_states.insert(*i);
      }

    /*----------.
    | Main loop |
    `----------*/
    while (!queue.empty())
      {	
	state = queue.front();
	queue.pop();
	delta_ret.clear();

	// FIXME : do it with a better delta !
	a.deltac(delta_ret, state, delta_kind::states());
	for (typename delta_ret_t::const_iterator j = delta_ret.begin();
	     j != delta_ret.end();
	     ++j)
	  {
	    state = *j;
	    if (reachable_states.find(state) == reachable_states.end())
	      {
		reachable_states.insert(state);
		queue.push(state);
	      }
	  }
      }
    return reachable_states;
  }

  template<typename A, typename T>
  std::set<hstate_t>
  start_reachable_states(const Element<A, T>& a)
  {
    return do_start_reachable_states(a.set(), a);
  }

  template<typename A, typename T>
  void
  auto_in_start_reachable(Element<A, T>& a)
  {    
    auto_in_extract(a, start_reachable_states(a));
  }

  template<typename A, typename T>
  Element<A, T>
  auto_start_reachable(const Element<A, T>& a)
  {    
    return auto_extract(a, start_reachable_states(a));
  }

  /*--------------------------.
  | do_start_reachable_states |
  `--------------------------*/
  // preconditions :
  //
  //
  template <class A_, typename Auto_>
  std::set<hstate_t>
  do_final_reachable_states(const AutomataBase<A_>& a_set,
			    const Auto_&		   a)
  {
    return start_reachable_states(transpose_view(a));
  }

  template<typename A, typename T>
  std::set<hstate_t>
  final_reachable_states(const Element<A, T>& a)
  {
    return do_final_reachable_states(a.set(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  auto_final_reachable(const Element<A, T>& a)
  {
    return auto_extract(a, final_reachable_states(a));
  }

  template<typename A, typename T>
  void
  auto_in_final_reachable(Element<A, T>& a)
  {
    auto_in_extract(a, final_reachable_states(a));
  }
  
} // vcsn

#endif // ALGORITHMS_REACHABLE_HXX
