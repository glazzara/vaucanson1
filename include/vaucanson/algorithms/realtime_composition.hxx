// realtime_composition.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_REALTIME_COMPOSITION_HXX
# define VCSN_ALGORITHMS_REALTIME_COMPOSITION_HXX

# include <vaucanson/algorithms/realtime_composition.hh>

# include <vaucanson/automata/concept/transducer.hh>

# include <queue>

namespace vcsn {

  /* Composition for realtime transducers. */
  template< typename S,
	    typename Trans_t>
  void
  do_realtime_composition(const TransducerBase<S>&,
			  const Trans_t& lhs,
			  const Trans_t& rhs,
			  Trans_t& ret)
  {
    AUTOMATON_TYPES(Trans_t);

    using namespace std;

    typedef series_set_elt_t exp_t;
    typedef typename series_set_elt_t::semiring_elt_t  output_exp_t;
    typedef set<std::pair<hstate_t, output_exp_t> >    state_exp_pair_set_t;
    typedef pair<hstate_t, hstate_t>		       state_pair_t;
    typedef map<state_pair_t, hstate_t>		       state_pair_map_t;
    typedef queue<state_pair_t>			       state_pair_queue_t;
    typedef set<htransition_t>			       set_of_transitions_t;

    typedef typename Trans_t::value_t			  T;
    typedef typename output_projection_helper<S, T>::ret  Auto_t;
    typedef typename Auto_t::set_t::series_set_t	  Auto_series_set_t;
    typedef typename Auto_t::set_t			  o_automata_set_t;

    o_automata_set_t auto_structure
      (Auto_series_set_t (lhs.structure().series().semiring()));

    AUTOMATON_TYPES_(Auto_t, a_);

    state_exp_pair_set_t     sep_set;
    state_pair_map_t	     sp_map;

    state_pair_queue_t	     sp_queue;

    exp_t	  null_exp = lhs.series().zero_;
    monoid_elt_t  empty	   = lhs.series().monoid().empty_;

    for_each_initial_state(p, lhs)
    {
      exp_t exp = lhs.get_initial(*p);
      partial_evaluation(exp, rhs, sep_set);

      for_each_const_(state_exp_pair_set_t, mypair, sep_set)
      {

	hstate_t new_state = ret.add_state(); // add_state

	state_pair_t sp;
	sp.first  = *p;
	sp.second = (*mypair).first;

	sp_queue.push(sp);
	sp_map[sp] = new_state;
	exp_t s(exp.structure());
	s.assoc(empty, (*mypair).second);
	ret.set_initial(new_state, s);
      }

    }
    while(!sp_queue.empty())
    {
      state_pair_t sp = sp_queue.front();
      sp_queue.pop();
      hstate_t p = sp.first;
      hstate_t q = sp.second;

      if (lhs.is_final(p))
      {
	exp_t exp = lhs.get_final(p);

	Auto_t a(auto_structure);
	standard_of(a, exp.get(empty).value());

	output_exp_t exp1 (a.series());
	partial_2(a, rhs, q, exp1);

	output_exp_t null_series =
	  a.series().zero(SELECT(typename a_series_set_elt_t::value_t));

	if (exp1 != null_series)
	{
	  exp_t s (lhs.series());
	  s.assoc(empty, exp1);
	  ret.set_final(sp_map[sp], s);
	}
      }

      set_of_transitions_t transitions;
      lhs.deltac(transitions, p, delta_kind::transitions());

      for_each_const_(set_of_transitions_t, e, transitions)
      {
	hstate_t p_ = lhs.aim_of(*e);
	exp_t exp = lhs.series_of(*e);

	assertion(exp.supp().size() == 1);
	monoid_elt_t word (exp.structure().monoid(),
			   *(exp.supp().begin()));
	// This supp would have one word

	Auto_t a(auto_structure);
	standard_of(a, exp.get(word).value());
	state_exp_pair_set_t sep_set1;
	partial_3(a, rhs, q, sep_set1);

	for_each_const_(state_exp_pair_set_t, mypair, sep_set1)
	{
	  state_pair_t sp1;
	  sp1.first = p_;
	  sp1.second = (*mypair).first;
	  if (sp_map.find(sp1) == sp_map.end())
	  {
	    hstate_t new_state = ret.add_state();
	    sp_map[sp1] = new_state;
	    sp_queue.push(sp1);
	  }

	  exp_t s (lhs.structure().series());
	  s.assoc(word, (*mypair).second);
	  ret.add_series_transition( sp_map[sp], sp_map[sp1], s);
	}
      }
    }

  }

  template< typename S, typename T>
  void
  realtime_composition(const Element<S, T>& lhs,
		       const Element<S, T>& rhs,
		       Element<S, T>& ret)
  {
    do_realtime_composition(lhs.structure(), lhs, rhs, ret);
  }


  template< typename S, typename T>
  Element<S, T>
  realtime_composition(const Element<S, T>& lhs,
		       const Element<S, T>& rhs)
  {
    Element<S, T> ret (lhs.structure());
    do_realtime_composition(lhs.structure(), lhs, rhs, ret);
    return ret;
  }
}

#endif // ! VCSN_ALGORITHMS_REALTIME_COMPOSITION_HXX
