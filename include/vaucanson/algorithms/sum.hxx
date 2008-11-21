// sum.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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

  template <typename A, typename AI1, typename AI2>
  void
  do_sum(const AutomataBase<A>&, Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    typedef Element<A, AI1> lhs_t;
    typedef Element<A, AI2> rhs_t;
    typedef typename rhs_t::state_iterator state_iterator;

    /*--------------.
    | Sum of states |
    `--------------*/
    std::map<typename rhs_t::hstate_t, typename lhs_t::hstate_t> states_map;

    for_all_const_states(i, rhs)
    {
      typename lhs_t::hstate_t new_state = lhs.add_state();
      states_map[*i] = new_state;

      //  lhs.history().set_state_event_about(INSUM_EVENT, new_state, *i);

      lhs.set_final(new_state, rhs.get_final(*i));
      lhs.set_initial(new_state, rhs.get_initial(*i));
    }

    /*---------------------.
    | Sum of transitions.  |
    `---------------------*/

    for_all_const_states(i, rhs)
    {
      for (typename rhs_t::delta_iterator d(rhs.value(), *i);
           ! d.done();
           d.next())
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
  template<typename A, typename AI1, typename AI2>
  void
  sum_here(Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    do_sum(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename AI1, typename AI2>
  Element<A, AI1>
  sum(const Element<A, AI1>& lhs, const Element<A, AI2>& rhs)
  {
    Element<A, AI1> ret(lhs);
    //	  ret.history().set_auto_event_about(INSUM_EVENT, lhs, rhs);
    do_sum(ret.structure(), ret, rhs);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_SUM_HXX
