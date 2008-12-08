// normalized_composition.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
   * The algorithm is described in section 2.3 of "Inside Vaucanson".
   *
   * @see http://www.lrde.org/cgi-bin/twiki/view/Publications/200506-Ciaa
   *
   * @author Sarah O'Connor
   */


# include <set>
# include <queue>
# include <vaucanson/algorithms/normalized_composition.hh>
# include <vaucanson/algorithms/internal/outsplitting.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/automata/concept/automata.hh>


namespace vcsn {

  template <typename S, typename M1, typename M2, typename lhs_t,
	    typename rhs_t, typename res_t>
  struct composer
  {
    AUTOMATON_TYPES(res_t);
    AUTOMATON_TYPES_(lhs_t, lhs_);
    AUTOMATON_TYPES_(rhs_t, rhs_);

   #define SPECIFIC_TYPES(Auto) \
      typedef std::list<typename Auto##_t::htransition_t>      Auto##_delta_ret_t; \

    SPECIFIC_TYPES(lhs);
    SPECIFIC_TYPES(rhs);
    SPECIFIC_TYPES(res);

    #undef SPECIFIC_TYPES
    typedef std::pair<lhs_hstate_t, rhs_hstate_t>	pair_hstate_t;
    typedef std::map<pair_hstate_t, hstate_t>		visited_t;
    typedef std::map<hstate_t, pair_hstate_t>		map_of_states_t;
    typedef std::queue<pair_hstate_t>			to_process_t;

    typedef std::list<htransition_t>			delta_ret_t;
    typedef typename series_set_elt_t::support_t	support_t;
    typedef typename lhs_series_set_elt_t::support_t	lhs_support_t;
    typedef typename rhs_series_set_elt_t::support_t	rhs_support_t;

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

    visited_t visited;
    to_process_t to_process;
    map_of_states_t m;

    const lhs_t&                 lhs;
    const rhs_t&                 rhs;
    res_t&                       output;
    std::set<typename lhs_t::hstate_t>& lhs_black_states;
    std::set<typename rhs_t::hstate_t>& rhs_black_states;

    const series_set_t&	series;
    const monoid_t&	monoid;

    const lhs_series_set_t&	lhs_series;
    const lhs_monoid_t&		lhs_monoid;

    const rhs_series_set_t&	rhs_series;
    const rhs_monoid_t&		rhs_monoid;

    lhs_first_monoid_elt_t lhs_first_identity;
    rhs_first_monoid_elt_t rhs_first_identity;
    lhs_second_monoid_elt_t lhs_second_identity;
    rhs_second_monoid_elt_t rhs_second_identity;

    composer (const AutomataBase<S>&,
	      const algebra::FreeMonoidProduct<M1, M2>&,
	      const lhs_t&			  aLhs,
	      const rhs_t&			  aRhs,
	      res_t&				  aOutput,
	      std::set<typename lhs_t::hstate_t>& aLhs_states,
	      std::set<typename rhs_t::hstate_t>& aRhs_states)
      : lhs (aLhs),
	rhs (aRhs),
	output (aOutput),
	lhs_black_states (aLhs_states),
	rhs_black_states (aRhs_states),

        series (output.structure().series()),
	monoid (series.monoid()),

	lhs_series (lhs.structure().series()),
	lhs_monoid (lhs_series.monoid()),

	rhs_series (rhs.structure().series()),
	rhs_monoid (rhs_series.monoid()),

	lhs_first_identity (algebra::identity_as<lhs_first_monoid_elt_value_t>::
			    of(lhs_monoid.first_monoid())),
	rhs_first_identity (algebra::identity_as<rhs_first_monoid_elt_value_t>::
			    of(rhs_monoid.first_monoid())),
	lhs_second_identity (algebra::identity_as<lhs_second_monoid_elt_value_t>::
			     of(lhs_monoid.second_monoid())),
	rhs_second_identity (algebra::identity_as<rhs_second_monoid_elt_value_t>::
			     of(rhs_monoid.second_monoid()))
    {
    }

    // - Add a transition between current_state and the state
    //   corresponding to the pair (from,to).
    // - If the state (from,to) does not exist, then it is created.
    // - The transition is labelled by prod_series.
    void
    add_transition(const hstate_t current_state,
		   const hstate_t from,
		   const hstate_t to,
		   typename res_t::series_set_elt_t& prod_series)
    {
      if (lhs_black_states.find(from) == lhs_black_states.end()
	  or rhs_black_states.find(to) == rhs_black_states.end())
	{
	  const pair_hstate_t new_pair (from, to);

	  typename visited_t::const_iterator found =
	    visited.find(new_pair);
	  hstate_t dst;
	  if (found == visited.end())
	    {
	      dst = output.add_state();
	      visited[new_pair] = dst;
	      m[dst] = new_pair;
	      to_process.push(new_pair);
	    }
	  else
	    dst = found->second;
	  output.add_series_transition(current_state, dst, prod_series);
	}
    }

