// accessible.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_ACCESSIBLE_HH
# define VCSN_ALGORITHMS_ACCESSIBLE_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <set>

namespace vcsn {

  /** \addtogroup algorithms */  /* @{ */

  /// Returns reachables states from the input states.
  template<typename A, typename T>
  std::set<hstate_t>
  accessible_states(const Element<A, T>& a);

  /// Extracts the sub-automaton composed of the start reachable states.
  template<typename A, typename T>
  Element<A, T>
  accessible(const Element<A, T>& a);

  /// In-place extract the sub-automaton of start reachable states.
  template<typename A, typename T>
  void
  accessible_here(Element<A, T>& a);
  
  /// Returns co-accessible states from the final states.
  template<typename A, typename T>
  std::set<hstate_t>
  coaccessible_states(const Element<A, T>& a);
  
  /// Extracts the sub-automaton composed of the final co-accessible states. 
  template<typename A, typename T>
  Element<A, T>
  coaccessible(const Element<A, T>& a);
  
  /// In-place extract the sub-automaton of final co-reachable states.
  template<typename A, typename T>
  void
  coaccessible_here(Element<A, T>& a);

  /** @} */
  
} // vcsn

# include <vaucanson/algorithms/accessible.hxx>

#endif // ALGORITHMS_ACCESSIBLE_HH
