// accessible.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_ACCESSIBLE_HXX
# define VCSN_ALGORITHMS_ACCESSIBLE_HXX

# include <vaucanson/algorithms/accessible.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concrete/transpose_view.hh>
# include <vaucanson/algorithms/sub_automaton.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <queue>
# include <set>


namespace vcsn {

  /*---------------------.
  | do_accessible_states |
  `---------------------*/
  // preconditions :
  //
  //
  template <class A_, typename Auto_>
  std::set<hstate_t>
  do_accessible_states(const AutomataBase<A_>&,
		       const Auto_&		   a)
  {
    AUTOMATON_TYPES(Auto_);
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
    for_each_initial_state(i, a)
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
	a.deltac(delta_ret, state, delta_kind::states());
	for_each_const_(delta_ret_t, j, delta_ret)
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
  accessible_states(const Element<A, T>& a)
  {
    return do_accessible_states(a.set(), a);
  }

  template<typename A, typename T>
  void
  accessible_here(Element<A, T>& a)
  {
    sub_automaton_here(a, accessible_states(a));
  }

  template<typename A, typename T>
  Element<A, T>
  accessible(const Element<A, T>& a)
  {
    return sub_automaton(a, accessible_states(a));
  }

  /*-----------------------.
  | do_coaccessible_states |
  `-----------------------*/
  // preconditions :
  //
  //
  template <class A_, typename Auto_>
  std::set<hstate_t>
  do_coaccessible_states(const AutomataBase<A_>&,
			 const Auto_&	       a)
  {
    return accessible_states(transpose_view(a));
  }

  template<typename A, typename T>
  std::set<hstate_t>
  coaccessible_states(const Element<A, T>& a)
  {
    return do_coaccessible_states(a.set(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  coaccessible(const Element<A, T>& a)
  {
    return sub_automaton(a, coaccessible_states(a));
  }

  template<typename A, typename T>
  void
  coaccessible_here(Element<A, T>& a)
  {
    sub_automaton_here(a, coaccessible_states(a));
  }

} // vcsn

#endif // VCSN_ALGORITHMS_ACCESSIBLE_HXX
