// closure.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_CLOSURE_HXX
# define VCSN_ALGORITHMS_CLOSURE_HXX

# include <vaucanson/algorithms/closure.hh>

# include <algorithm>
# include <set>
# include <queue>
# include <utility>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  /*-----------.
  | in_closure |
  `-----------*/
  template <class A_, typename Auto_>
  void
  do_in_closure(const AutomataBase<A_>& a_set,
		Auto_&			   a)
  {
    AUTOMATON_TYPES(Auto_);
    typedef std::set<hedge_t>					edelta_ret_t;
    typedef std::set<hstate_t>					sdelta_ret_t;
    typedef std::queue<std::pair<hstate_t, weight_t> >		queue_t;
    
    unsigned		  new_edge = 0;
    sdelta_ret_t	  known_succ;
    edelta_ret_t	  new_succ, succ, aim;
    queue_t		  queue;
    monoid_elt_t	  monoid_identity = a.series().monoid().empty_;
    weight_t		  weight_zero = a.series().weights().wzero_;

    for_each_state(i, a)
      {
	known_succ.clear();
	succ.clear();
	// get every spontaneous transition.
	a.letter_deltac(succ, *i, monoid_identity, delta_kind::edges());
	// and insert next states into the queue.
	for_each_const_(edelta_ret_t, d, succ)
	  {
	    queue.push(std::make_pair
		       (a.aim_of(*d), 
			a.serie_of(*d).value_get(monoid_identity.value())));
	    known_succ.insert(a.aim_of(*d));
	  }
	
	while (!queue.empty())
	  {
	    hstate_t		c = queue.front().first;
	    weight_t		w = queue.front().second;
	    queue.pop();
	    new_edge = 0;
	    aim.clear();
	    // get every spontaneous transition.
	    a.letter_deltac(aim, c, monoid_identity, delta_kind::edges());
	    for_each_const_(edelta_ret_t, e, aim)
	      {
		series_elt_t s   = a.serie_of(*e);
		weight_t     w_  = s.get(monoid_identity);
		hstate_t     ns  = a.aim_of(*e);
		// we must create a new edge between A and C when
		// there is two subsequent epsilon transitions between
		// A and B and between B and C.
		if ((w_ != weight_zero) && 
		    (known_succ.find(ns) == known_succ.end()))
		  {
		    weight_t w__ = w * w_;
		    queue.push(std::make_pair(ns, w__));
		    known_succ.insert(ns);
		    a.add_serie_edge(*i, ns, series_elt_t(w__));
		  }
	      }
	  }
      }
  }

  template<typename A, typename T>
  void
  in_closure(Element<A, T>& a)
  {
    do_in_closure(a.set(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  closure(const Element<A, T>& a)
  {
    Element<A, T> ret(a);

    ret.emancipate();
    do_in_closure(ret.set(), ret);
    return ret;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_CLOSURE_HXX
