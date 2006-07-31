// skeleton.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_SKELETON_HH
# define VCSN_ALGORITHMS_INTERNAL_SKELETON_HH

/**
 * @file skeleton.hh
 * @author Rodrigo de Souza <arsouza@enst.fr>
 *
 * @brief The @c Skeleton class. (undocumented-internal)
 *
 * This file describe the skeleton of an automaton, i.e. a certain
 * view of an automaton through vectors.
 */

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vector>


namespace vcsn
{
  // "Skeleton" of an automaton, consisting of a numbering of states
  // and transitions by means of vectors. Additional auxiliary vectors are
  // not used in this file.
  template<typename A, typename T>
  class Skeleton
  {
    public:

      Skeleton(const Element<A, T>& x);

      const Element<A, T>& a;

      // Vector of states. Each states can be also represented by its
      // index.
      std::vector<hstate_t> states;
      // Vector of transitions. Each transition can be also
      // represented by its index.
      std::vector<htransition_t> transitions;
      std::vector<int> src_transitions;
      std::vector<int> dst_transitions;

      // List of indices of ingoing transitions in lex. order of each state
      std::vector< std::list<int> > delta_in;
      // List of indices of outgoing transitions in lex. order of each state
      std::vector< std::list<int> > delta_out;


      // Indices of initial and final states
      std::list<int> I, F;
      // Index in labels of the label of each transition
      std::vector<int> transitions_labels;
      // (transitions_labels[i] = index of label of transition i) Auxiliary data
      std::vector<int> aux_states_int;
      std::vector<bool> aux_states_bool;
      std::vector<void*> aux_states_generic;
      std::vector<int> aux_transitions_int;
      std::vector<bool> aux_transitions_bool;
      std::vector<void*> aux_transitions_generic;

      void reserve_aux_states_int();
      void reserve_aux_states_bool();
      void reserve_aux_states_generic();
      void reserve_aux_transitions_int();
      void reserve_aux_transitions_bool();
      void reserve_aux_transitions_generic();
  };

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/internal/skeleton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_INTERNAL_SKELETON_HH
