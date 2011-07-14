// eps_removal.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2008, 2010, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EPS_REMOVAL_HXX
# define VCSN_ALGORITHMS_EPS_REMOVAL_HXX

# include <vaucanson/algorithms/eps_removal.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <list>
# include <map>
# include <utility>

namespace vcsn {

  // For automata.
  template <class A, typename M, typename AI>
  bool
  do_is_proper(const AutomataBase<A>&, const M&, const Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("is_proper (automaton)");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for_all_const_transitions(e, a)
      {
	// A transition labelled by "1+a" is not considered to be
	// spontaneous by is_spontaneous(), yet it cannot belong to a
	// proper automaton.
	series_set_elt_t label = a.series_of(*e);
	for_all_const_(series_set_elt_t::support_t, it, label.supp())
	  if ((*it).empty())
	    return false;
      }
    return true;
  }

  // For FMP.
  template <class A, typename F, typename S, typename AI>
  bool
  do_is_proper(const AutomataBase<A>&,
	       const algebra::FreeMonoidProduct<F, S>&,
	       const Element<A, AI>& a)
  {
    BENCH_TASK_SCOPED("is_proper (FMP)");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for_all_const_transitions(e, a)
      {
	series_set_elt_t label = a.series_of(*e);
	for_all_const_(series_set_elt_t::support_t, it, label.supp())
	  if ((*it).first.empty() && (*it).second.empty())
	    return false;
      }
    return true;
  }

  template <typename A, typename AI>
  bool
  is_proper(const Element<A, AI>& a)
  {
    return do_is_proper(a.structure(), a.series().monoid(), a);
  }


  // Forward declaration.
  template <class A_, typename Auto, typename Weight>
  class EpsilonRemover;

  template <class A_, typename Auto, typename Weight, int>
  struct test_for_non_positive_semiring
  {
    bool run(const Auto&) const
    {
      return true;
    }
  };

  template <class A_, typename Auto, typename Weight>
  struct test_for_non_positive_semiring<A_, Auto, Weight, 0>
  {
    bool run(const Auto& a) const; // See After the EpsilonRemover declaration.
  };

  /*--------------------------------------.
  | EpsilonRemover for weighted automaton |
  `--------------------------------------*/

  template <class A_, typename Auto, typename Weight>
  class EpsilonRemover
  {
    AUTOMATON_TYPES(Auto);
	typedef typename series_set_elt_t::support_t support_t;

    friend struct test_for_non_positive_semiring
    <A_, Auto, Weight, semiring_traits<semiring_t,
				       semiring_elt_value_t>::is_positive>;


    automaton_t&	a;
    // zero and identity of used algebraic structure.
    series_set_elt_t	null_series;
    semiring_elt_t	semiring_elt_zero,
      semiring_elt_unit;
    monoid_elt_t	monoid_identity;


  public:
    EpsilonRemover(const AutomataBase<A_>&,
		   Auto& aut)
      : a(aut),
	null_series(aut.series().zero_),
	semiring_elt_zero(aut.series().semiring().wzero_),
	semiring_elt_unit(aut.series().semiring().wone_),
	monoid_identity(aut.series().monoid().VCSN_EMPTY_)
    {}

    void operator()(misc::direction_type dir)
    {
      test_for_non_positive_semiring
	<A_, Auto, Weight, semiring_traits<semiring_t,
					   semiring_elt_value_t>::is_positive>
	nps;
      result_not_computable_if(!nps.run(a));

      std::list<hstate_t> eps_states;
       if (dir == misc::backward)
	this->epsilon_covering(eps_states);
      else
	this->epsilon_co_covering(eps_states);
      result_not_computable_if(!spontaneous_suppression(eps_states));
      merge_transitions();
    }

    private:

  	/* This method computes a covering of the automaton such
  	   that, in this covering, there are two kinds of states:
  	   -- states whose incoming transitions are not spontaneous;
  	   -- non initial states whose incoming transitions are spontaneous.
  	   The argument is filled with the states which belong to the second kind.
	*/
    void epsilon_covering(std::list<hstate_t>& spontaneous_states)
    {
      //list of states to split
      std::list<hstate_t> split_states;
      for_all_states(s, a)
	{
	  bool eps_in = false;
	  bool other_in = a.is_initial(*s);

	  // Test whether there are different types of incoming transitions.

	  std::list<htransition_t> transitions;
	  for (rdelta_iterator e(a.value(), *s); ! e.done(); e.next())
	    transitions.push_back(*e);
	  for_all_(std::list<htransition_t>, e, transitions)
	    {
	      series_set_elt_t t = a.series_of(*e);
	      semiring_elt_t eps_weight= t.get(monoid_identity);
	      if (eps_weight == semiring_elt_zero)
		other_in = true ;
	      else
		{
		  eps_in=true;
		  if (t.supp().size() > 1)
	  	    other_in = true;
		}
	    }
	  if (eps_in)
	    {
	      if (other_in)
		split_states.push_back(*s);
	      else
		spontaneous_states.push_back(*s);
	    }
	}
      //Split the states which have to
      for_all_(std::list<hstate_t>, s, split_states)
	{
	  hstate_t eps_state = a.add_state();
	  spontaneous_states.push_back(eps_state);
	  //incoming transitions (the original state remains initial if it is)
	  std::list<htransition_t> transitions;
	  for (rdelta_iterator e(a.value(), *s); ! e.done(); e.next())
	    transitions.push_back(*e);
	  for_all_(std::list<htransition_t>, e, transitions)
	    {
	      series_set_elt_t t = a.series_of(*e);
	      semiring_elt_t eps_weight= t.get(monoid_identity);
	      if (eps_weight == semiring_elt_zero)
		continue;
	      series_set_elt_t eps_label(a.structure().series());
	      eps_label.assoc(monoid_identity.value(), eps_weight.value());
	      //which remains on the transition without epsilon:
	      t.assoc(monoid_identity.value(), semiring_elt_zero.value());
	      hstate_t source=a.src_of(*e);
	      a.add_series_transition(source, eps_state, eps_label);
	      if (t != null_series)
	    	a.add_series_transition(source, *s, t);
	      a.del_transition(*e);
	    }
	  //outgoing transitions and final states
	  if (a.is_final(*s))
	    a.set_final(eps_state,a.get_final(*s));
	  for (delta_iterator e(a.value(), *s); ! e.done(); e.next())
	    a.add_series_transition(eps_state, a.dst_of(*e), a.series_of(*e));
	  /* Notice that if there is a loop on *s, with label a+1, the
	     step "incoming transitions" turns it into a loop with
	     label 'a' and a transition from *s to eps_state with
	     label 1, and the step "outgoing transitions" build a
	     transition from eps_state to *s with label '1' and a loop
	     on eps_state with label 1, which is what it is
	     expected */
	}
    }

    /* Initial and final cleaner. This method adds if necessary an
       initial and/or a final state such that series labelling initial
       and final arrows are constant. This method is presently unused.
    */
    void initial_final_cleaner()
    {
      {
	//Initial
	std::list<hstate_t> initial_states;
	for_all_initial_states(s, a)
	  initial_states.push_back(*s);
	hstate_t new_initial=a.add_state();
	for_all_(std::list<hstate_t>, s, initial_states)
	  {
	    series_set_elt_t t = a.get_initial(*s);
	    semiring_elt_t eps_weight= t.get(monoid_identity);
	    t.assoc(monoid_identity, semiring_elt_zero.value());
	    if (t != null_series)
	      {
		a.unset_initial(*s);
		a.add_series_transition(new_initial, *s, t);
		if (eps_weight != semiring_elt_zero)
		  {
		    series_set_elt_t cst(a.structure().series());
		    cst.assoc(monoid_identity, eps_weight.value());
		    a.set_initial(*s, cst);
		  }
	      }
	  }
	delta_iterator test(a.value(), new_initial);
	if (test.done())
	  a.del_state(new_initial);
	else
	  a.set_initial(new_initial);
      }
      {
	//Final
	std::list<hstate_t> final_states;
	for_all_final_states(s, a)
	  final_states.push_back(*s);
	hstate_t new_final=a.add_state();
	for_all_(std::list<hstate_t>, s, final_states)
	  {
	    series_set_elt_t t = a.get_final(*s);
	    semiring_elt_t eps_weight= t.get(monoid_identity);
	    t.assoc(monoid_identity, semiring_elt_zero.value());
	    if (t != null_series)
	      {
		a.unset_final(*s);
		a.add_series_transition(*s, new_final, t);
		if(eps_weight != semiring_elt_zero)
		  {
		    series_set_elt_t cst(a.structure().series());
		    cst.assoc(monoid_identity, eps_weight.value());
		    a.set_final(*s, cst);
		  }
	      }
	  }
	rdelta_iterator test(a.value(), new_final);
	if (test.done())
	  a.del_state(new_final);
	else
	  a.set_final(new_final);
      }
    }

