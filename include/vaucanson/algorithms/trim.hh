// trim.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_TRIM_HH
# define VCSN_ALGORITHMS_TRIM_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file trim.hh
 *
 * This file contains the declaration of useful_states() and trim().
 *
 * @see useful_states(), trim()
 */
/** @} */

// INTERFACE: HList useful_states(const Automaton& a) { return list_of_set(vcsn::useful_states(*a)); }
// INTERFACE: HList useful_states(const GenAutomaton& a) { return list_of_set(vcsn::useful_states(*a)); }

// INTERFACE: Automaton trim(const Automaton& a) { return vcsn::trim(*a); }
// INTERFACE: GenAutomaton trim(const GenAutomaton& a) { return vcsn::trim(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Returns a useful states of the automaton (start reachable and final co-).
  template<typename A, typename T>
  std::set<hstate_t>
  useful_states(const Element<A, T>& a);

  /// Return a fresh automaton in which non useful states are removed.
  template<typename A, typename T>
  Element<A, T>
  trim(const Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/trim.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_TRIM_HH
