// normalized_composition.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HXX
# define VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HXX


/**
 * @file normalized_composition.hxx
 *
 * @brief Composition for normalized and sub-normalized transducers
 * seen as automata over a free monoid product.
 *
 * @author Sarah O'Connor
 */


# include <set>
# include <queue>
# include <vaucanson/algorithms/normalized_composition.hh>
# include <vaucanson/algorithms/outsplitting.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/automata/concept/automata.hh>


namespace vcsn {

  template <typename S, typename M1, typename M2, typename lhs_t,
	    typename rhs_t, typename res_t>
  void
  do_b_composition(const AutomataBase<S>&,
		   const algebra::FreeMonoidProduct<M1, M2>&,
		   const lhs_t&			lhs,
		   const rhs_t&			rhs,
		   res_t&			output,
		   std::set<hstate_t>&		lhs_states,
		   std::set<hstate_t>&		rhs_states,
		   std::map< hstate_t, std::pair<hstate_t, hstate_t> >& m)
  {
    AUTOMATON_TYPES(res_t);
    AUTOMATON_TYPES_(lhs_t, lhs_);
    AUTOMATON_TYPES_(rhs_t, rhs_);

    typedef std::pair<hstate_t, hstate_t>		pair_hstate_t;
    typedef std::set<htransition_t>				delta_ret_t;
    typedef std::map<pair_hstate_t, hstate_t>		visited_t;
    typedef typename series_set_elt_t::support_t	support_t;
    typedef typename lhs_series_set_elt_t::support_t	lhs_support_t;
    typedef typename rhs_series_set_elt_t::support_t	rhs_support_t;


    const series_set_t&	series	 = output.structure().series();
    const monoid_t&	monoid	 = series.monoid();

    const lhs_series_set_t&	lhs_series   = lhs.structure().series();
    const lhs_monoid_t&		lhs_monoid   = lhs_series.monoid();

    const rhs_series_set_t&	rhs_series   = rhs.structure().series();
    const rhs_monoid_t&		rhs_monoid   = rhs_series.monoid();


    typedef typename lhs_monoid_t::first_monoid_t
      lhs_first_monoid_t;
    typedef typename lhs_monoid_elt_value_t::first_type
      lhs_first_monoid_elt_value_t;
    typedef Element<lhs_first_monoid_t, lhs_first_monoid_elt_value_t>
      lhs_first_monoid_elt_t;

    typedef typename rhs_monoid_t::first_monoid_t
      rhs_first_monoid_t;
    typedef typename rhs_monoid_elt_value_t::first_type
      rhs_first_monoid_elt_value_t;
    typedef Element<rhs_first_monoid_t, rhs_first_monoid_elt_value_t>
      rhs_first_monoid_elt_t;

    typedef typename lhs_monoid_t::second_monoid_t
      lhs_second_monoid_t;
    typedef typename lhs_monoid_elt_value_t::second_type
      lhs_second_monoid_elt_value_t;
    typedef Element<lhs_second_monoid_t, lhs_second_monoid_elt_value_t>
      lhs_second_monoid_elt_t;

    typedef typename rhs_monoid_t::second_monoid_t
      rhs_second_monoid_t;
    typedef typename rhs_monoid_elt_value_t::second_type
      rhs_second_monoid_elt_value_t;
    typedef Element<rhs_second_monoid_t, rhs_second_monoid_elt_value_t>
      rhs_second_monoid_elt_t;



    lhs_first_monoid_elt_t lhs_first_identity =
      algebra::identity_as<lhs_first_monoid_elt_value_t>::
      of(lhs.structure().series().monoid().first_monoid());
    rhs_first_monoid_elt_t rhs_first_identity =
      algebra::identity_as<rhs_first_monoid_elt_value_t>::
      of(rhs.structure().series().monoid().first_monoid());
    lhs_second_monoid_elt_t lhs_second_identity =
      algebra::identity_as<lhs_second_monoid_elt_value_t>::
      of(lhs.structure().series().monoid().second_monoid());
    rhs_second_monoid_elt_t rhs_second_identity =
      algebra::identity_as<rhs_second_monoid_elt_value_t>::
      of(rhs.structure().series().monoid().second_monoid());


    visited_t			visited;
    std::queue<pair_hstate_t>	to_process;

    /*----------------------------------.
    | Get initial states of the product |
    `----------------------------------*/
    for_each_initial_state(lhs_s, lhs)
      for_each_initial_state(rhs_s, rhs)
    {
      if (lhs_states.find(*lhs_s) == lhs_states.end() or
	  rhs_states.find(*rhs_s) == rhs_states.end())
      {
	const hstate_t	new_state = output.add_state();
	const pair_hstate_t	new_pair (*lhs_s, *rhs_s);

	m[new_state] = new_pair;
	visited[new_pair] = new_state;
	to_process.push(new_pair);
      }
    }

    /*-----------.
    | Processing |
    `-----------*/
    while (not to_process.empty())
    {
      const pair_hstate_t current_pair	= to_process.front();
      to_process.pop();

      const hstate_t lhs_s	     = current_pair.first;
      const hstate_t rhs_s	     = current_pair.second;
      const hstate_t current_state = visited[current_pair];

      if (lhs.is_initial(lhs_s) and rhs.is_initial(rhs_s))
      {
	lhs_series_set_elt_t in_l = lhs.get_initial(lhs_s);
	rhs_series_set_elt_t in_r = rhs.get_initial(rhs_s);

	lhs_support_t		in_left_supp = in_l.supp();
	rhs_support_t		in_right_supp = in_r.supp();

	semiring_elt_t in_semi_elt = in_l.get(*(in_left_supp.begin())) *
	  in_r.get(*(in_right_supp.begin()));

	series_set_elt_t in_series_elt(series);

	in_series_elt.assoc(monoid_elt_t(monoid,
					 algebra::identity_as<
					 monoid_elt_value_t>::
					 of(monoid).value()),
			    in_semi_elt);

	output.set_initial(current_state, in_series_elt);
      }

      if (lhs.is_final(lhs_s) and rhs.is_final(rhs_s))
      {
	lhs_series_set_elt_t out_l = lhs.get_final(lhs_s);
	rhs_series_set_elt_t out_r = rhs.get_final(rhs_s);

	lhs_support_t out_left_supp = out_l.supp();
	rhs_support_t out_right_supp = out_r.supp();

	semiring_elt_t out_semi_elt = out_l.get(*(out_left_supp.begin())) *
	  out_r.get(*(out_right_supp.begin()));

	series_set_elt_t out_series_elt(series);

	out_series_elt.assoc(monoid_elt_t(monoid,
					  algebra::identity_as<
					  monoid_elt_value_t>::of(monoid)),
			     out_semi_elt);


	output.set_final(current_state, out_series_elt);
      }

      delta_ret_t transition_lhs;
      delta_ret_t transition_rhs;
      lhs.deltac(transition_lhs, lhs_s, delta_kind::transitions());
      rhs.deltac(transition_rhs, rhs_s, delta_kind::transitions());

      for_all_const_(delta_ret_t, l, transition_lhs)
      {
	const lhs_series_set_elt_t	left_series  = lhs.series_of(*l);
	lhs_support_t		left_supp = left_series.supp();
	const lhs_monoid_elt_t	left_supp_elt (lhs_monoid,
					       *(left_supp.begin()));

	// If the outgoing transition is of type (*, 1).
	if (left_supp_elt.value().second == lhs_second_identity.value())
	{
	  series_set_elt_t	    prod_series (series);
	  const monoid_elt_value_t word(left_supp_elt.value().first,
					rhs_second_identity.value());
	  prod_series.assoc(monoid_elt_t(monoid, word),
			    left_series.get(left_supp_elt));

	  const pair_hstate_t new_pair (lhs.dst_of(*l), rhs_s);

	  /*-----------------.
	  | Add transition.  |
	  `-----------------*/

	  if (lhs_states.find(new_pair.first) == lhs_states.end() or
	      rhs_states.find(new_pair.second) == rhs_states.end())
	  {
	    typename visited_t::const_iterator found =
	      visited.find(new_pair);
	    hstate_t aim;
	    if (found == visited.end())
	    {
	      aim = output.add_state();
	      visited[new_pair] = aim;
	      m[aim] = new_pair;
	      to_process.push(new_pair);
	    }
	    else
	      aim = found->second;
	    output.add_series_transition(current_state, aim, prod_series);
	  }

	}
	else
	{
	  for_all_const_(delta_ret_t, r, transition_rhs)
	  {
	    const rhs_series_set_elt_t	right_series =
	      rhs.series_of(*r);
	    rhs_support_t		right_supp =
	      right_series.supp();
	    const rhs_monoid_elt_t	right_supp_elt
	      (rhs_monoid, *(right_supp.begin()));

	    // If the incoming transition is not of type (1, *).
	    if (right_supp_elt.value().first !=
		rhs_first_identity.value())
	    {
	      //  we try to connect a transition of lhs and
	      // a transition of rhs.
	      if (left_supp_elt.value().second ==
		  right_supp_elt.value().first)
	      {
		series_set_elt_t		prod_series (series);
		const monoid_elt_value_t	word
		  (left_supp_elt.value().first,
		   right_supp_elt.value().second);
		const semiring_elt_t		p =
		  left_series.get(left_supp_elt) *
		  right_series.get(right_supp_elt);

		prod_series.assoc(word, p.value());


		const pair_hstate_t new_pair (lhs.dst_of(*l),
					      rhs.dst_of(*r));


		/*-----------------.
		| Add transition.  |
		`-----------------*/

		if (lhs_states.find(new_pair.first) ==
		    lhs_states.end()
		    or
		    rhs_states.find(new_pair.second) ==
		    rhs_states.end())
		{
		  typename visited_t::const_iterator found =
		    visited.find(new_pair);
		  hstate_t aim;
		  if (found == visited.end())
		  {
		    aim = output.add_state();
		    visited[new_pair] = aim;
		    m[aim] = new_pair;
		    to_process.push(new_pair);
		  }
		  else
		    aim = found->second;
		  output.add_series_transition(current_state, aim,
					       prod_series);
		}
	      }
	    }
	  }
	}
      }

      for_all_const_(delta_ret_t, r, transition_rhs)
      {
	const rhs_series_set_elt_t  right_series =
	  rhs.series_of(*r);
	rhs_support_t		right_supp =
	  right_series.supp();
	const rhs_monoid_elt_t	right_supp_elt
	  (rhs_monoid, *(right_supp.begin()));

	if (right_supp_elt.value().first ==
	    rhs_first_identity.value())
	{
	  series_set_elt_t	prod_series (series);
	  const monoid_elt_value_t	word
	    (lhs_first_identity.value(),
	     right_supp_elt.value().second);
	  prod_series.assoc(monoid_elt_t(monoid, word),
			    right_series.get(right_supp_elt));

	  const pair_hstate_t new_pair (lhs_s, rhs.dst_of(*r));


	  /*-----------------.
	  | Add transition.  |
	  `-----------------*/

	  if (lhs_states.find(new_pair.first) ==
	      lhs_states.end() or
	      rhs_states.find(new_pair.second) ==
	      rhs_states.end())
	  {
	    typename visited_t::const_iterator found =
	      visited.find(new_pair);
	    hstate_t aim;
	    if (found == visited.end())
	    {
	      aim = output.add_state();
	      visited[new_pair] = aim;
	      m[aim] = new_pair;
	      to_process.push(new_pair);
	    }
	    else
	      aim = found->second;
	    output.add_series_transition(current_state, aim,
					 prod_series);
	  }
	}
      }
    }

  }


