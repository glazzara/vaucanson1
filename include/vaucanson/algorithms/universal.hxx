// universal.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_UNIVERSAL_HXX
# define VCSN_ALGORITHMS_UNIVERSAL_HXX


# include <map>
# include <set>

# include <vaucanson/boolean_automaton.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/complete.hh>

# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  namespace universal_internal {

    // Returns the intersection of two sets.
    template<typename Set>
    Set intersection_structure(const Set& set1, const Set& set2)
    {
      Set tmp;
      std::insert_iterator<Set> i(tmp, tmp.begin());
      std::set_intersection(set1.begin(), set1.end(),
			    set2.begin(), set2.end(),
			    i);
      return tmp;
    }

    // A simple intersection closure.
    template<typename Set>
    std::set<Set> intersection_closure(const std::set<Set>& s)
    {
      std::set<Set> tmp = s;
      std::set<Set> ret = s;

      do {
	std::swap(ret, tmp);
	for_all_const_(std::set<Set>, s1, tmp)
	  for_all_const_(std::set<Set>, s2, tmp)
          ret.insert(intersection_structure(*s1, *s2));
      } while (ret.size() != tmp.size());
      return ret;
    }

    // Return the image of a map.
    template<typename K, typename V>
    std::set<V> image(const std::map<K,V>& m)
    {
      std::set<V> ret;
      for(typename std::map<K,V>::const_iterator a=m.begin(); a!= m.end(); ++a)
	ret.insert(a->second);
      return ret;
    }

    // Return true if a set1 \subset set2.
    template <class Container1, class Container2>
    bool includes(const Container1& set1, const Container2& set2)
    {
      return std::includes(set2.begin(), set2.end(),
			   set1.begin(), set1.end());
    }
  } //univeral_internal


// And now, the algorithm:
  template<typename A, typename AI>
  void do_universal(const AutomataBase<A>&,
		    const Element<A,AI>& a,
		    Element<A,AI>& u)
  {
    typedef Element<A, AI> Auto;
    AUTOMATON_TYPES(Auto);
    AUTOMATON_FREEMONOID_TYPES(Auto);

    typedef std::set<std::set<hstate_t> >		pstate_t;
    typedef std::set<hstate_t>			state_set_t;
    typedef std::map<hstate_t, state_set_t>	map_t;

    using namespace universal_internal;

    Auto automaton(a);

    if(!is_deterministic(automaton))
      automaton = determinize(automaton);
    if(!is_complete(automaton))
      automaton = complete(automaton);


    // let i, be the initial state of automaton.
    hstate_t i = *automaton.initial().begin();

    // compute the co-determinized of the minimal automaton
    // and retrieve the origin of each state.
    map_t origin;
    Auto transposed = transpose(automaton);
    Auto co_det = determinize(transposed, origin);

    // the 'origin' is a map from co_det's hstate_t to
    // minimal's std::set<hstate_t>.
    // let 'transp_states' be the image of 'origin'.
    pstate_t transp_states = image(origin);

    // the universal automaton's state set is its intersection closure.
    pstate_t univers_states(intersection_closure(transp_states));

    // we have to save the state set associated to each automaton.
    map_t subset_label;

    // X = univers_states \ {}.
    for_all_const_(pstate_t, s, univers_states)
      if (s->size() != 0)
      {
	hstate_t new_s = u.add_state();
	subset_label[new_s] = *s;
	// J = { X | i in X }
	if (s->find(i) != s->end())
	  u.set_initial(new_s);
	// U = { X | X \subset T }
	if (includes(*s, automaton.final()))
	  u.set_final(new_s);
      }

    // finally, the transition set.
    for_all_states(x, u)
      for_all_states(y, u)
      for_all_letters(a, u.series().monoid().alphabet())
    {
      bool cont = false;
      std::set<hstate_t> delta_ret;
      for_all_const_(state_set_t, s, subset_label[*x])
      {
	bool empty = true;
	// FIXME: bmig complains "Assertion failed: has_state(s)" for
	// the line below.
	for (typename automaton_t::delta_iterator dst(automaton.value(), *s);
	     ! dst.done(); dst.next())
	{
	  monoid_elt_t w(automaton.series_of(*dst).structure().monoid(), *a);
	  if (automaton.series_of(*dst).get(w)
	      != automaton.series().semiring().wzero_)
	  {
	    empty = false;
	    delta_ret.insert(automaton.dst_of(*dst));
	  }
	}
	if (empty)
	{
	  cont = true;
	  break;
	}
      }
      // case 1: \exists p \in X, p.a = {}
      if (cont)
	continue;
      // case 2: X.a \subset Y ?
      if (includes(delta_ret, subset_label[*y]))
	u.add_letter_transition(*x, *y, *a);
    }
  }

  template<typename  A, typename  AI>
  Element<A, AI>
  universal(const Element<A, AI>& a)
  {
    precondition(is_realtime(a));

    Element<A, AI> ret(a.structure());
    do_universal(a.structure(), a, ret);
    return ret;
  }

} // vcsn
#endif // !VCSN_ALGORITHMS_UNIVERSAL_HXX
