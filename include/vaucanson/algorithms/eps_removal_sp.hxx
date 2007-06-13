// eps_removal.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EPS_REMOVAL_SP_HXX
# define VCSN_ALGORITHMS_EPS_REMOVAL_SP_HXX

# include <vaucanson/algorithms/eps_removal.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <boost/multi_index_container.hpp>
# include <boost/multi_index/member.hpp>
# include <boost/multi_index/hashed_index.hpp>
# include <boost/multi_index/composite_key.hpp>
# include <boost/functional/hash/hash.hpp>
# include <boost/tuple/tuple.hpp>
# include <vector>
# include <queue>
# include <map>
# include <utility>
# include <set>

namespace vcsn {

  /*----------------------------------------.
  | EpsilonRemoverSp for weighted automaton |
  `----------------------------------------*/

  template
  <class A_, typename Auto, typename Weight>
  class EpsilonRemoverSp
  {
    AUTOMATON_TYPES(Auto);
  public:
    struct s_shortest
    {
      s_shortest(const hstate_t src_, const hstate_t dst_, semiring_elt_t& d_, semiring_elt_t& r_)
	: src(src_),
	  dst(dst_),
	  dist(d_),
	  rel(r_)
      {}

      const hstate_t src;
      const hstate_t dst;
      semiring_elt_t dist;
      semiring_elt_t rel;
    };

    struct change_rel
    {
      change_rel(const semiring_elt_t& new_rel)
	: new_rel(new_rel)
      {}

      void operator() (s_shortest& s)
      {
	s.rel = new_rel;
      }
      private:
      semiring_elt_t new_rel;
    };

    struct change_dist
    {
      change_dist(const semiring_elt_t& new_dist)
	: new_dist(new_dist)
      {}

      void operator() (s_shortest& s)
      {
	s.dist = new_dist;
      }
      private:
      semiring_elt_t new_dist;
    };

    struct add_dr
    {
      add_dr(const semiring_elt_t& new_dist, const semiring_elt_t& new_rel)
	: new_dist(new_dist),
	  new_rel(new_rel)
      {}

      void operator() (s_shortest& s)
      {
	s.dist += new_dist;
	s.rel += new_rel;
      }
      private:
      semiring_elt_t new_dist;
      semiring_elt_t new_rel;
    };

    typedef boost::multi_index_container
    <
      s_shortest,
      boost::multi_index::indexed_by
      <
	boost::multi_index::hashed_unique
	<
	  boost::multi_index::composite_key
	  <
	    s_shortest,
	    BOOST_MULTI_INDEX_MEMBER(s_shortest, const hstate_t, src),
	    BOOST_MULTI_INDEX_MEMBER(s_shortest, const hstate_t, dst)
	  >
	>
      >
    > s_shortest_hash;

    EpsilonRemoverSp(const AutomataBase<A_>&,
		     Auto& aut)
      : a(aut),
	null_series(aut.series().zero_),
	semiring_elt_zero(aut.series().semiring().wzero_),
	semiring_elt_one(aut.series().semiring().wone_),
	monoid_identity(aut.series().monoid().vcsn_empty)
    {
      shortest_eps_distance();
    }

    void operator() (misc::direction_type dir)
    {
      if (dir == misc::backward)
	backward_remove();
      else
	forward_remove();
    }

  private:
    void shortest_eps_distance()
    {
      for_all_states(s, a)
      {
	typename s_shortest_hash::iterator it;
	shortest_hash.insert(s_shortest(*s, *s, semiring_elt_one, semiring_elt_one));
	squeue.insert(*s);
	while (!squeue.empty())
	{
	  hstate_t curr = *squeue.begin();
	  squeue.erase(squeue.begin());
	  semiring_elt_t R = semiring_elt_zero;
	  it = shortest_hash.find(boost::make_tuple(*s, curr));
	  if (it != shortest_hash.end())
	  {
	    R = it->rel;
	    shortest_hash.modify(it, change_rel(semiring_elt_zero));
	  }

	  std::list<htransition_t> transition_list;
	  a.spontaneous_deltac(transition_list, curr, delta_kind::transitions());
	  for_all_const_(std::list<htransition_t>, e, transition_list)
	  {
	    semiring_elt_t dist = semiring_elt_zero;
	    it = shortest_hash.find(boost::make_tuple(*s, a.dst_of(*e)));
	    if (it != shortest_hash.end())
	      dist = it->dist;
	    semiring_elt_t we = a.series_of(*e).get(monoid_identity);
	    we = R * we;
	    if (dist != dist +  we)
	      if (it != shortest_hash.end())
	      {
		shortest_hash.modify(it, add_dr(we, we));
		squeue.insert(a.dst_of(*e));
	      }
	      else
	      {
		shortest_hash.insert(s_shortest(*s, a.dst_of(*e), we, we));
		squeue.insert(a.dst_of(*e));
	      }
	  }
	 //it = shortest_hash.find(boost::make_tuple(*s, *s));
	 //result_not_computable_if(!it->rel.starable());
	}
      }
    }

