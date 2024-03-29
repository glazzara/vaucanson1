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

# ifndef VCSN_NDEBUG
#  include <vaucanson/algorithms/realtime.hh>
# endif // ! VCSN_NDEBUG

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
    // Note that this algorithm may be used on non-deterministic
    // automata.
    precondition(is_realtime(work));
    BENCH_TASK_SCOPED("complete");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);

    hstate_t sink_state = work.add_state();
    bool sink_needed = false;

    // If the sink states is the only state of the automaton, we want
    // to keep it as an initial state.  This is meant!  The empty
    // automaton is deterministic, but a complete deterministic
    // automata has at least one state (it is then easier to
    // complement it).
    if (work.states().size() ==  1)
    {
      sink_needed = true;
      work.set_initial(sink_state);
    }

    for_all_const_states(s, work)
      for_all_const_letters(l, work.structure().series().monoid().alphabet())
      {
        bool empty = true;
        for (delta_iterator t(work.value(), *s); ! t.done(); t.next())
        {
          monoid_elt_t w(work.series_of(*t).structure().monoid(), *l);
          if (work.series_of(*t).get(w) != work.series().semiring().wzero_)
          {
            empty = false;
            break;
          }
        }
        if (empty)
        {
	  sink_needed = true;
          work.add_letter_transition(*s, sink_state, *l);
	}
      }

    if (!sink_needed)
      work.del_state(sink_state);
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
    BENCH_TASK_SCOPED("is_complete");
    if (e.states().size() ==  0)
      return false;
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    const alphabet_t& alpha = e.structure().series().monoid().alphabet();
    for_all_const_states(i, e)
    {
      for_all_const_letters(j, alpha)
      {
	bool empty = true;
        for (delta_iterator t(e.value(), *i);
             ! t.done() && empty;
             t.next())
        {
          monoid_elt_t w(e.series_of(*t).structure().monoid(), *j);
          if (e.series_of(*t).get(w) != e.series().semiring().wzero_)
          {
            empty = false;
            break;
          }
        }

	if (empty)
	  return false;
      }
    }
    return true;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_COMPLETE_HXX
