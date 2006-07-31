// sum.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_SUM_HXX
# define VCSN_ALGORITHMS_SUM_HXX

# include <vaucanson/algorithms/sum.hh>

# include <vaucanson/automata/concept/automata_base.hh>

# include <set>
# include <map>

namespace vcsn {

  // FIXME : this should be defined differently :
# define INSUM_EVENT	"in place sum "

  /*------.
  |  sum  |
  `------*/

  template <typename A, typename lhs_t, typename rhs_t>
  void do_sum(const AutomataBase<A>& ,
	      lhs_t& lhs,
	      const rhs_t& rhs)
  {
    /*--------------.
    | Sum of states |
    `--------------*/
    std::map<hstate_t, hstate_t> states_map;

    for (typename rhs_t::state_iterator i = rhs.states().begin();
	 i != rhs.states().end();
	 ++i)
    {
      hstate_t new_state = lhs.add_state();
      states_map[*i] = new_state;

      //  lhs.history().set_state_event_about(INSUM_EVENT, new_state, *i);

      lhs.set_final(new_state, rhs.get_final(*i));
      lhs.set_initial(new_state, rhs.get_initial(*i));
    }

    /*---------------------.
    | Sum of transitions.  |
    `---------------------*/

    typedef std::set<htransition_t> dst_t;
    dst_t dst;

    for (typename rhs_t::state_iterator i = rhs.states().begin();
	 i != rhs.states().end();
	 ++i)
    {
      dst.clear();
      rhs.deltac(dst, *i, delta_kind::transitions());
      for (typename dst_t::const_iterator d = dst.begin();
	   d != dst.end();
	   ++d)
      {
	lhs.add_transition(states_map[rhs.src_of(*d)],
			   states_map[rhs.dst_of(*d)],
			   rhs.label_of(*d));

	//  lhs.history().set_transition_event_about(INSUM_EVENT,
	//					     new_transition, *d);
      }
    }
  }

  // wrappers
  template<typename A, typename T, typename U>
  void sum_here(Element<A, T>& lhs, const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    do_sum(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T>
  sum(const Element<A, T>& lhs, const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    Element<A, T> ret(lhs);
    //	  ret.history().set_auto_event_about(INSUM_EVENT, lhs, rhs);
    do_sum(ret.structure(), ret, rhs);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_SUM_HXX
