// skeleton.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//    * Michael Cadilhac <michael.cadilhac@lrde.epita.fr>
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
# include <vaucanson/tools/usual_macros.hh>
# include <vector>


namespace vcsn
{
  // "Skeleton" of an automaton, consisting of a numbering of states
  // and edges by means of vectors. Additional auxiliary vectors are
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
      std::vector<hedge_t> edges;
      std::vector<int> origins_edges;
      std::vector<int> aims_edges;

      // List of indices of ingoing edges in lex. order of each state
      std::vector< std::list<int> > delta_in;
      // List of indices of outgoing edges in lex. order of each state
      std::vector< std::list<int> > delta_out;


       // Indices of initial and final states
      std::list<int> I, F;
      // Index in labels of the label of each transition
      std::vector<int> edges_labels;
      // (edges_labels[i] = index of label of edge i) Auxiliary data
      std::vector<int> aux_states_int;
      std::vector<bool> aux_states_bool;
      std::vector<void*> aux_states_generic;
      std::vector<int> aux_edges_int;
      std::vector<bool> aux_edges_bool;
      std::vector<void*> aux_edges_generic;

      void reserve_aux_states_int();
      void reserve_aux_states_bool();
      void reserve_aux_states_generic();
      void reserve_aux_edges_int();
      void reserve_aux_edges_bool();
      void reserve_aux_edges_generic();
  };

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/internal/skeleton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_INTERNAL_SKELETON_HH
