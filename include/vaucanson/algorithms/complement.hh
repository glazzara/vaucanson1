// complement.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_COMPLEMENT_HH
# define VCSN_ALGORITHMS_COMPLEMENT_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   complement.hh
 *
 * Complementation algorithm for Boolean automata.
 *
 * @see complement(), complement_here()
 */
/** @} */

// INTERFACE: void complement_here(Automaton& a) { return vcsn::complement_here(*a); }
// INTERFACE: void complement_here(GenAutomaton& a) { return vcsn::complement_here(*a); }

// INTERFACE: Automaton complement(const Automaton& a) { return vcsn::complement(*a); }
// INTERFACE: GenAutomaton complement(const GenAutomaton& a) { return vcsn::complement(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Complement in place the set of final states.
   *
   * @param a The deterministic Boolean automaton to complement.
   *
   * @note The input automaton must be complete and deterministic.
   *
   * @see complement()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename T>
  void
  complement_here(Element<A, T>& a);

  /**
   * Complement the set of final states.
   *
   * @param a the deterministic Boolean automaton to complement.
   *
   * @note the input automaton must be complete and deterministic.
   *
   * @see complement_here()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename T>
  Element<A, T>
  complement(const Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/complement.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_COMPLEMENT_HH
