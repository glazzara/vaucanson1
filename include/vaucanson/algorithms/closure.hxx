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


#ifndef ALGORITHMS_CLOSURE_HXX
# define ALGORITHMS_CLOSURE_HXX

# include <vaucanson/algorithms/closure.hh>

# include <algorithm>
# include <set>
# include <queue>
# include <utility>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>

namespace vcsn {

  /*-----------.
  | in_closure |
  `-----------*/
  // preconditions :
  //
  // note : this a particularily dummy closure. to be optimized.
  template <class A_, typename Auto_>
  void
  do_in_closure(const AutomataBase<A_>& a_set,
		Auto_&			   a)
  {
    typedef Auto_						automaton_t;
    typedef typename automaton_t::series_t			series_t;
    typedef typename automaton_t::series_elt_t			series_elt_t;
    typedef typename series_elt_t::monoid_elt_t			monoid_elt_t;
    typedef typename series_t::monoid_t				monoid_t;
    typedef typename series_t::weights_t			weights_t;
    typedef typename series_elt_t::weight_t			weight_t;
    typedef std::set<hedge_t>					edelta_ret_t;
    typedef std::set<hstate_t>					sdelta_ret_t;
    typedef std::queue<std::pair<hstate_t, weight_t> >	queue_t;
    
    unsigned		  new_edge = 0;
    sdelta_ret_t	  known_succ;
    edelta_ret_t	  new_succ, succ, aim;
    queue_t		  queue;
    monoid_elt_t	  monoid_identity 
      = a.series().monoid().identity(SELECT(typename monoid_elt_t::value_t));
    series_elt_t          series_identity 
      = a.series().identity(SELECT(typename series_elt_t::value_t));
    weight_t		  weight_zero 
      = a.series().weights().zero(SELECT(typename weight_t::value_t));

    for (typename automaton_t::state_iterator i = a.states().begin();
	 i != a.states().end();
	 ++i)
      {
	known_succ.clear();
	succ.clear();
	// FIXME : use a new delta version here !
	a.letter_deltac(succ, *i, monoid_identity, delta_kind::edges());
	for (typename edelta_ret_t::const_iterator d = succ.begin();
	     d != succ.end();
	     ++d)
	  {
	    queue.push(std::make_pair(a.aim_of(*d), a.serie_of(*d).value_get(monoid_identity.value())));
	    known_succ.insert(a.aim_of(*d));
	  }
	
	while (!queue.empty())
	  {
	    hstate_t		c = queue.front().first;
	    weight_t		w = queue.front().second;
	    queue.pop();
	    new_edge = 0;
	    aim.clear();
	    a.letter_deltac(aim, c, monoid_identity, delta_kind::edges());
	    for (typename edelta_ret_t::const_iterator e = aim.begin();
		 e != aim.end();
		 ++e)
	      {
		series_elt_t s =  a.serie_of(*e);
		weight_t w_  = s.get(monoid_identity);
		if ((w_ != weight_zero) && 
		    (known_succ.find(a.aim_of(*e)) == known_succ.end()))
		  {
		    weight_t w__ = w * w_;
		    queue.push(std::make_pair(a.aim_of(*e), w__));
		    known_succ.insert(a.aim_of(*e));
		    a.add_serie_edge(*i, a.aim_of(*e), series_elt_t(w__));
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

#endif // ALGORITHMS_CLOSURE_HXX
