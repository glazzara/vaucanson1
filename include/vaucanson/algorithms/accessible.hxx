// accessible.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_ACCESSIBLE_HXX
# define VCSN_ALGORITHMS_ACCESSIBLE_HXX

# include <vaucanson/algorithms/accessible.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/implementation/transpose_view.hh>
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
    return do_accessible_states(a.structure(), a);
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
    return do_coaccessible_states(a.structure(), a);
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

#endif // ! VCSN_ALGORITHMS_ACCESSIBLE_HXX
