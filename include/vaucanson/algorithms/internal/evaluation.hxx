// evaluation.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EVALUATION_HXX
# define VCSN_ALGORITHMS_EVALUATION_HXX

# include <vaucanson/algorithms/internal/evaluation.hh>

# include <vaucanson/automata/concept/transducer_base.hh>

# include <vaucanson/algorithms/product.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/algorithms/extension.hh>
# include <vaucanson/algorithms/image.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  template <typename SA, typename ST, typename SRET,
	    typename Auto_t, typename Trans_t, typename Ret_t>
  void
  do_evaluation(const AutomataBase<SA>&,
		const TransducerBase<ST>&,
		const AutomataBase<SRET>&,
		const Auto_t& a,
		const Trans_t& t,
		Ret_t& ret)
  {
    image(trim(product(t, extension(a, t))), ret);
  }

  template<typename SA, typename TA, typename ST,
	   typename TT, typename SRET, typename TRET>
  void
  evaluation(const Element<SA, TA>& a, const Element<ST, TT>& t,
	     Element<SRET, TRET>& ret)
  {
    do_evaluation(a.structure(), t.structure(), ret.structure(), a, t, ret);
  }

  template<typename U, typename V,
           typename Trans_t, typename M>
  void
  do_partial_evaluation(const U& E,
			const TransducerBase<V>&,
			const Trans_t& S,
			const typename Trans_t::hstate_t& p,
			M& res)
  {
    // type helpers
    typedef typename Trans_t::value_t W;
    typedef typename output_projection_helper<V, W>::ret Auto_t;
    AUTOMATON_TYPES(Auto_t);
    AUTOMATON_TYPES_(Trans_t, t_);
    typedef typename Auto_t::set_t Auto_set_t;
    typedef typename Auto_set_t::series_set_t Auto_series_set_t;
    typedef series_set_elt_t exp_t;
    typedef t_series_set_elt_t t_exp_t;
    typedef std::map<t_hstate_t, std::pair<t_hstate_t, t_hstate_t> >
    state_pair_map_t;
    typedef std::map<t_hstate_t, hstate_t> state_state_map_t;
    typedef std::pair<t_hstate_t, exp_t> se_pair_t;
    Auto_set_t auto_structure(Auto_series_set_t(S.structure().series().semiring()));

    //
    // Part 1.
    // Construct A = standard_of(E).
    //

    // Hold standard_of(E).
    Auto_t A(auto_structure);
    // The expression must come from a realtime automaton.
    assertion(E.supp().size() == 1);
    monoid_elt_t word(E.structure().monoid(), *E.supp().begin());
    standard_of(A, E.get(word).value());

    //
    // Part 2.
    // Sp construction.
    //

    // Does a copy of S,
    Trans_t Sp = S;
    state_state_map_t Sp_to_S;
    for_all_const_initial_states_(t_, q, Sp)
    {
      if (*q == Sp.get_state(size_t(p)))
	Sp.set_initial(*q);
      else
	Sp.unset_initial(*q);
    }
    // FIXME: initial or all states?
    for_all_const_states_(t_, q, Sp)
    Sp_to_S[*q] = S.get_state(size_t(*q));

    //
    // evaluation(A, Sp)
    // Evaluation: we keep some information for later.
    //

    // extension
    Trans_t tmp_trans(Sp.structure());
    tmp_trans = extension(A, Sp);

    // product
    Trans_t pro(Sp.structure());
    state_pair_map_t sp_m;
    pro = product(tmp_trans, Sp, sp_m);

    // build map we will reuse later
    std::map<typename Trans_t::hstate_t, typename Trans_t::hstate_t>    states_map_for_sp_m;
    for_all_iterator (typename state_pair_map_t::iterator, i, sp_m)
    states_map_for_sp_m.insert(std::make_pair(pro.get_state(size_t(i->first)), i->first));

    // image
    Auto_t G(auto_structure);
    state_state_map_t proj_m;
    G = image(pro, proj_m);

    std::map<typename Trans_t::hstate_t, typename Trans_t::hstate_t>    states_map_for_proj_m;
    for_all_iterator (typename state_state_map_t::iterator, i, proj_m)
    states_map_for_proj_m.insert(std::make_pair(G.get_state(size_t(i->first)), i->first));

    // add i state
    const hstate_t i = G.add_state();
    for_all_const_initial_states(r, G)
    {
      exp_t old_label = G.get_initial(*r);
      G.add_series_transition(i, *r, old_label);
      G.unset_initial(*r);
    }
    G.set_initial(i);

    //
    // Part 3.
    // Initialize map.
    //

    G.clear_final();
    state_state_map_t state_of, is_state_of;
    for_all_const_states_(t_, u, Sp)
    {
      hstate_t new_state = G.add_state();
      state_of[*u] = new_state;
      is_state_of[new_state] = *u;
      G.set_final(new_state);
    }

    //
    // Part 4.
    // Create spontaneous transitions.
    //

    for_all_const_states(ig, G)
    {
      if (*ig != i && !G.is_final(*ig))
      {
	t_hstate_t t = sp_m[states_map_for_sp_m[proj_m[states_map_for_proj_m[*ig]]]].first;
	t_hstate_t u = sp_m[states_map_for_sp_m[proj_m[states_map_for_proj_m[*ig]]]].second;

	if (tmp_trans.is_final(t))
	  G.add_spontaneous(*ig, state_of[u]);
      }
    }

    //
    // Part 5.
    // Construct the output map.
    //

    M se;
    partial_elimination(G, se);

    for_all_(M, p, se)
    {
      se_pair_t my_pair = std::make_pair(Sp_to_S[is_state_of[(*p).first]], p->second);
      res.insert(my_pair);
    }
  }

  template<typename S1, typename T1, 
  typename S2, typename T2, 
  typename M>
  void
  partial_evaluation(const Element<S1, T1>& E,
		     const Element<S2, T2>& S,
		     const typename Element<S2, T2>::hstate_t& p,
		     M& res)
  {
    do_partial_evaluation(E, S.structure(), S, p, res);
  }

  template<typename S, typename Auto_t, typename M, typename Chooser_t>
  void
  do_partial_elimination(const AutomataBase<S>&,
			 const Auto_t& a,
			 Chooser_t chooser,
			 M& state_exp_pair_set)
  {
    AUTOMATON_TYPES(Auto_t);
    typedef typename std::set<htransition_t>		htransition_set_t;
    typedef typename Auto_t::hstate_t			hstate_t;
    typedef std::map<hstate_t, series_set_elt_t>	sums_t;

    typename htransition_set_t::const_iterator		i, j;
    hstate_t						q;
    htransition_set_t					transitions;

    Auto_t b = a;

    // Save a map linking hstates between automata a and b.
    // This is needed to be able to fill state_exp_pair_set with correct hstates.
    std::map<hstate_t, hstate_t>			states_map;
    for (state_iterator i = a.states().begin(), j = b.states().begin(),
	 end_ = a.states().end();
	 i != end_;
	 ++i, ++j)
      states_map.insert(std::make_pair(*j, *i));

    // FIXME: check dead code
//    standardize(b);

    // all final states and the initial state.
    int num = b.final().size() + b.initial().size();

    while (int(b.states().size()) != num)
    {
      series_set_elt_t loop_sum(b.series());
      sums_t	   in_sums, out_sums;
      typename sums_t::iterator f;
      q = chooser(b);
      if (b.is_initial(q) || b.is_final(q))
	continue;

      transitions.clear();
      for (typename automaton_t::delta_iterator e(b.value(), q); ! e.done(); e.next())
        transitions.insert(*e);
      for (i = transitions.begin(); i != transitions.end(); i = j)
      {
	j = i; ++j;

	if (b.dst_of(*i) == q)
	  loop_sum += b.series_of(*i);
	else if ((f = out_sums.find(b.dst_of(*i))) !=
		 out_sums.end())
	  f->second += b.series_of(*i);
	else
	  out_sums.insert(std::make_pair(b.dst_of(*i), b.series_of(*i)));
	b.del_transition(*i);
      }
      transitions.clear();
      for (typename automaton_t::rdelta_iterator e(b.value(), q); ! e.done(); e.next())
        transitions.insert(*e);
      for (i = transitions.begin(); i != transitions.end(); i = j)
      {
	j = i; ++j;
	// here all loops have already been removed
	if ((f = in_sums.find(b.src_of(*i))) !=
	    in_sums.end())
	  f->second += b.series_of(*i);
	else
	  in_sums.insert(std::make_pair(b.src_of(*i), b.series_of(*i)));
	b.del_transition(*i);
      }
      loop_sum.star();
      for_all_const_(sums_t, in, in_sums)
	for_all_const_(sums_t, out, out_sums)
	{
	  series_set_elt_t res = in->second * loop_sum * out->second;
	  b.add_series_transition(in->first, out->first, res);
	}
      b.del_state(q);
    }

    typedef std::map<hstate_t, series_set_elt_t>   se_map_t;
    typedef std::pair<hstate_t, series_set_elt_t>  state_exp_pair_t;
    se_map_t se_m;

    // maybe there are more than one transition comming to one final state
    // we must sum the labels
    for_all_transitions(e, b)
    {
      hstate_t dst = b.dst_of(*e);
      typename se_map_t::iterator i = se_m.find(dst);
      if (i == se_m.end())
	se_m.insert(std::make_pair(dst,
				   series_set_elt_t (b.structure().series(),
						     b.label_of(*e))));
      else
	i->second += b.label_of(*e);
    }

    for_all_final_states(p, b)
    {
      typename se_map_t::iterator i = se_m.find(*p);
      if (i != se_m.end())
	state_exp_pair_set.insert(std::make_pair(states_map[*p], i->second));
    }
  }

  /*------------.
  | elimination |
  `------------*/
  // FIXME: add the generalized automaton precondition
  // preconditions :
  //   - hope that automaton's labels are sufficient to support "star"
  //	 => in fact, generalized automaton are generally expected here.
  template<typename A, typename T, typename M>
  void
  partial_elimination(const Element<A, T>& a,
		      M& state_exp_pair_set)
  {
    do_partial_elimination(a.structure(),
			   a,
			   DefaultChooser(),
			   state_exp_pair_set);
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_EVALUATION_HXX
