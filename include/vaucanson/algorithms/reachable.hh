// reachable.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_REACHABLE_HH
# define VCSN_ALGORITHMS_REACHABLE_HH

# include <set>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  //! Return reachables states from the input states.
  template<typename A, typename T>
  std::set<hstate_t>
  start_reachable_states(const Element<A, T>& a);

  //! Extracts the sub-automaton composed of the start reachable states.
  template<typename A, typename T>
  Element<A, T>
  auto_start_reachable(const Element<A, T>& a);

  //! In-place extraction of the sub-automaton of start reachable states.
  template<typename A, typename T>
  void
  auto_in_start_reachable(Element<A, T>& a);
  
  //! Return co-reachables states from the final states.
  template<typename A, typename T>
  std::set<hstate_t>
  final_reachable_states(const Element<A, T>& a);

  //! Extracts the sub-automaton composed of the final co-reachable states. 
  template<typename A, typename T>
  Element<A, T>
  auto_final_reachable(const Element<A, T>& a);

  //! In-place extraction of the sub-automaton of final co-reachable states.
  template<typename A, typename T>
  void
  auto_in_final_reachable(Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/reachable.hxx>

#endif // ALGORITHMS_REACHABLE_HH
