// transpose.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
//
#ifndef VCSN_ALGORITHMS_TRANSPOSE_HH
# define VCSN_ALGORITHMS_TRANSPOSE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file algorithms/transpose.hh
 *
 * This file contain the function which transpose an automaton.
 */
/** @} */

// INTERFACE: void transpose(Automaton& dst, const Automaton& src) { vcsn::transpose(*dst, *src); }
// INTERFACE: void transpose(GenAutomaton& dst, const GenAutomaton& src) { vcsn::transpose(*dst, *src); }

// INTERFACE: Automaton transpose(const Automaton& a) { return vcsn::transpose(*a); }
// INTERFACE: GenAutomaton transpose(const GenAutomaton& a) { return vcsn::transpose(*a); }

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Transposition of an automaton.
   *
   * This function copy in @c dst the transposition of the automaton @c from.
   *
   * @param from Automaton to transpose
   * @param dst Destination
   */
  template<typename lhs_t, typename rhs_t>
  void
  transpose(lhs_t& dst, const rhs_t& from);

  /**
   * Return a fresh transposed automaton.
   *
   * This function returns the transposition of an automaton.
   *
   * @param from Automaton to transpose.
   */
  template<typename auto_t>
  auto_t
  transpose(const auto_t& from);

  /** @} */

} //vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/transpose.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_TRANSPOSE_HH
