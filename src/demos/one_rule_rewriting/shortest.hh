// shortest.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009 The Vaucanson Group.
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
#ifndef SHORTEST_HH
# define SHORTEST_HH

#include <queue>
#include <set>
#include <map>

#include <vaucanson/boolean_automaton.hh>

namespace vcsn
{
  // To be applied only to "realtime" automata.
  boolean_automaton::monoid_elt_t
  shortest(const vcsn::boolean_automaton::automaton_t& autom)
  {
    using namespace vcsn::boolean_automaton;

    monoid_t themonoid = autom.structure().series().monoid();
    std::map<hstate_t,monoid_elt_t*> theword; // a pointer to the shortest word read at this state
    std::queue<hstate_t> thequeue;

    monoid_elt_t empty_word = themonoid.identity(SELECT(monoid_elt_value_t));

    for_all_initial_states(j, autom)
    {
      theword[*j] = &empty_word;
      if (autom.is_final(*j))
	return empty_word;
      thequeue.push(*j);
    }

    typedef std::set<hstate_t> setstate_t;

    while (not thequeue.empty())
    {
      hstate_t i = thequeue.front();
      thequeue.pop();
      for_all_letters(a, themonoid.alphabet())
      {
	for (vcsn::boolean_automaton::automaton_t::delta_iterator t(autom.value(), i);
	     ! t.done();
	     t.next())
	{
	  // iterate over successors of i by *a
	  monoid_elt_t w(autom.series_of(*t).structure().monoid(), *a);
	  if (autom.series_of(*t).get(w) != autom.series().semiring().zero(SELECT(semiring_elt_t::value_t)))
	  {
	    hstate_t j = autom.dst_of(*t);
	    if (theword.find(j) == theword.end())
	    {
	      // j is in the map only if it has been seen before, otherwise:
	      theword[j] = new monoid_elt_t((*theword[i]) * (*a));
	      if (autom.is_final(j))
		return *theword[j];
	      thequeue.push(j);
	    }
	  }
	}
      }
    }

    std::cout << "Empty language" << std::endl;

    return empty_word;
  }

} // ! vcsn

#endif // ! SHORTEST_HH