  template <typename S, typename M1, typename M2, typename lhs_t,
	    typename rhs_t, typename res_t>
  void
  do_normalized_composition(const AutomataBase<S>&,
			    const algebra::FreeMonoidProduct<M1, M2>&,
			    const lhs_t& lhs,
			    const rhs_t& rhs,
			    res_t& ret)
  {
    typedef std::set<hstate_t>			set_of_states_t;
    typedef std::map<hstate_t, std::pair<hstate_t, hstate_t> >
      map_of_states_t;
    set_of_states_t lhs_states;
    set_of_states_t rhs_states;

    lhs_t lhs_cov = outsplitting(lhs, lhs_states);
    rhs_t rhs_cov = insplitting(rhs, rhs_states);

    map_of_states_t m;
    do_b_composition(ret.structure(), ret.structure().series().monoid(),
		     lhs_cov, rhs_cov, ret, lhs_states, rhs_states, m);
  }



  template <typename S, typename T>
  void
  b_composition(const Element<S, T>& lhs,
		const Element<S, T>& rhs,
		Element<S, T>& ret)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    typedef std::set<hstate_t>			set_of_states_t;
    typedef std::map<hstate_t, std::pair<hstate_t, hstate_t> >
      map_of_states_t;
    set_of_states_t lhs_states;
    set_of_states_t rhs_states;
    map_of_states_t m;