    /* This method computes a co-covering of the automaton such
       that, in this co-covering, there are two kinds of states:
       -- states whose outgoing transitions are not spontaneous;
       -- non final states whose outgoing transitions are spontaneous.
       The argument is filled with the states which belong to the second kind.
    */
    void epsilon_co_covering(std::list<hstate_t>& spontaneous_states)
    {
      //list of states to split
      std::list<hstate_t> split_states;
      for_all_states(s, a)
	{
	  bool eps_out = false;
	  bool other_out = a.is_final(*s);

	  // Test whether there are different types of outgoing transitions.

	  std::list<htransition_t> transitions;
	  for (delta_iterator e(a.value(), *s); !e.done(); e.next())
	    transitions.push_back(*e);
	  for_all_(std::list<htransition_t>, e, transitions)
	    {
	      series_set_elt_t t = a.series_of(*e);
	      semiring_elt_t eps_weight= t.get(monoid_identity);
	      if(eps_weight == semiring_elt_zero)
		other_out=true ;
	      else
		{
		  eps_out=true;
		  if (t.supp().size() > 1)
	  	    other_out=true;
		}
	    }
	  if (eps_out)
	    {
	      if (other_out)
		split_states.push_back(*s);
	      else
		spontaneous_states.push_back(*s);
	    }
	}
      //Split the states which have to
      for_all_(std::list<hstate_t>, s, split_states)
	{
	  hstate_t eps_state = a.add_state();
	  spontaneous_states.push_back(eps_state);
	  //outgoing transitions (the original state remains final if it is)
	  std::list<htransition_t> transitions;
	  for (delta_iterator e(a.value(), *s); !e.done(); e.next())
	    transitions.push_back(*e);
	  for_all_(std::list<htransition_t>, e, transitions)
	    {
	      series_set_elt_t t = a.series_of(*e);
	      semiring_elt_t eps_weight= t.get(monoid_identity);
	      if (eps_weight == semiring_elt_zero)
		continue;
	      series_set_elt_t eps_label(a.structure().series());
	      eps_label.assoc(monoid_identity.value(), eps_weight.value());
	      //which remains on the transition without epsilon:
	      t.assoc(monoid_identity.value(), semiring_elt_zero.value());
	      hstate_t target=a.dst_of(*e);
	      a.add_series_transition(eps_state, target, eps_label);
	      if (t != null_series)
		a.add_series_transition(*s, target, t);
	      a.del_transition(*e);
	    }
	  //incoming transitions and initial states
	  if (a.is_initial(*s))
	    a.set_initial(eps_state,a.get_initial(*s));
	  for (rdelta_iterator e(a.value(), *s); ! e.done(); e.next())
	    a.add_series_transition(a.src_of(*e), eps_state, a.series_of(*e));
	  /* Notice that if there is a loop on *s, with label a+1, the
	     step "outgoing transitions" turns it into a loop with
	     label 'a' and a transition from eps_state to *s with
	     label 1, and the step "incoming transitions" build a
	     transition from *s to eps_state with label '1' and a loop
	     on eps_state with label 1, which is what it is
	     expected */
	}
    }