    void backward_remove()
    {
      // Backward_eps_removal
      // Initialize the m_wfinal
      for_all_transitions(e,a)
      {
	series_set_elt_t t = a.series_of(*e);
	if (t.get(monoid_identity) != semiring_elt_zero)
	{
	  t.assoc(monoid_identity.value(), semiring_elt_zero.value()); // remove epsilon trans into t
	  if (t != null_series)
	    a.add_series_transition(a.src_of(*e), a.dst_of(*e), t);
	  a.del_transition(*e);
	}
      }
      std::map<hstate_t, series_set_elt_t>	state_to_wfinal;
      for_all_states(s, a)
	state_to_wfinal.insert(std::make_pair(*s, a.get_final(*s)));
      a.clear_final();

      // Compute the backward_eps_removal
      for_all_states(s, a)
      {
	std::list<htransition_t> transition_list;
	a.rdeltac(transition_list, *s, delta_kind::transitions());
	for_all_const_(std::list<htransition_t>, e, transition_list)
	{
	  series_set_elt_t t = a.series_of(*e);
	  for_all_states(s1, a)
	  {
	    typename s_shortest_hash::iterator it = shortest_hash.find(boost::make_tuple(*s1, a.src_of(*e)));
	    if (it != shortest_hash.end() && it->dist != semiring_elt_zero)
	      a.add_series_transition(*s1, *s, it->dist * t);
	  }
	  a.del_transition(*e);
	}
	series_set_elt_t tw = null_series;
	for_all_states(s1, a)
	{
	  typename s_shortest_hash::iterator it = shortest_hash.find(boost::make_tuple(*s, *s1));
	  if (it != shortest_hash.end())
	    tw += it->dist * state_to_wfinal.find(*s1)->second;
	}
	if (tw != null_series)
	  a.set_final(*s, tw);
      }
    }

    void forward_remove()
    {
      // Forward eps_removal
      // Initialize the m_wfinal
      for_all_transitions(e,a)
      {
	series_set_elt_t t = a.series_of(*e);
	if (t.get(monoid_identity) != semiring_elt_zero)
	{
	  t.assoc(monoid_identity.value(), semiring_elt_zero.value()); // remove epsilon trans into t
	  if (t != null_series)
	    a.add_series_transition(a.src_of(*e), a.dst_of(*e), t);
	  a.del_transition(*e);
	}
      }
      std::map<hstate_t, series_set_elt_t>	state_to_winitial;
      for_all_states(s, a)
	state_to_winitial.insert(std::make_pair(*s, a.get_initial(*s)));
      a.clear_final();

      // Compute the forward_eps_removal
      for_all_states(s, a)
      {
	std::list<htransition_t> transition_list;
	a.deltac(transition_list, *s, delta_kind::transitions());
	for_all_const_(std::list<htransition_t>, e, transition_list)
	{
	  series_set_elt_t t = a.series_of(*e);
	  for_all_states(s1, a)
	  {
	    typename s_shortest_hash::iterator it = shortest_hash.find(boost::make_tuple(a.dst_of(*e), *s1));
	    if (it != shortest_hash.end() && it->dist != semiring_elt_zero)
	      a.add_series_transition(*s, *s1, it->dist * t);
	  }
	  a.del_transition(*e);
	}
	series_set_elt_t tw = null_series;
	for_all_states(s1, a)
	{
	  typename s_shortest_hash::iterator it = shortest_hash.find(boost::make_tuple(*s1, *s));
	  if (it != shortest_hash.end())
	    tw += it->dist * state_to_winitial.find(*s1)->second;
	}
	if (tw != null_series)
	  a.set_initial(*s, tw);
      }
    }

    automaton_t&	a;

    // zero and identity of used algebraic structure.
    series_set_elt_t	null_series;
    semiring_elt_t	semiring_elt_zero;
    semiring_elt_t	semiring_elt_one;
    monoid_elt_t	monoid_identity;

    // Shortest distance structures
    s_shortest_hash	shortest_hash;
    std::set<hstate_t>	squeue;
  };

  /*--------------.
  | eps_removal.  |
  `--------------*/

  template<class A_, typename Auto, typename Weight>
  void
  do_eps_removal_here_sp(const AutomataBase<A_>& a_set,
		      const Weight&,
		      Auto& a,
		      misc::direction_type dir)
  {
    TIMER_SCOPED("eps_removal");

    EpsilonRemoverSp<A_, Auto, Weight> algo(a_set, a);
    algo(dir);
  }

  template<typename  A, typename  T>
  void
  eps_removal_here_sp(Element<A, T>& a, misc::direction_type dir)
  {
    typedef Element<A, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    do_eps_removal_here(a.structure(),
			SELECT(semiring_elt_value_t),
			a, dir);
  }

  template<typename  A, typename  T>
  Element<A, T>
  eps_removal_sp(const Element<A, T>& a, misc::direction_type dir)
  {
    typedef Element<A, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    Element<A, T> ret(a);
    do_eps_removal_here(ret.structure(),
			SELECT(semiring_elt_value_t),
			ret, dir);
    return ret;
  }

  template<typename  A, typename  T>
  void
  backward_eps_removal_here_sp(Element<A, T>& a)
  {
    typedef Element<A, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    do_eps_removal_here(a.structure(),
			SELECT(semiring_elt_value_t),
			a, misc::backward);
  }

  template<typename  A, typename  T>
  Element<A, T>
  backward_eps_removal_sp(const Element<A, T>& a)
  {
    typedef Element<A, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    Element<A, T> ret(a);
    do_eps_removal_here(ret.structure(),
			SELECT(semiring_elt_value_t),
			ret, misc::backward);
    return ret;
  }

  template<typename  A, typename  T>
  void
  forward_eps_removal_here_sp(Element<A, T>& a)
  {
    typedef Element<A, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    do_eps_removal_here(a.structure(),
			SELECT(semiring_elt_value_t),
			a, misc::forward);
  }

  template<typename  A, typename  T>
  Element<A, T>
  forward_eps_removal_sp(const Element<A, T>& a)
  {
    typedef Element<A, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    Element<A, T> ret(a);
    do_eps_removal_here(ret.structure(),
			SELECT(semiring_elt_value_t),
			ret, misc::forward);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_EPS_REMOVAL_HXX
