// one_eps_closure.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2010 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_ONE_EPS_CLOSURE_HXX
# define VCSN_ALGORITHMS_ONE_EPS_CLOSURE_HXX

# include <vaucanson/algorithms/one_eps_closure.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <list>

namespace vcsn
{

  template<typename A, typename AI, typename S, typename V>
  void
  workaround_add_series_transition(const AutomataBase<A>& a_set,
				   Element<A, AI>&   a,
				   S& src, S& dst, V& val)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t)
    // We cannot update a transition with the current interface.
    // Instead...
    // Find the first transitions going from source to target,
    // labelled by K.  If it exists, remove it and add
    // its label K to the series we wanted to create.
    for (delta_iterator j(a.value(), src); !j.done(); j.next())
      {
	if (a.dst_of(*j) != dst)
	  {
	    continue;
	  }
	else
	  {
	    val += a.series_of(*j);
	    a.del_transition(*j);
	    break;
	  }
      }
	if (val != a.series().zero_)
    	a.add_series_transition(src, dst, val);
  }

  /*-------------------------------------------.
  | One Epsilon Closure for weighted automaton |
  `--------------------------------------------*/


  template<class A, typename AI, typename EPS>
  void
  do_backward_one_eps_closure(const AutomataBase<A>& a_set,
			      Element<A, AI>&   a,
			      const EPS& eps)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t)

    hstate_t source = eps.src();
    hstate_t dest = eps.dst();

    precondition(source != dest);

    // Computation of the list of transitions which follow 'eps' This
    // list has to be computed before creating any new transition.
    // Otherwise, if add_to_transition() deletes a transition, it
    // makes the delta_iterator invalid.
    std::list<htransition_t> transition_list;
    for (delta_iterator it(a.value(), dest); !it.done(); it.next())
      transition_list.push_back(*it);

    // Creation of the new transitions.
    for(typename std::list<htransition_t>::iterator it =
	  transition_list.begin(); it != transition_list.end(); ++it)
      {
	series_set_elt_t series = eps.weight() * a.series_of(*it);

	if (series == a.series().zero_)
	  continue;

	hstate_t target = a.dst_of(*it);

	workaround_add_series_transition(a.structure(), a,
					 source, target, series);
      }


    // Handling final functions.
    series_set_elt_t fin_weight =
      a.get_final(source) + eps.weight() * a.get_final(dest);

    a.set_final(source, fin_weight);
  }

  template<class A, typename AI, typename EPS>
  void
  do_forward_one_eps_closure(const AutomataBase<A>& a_set,
		      Element<A, AI>&   a,
		      const EPS& eps)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    hstate_t source = eps.src();
    hstate_t dest = eps.dst();

    precondition(source != dest);

    // Computation of the list of transitions which precede 'eps'.
    // This list has to be coumputed before creating any new
    // transition.  Otherwise, if add_to_transition deletes a
    // transition, it makes the delta_iterator invalid.
    std::list<htransition_t> transition_list;
    for (rdelta_iterator it(a.value(), source); ! it.done(); it.next())
      transition_list.push_back(*it);

    // Creation of the new transitions.
    for(typename std::list<htransition_t>::iterator it =
	  transition_list.begin(); it != transition_list.end(); ++it)
      {
	series_set_elt_t series = a.series_of(*it) * eps.weight();

	if (series == a.series().zero_)
	  continue;

	hstate_t target = a.dst_of(*it);

	workaround_add_series_transition(a.structure(), a,
					 source, target, series);
      }

    // Handling initial functions.
    series_set_elt_t ini_weight =
      a.get_initial(source) * eps.weight() + a.get_initial(dest);
    a.set_initial(dest, ini_weight);
  }

  template<typename A, typename AI, typename EPS>
  void
  backward_one_eps_closure(Element<A, AI>& a, const EPS& eps)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    do_backward_one_eps_closure(a.structure(), a, eps);
  }

  template<typename A, typename AI, typename EPS>
  void
  forward_one_eps_closure(Element<A, AI>& a, const EPS& eps)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    do_forward_one_eps_closure(a.structure(), a, eps);
  }

  template<typename A, typename AI, typename EPS>
  void
  one_eps_closure(Element<A, AI>& a, const EPS& eps, misc::direction_type dir)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    switch(dir){
    case misc::backward :
      do_backward_one_eps_closure(a.structure(), a, eps);
      break;
    case misc::forward :
      do_forward_one_eps_closure(a.structure(), a, eps);
      break;
    }
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_ONE_EPS_CLOSURE_HXX