    for_each_state (s, ret)
      {
	ret.del_state (*s);
      }
    do_b_composition(ret.structure(), ret.structure().series().monoid(),
		     lhs, rhs, ret, lhs_states, rhs_states, m);
  }


  template <typename S, typename T>
  Element<S, T>
  b_composition(const Element<S, T>& lhs,
		const Element<S, T>& rhs)
  {
    typedef Element<S, T> auto_t;

    typedef algebra::FreeMonoidProduct<
      typename auto_t::series_set_t::monoid_t::first_monoid_t,
      typename auto_t::series_set_t::monoid_t::second_monoid_t>	monoid_t;

    typedef algebra::Series<typename auto_t::series_set_t::semiring_t,
      monoid_t>
      series_set_t;

    monoid_t monoid(lhs.structure().series().monoid().first_monoid(),
		    rhs.structure().series().monoid().second_monoid());


    series_set_t series(lhs.structure().series().semiring(), monoid);

    Automata<series_set_t> aut_set(series);

    Element< Automata<series_set_t>, T> ret(aut_set);

    typedef std::set<hstate_t>			set_of_states_t;
    typedef std::map<hstate_t, std::pair<hstate_t, hstate_t> >
      map_of_states_t;
    set_of_states_t lhs_states;
    set_of_states_t rhs_states;
    map_of_states_t m;

    do_b_composition(ret.structure(), ret.structure().series().monoid(),
		     lhs, rhs, ret, lhs_states, rhs_states, m);
    return ret;
  }



  template <typename S, typename T>
  void
  normalized_composition(const Element<S, T>& lhs,
			 const Element<S, T>& rhs,
			 Element<S, T>& ret)
  {
    typedef Element<S,T> auto_t;
    AUTOMATON_TYPES(auto_t);

    for_each_state (s, ret)
      {
	ret.del_state (*s);
      }
    do_normalized_composition(ret.structure(),
			      ret.structure().series().monoid(),
			      lhs, rhs, ret);
  }


  template <typename S, typename T>
  Element<S, T>
  normalized_composition(const Element<S, T>& lhs,
			 const Element<S, T>& rhs)
  {
    typedef Element<S, T> auto_t;

    typedef algebra::FreeMonoidProduct<
      typename auto_t::series_set_t::monoid_t::first_monoid_t,
      typename auto_t::series_set_t::monoid_t::second_monoid_t>	monoid_t;

    typedef algebra::Series<typename auto_t::series_set_t::semiring_t,
      monoid_t>
      series_set_t;

    monoid_t monoid(lhs.structure().series().monoid().first_monoid(),
		    rhs.structure().series().monoid().second_monoid());


    series_set_t series(lhs.structure().series().semiring(), monoid);

    Automata<series_set_t> aut_set(series);

    Element< Automata<series_set_t>, T> ret(aut_set);
    do_normalized_composition(ret.structure(),
			      ret.structure().series().monoid(),
			      lhs, rhs, ret);
    return ret;
  }



} // End of namespace vcsn.

#endif // ! VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HXX
