// eps_removal_sp.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2008 The Vaucanson Group.
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
# include <list>
# include <queue>
# include <map>
# include <utility>
# include <set>
# include <stack>

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
    struct tr_t
    {
      tr_t(hstate_t src_, hstate_t dst_, series_set_elt_t series_)
	  : src(src_),
	    dst(dst_),
	    series(series_)
      {}

      hstate_t src;
      hstate_t dst;
      series_set_elt_t series;
    };

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
	monoid_identity(aut.series().monoid().VCSN_EMPTY_)
    {
      shortest_eps_distance();
    }

    void operator() (misc::direction_type dir)
    {
      // Remove epsilon-transitions
      for_all_transitions(e,a)
      {
	series_set_elt_t t = a.series_of(*e);
	if (t.get(monoid_identity) != semiring_elt_zero)
	{
	  t.assoc(monoid_identity.value(), semiring_elt_zero.value());
	  if (t != null_series)
	    a.add_series_transition(a.src_of(*e), a.dst_of(*e), t);
	  a.del_transition(*e);
	}
      }

      if (dir == misc::backward)
	backward_remove();
      else
	forward_remove();
    }

  private:
    void shortest_eps_distance()
    {
      for_all_const_states(s, a)
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

          for (delta_iterator e(a.value(), curr); ! e.done(); e.next())
            if (a.is_spontaneous(*e))
            {
              semiring_elt_t dist = semiring_elt_zero;
              it = shortest_hash.find(boost::make_tuple(*s, a.dst_of(*e)));
              if (it != shortest_hash.end())
                dist = it->dist;
              semiring_elt_t we = a.series_of(*e).get(monoid_identity);
              we = R * we;
              if (dist != dist +  we)
              {
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
            }
	}
      }
    }

    void backward_remove()
    {
      std::list<std::pair<htransition_t, semiring_elt_t> > tr_l;
      std::list<std::pair<hstate_t, semiring_elt_t> > fin_l;
      std::stack<tr_t> tr_st;
      std::stack<std::pair<hstate_t, series_set_elt_t> > fin_st;

      for_all_(s_shortest_hash, it, shortest_hash)
	if (it->src != it->dst)
	{
          for (delta_iterator e(a.value(), it->dst); ! e.done(); e.next())
	    tr_st.push(tr_t(it->src, a.dst_of(*e), it->dist * a.series_of(*e)));
	  if (a.is_final(it->dst))
	    fin_st.push(make_pair(it->src, it->dist * a.get_final(it->dst)));
	}
	else
	{
	  if (it->dist != semiring_elt_one)
	  {
            for (delta_iterator e(a.value(), it->dst); ! e.done(); e.next())
	      tr_l.push_front(std::pair<htransition_t, semiring_elt_t>(*e, it->dist)); // associate each e with it->dist
	    if (a.is_final(it->dst))
	      fin_l.push_front(std::pair<hstate_t, semiring_elt_t>(it->src, it->dist));// store what we need to multiply w(final(it->src)) by it->dist
	  }
	}

      for (typename std::list<std::pair<htransition_t, semiring_elt_t> >::iterator it = tr_l.begin();
	   it != tr_l.end(); ++it)
      {
	series_set_elt_t s = a.series_of(it->first) * it->second;
	if (s != null_series)
	  a.add_series_transition(a.src_of(it->first), a.dst_of(it->first), s);
	a.del_transition(it->first);
      }

      for (typename std::list<std::pair<hstate_t, semiring_elt_t> >::iterator it = fin_l.begin();
	   it != fin_l.end(); ++it)
	a.set_final(it->first, it->second * a.get_final(it->first));

      while (!tr_st.empty())
      {
	a.add_series_transition(tr_st.top().src, tr_st.top().dst, tr_st.top().series);
	tr_st.pop();
      }

      while (!fin_st.empty())
      {
	a.set_final(fin_st.top().first, a.get_final(fin_st.top().first) +
					     fin_st.top().second);
	fin_st.pop();
      }
    }

    void forward_remove()
    {
      std::list<std::pair<htransition_t, semiring_elt_t> > tr_l;
      std::list<std::pair<hstate_t, semiring_elt_t> > fin_l;
      std::stack<tr_t> tr_st;
      std::stack<std::pair<hstate_t, series_set_elt_t> > init_st;

      for_all_(s_shortest_hash, it, shortest_hash)
	if (it->src != it->dst)
	{
          for (rdelta_iterator e(a.value(), it->dst); ! e.done(); e.next())
            tr_st.push(tr_t(a.src_of(*e), it->dst, a.series_of(*e) * it->dist));
          if (a.is_initial(it->src))
            init_st.push(make_pair(it->dst, a.get_initial(it->src) * it->dist));
	}
	else
	{
	  if (it->dist != semiring_elt_one)
	  {
            for (rdelta_iterator e(a.value(), it->dst); ! e.done(); e.next())
	      tr_l.push_front(std::pair<htransition_t, semiring_elt_t>(*e, it->dist)); // associate each e with it->dist
	    if (a.is_initial(it->src))
	      fin_l.push_front(std::pair<hstate_t, semiring_elt_t>(it->dst, it->dist));// store what we need to multiply w(final(it->src)) by it->dist
	  }
	}

      for (typename std::list<std::pair<htransition_t, semiring_elt_t> >::iterator it = tr_l.begin();
	   it != tr_l.end(); ++it)
      {
	series_set_elt_t s = a.series_of(it->first) * it->second;
	if (s != null_series)
	  a.add_series_transition(a.src_of(it->first), a.dst_of(it->first), s);
	a.del_transition(it->first);
      }

      for (typename std::list<std::pair<hstate_t, semiring_elt_t> >::iterator it = fin_l.begin();
	   it != fin_l.end(); ++it)
	a.set_initial(it->first, it->second * a.get_initial(it->first));

      while (!tr_st.empty())
      {
	a.add_series_transition(tr_st.top().src, tr_st.top().dst, tr_st.top().series);
	tr_st.pop();
      }

      while (!init_st.empty())
      {
	a.set_initial(init_st.top().first, a.get_initial(init_st.top().first) +
					     init_st.top().second);
	init_st.pop();
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
    BENCH_TASK_SCOPED("eps_removal");

    EpsilonRemoverSp<A_, Auto, Weight> algo(a_set, a);
    algo(dir);
  }

  template<typename  A, typename AI>
  void
  eps_removal_here_sp(Element<A, AI>& a, misc::direction_type dir)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    do_eps_removal_here_sp(a.structure(),
			   SELECT(semiring_elt_value_t),
			   a, dir);
  }

  template<typename  A, typename AI>
  Element<A, AI>
  eps_removal_sp(const Element<A, AI>& a, misc::direction_type dir)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    automaton_t ret(a);
    do_eps_removal_here_sp(ret.structure(),
			   SELECT(semiring_elt_value_t),
			   ret, dir);
    return ret;
  }

  template<typename  A, typename AI>
  void
  backward_eps_removal_here_sp(Element<A, AI>& a)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    do_eps_removal_here_sp(a.structure(),
			   SELECT(semiring_elt_value_t),
			   a, misc::backward);
  }

  template<typename  A, typename AI>
  Element<A, AI>
  backward_eps_removal_sp(const Element<A, AI>& a)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    automaton_t ret(a);
    do_eps_removal_here_sp(ret.structure(),
			   SELECT(semiring_elt_value_t),
			   ret, misc::backward);
    return ret;
  }

  template<typename  A, typename AI>
  void
  forward_eps_removal_here_sp(Element<A, AI>& a)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    do_eps_removal_here_sp(a.structure(),
			   SELECT(semiring_elt_value_t),
			   a, misc::forward);
  }

  template<typename  A, typename AI>
  Element<A, AI>
  forward_eps_removal_sp(const Element<A, AI>& a)
  {
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    automaton_t ret(a);
    do_eps_removal_here_sp(ret.structure(),
			   SELECT(semiring_elt_value_t),
			   ret, misc::forward);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_EPS_REMOVAL_HXX
