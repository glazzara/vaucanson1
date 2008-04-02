// complete.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_COMPLETE_HXX
# define VCSN_ALGORITHMS_COMPLETE_HXX

# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/realtime.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <list>
# include <set>

namespace vcsn {

  /*--------------.
  | complete_here |
  `--------------*/

  template <typename A, typename AI>
  void
  complete_here(Element<A, AI>& work)
  {
    precondition(is_realtime(work));
    TIMER_SCOPED("complete");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    hstate_t sink_state;
    bool sink_added = false;
    std::list<hstate_t> dst;

    for_all_const_states(s, work)
      for_all_const_letters(l, work.structure().series().monoid().alphabet())
      {
	dst.clear();
	work.letter_deltac(dst, *s, *l, delta_kind::states());
	if (dst.size() == 0)
	{
	  if (not sink_added)
	  {
	    sink_state = work.add_state();
	    sink_added = true;
	  }
	  work.add_letter_transition(*s, sink_state, *l);
	}
      }

    if (work.states().size() ==  0)
    {
      sink_state = work.add_state();
      sink_added = true;
      work.set_initial(sink_state);
    }

    if (sink_added)
      for_all_const_letters(l, work.structure().series().monoid().alphabet())
	work.add_letter_transition(sink_state, sink_state, *l);
  }

  /*---------.
  | complete |
  `---------*/

  template <typename A, typename AI>
  Element<A, AI>
  complete(const Element<A, AI>& e)
  {
    Element<A, AI> res(e);
    complete_here(res);
    return res;
  }

  /*------------.
  | is_complete |
  `------------*/

  template <typename A, typename AI>
  bool
  is_complete(const Element<A, AI>& e)
  {
    precondition(is_realtime(e));
    TIMER_SCOPED("is_complete");
    if (e.states().size() ==  0)
      return false;
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    const alphabet_t& alpha = e.structure().series().monoid().alphabet();
    for_all_const_states(i, e)
    {
      std::set<hstate_t> dst;
      for_all_const_letters(j, alpha)
      {
	dst.clear();
	e.letter_deltac(dst, *i, *j, delta_kind::states());

	if (dst.size() == 0)
	  return false;
      }
    }
    return true;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_COMPLETE_HXX
