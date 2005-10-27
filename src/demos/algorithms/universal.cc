// universal.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/algorithms/complete.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <iostream>

using namespace vcsn::boolean_automaton;

// We are working with Vaucanson : let's open its namespace.
using namespace vcsn;

// Declare some useful types.
typedef std::set<std::set<hstate_t> >		pstate_t;
typedef std::set<hstate_t>			state_set_t;
typedef std::map<hstate_t, state_set_t>		map_t;

// First, some functions that are not in Vaucanson today but probably
// will:

// Returns the intersection of two sets.
state_set_t intersection_structure(const state_set_t& set1, const state_set_t& set2)
{
  state_set_t tmp;
  std::insert_iterator<state_set_t> i(tmp, tmp.begin());
  std::set_intersection(set1.begin(), set1.end(),
			set2.begin(), set2.end(),
			i);
  return tmp;
}

// A simple intersection closure.
pstate_t intersection_closure(const pstate_t& s)
{
  pstate_t tmp = s;
  pstate_t ret = s;

  do {
    std::swap(ret, tmp);
    for_all_const(pstate_t, s1, tmp)
      for_all_const(pstate_t, s2, tmp)
      ret.insert(intersection_structure(*s1, *s2));
  } while (ret.size() != tmp.size());
  return ret;
}

// Return the image of a map.
pstate_t image(const map_t& m)
{
  pstate_t ret;
  for_all_const(map_t, a, m)
    ret.insert(a->second);
  return ret;
}

// Return the union of set1 and set2.
state_set_t union_structure(const state_set_t& set1, const state_set_t& set2)
{
  state_set_t tmp;
  std::insert_iterator<state_set_t> i(tmp, tmp.begin());
  std::set_union(set1.begin(), set1.end(),
		 set2.begin(), set2.end(),
		 i);
  return tmp;
}

// Return true if a set1 \subset set2.
template <class Container1, class Container2>
bool includes(const Container1& set1, const Container2& set2)
{
  return std::includes(set2.begin(), set2.end(),
		       set1.begin(), set1.end());
}

// And now, the algorithm:
automaton_t universal(const automaton_t& automaton)
{
  // let i, be the initial state of automaton.
  hstate_t i = *automaton.initial().begin();

  // compute the co-determinized of the minimal automaton
  // and retrieve the origin of each state.
  map_t origin;
  automaton_t transposed = transpose(automaton);
  automaton_t co_det = determinize(transposed, origin);

  // the 'origin' is a map from co_det's hstate_t to
  // minimal's std::set<hstate_t>.
  // let 'transp_states' be the image of 'origin'.
  pstate_t transp_states = image(origin);

  // the universal automaton's state set is its intersection closure.
  pstate_t univers_states(intersection_closure(transp_states));

  // create the universal automaton.
  automaton_t u = new_automaton(automaton.series().monoid().alphabet());

  // we have to save the state set associated to each automaton.
  map_t subset_label;

  // X = univers_states \ {}.
  for_all_const(pstate_t, s, univers_states)
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
  for_each_state(x, u)
    for_each_state(y, u)
    for_each_letter(a, u.series().monoid().alphabet())
    {
      bool cont = false;
      std::set<hstate_t> delta_ret;
      for_all_const(state_set_t, s, subset_label[*x])
	{
	  state_set_t delta_tmp;
	  automaton.letter_deltac(delta_tmp, *s, *a, delta_kind::states());
	  if (delta_tmp.size() == 0)
	    {
	      cont = true;
	      break;
	    }
	  delta_ret = union_structure(delta_ret, delta_tmp);
	}
      // case 1: \exists p \in X, p.a = {}
      if (cont)
	continue;
      // case 2: X.a \subset Y ?
      if (includes(delta_ret, subset_label[*y]))
 	u.add_letter_edge(*x, *y, *a);
    }
  return u;
}


int main()
{
  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');
  automaton_t a = new_automaton(alpha);
  hstate_t p = a.add_state();
  hstate_t q = a.add_state();
  hstate_t r = a.add_state();
  a.add_letter_edge(p, q, 'a');
  a.add_letter_edge(p, q, 'c');
  a.add_letter_edge(p, r, 'b');
  a.add_letter_edge(q, p, 'b');
  a.add_letter_edge(q, p, 'c');
  a.add_letter_edge(q, r, 'a');
  a.add_letter_edge(r, r, 'b');
  a.add_letter_edge(r, p, 'a');
  a.add_letter_edge(r, p, 'c');
  a.set_initial(p);
  a.set_final(r);
  automaton_t univers = universal(a);
  tools::dot_dump(std::cout, univers, "automaton");
}

