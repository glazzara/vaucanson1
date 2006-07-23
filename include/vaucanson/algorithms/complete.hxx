// complete.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <list>
# include <set>

namespace vcsn {

  /*--------------.
  | complete_here |
  `--------------*/

  template <typename A, typename T>
  void
  complete_here(Element<A, T>& work)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    hstate_t sink_state;
    bool sink_added = false;
    std::list<hstate_t> aim;

    for_all_states(s, work)
    {
      for_all_letters(l, work.structure().series().monoid().alphabet())
      {
	aim.clear();
	work.letter_deltac(aim, *s, *l, delta_kind::states());
	if (aim.size() == 0)
	{
	  if (not sink_added)
	  {
	    sink_state = work.add_state();
	    sink_added = true;
	  }
	  work.add_letter_transition(*s, sink_state, *l);
	}
      }
    }
    if (sink_added)
      for_all_letters(l, work.structure().series().monoid().alphabet())
	work.add_letter_transition(sink_state, sink_state, *l);
  }

  /*---------.
  | complete |
  `---------*/

  template <typename A, typename T>
  Element<A, T>
  complete(const Element<A, T>& e)
  {
    Element<A, T> res(e);
    complete_here(res);
    return res;
  }

  /*------------.
  | is_complete |
  `------------*/

  template <class A, class T>
  bool
  is_complete(const Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    for_all_states(i, e)
    {
      std::set<hstate_t> aim;
      const alphabet_t& alpha = e.structure().series().monoid().alphabet();
      for_all_letters(j, alpha)
      {
	aim.clear();
	e.letter_deltac(aim, *i, *j, delta_kind::states());

	if (aim.size() == 0)
	  return false;
      }
    }
    return true;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_COMPLETE_HXX