    typename res_t::series_set_elt_t
    series_product (typename monoid_elt_value_t::first_type l1,
		    typename monoid_elt_value_t::second_type l2,
		    semiring_elt_t w)
    {
      typename res_t::series_set_elt_t res (series);
      const monoid_elt_value_t word (l1, l2);
      res.assoc(word, w.value());
      return res;
    }


    // Compute the series for an initial or a final state, on the
    // empty word.
    typename res_t::series_set_elt_t
    state_series (lhs_series_set_elt_t l,
		  rhs_series_set_elt_t r)
    {
      series_set_elt_t res(series);
      res.assoc(monoid_elt_t(monoid,
			     algebra::identity_as<monoid_elt_value_t>::
			     of(monoid).value()),
		l.get(*l.supp().begin()) * r.get(*r.supp().begin()));
      return res;
    }

    void process_one_pair (const hstate_t current_state,
			   const typename lhs_t::hstate_t lhs_s,
                           const hstate_t rhs_s)
    {

      if (lhs.is_initial(lhs_s) and rhs.is_initial(rhs_s))
	output.set_initial(current_state,
			   state_series (lhs.get_initial(lhs_s),
					 rhs.get_initial(rhs_s)));

      if (lhs.is_final(lhs_s) and rhs.is_final(rhs_s))
	output.set_final(current_state,
			 state_series (lhs.get_final(lhs_s),
				       rhs.get_final(rhs_s)));

      for (delta_iterator l(lhs.value(), lhs_s); ! l.done(); l.next())
	{
	  const lhs_series_set_elt_t left_series = lhs.series_of(*l);
	  const lhs_monoid_elt_t left_supp_elt (lhs_monoid,
						*left_series.supp().begin());

	  // (i)
	  // If the outgoing transition is of type (*, 1).
	  if (left_supp_elt.value().second == lhs_second_identity.value())
	    {
	      series_set_elt_t s =
		series_product (left_supp_elt.value().first,
				rhs_second_identity.value(),
				left_series.get(left_supp_elt));
	      add_transition (current_state,
			      lhs.dst_of(*l), rhs_s, s);
	    }
	  // (iii')
	  else
	    {
              for (delta_iterator r(rhs.value(), rhs_s); ! r.done(); r.next())
		{
		  const rhs_series_set_elt_t right_series =
		    rhs.series_of(*r);
		  const rhs_monoid_elt_t right_supp_elt
		    (rhs_monoid, *right_series.supp().begin());

		  // If the incoming transition is not of type (1, *).
		  if (right_supp_elt.value().first !=
		      rhs_first_identity.value())
		    //  we try to connect a transition of lhs and
		    // a transition of rhs.
		    if (left_supp_elt.value().second ==
			right_supp_elt.value().first)
		      {
			series_set_elt_t s =
			  series_product (left_supp_elt.value().first,
					  right_supp_elt.value().second,
					  left_series.get(left_supp_elt)
					  * right_series.get(right_supp_elt));
			add_transition
			  (current_state,
			   lhs.dst_of(*l), rhs.dst_of(*r),
			   s);
		      }
		}
	    }
	}

      for (delta_iterator r(rhs.value(), rhs_s); ! r.done(); r.next())
	{
	  const rhs_series_set_elt_t right_series = rhs.series_of(*r);
	  const rhs_monoid_elt_t right_supp_elt (rhs_monoid,
						 *right_series.supp().begin());

	  // (ii)
	  if (right_supp_elt.value().first == rhs_first_identity.value())
	    {
	      series_set_elt_t s =
		series_product (lhs_first_identity.value(),
				right_supp_elt.value().second,
				right_series.get(right_supp_elt));
	      add_transition (current_state,
			      lhs_s, rhs.dst_of(*r), s);
	    }
	}

    }


    void operator() ()
    {

      /*----------------------------------.
      | Get initial states of the product |
      `----------------------------------*/
      for_all_const_initial_states(lhs_s, lhs)
	for_all_const_initial_states(rhs_s, rhs)
	{
	  if (lhs_black_states.find(*lhs_s) == lhs_black_states.end() or
	      rhs_black_states.find(*rhs_s) == rhs_black_states.end())
	    {
	      const hstate_t	  new_state = output.add_state();
	      const pair_hstate_t new_pair (*lhs_s, *rhs_s);

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
	  const pair_hstate_t p = to_process.front();
	  to_process.pop();
	  process_one_pair (visited[p], p.first, p.second);
	}
    }
  };



  /// Ambiguous composition.
  /// Works only for boolean transducers.
  template <typename S, typename M1, typename M2, typename lhs_t,
	    typename rhs_t, typename res_t>
  void
  do_compose(const AutomataBase<S>&,
	     const algebra::FreeMonoidProduct<M1, M2>&,
	     const lhs_t& lhs,
	     const rhs_t& rhs,
	     res_t& ret)
  {
    AUTOMATON_TYPES(res_t);

    std::set<typename lhs_t::hstate_t> lhs_states;
    std::set<typename rhs_t::hstate_t> rhs_states;

    composer<S, M1, M2, lhs_t, rhs_t, res_t>
      compose (ret.structure(), ret.structure().series().monoid(),
	       lhs, rhs, ret, lhs_states, rhs_states);
    compose ();
  }

