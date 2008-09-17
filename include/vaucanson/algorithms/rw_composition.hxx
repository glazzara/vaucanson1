// rw_composition.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The
// Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_RW_COMPOSITION_HXX
# define VCSN_ALGORITHMS_RW_COMPOSITION_HXX

# include <map>
# include <queue>
# include <set>

# include <vaucanson/algorithms/rw_composition.hh>
# include <vaucanson/automata/concept/transducer.hh>
// FIXME: The code for geometry computation must be enabled statically.
// (see product.hxx for some hints)
# include <vaucanson/automata/implementation/geometry.hh>

namespace vcsn {

  template<typename U, typename Trans_t>
  void
  do_rw_composition(const TransducerBase<U>&,
		    const Trans_t& R,
		    const Trans_t& S,
		    Trans_t& T)
  {
    TIMER_SCOPED("rw_composition");

    // type helpers
    AUTOMATON_TYPES(Trans_t);
    typedef series_set_elt_t exp_t;
    typedef typename series_set_elt_t::semiring_elt_t output_exp_t;
    typedef std::set<std::pair<hstate_t, output_exp_t> > state_exp_pair_set_t;
    typedef typename std::map<hstate_t, typename Trans_t::geometry_t::coords_t>::const_iterator geom_iter_t;
    typedef std::pair<hstate_t, hstate_t> state_pair_t;
    typedef std::queue<state_pair_t> state_pair_queue_t;
    typedef std::map<state_pair_t, hstate_t> state_pair_map_t;
    typedef std::set<htransition_t> set_of_transitions_t;

    // declare the main queue
    state_pair_queue_t queue;

    // We will reuse this structure many times:
    // each time we call partial_evaluation.
    // Do not forget to clear() it before the call.
    state_exp_pair_set_t sep_set;

    // Each time we create a new state in the output transducer
    // (say a pair (p, r)), we will add it to the following map
    // with the corresponding hstate_t, to speedup lookups.
    state_pair_map_t Tstates;

    // These variables help us create the new state geometry.
    double xgeom;
    double ygeom;
    geom_iter_t iter;

    //
    // Part 1 (refer to the algorithm description - see header).
    // Initial states creation.
    //

    for_all_const_initial_states (p, R)
    {
      // Hold the initial weight of the state p.
      exp_t E = R.get_initial(*p);

      for_all_const_initial_states (q, S)
      {
	// Hold the initial weight of the state q.
	exp_t F = S.get_initial(*q);

	// Partial evaluation.
	sep_set.clear();
	partial_evaluation(E, S, *q, sep_set);

	// Iterates throughout the partial_evaluation output.
	for_all_const_(state_exp_pair_set_t, ig, sep_set)
	{
	  // Construct the state representation (p, r).
	  state_pair_t sp;
	  sp.first = *p;
	  sp.second = (*ig).first;

	  // FIXME: store the iterator for later reuse
	  if (Tstates.find(sp) == Tstates.end())
	  {
	    // (p, r) does not exists yet in the output
	    // transducer.

	    // So we create it,
	    hstate_t new_state = T.add_state();

	    // add it the deduced geometry from p and r,
	    iter = R.geometry().states().find(*p);
	    if (iter != R.geometry().states().end())
	      xgeom = (*iter).second.first;
	    else
	      xgeom = 0;
	    iter = S.geometry().states().find(*q);
	    if (iter != S.geometry().states().end())
	      ygeom = (*iter).second.second;
	    else
	      ygeom = 0;
	    T.geometry().states()[new_state] = std::make_pair(xgeom, ygeom);

	    // store it in our lookup table,
	    Tstates[sp] = new_state;

	    // set the initial weight (we are only dealing with
	    // initial states),
	    T.set_initial(new_state, F * ((*ig).second));

	    // and finally push it in the queue.
	    queue.push(sp);
	  }
	  else
	  {
	    // (p, r) has already been created: we only
	    // update its initial weight.
	    T.set_initial(Tstates[sp],
			  T.get_initial(Tstates[sp]) + F * ((*ig).second));
	  }
	} // ! for_all_const_state_exp_pair_set_t
      } // ! for_all_const_initial_states
    } // ! for_all_const_initial_states

    //
    // Part 2 (refer to the algorithm description - see header).
    // Main loop (runs until the queue is exhausted).
    //

    while (not queue.empty())
    {
      // Pop one state from the queue.
      const state_pair_t sp = queue.front();
      queue.pop();

      const hstate_t p = sp.first;
      const hstate_t q = sp.second;

      // Fill a transition set appropriately.
      // FIXME: we should better use the transitions iterators.
      set_of_transitions_t transitions;
      R.deltac(transitions, p, delta_kind::transitions());

      for_all_const_(set_of_transitions_t, e, transitions)
      {
	// set s
	hstate_t s = R.dst_of(*e);
	// set E
	exp_t E = R.series_of(*e);
	// set x
	// Input must be realtime.
	assertion(E.supp().size() == 1);
	monoid_elt_t x(E.structure().monoid(), *E.supp().begin());

	// Partial evaluation.
	sep_set.clear();
	partial_evaluation(E, S, q, sep_set);

	for_all_const_(state_exp_pair_set_t, ig, sep_set)
	{
	  // Construct the state representation (s, r).
	  state_pair_t sp1;
	  sp1.first = s;
	  sp1.second = (*ig).first;

	  // FIXME: store the iterator for later reuse
	  if (Tstates.find(sp1) == Tstates.end())
	  {
	    // (s, r) does not exists yet in the output
	    // transducer.

	    // So we create it,
	    hstate_t new_state = T.add_state();

	    // add it the deduced geometry from s and r,
	    iter = R.geometry().states().find(sp1.first);
	    if (iter != R.geometry().states().end())
	      xgeom = (*iter).second.first;
	    else
	      xgeom = 0;
	    iter = S.geometry().states().find(sp1.second);
	    if (iter != S.geometry().states().end())
	      ygeom = (*iter).second.second;
	    else
	      ygeom = 0;
	    T.geometry().states()[new_state] = std::make_pair(xgeom, ygeom);

	    // store it in our lookup table,
	    Tstates[sp1] = new_state;

	    // and finally push it in the queue.
	    queue.push(sp1);
	  }

	  exp_t Gexp (R.structure().series());
	  Gexp.assoc(x, (*ig).second);
	  // FIXME: if new_state optim?
	  T.add_series_transition(Tstates[sp], Tstates[sp1], Gexp);
	}
      } // ! for_all_const_set_of_transitions_t

      // Handle final states.
      if (R.is_final(p))
      {
	// Partial evaluation.
	sep_set.clear();
	partial_evaluation(R.get_final(p), S, q, sep_set);

	for_all_const_(state_exp_pair_set_t, ig, sep_set)
	{
	  const hstate_t r = (*ig).first;
	  if (S.is_final(r))
	    T.set_final(Tstates[sp], (*ig).second * S.get_final(r));
	}
      }
    } // ! main loop
  }

  // Wrapper around do_rw_composition.
  template< typename S, typename T>
  void
  rw_composition(const Element<S, T>& lhs,
		 const Element<S, T>& rhs,
		 Element<S, T>& ret)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);
    // We need to make sure RET is empty before passing it
    // to do_rw_composition(), therefore it won't work if
    // RET refers to the same automaton as LHS or RHS.
    precondition(&ret != &lhs);
    precondition(&ret != &rhs);
    for_all_states (s, ret)
      ret.del_state (*s);
    do_rw_composition(lhs.structure(), lhs, rhs, ret);
  }

  // This wrapper creates a new automaton. No
  // special care needs be taken.
  template< typename S, typename T>
  Element<S, T>
  rw_composition(const Element<S, T>& lhs, const Element<S, T>& rhs)
  {
    Element<S, T> ret (lhs.structure());
    do_rw_composition(lhs.structure(), lhs, rhs, ret);
    return ret;
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_RW_COMPOSITION_HXX
