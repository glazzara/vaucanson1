// rw_composition.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 The
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
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/automata/concept/transducer.hh>
// FIXME: The code for geometry computation must be enabled statically.
// (see product.hxx for some hints)
# include <vaucanson/automata/implementation/geometry.hh>
# include <vaucanson/algorithms/internal/evaluation.hh>

namespace vcsn
{
  template <typename U, typename Trans_t>
  void
  do_rw_composition(const TransducerBase<U>&,
		    const Trans_t& R,
		    const Trans_t& S,
		    Trans_t& T)
  {
    BENCH_TASK_SCOPED("rw_composition");

    // The second transducer must be realtime.
    precondition(is_realtime(S));

    // Type helpers.
    AUTOMATON_TYPES(Trans_t);
    typedef series_set_elt_t exp_t;
    typedef typename series_set_elt_t::semiring_elt_t output_exp_t;
    typedef std::set<std::pair<hstate_t, output_exp_t> > state_exp_pair_set_t;
    typedef typename std::map<hstate_t, typename Trans_t::geometry_t::coords_t>::const_iterator geom_iter_t;
    typedef std::pair<hstate_t, hstate_t> state_pair_t;
    typedef std::queue<state_pair_t> state_pair_queue_t;
    typedef std::map<state_pair_t, hstate_t> state_pair_map_t;
    typedef std::set<htransition_t> set_of_transitions_t;

    // Declare the main queue (FIFO).
    state_pair_queue_t queue;

    // We will reuse this structure many times:
    // each time we call partial_evaluation.
    // Do not forget to clear() it before the call.
    state_exp_pair_set_t sep_set;

    // Each time we create a new state in the output transducer
    // (say a pair (p, r)), we will add it to the following map
    // with the corresponding hstate_t, to speedup lookups.
    state_pair_map_t Tstates;

    // These variables help us to create the new state geometry.
    double xgeom;
    double ygeom;
    geom_iter_t iter;

    //
    // Part 1 (refer to the algorithm description - see header).
    // Initial states creation.
    //

    monoid_elt_t Ridentity = R.series().monoid().identity(SELECT(monoid_elt_value_t));
    monoid_elt_t Sidentity = S.series().monoid().identity(SELECT(monoid_elt_value_t));
    monoid_elt_t Tidentity = T.series().monoid().identity(SELECT(monoid_elt_value_t));

    for_all_const_initial_states (p, R)
    {
      // Hold the initial weight of the state p in R.
      // Warning: we suppose that the series on p is of the form: {w} 1, thus we
      // can access the weight directly. But R is not required to be realtime,
      // and there may be the series ({w} a) + ({z} b) on an initial state.
      output_exp_t E = R.get_initial(*p).get(Ridentity);

      for_all_const_initial_states (q, S)
      {
	// Hold the initial weight of the state q in S.
	// S is realtime, so we can access the weight directly.
	output_exp_t F = S.get_initial(*q).get(Sidentity);

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

	  if (Tstates.find(sp) == Tstates.end())
	  {
	    // (p, r) does not exists yet in the output transducer.

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

	    // Set the initial weight. (see hypothesis on R)
	    series_set_elt_t new_series(T.series());
	    new_series.assoc(Tidentity, F * ((*ig).second));
	    T.set_initial(new_state, new_series);

	    // and finally push it in the queue.
	    queue.push(sp);
	  }
	  else
	  {
	    // (p, r) has already been created: we only update its initial
	    // weight.
	    series_set_elt_t new_series(T.series());
	    new_series.assoc(Tidentity, T.get_initial(Tstates[sp]).get(Tidentity) + F * ((*ig).second));
	    T.set_initial(Tstates[sp], new_series);
	  }
	} // ! for_all_const_state_exp_pair_set_t
      } // ! for_all_const_initial_states (S)
    } // ! for_all_const_initial_states (R)

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

      // Build (p, x, E, s).
      for (delta_iterator e(R.value(), p); !e.done(); e.next())
      {
	hstate_t s = R.dst_of(*e);
	exp_t E = R.series_of(*e);

	// R is not required to be realtime so we must iterate over the support
	// of E.
	for_all_const_(series_set_elt_t::support_t, y, E.supp())
	{
	  const monoid_elt_t x(E.structure().monoid(), *y);

	  // Partial evaluation.
	  sep_set.clear();
	  partial_evaluation(E.get(x), S, q, sep_set);

	  for_all_const_(state_exp_pair_set_t, ig, sep_set)
	  {
	    // Construct the state representation (s, r).
	    state_pair_t sp1;
	    sp1.first = s;
	    sp1.second = (*ig).first;

	    if (Tstates.find(sp1) == Tstates.end())
	    {
	      // (s, r) does not exists yet in the output transducer.

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

	    exp_t Gexp(R.structure().series());
	    Gexp.assoc(x, (*ig).second);
	    T.add_series_transition(Tstates[sp], Tstates[sp1], Gexp);
	  } // ! for_all_const_state_exp_pair_set_t
	} // ! for_all_const_series_set_elt_t::support_t
      } // ! outgoing transitions from p in R

      // Handle final states.
      if (R.is_final(p))
      {
	// Partial evaluation.
	// The same hypothesis on the final states than for initial states hold.
	sep_set.clear();
	partial_evaluation(R.get_final(p).get(Ridentity), S, q, sep_set);

	for_all_const_(state_exp_pair_set_t, ig, sep_set)
	{
	  const hstate_t r = (*ig).first;
	  if (S.is_final(r))
	  {
	    series_set_elt_t new_series(T.series());
	    // S is realtime so we can directly access the final weight.
	    new_series.assoc(Tidentity, (*ig).second * S.get_final(r).get(Sidentity));
	    T.set_final(Tstates[sp], new_series);
	  }
	}
      } // ! is_final
    } // ! main loop
  }

  // Wrapper around do_rw_composition.
  template <typename S, typename T>
  void
  rw_composition(const Element<S, T>& lhs,
		 const Element<S, T>& rhs,
		 Element<S, T>& ret)
  {
    // Type helpers.
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    // We need to make sure RET is empty before passing it
    // to do_rw_composition(), therefore it won't work if
    // RET refers to the same automaton as LHS or RHS.
    precondition(&ret != &lhs);
    precondition(&ret != &rhs);

    // Remove all the state from ret.
    for_all_states (s, ret)
      ret.del_state(*s);

    do_rw_composition(lhs.structure(), lhs, rhs, ret);
  }

  // This wrapper creates a new automaton. No
  // special care needs be taken.
  template <typename S, typename T>
  Element<S, T>
  rw_composition(const Element<S, T>& lhs, const Element<S, T>& rhs)
  {
    // Create an empty automaton based on the lhs structure.
    Element<S, T> ret(lhs.structure());

    do_rw_composition(lhs.structure(), lhs, rhs, ret);
    return ret;
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_RW_COMPOSITION_HXX
