// union.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef ALGORITHMS_UNION_HXX
# define ALGORITHMS_UNION_HXX

# include <set>
# include <map>
# include <vaucanson/algorithms/union.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/history.hh>

namespace vcsn {

  // FIXME : this should be defined differently :
  # define INUNION_EVENT	"in place union "

  /*------.
  | union |
  `------*/

  template <typename A, typename lhs_t, typename rhs_t>
  void auto_do_union(const AutomataBase<A>&,
		     lhs_t& lhs,
		     const rhs_t& rhs)
  {
    /*----------------.
    | Union of states |
    `----------------*/
    std::map<hstate_t, hstate_t> states_map;

    for (typename rhs_t::state_iterator i = rhs.states().begin();
	 i != rhs.states().end();
	 ++i)
      {
	hstate_t new_state = lhs.add_state();
	states_map[*i] = new_state;

	//	lhs.history().set_state_event_about(INUNION_EVENT, new_state, *i);

	lhs.set_final(new_state, rhs.get_final(*i));
	lhs.set_initial(new_state, rhs.get_initial(*i));
      }

    /*---------------.
    | Union of edges |
    `---------------*/

    typedef std::set<hedge_t> aim_t;
    aim_t aim;

    for (typename rhs_t::state_iterator i = rhs.states().begin();
	 i != rhs.states().end();
	 ++i)
      {
	aim.clear();
	rhs.deltac(aim, *i, delta_kind::edges());
	for (typename aim_t::const_iterator d = aim.begin();
	     d != aim.end();
	     ++d)
	  {
	      lhs.add_edge(states_map[rhs.origin_of(*d)],
			   states_map[rhs.aim_of(*d)],
			   rhs.label_of(*d));

	    //  lhs.history().set_edge_event_about(INUNION_EVENT, new_edge, *d);
	  }
      }
  }

  // wrappers
  template<typename A, typename T, typename U>
  void auto_in_union(Element<A, T>& lhs, const Element<A, U>& rhs)
  {
    // assert (lhs.set() == rhs.set())
    auto_do_union(lhs.set(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T> 
  auto_union(const Element<A, T>& lhs, const Element<A, U>& rhs)
  {
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(lhs);
    ret.emancipate();
    //    ret.history().set_auto_event_about(INUNION_EVENT, lhs, rhs);
    auto_do_union(ret.set(), ret, rhs);
    return ret;
  }

} // vcsn

#endif // ALGO_UNION_HXX
