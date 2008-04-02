// concatenate.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_CONCATENATE_HXX
# define VCSN_ALGORITHMS_CONCATENATE_HXX

# include <vaucanson/algorithms/concatenate.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <map>

namespace vcsn {

  template <typename A, typename AI>
  void
  do_auto_in_concat(const AutomataBase<A>&	,
		    Element<A, AI>&		lhs,
		    const Element<A, AI>&	rhs)
  {
    TIMER_SCOPED("concatentate");
    typedef Element<A, AI>		automaton_t;
    AUTOMATON_TYPES(automaton_t);
    std::map<hstate_t, hstate_t>	trans;

    for_all_const_states(s, rhs)
    {
      hstate_t ns = lhs.add_state();
      trans[*s] = ns;
      if (rhs.is_initial(*s))
	for_all_const_final_states(f, lhs)
	  lhs.add_series_transition(*f, ns,
				    lhs.get_final(*f) * rhs.get_initial(*s));
    }
    for_all_const_transitions(e, rhs)
      lhs.add_transition(trans[rhs.src_of(*e)],
			 trans[rhs.dst_of(*e)],
			 rhs.label_of(*e));
    lhs.clear_final();
    for_all_const_final_states(f, rhs)
      lhs.set_final(trans[*f], rhs.get_final(*f));
  }


  template <typename A, typename AI>
  Element<A, AI>
  concatenate(const Element<A, AI>& lhs, const Element<A, AI>& rhs)
  {
    Element<A, AI> ret(lhs);
    do_auto_in_concat(ret.structure(), ret, rhs);
    return ret;
  }

  template <typename A, typename AI>
  void
  concatenate_here(Element<A, AI>& lhs, const Element<A, AI>& rhs)
  {
    do_auto_in_concat(lhs.structure(), lhs, rhs);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_CONCATENATE_HXX
