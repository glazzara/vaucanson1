// forward_realtime.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_FORWARD_REALTIME_HXX
# define VCSN_ALGORITHMS_FORWARD_REALTIME_HXX

# include <algorithm>
# include <set>
# include <queue>
# include <vaucanson/algorithms/forward_realtime.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algorithms/forward_closure.hh>
# include <vaucanson/algorithms/accessible.hh>

namespace vcsn {

  template <class A_, typename Auto_>
  void
  do_forward_realtime_here(const AutomataBase<A_>&,
		 Auto_&			 a)
  {
    typedef Auto_				automaton_t;
    AUTOMATON_TYPES(automaton_t);
    typedef std::set<hedge_t>		    	delta_ret_t;
    typedef std::deque<hedge_t>	     		queue_t;

    queue_t		  to_del, origin_d;
    delta_ret_t		  aim_d;
    monoid_elt_t	  monoid_identity =
      algebra::identity_as<monoid_elt_value_t>::of(a.set().series().monoid());
    semiring_elt_t		  semiring_zero =
      algebra::zero_as<semiring_elt_value_t>::of(a.set().series().semiring());
    series_elt_t          series_identity =
      algebra::identity_as<series_value_t>::of(a.set().series());

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

    accessible_here(a);
  }

  template<typename A, typename T>
  void
  forward_realtime_here(Element<A, T>& a)
  {
    do_forward_realtime_here(a.set(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  forward_realtime(const Element<A, T>& a)
  {
    Element<A, T> ret(a);
    do_forward_realtime_here(ret.set(), ret);
    return ret;
  }  

} // vcsn

#endif // VCSN_ALGORITHMS_FORWARD_REALTIME_HXX
