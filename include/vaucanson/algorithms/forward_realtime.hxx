// forward_realtime.hxx: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_FORWARD_REALTIME_HXX
# define VCSN_ALGORITHMS_FORWARD_REALTIME_HXX

# include <vaucanson/algorithms/backward_realtime.hh>
# include <vaucanson/algorithms/forward_realtime.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/closure.hh>
# include <vaucanson/algorithms/accessible.hh>

# include <deque>
# include <set>

namespace vcsn {

  template <class A_, typename Auto_>
  void
  do_forward_realtime_here(const AutomataBase<A_>&,
			   Auto_& a)
  {
    typedef Auto_				automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef std::set<hedge_t>		    	delta_ret_t;
    typedef std::deque<hedge_t>	     		queue_t;

    queue_t		  to_del, origin_d;
    delta_ret_t		  aim_d;
    monoid_elt_t	  monoid_identity =
      algebra::identity_as<monoid_elt_value_t>::
      of(a.structure().series().monoid());
    semiring_elt_t		  semiring_zero =
      algebra::zero_as<semiring_elt_value_t>::
      of(a.structure().series().semiring());
    series_set_elt_t          series_identity =
      algebra::identity_as<series_set_elt_value_t>::of(a.structure().series());

    forward_closure_here(a);

    for_each_state(origin, a)
      {
	std::insert_iterator<queue_t> origin_i(origin_d, origin_d.begin());
	a.delta(origin_i, *origin, delta_kind::edges());

	while (!origin_d.empty())
	  {
	    hedge_t d_o = origin_d.front();
	    origin_d.pop_front();
	    if (a.series_of(d_o).get(monoid_identity) != semiring_zero)
	      {
		aim_d.clear();
		a.deltac(aim_d, a.aim_of(d_o), delta_kind::edges());
		for (typename delta_ret_t::const_iterator d = aim_d.begin();
		     d != aim_d.end();
		     ++d)
		  if (a.series_of(*d).get(monoid_identity) == semiring_zero)
		    {
		      bool new_edge = true;
		      for (typename queue_t::const_iterator d__o =
			     origin_d.begin();
			   d__o != origin_d.end();
			   ++d__o)
			if ((a.aim_of(*d__o) == a.aim_of(*d) &&
			     (a.label_of(*d__o) == a.label_of(*d))))
			  {
			    new_edge = false;
			    break;
			  }

		      if (new_edge)
			{
			  hedge_t new_hedge = a.add_series_edge
			    (*origin,
			     a.aim_of(*d),
			     a.series_of(d_o) * a.series_of(*d));
			  origin_d.push_back(new_hedge);
			}
		    }
		if (a.is_final(a.aim_of(d_o)))
		  a.set_final(*origin);
	      }
	  }
      }

    for (typename automaton_t::edge_iterator e = a.edges().begin();
	 e != a.edges().end();
	 ++e)
      if (a.series_of(*e).get(monoid_identity) != semiring_zero)
	to_del.push_back(*e);

    while (!to_del.empty())
      {
	hedge_t e = to_del.front();
	to_del.pop_front();
	a.del_edge(e);
      }
   
    coaccessible_here(a);

    realtime_words_here(a);
  }

  template<typename A, typename T>
  void
  forward_realtime_here(Element<A, T>& a)
  {
    do_forward_realtime_here(a.structure(), a);
  }

  template<typename A_, typename Auto_>
  Auto_
  do_forward_realtime(const AutomataBase<A_>&, const Auto_& a)
  {
    Auto_ ret(a);
    do_forward_realtime_here(ret.structure(), ret);
    return ret;
  }


  template<typename A, typename T>
  Element<A, T>
  forward_realtime(const Element<A, T>& a)
  {
    return do_forward_realtime(a.structure(), a);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_FORWARD_REALTIME_HXX
