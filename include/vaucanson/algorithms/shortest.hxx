// shortest.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009, 2010 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_SHORTEST_HXX
# define VCSN_ALGORITHMS_SHORTEST_HXX

#include <vaucanson/algorithms/shortest.hh>
#include <vaucanson/automata/concept/automata_base.hh>
#include <vaucanson/misc/usual_macros.hh>
#include <queue>
#include <map>
#include <vaucanson/misc/military_order.hh>
#include <vaucanson/algorithms/shortest.hh>

namespace vcsn
{
  template<typename Automaton, typename MonoidElt>
  bool
  do_shortest(const Automaton& autom, MonoidElt& word)
  {
    precondition(is_realtime(autom));
    AUTOMATON_TYPES(Automaton);
    AUTOMATON_FREEMONOID_TYPES (Automaton);

    monoid_t themonoid = autom.structure().series().monoid();
    // shortest word read at this state
    typedef std::map<hstate_t, monoid_elt_t> theword_t;
    theword_t theword;
    std::queue<hstate_t> thequeue;

    monoid_elt_t empty_word = themonoid.identity(SELECT(monoid_elt_value_t));

    for_all_initial_states(j, autom)
      {
	theword.insert(std::pair<hstate_t,monoid_elt_t>(*j, empty_word));
	if (autom.is_final(*j))
	  {
	    word = empty_word;
	    return true;
	  }
	thequeue.push(*j);
      }

    while (not thequeue.empty())
      {
	hstate_t i = thequeue.front();
	thequeue.pop();
	for_all_letters(a, themonoid.alphabet())
	  {
	    for (typename Automaton::delta_iterator t(autom.value(), i);
		 ! t.done();
		 t.next())
	      {
		// iterate over successors of i by *a
		monoid_elt_t w(themonoid, *a);
		if (autom.series_of(*t).get(w)
		    != autom.series().semiring()
		       .zero(SELECT(typename semiring_elt_t::value_t)))
		  {
		    hstate_t j = autom.dst_of(*t);
		    if (theword.find(j) == theword.end())
		      {
			// j is in the map only if it has been seen
			// before, otherwise:

			typename theword_t::const_iterator k = theword.find(i);
			assert(k != theword.end());

			theword.insert(std::pair<hstate_t, monoid_elt_t>(j, k->second * (*a)));
			if (autom.is_final(j))
			  {
			    typename theword_t::const_iterator k = theword.find(j);
			    assert(k != theword.end());

			    word = k->second;
			    return true;
			  }
			thequeue.push(j);
		      }
		  }
	      }
	  }
      }
    return false;
  }

  template<typename Automaton, typename MonoidElt, typename Alloc>
  void
  do_enumerate(const Automaton& autom,
	       unsigned max_length,
	       std::list<MonoidElt, Alloc>& words)
  {
    precondition(is_realtime(autom));

    AUTOMATON_TYPES(Automaton);
    AUTOMATON_FREEMONOID_TYPES (Automaton);
    monoid_t themonoid = autom.structure().series().monoid();
    // a list of words that leads to this state
    std::map<hstate_t,std::list<monoid_elt_t> > theword;
    //std::list allows swap, contrary to std::queue
    std::list<std::pair<hstate_t,monoid_elt_t> > queue1;
    std::list<std::pair<hstate_t,monoid_elt_t> > queue2;

    monoid_elt_t empty_word = themonoid.identity(SELECT(monoid_elt_value_t));

    for_all_initial_states(j, autom)
      {
	theword[*j].push_back(empty_word);
     	queue1.push_back(std::pair<hstate_t,monoid_elt_t>(*j, empty_word));
      }

    for(unsigned i = 0; i < max_length && not queue1.empty(); i++)
      {
	while (not queue1.empty())
  	  {
	    std::pair<hstate_t,monoid_elt_t> thepair = queue1.front();
	    queue1.pop_front();
	    hstate_t s = thepair.first;
	    monoid_elt_t oldword = thepair.second;
	    for (typename Automaton::delta_iterator t(autom.value(), s);
		 ! t.done();
		 t.next())
	      {
		for_all_letters(a, themonoid.alphabet())
		  {
		    // iterate over successors of i by *a
		    monoid_elt_t w(themonoid, *a);
		    if (autom.series_of(*t).get(w) !=
			autom.series().semiring().zero(SELECT(typename semiring_elt_t::value_t)))
		      {
			monoid_elt_t newword = oldword *(*a);
			theword[autom.dst_of(*t)].push_back(newword);
			queue2.push_back(std::pair<hstate_t,monoid_elt_t>(autom.dst_of(*t),newword));
		      }
		  }
	      }
	  }
	queue1.swap(queue2);
      }

    std::vector<monoid_elt_t> v;
    for_all_final_states(j, autom)
      {
	std::list<monoid_elt_t> &l = theword[*j];
	v.insert(v.end(), l.begin(), l.end());
      }
    sort(v.begin(), v.end(), MilitaryOrder<monoid_elt_t>());
    typename std::vector<monoid_elt_t>::iterator v_last
      = std::unique(v.begin(), v.end());
    words.insert(words.begin(), v.begin(), v_last);
  }

  template<typename Automaton>
  typename Automaton::monoid_elt_t
  shortest(const Automaton& autom)
  {
    typename Automaton::monoid_elt_t word(autom.structure().series().monoid());
    do_shortest(autom, word);
    return word;
  }

  template<typename Automaton, typename MonoidElt>
  bool
  shortest(const Automaton& autom, MonoidElt& word)
  {
    return do_shortest(autom, word);
  }

  template<typename Automaton, typename MonoidElt, typename Alloc>
  void
  enumerate(const Automaton& autom, unsigned max_length,
	    std::list<MonoidElt, Alloc>& word_list)
  {
    do_enumerate(autom, max_length, word_list);
  }
} // ! vcsn

#endif // ! VCSN_ALGORITHMS_SHORTEST_HXX