    /* This method computes an equivalent K-automaton with only
       positive transitions (excepted final arrows).  A second copy of
       the automaton is built, a negative weight makes switch from a
       copy to another.  Two final states are added, one where
       positive paths end, the other one where negative paths end. In
       the result, all the edges have positive weight; the two final
       states have resp.  weights equal to 1 and -1.
    */
    void positive_path_covering()
    {
      std::map<hstate_t,hstate_t> clones;
      std::list<hstate_t> states;
      for_all_states(s, a)
	states.push_back(*s);
      for_all_(std::list<hstate_t>, s, states)
	clones[*s]=a.add_state();
      hstate_t pos_final_state=a.add_state();
      hstate_t neg_final_state=a.add_state();
      std::list<htransition_t> transitions;
      for_all_transitions(e, a)
	transitions.push_back(*e);
      for_all_(std::list<htransition_t>, e, transitions)
	{
	  series_set_elt_t posit = a.series_of(*e);
	  series_set_elt_t negat(a.structure().series());
	  support_t su = posit.supp();
	  for_all_(support_t, x, su)
  	    {
	      semiring_elt_t weight=posit.get(*x);
	      if (weight < semiring_elt_zero)
  	    	{
  	    	  negat.assoc(*x,-weight.value());
  	    	  posit.assoc(*x,semiring_elt_zero.value());
  	    	}
  	    }
	  hstate_t src=a.src_of(*e), dst=a.dst_of(*e);
	  if (posit != null_series)
	    a.add_series_transition(clones[src], clones[dst], posit);
	  if (negat != null_series)
  	    {
	      a.add_series_transition(src, clones[dst], negat);
	      a.add_series_transition(clones[src], dst, negat);
	      if (posit != null_series)
		a.add_series_transition(src, dst, posit);
	      a.del_transition(*e);
  	    }
	}
      states.clear();
      for_all_initial_states(s, a)
	states.push_back(*s);
      for_all_(std::list<hstate_t>, s, states)
	{
	  series_set_elt_t posit = a.get_initial(*s);
	  series_set_elt_t negat(a.structure().series());
	  support_t su = posit.supp();
	  for_all_(support_t, x, su)
  	    {
	      semiring_elt_t weight = posit.get(*x);
	      if (weight < semiring_elt_zero)
  	    	{
  	    	  negat.assoc(*x,-weight.value());
  	    	  posit.assoc(*x,semiring_elt_zero.value());
  	    	}
  	    }
	  if (negat != null_series)
  	    {
	      a.set_initial(clones[*s], negat);
	      a.unset_initial(*s);
	      if (posit != null_series)
		a.set_initial(*s,posit);
  	    }
	}
      states.clear();
      for_all_final_states(s, a)
	states.push_back(*s);
      for_all_(std::list<hstate_t>, s, states)
	{
	  series_set_elt_t posit = a.get_final(*s);
	  series_set_elt_t negat(a.structure().series());
	  support_t su = posit.supp();
	  for_all_(support_t, x, su)
  	    {
	      semiring_elt_t weight=posit.get(*x);
	      if (weight < semiring_elt_zero)
  	    	{
  	    	  negat.assoc(*x,-weight.value());
  	    	  posit.assoc(*x,semiring_elt_zero.value());
  	    	}
  	    }
	  if (negat != null_series)
  	    {
	      a.add_series_transition(*s, neg_final_state, negat);
	      a.add_series_transition(clones[*s], pos_final_state, negat);
  	    }
	  a.unset_final(*s);
	  if (posit != null_series)
  	    {
	      a.add_series_transition(*s, pos_final_state, posit);
	      a.add_series_transition(clones[*s], neg_final_state, posit);
  	    }
	}
      a.set_final(pos_final_state);
      series_set_elt_t mss = a.get_final(pos_final_state);
      mss.assoc(monoid_identity,-semiring_elt_unit.value());
      a.set_final(neg_final_state,mss);
      accessible_here(a);
    }

    /*supression of "epsilon-states"
      epsilon_covering should have been called before
      This part of the algorithm is symmetrical and is exactly
      the "elimination state method" applicated to a list of states.
      We consider the case where the state is initial or final, even if
      in the backward case the 'epsilon state' cannot be initial for instance
     */
    bool spontaneous_suppression(std::list<hstate_t>& sp_states)
    {
      for_all_(std::list<hstate_t>, s, sp_states)
    	{
	  std::list<htransition_t> incoming_transitions;
	  //list of incoming transitions, beginning with loops
	  for (rdelta_iterator e(a.value(), *s); ! e.done(); e.next())
	    {
	      if (a.src_of(*e) == a.dst_of(*e))
		incoming_transitions.push_front(*e);
	      else
		incoming_transitions.push_back(*e);
	    }
	  bool hasloop=false;
	  series_set_elt_t loop_series(a.structure().series());
	  //loops are removed from incoming transitions;
	  while (!incoming_transitions.empty())
	    {
	      htransition_t& loop=incoming_transitions.front();
	      if(a.src_of(loop)==a.dst_of(loop))
		{
		  hasloop=true;
		  loop_series += a.series_of(loop);
		  incoming_transitions.pop_front();
		}
	      else
		break;
	    }
	  if (hasloop)
	    {
	      if (!loop_series.get(monoid_identity).starable())
		return false;
	      loop_series = loop_series.star();
	    }
	  std::list<htransition_t> outgoing_transitions;
	  for (delta_iterator e(a.value(), *s); ! e.done(); e.next())
	      if (a.src_of(*e)!=a.dst_of(*e))
		outgoing_transitions.push_back(*e);
	  for_all_(std::list<htransition_t>, e, incoming_transitions)
	    for_all_(std::list<htransition_t>, f, outgoing_transitions)
	      if (hasloop)
		a.add_series_transition(a.src_of(*e), a.dst_of(*f),
					a.series_of(*e)*loop_series*a.series_of(*f));
	      else
		a.add_series_transition(a.src_of(*e), a.dst_of(*f),
					a.series_of(*e)*a.series_of(*f));
	  if (a.is_final(*s))
	    {
	      series_set_elt_t final_s = a.get_final(*s);
	      for_all_(std::list<htransition_t>, e, incoming_transitions)
		{
		  hstate_t p = a.src_of(*e);
		  series_set_elt_t t = a.get_final(p);
		  if (hasloop)
		    t += a.series_of(*e)*loop_series*final_s;
		  else
		    t += a.series_of(*e)*final_s;
		  a.unset_final(p);
		  if (t != null_series)
		    a.set_final(p,t);
		}
	    }
	  if (a.is_initial(*s))
	    {
	      series_set_elt_t initial_s=a.get_initial(*s);
	      for_all_(std::list<htransition_t>, f, outgoing_transitions)
		{
		  hstate_t p = a.dst_of(*f);
		  series_set_elt_t t = a.get_initial(p);
		  if (hasloop)
		    t += initial_s*loop_series*a.series_of(*f);
		  else
		    t += initial_s*a.series_of(*f);
		  a.unset_initial(p);
		  if (t != null_series)
		    a.set_initial(p,t);
		}
	    }
	  a.del_state(*s);
    	}
      return true;
    }

