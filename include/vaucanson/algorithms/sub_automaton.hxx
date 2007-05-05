// sub_automaton.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_SUB_AUTOMATON_HXX
# define VCSN_ALGORITHMS_SUB_AUTOMATON_HXX

# include <vaucanson/algorithms/sub_automaton.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <list>

namespace vcsn {

  /*----------------------------------------.
  | SubAutomaton defined by a set of states |
  `----------------------------------------*/

  template<typename A, typename auto_t, typename list_t>
  void do_sub_automaton_here(const AutomataBase<A>&,
			     auto_t& a,
			     const list_t& selected,
			     bool check_states)
  {
    TIMER_SCOPED("sub_automaton");
    std::list<typename auto_t::hstate_t> to_be_removed;
    for (typename auto_t::state_iterator i = a.states().begin();
	 i != a.states().end(); ++i)
      if (std::find(selected.begin(), selected.end(), *i) == selected.end())
	to_be_removed.push_back(*i);

    for_all_const_(std::list<typename auto_t::hstate_t>, i, to_be_removed)
      if (!check_states
	  || a.has_state(*i))
	a.del_state(*i);
  }


  // wrapper:
  template<typename A, typename T, typename StatesSet>
  Element<A, T>
  sub_automaton(const Element<A, T>& a, const StatesSet& s, bool check_states)
  {
    Element<A, T> ret(a);
    do_sub_automaton_here(ret.structure(), ret, s, check_states);
    return ret;
  }

  template<typename A, typename T, typename StatesSet>
  void sub_automaton_here(Element<A, T>& a, const StatesSet& s, bool check_states)
  {
    do_sub_automaton_here(a.structure(), a, s, check_states);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_SUB_AUTOMATON_HXX
