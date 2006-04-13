// skeleton.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_SKELETON_HXX
# define VCSN_ALGORITHMS_INTERNAL_SKELETON_HXX

# include <vaucanson/algorithms/internal/skeleton.hh>

namespace vcsn
{

  /*------------------------.
  | Skeleton Implementation |
  `------------------------*/

  template<typename A, typename T>
  Skeleton<A, T>::Skeleton(const Element<A, T>& x) : a(x)
  {

    typedef Element<A, T> automaton_t;

    AUTOMATON_TYPES(automaton_t);

    int i, j;
    std::set<htransition_t> out;
    std::map<series_set_elt_t, int> Lmap;
    std::map<hstate_t, int> Smap;

    states.reserve(a.states().size());
    transitions.reserve(a.transitions().size());
    origins_transitions.reserve(a.transitions().size());
    aims_transitions.reserve(a.transitions().size());
    transitions_labels.reserve(a.transitions().size());

    // *** FIXME ***
    // HOW TO INITIALIZE A VECTOR OF LISTS?
    std::list<int> dummy;
    delta_in.assign(a.states().size(), dummy);
    delta_out.assign(a.states().size(), dummy);


    // Gives each state a number. Constructs lists I and T of initial
    // and final states
    // Time complexity: O(n log n)
    i = 0;
    for_each_state(q, a)
    {
      states.push_back(*q);
      Smap[*q] = i++;

      if (a.is_initial(*q))
	I.push_front(i - 1);
      else
	if (a.is_final(*q))
	  F.push_front(i - 1);
    }

    // Gives each transition an index (transition[i] = transition whose index is i)
    // Gives each label an index in map Lmap
    // Gives each transition the index of its label (transitions_labels[i] = index
    // of label of transition i)
    // (time complexity: O(m log s + m log n))
    // Constructs vectors src_of and dst_of

    // Index of the labels
    i = 0;
    // Index of the transitions
    j = 0;
    for_each_transition(e, a)
    {
      transitions.push_back(*e);
      origins_transitions.push_back(Smap[a.src_of(*e)]);
      aims_transitions.push_back(Smap[a.dst_of(*e)]);

      if (Lmap.find(a.series_of(*e)) == Lmap.end())
	transitions_labels.push_back(Lmap[a.series_of(*e)] = i++);
      else
	transitions_labels.push_back(Lmap[a.series_of(*e)]);
    }

    // Here, i = number of different labels

    /*** FIXME ***/
    // The following piece of code is intended to visit each entry of
    // map Lmap and put each label in its place in vector
    // labels, but it doesn't compile. The problem is then solved by
    // visiting all the transitions of the automaton, what can produce
    // several visits to the same label.
    //
    //	  for (std::map<label_t, int>::iterator itr = Lmap.begin();
    //	       itr != Lmap.end(); itr++)
    //	    labels[itr->second] = itr->first;
    // *** REMARK: vector labels is obsolete


    // Construct the list of transitions for each label (transitions_lex indexed
    // by labels, transitions_lex[i] = list of transitions with label i)

    std::vector< std::list<int> > transitions_lex(i);

    for (i = 0; i < static_cast<int>(a.transitions().size()); i++)
      transitions_lex[transitions_labels[i]].push_front(i);

    // By using vector transitions_lex, defines ingoing and outgoing transitions
    // of each state in lexicographic order
    for (i = 0; i < static_cast<int>(transitions_lex.capacity()); i++)
      for (std::list<int>::iterator it = transitions_lex[i].begin();
	   it != transitions_lex[i].end(); it++)
      {
	delta_in[aims_transitions[*it]].push_back(*it);
	delta_out[origins_transitions[*it]].push_back(*it);
      }

  }

  template<typename A, typename T>
  void Skeleton<A, T>::reserve_aux_states_int()
  {
    aux_states_int.reserve(a.states().size());
  }

  template<typename A, typename T>
  void Skeleton<A, T>::reserve_aux_states_bool()
  {
    aux_states_bool.reserve(a.states().size());
  }

  template<typename A, typename T>
  void Skeleton<A, T>::reserve_aux_states_generic()
  {
    aux_states_generic.reserve(a.states().size());
  }

  template<typename A, typename T>
  void Skeleton<A, T>::reserve_aux_transitions_int()
  {
    aux_transitions_int.reserve(a.transitions().size());
  }

  template<typename A, typename T>
  void Skeleton<A, T>::reserve_aux_transitions_bool()
  {
    aux_transitions_bool.reserve(a.transitions().size());
  }

  template<typename A, typename T>
  void Skeleton<A, T>::reserve_aux_transitions_generic()
  {
    aux_transitions_generic.reserve(a.transitions().size());
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_INTERNAL_SKELETON_HXX