    //merge transitions with the same ends
    void merge_transitions()
    {
      typedef std::map<hstate_t, series_set_elt_t> map_t;
      for_all_states(s, a)
	{
	  map_t map;
	  std::list<htransition_t> transitions;
	  for (delta_iterator e(a.value(), *s); ! e.done(); e.next())
	    {
	      hstate_t target = a.dst_of(*e);
	      transitions.push_back(*e);
	      typename map_t::iterator it = map.find(target);
	      if (it == map.end())
		map.insert(std::pair<hstate_t, series_set_elt_t>(target,
								 a.series_of(*e)));
	      else
		it->second += a.series_of(*e);
	    }
	  for_all_(std::list<htransition_t>, e, transitions)
	    a.del_transition(*e);
	  for_all_(map_t, it, map)
	    if(it->second != null_series)
		    a.add_series_transition(*s, it->first, it->second);
	}
    }

  };


  template <class A_, typename Auto, typename Weight>
  bool test_for_non_positive_semiring<A_, Auto, Weight, 0>::run(const Auto& a) const
  {
    AUTOMATON_TYPES(Auto);

    std::list<hstate_t> eps_states;
    automaton_t test(a);
    EpsilonRemover<A_, Auto, Weight> epsTest(test.structure(), test);
    epsTest.positive_path_covering();
    epsTest.epsilon_covering(eps_states);
    return epsTest.spontaneous_suppression(eps_states);
  }




  /*--------------.
    | eps_removal.  |
    `--------------*/

  template<class A_, typename Auto, typename Weight>
  void
  do_eps_removal_here(const AutomataBase<A_>& a_set,
		      const Weight&,
		      Auto& a,
		      misc::direction_type dir)
  {
    BENCH_TASK_SCOPED("eps_removal");
    AUTOMATON_TYPES(Auto);
    EpsilonRemover<A_, Auto, Weight> algo(a_set, a);
    algo(dir);
  }

  template<typename  A, typename  AI>
  void
  eps_removal_here(Element<A, AI>& a, misc::direction_type dir)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    do_eps_removal_here(a.structure(),
			SELECT(semiring_elt_value_t),
			a, dir);
  }

  template<typename  A, typename  AI>
  Element<A, AI>
  eps_removal(const Element<A, AI>& a, misc::direction_type dir)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    automaton_t ret(a);
    do_eps_removal_here(ret.structure(),
			SELECT(semiring_elt_value_t),
			ret, dir);
    return ret;
  }

  template<typename  A, typename  AI>
  void
  backward_eps_removal_here(Element<A, AI>& a)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    do_eps_removal_here(a.structure(),
			SELECT(semiring_elt_value_t),
			a, misc::backward);
  }

  template<typename  A, typename  AI>
  Element<A, AI>
  backward_eps_removal(const Element<A, AI>& a)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    automaton_t ret(a);
    do_eps_removal_here(ret.structure(),
			SELECT(semiring_elt_value_t),
			ret, misc::backward);
    return ret;
  }

  template<typename  A, typename  AI>
  void
  forward_eps_removal_here(Element<A, AI>& a)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    do_eps_removal_here(a.structure(),
			SELECT(semiring_elt_value_t),
			a, misc::forward);
  }

  template<typename  A, typename  AI>
  Element<A, AI>
  forward_eps_removal(const Element<A, AI>& a)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    automaton_t ret(a);
    do_eps_removal_here(ret.structure(),
			SELECT(semiring_elt_value_t),
			ret, misc::forward);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_EPS_REMOVAL_HXX