  /// Unambiguous composition.
  /// Works with all type of weighted transducers.
  template <typename S, typename M1, typename M2, typename lhs_t,
	    typename rhs_t, typename res_t>
  void
  do_u_compose(const AutomataBase<S>&,
	       const algebra::FreeMonoidProduct<M1, M2>&,
	       const lhs_t& lhs,
	       const rhs_t& rhs,
	       res_t& ret)
  {
    AUTOMATON_TYPES(res_t);

    std::set<typename lhs_t::hstate_t> lhs_states;
    std::set<typename rhs_t::hstate_t> rhs_states;

    lhs_t lhs_cov = splitting::outsplitting(lhs, lhs_states);
    rhs_t rhs_cov = splitting::insplitting(rhs, rhs_states);

    composer<S, M1, M2, lhs_t, rhs_t, res_t>
      compose (ret.structure(), ret.structure().series().monoid(),
	       lhs_cov, rhs_cov, ret, lhs_states, rhs_states);
    compose ();

    eps_removal_here (ret);
    sub_automaton_here (ret, useful_states (ret));
  }



  // Compose dispatchers
  template <typename S, typename M1, typename M2, typename lhs_t,
	    typename rhs_t, typename res_t>
  void
  do_compose_dispatcher(const AutomataBase<S>&,
			const algebra::FreeMonoidProduct<M1, M2>&,
			SELECTOR(bool),
			const lhs_t& lhs,
			const rhs_t& rhs,
			res_t& ret)
  {
    do_compose (ret.structure(),
		ret.structure().series().monoid(),
		lhs, rhs, ret);
  }


  template <typename S, typename M1, typename M2, typename lhs_t,
	    typename rhs_t, typename res_t, typename weight_t>
  void
  do_compose_dispatcher(const AutomataBase<S>&,
			const algebra::FreeMonoidProduct<M1, M2>&,
			const weight_t&,
			const lhs_t& lhs,
			const rhs_t& rhs,
			res_t& ret)
  {
    do_u_compose (ret.structure(),
		  ret.structure().series().monoid(),
		  lhs, rhs, ret);
  }

  // Facade for compose

  template <typename S, typename T>
  void
  compose(const Element<S, T>& lhs,
	  const Element<S, T>& rhs,
	  Element<S, T>& ret)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    for_all_states (s, ret)
      ret.del_state (*s);

    do_compose_dispatcher (ret.structure(),
			   ret.structure().series().monoid(),
			   SELECT(semiring_elt_value_t),
			   lhs, rhs, ret);
  }



  template <typename S, typename T>
  Element<S, T>
  compose(const Element<S, T>& lhs,
	  const Element<S, T>& rhs)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    typedef algebra::FreeMonoidProduct<
    typename auto_t::series_set_t::monoid_t::first_monoid_t,
      typename auto_t::series_set_t::monoid_t::second_monoid_t>	res_monoid_t;

    typedef algebra::Series<typename auto_t::series_set_t::semiring_t,
      res_monoid_t>
      res_series_set_t;

    res_monoid_t monoid(lhs.structure().series().monoid().first_monoid(),
			rhs.structure().series().monoid().second_monoid());


    res_series_set_t series(lhs.structure().series().semiring(), monoid);

    Automata<series_set_t, kind_t> aut_set(series);

    Element< Automata<series_set_t, kind_t>, T> ret(aut_set);
    do_compose_dispatcher(ret.structure(),
			  ret.structure().series().monoid(),
			  SELECT(semiring_elt_value_t),
			  lhs, rhs, ret);
    return ret;
  }


  // Facade for unambiguous composition
  template <typename S, typename T>
  void
  u_compose(const Element<S, T>& lhs,
	    const Element<S, T>& rhs,
	    Element<S, T>& ret)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    for_all_states (s, ret)
      ret.del_state (*s);

    do_u_compose (ret.structure(),
		  ret.structure().series().monoid(),
		  lhs, rhs, ret);
  }

  template <typename S, typename T>
  Element<S, T>
  u_compose(const Element<S, T>& lhs,
	    const Element<S, T>& rhs)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    typedef algebra::FreeMonoidProduct<
    typename auto_t::series_set_t::monoid_t::first_monoid_t,
      typename auto_t::series_set_t::monoid_t::second_monoid_t>	res_monoid_t;

    typedef algebra::Series<typename auto_t::series_set_t::semiring_t,
      res_monoid_t>
      res_series_set_t;

    res_monoid_t monoid(lhs.structure().series().monoid().first_monoid(),
			rhs.structure().series().monoid().second_monoid());


    res_series_set_t series(lhs.structure().series().semiring(), monoid);

    Automata<series_set_t, kind_t> aut_set(series);

    Element< Automata<series_set_t, kind_t>, T> ret(aut_set);
    do_u_compose(ret.structure(),
		 ret.structure().series().monoid(),
		 lhs, rhs, ret);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HXX
