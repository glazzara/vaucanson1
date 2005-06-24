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
// `NOTICE' file in the root directory.
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
    std::set<hedge_t> out;
    std::map<series_set_elt_t, int> Lmap;
    std::map<hstate_t, int> Smap;

    states.reserve(a.states().size());
    edges.reserve(a.edges().size());
    origins_edges.reserve(a.edges().size());
    aims_edges.reserve(a.edges().size());
    edges_labels.reserve(a.edges().size());

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

    // Gives each edge an index (edge[i] = edge whose index is i)
    // Gives each label an index in map Lmap
    // Gives each edge the index of its label (edges_labels[i] = index
    // of label of edge i)
    // (time complexity: O(m log s + m log n))
    // Constructs vectors origin_of and aim_of

    // Index of the labels
    i = 0;
    // Index of the edges
    j = 0;
    for_each_edge(e, a)
    {
      edges.push_back(*e);
      origins_edges.push_back(Smap[a.origin_of(*e)]);
      aims_edges.push_back(Smap[a.aim_of(*e)]);

      if (Lmap.find(a.series_of(*e)) == Lmap.end())
	edges_labels.push_back(Lmap[a.series_of(*e)] = i++);
      else
	edges_labels.push_back(Lmap[a.series_of(*e)]);
    }

    // Here, i = number of different labels

    /*** FIXME ***/
    // The following piece of code is intended to visit each entry of
    // map Lmap and put each label in its place in vector
    // labels, but it doesn't compile. The problem is then solved by
    // visiting all the edges of the automaton, what can produce
    // several visits to the same label.
    //
    //    for (std::map<label_t, int>::iterator itr = Lmap.begin();
    //	       itr != Lmap.end(); itr++)
    //      labels[itr->second] = itr->first;
    // *** REMARK: vector labels is obsolete


    // Construct the list of edges for each label (edges_lex indexed
    // by labels, edges_lex[i] = list of edges with label i)

    std::vector< std::list<int> > edges_lex(i);

    for (i = 0; i < static_cast<int>(a.edges().size()); i++)
      edges_lex[edges_labels[i]].push_front(i);

    // By using vector edges_lex, defines ingoing and outgoing edges
    // of each state in lexicographic order
    for (i = 0; i < static_cast<int>(edges_lex.capacity()); i++)
      for (std::list<int>::iterator it = edges_lex[i].begin();
	   it != edges_lex[i].end(); it++)
      {
	delta_in[aims_edges[*it]].push_back(*it);
	delta_out[origins_edges[*it]].push_back(*it);
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
  void Skeleton<A, T>::reserve_aux_edges_int()
  {
    aux_edges_int.reserve(a.edges().size());
  }

  template<typename A, typename T>
  void Skeleton<A, T>::reserve_aux_edges_bool()
  {
    aux_edges_bool.reserve(a.edges().size());
  }

  template<typename A, typename T>
  void Skeleton<A, T>::reserve_aux_edges_generic()
  {
    aux_edges_generic.reserve(a.edges().size());
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_INTERNAL_SKELETON_HXX
