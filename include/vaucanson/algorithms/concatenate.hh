// concatenate.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_CONCATENATE_HH
# define VCSN_ALGORITHMS_CONCATENATE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   concatenate.hh
 *
 * This file provides the general concatenation algorithm.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 17:42:32 2003
 *
 * @see concatenate(), concatenate_here()
 */
/** @} */

// INTERFACE: Automaton concatenate(const Automaton& a1, const Automaton& a2) { return vcsn::concatenate(*a1, *a2); }
// INTERFACE: GenAutomaton concatenate(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::concatenate(*a1, *a2); }

// INTERFACE: void concatenate_here(Automaton& a1, const Automaton& a2) { return vcsn::concatenate_here(*a1, *a2); }
// INTERFACE: void concatenate_here(GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::concatenate_here(*a1, *a2); }

# include <vaucanson/design_pattern/element.hh>

namespace vcsn {


  /** @addtogroup algorithms *//** @{ */

  /**
   * Return the concatenation of two automata.
   *
   * This function produces a new automata that realizes L(lhs).L(rhs).
   *
   * @param lhs The first automaton.
   * @param rhs The second automaton.
   *
   * @see concatenate_here()
   *
   * @return A fresh automaton that is the concatenation of lhs and rhs.
   */
  template <class A, class T>
  Element<A, T>
  concatenate(const Element<A, T>& lhs, const Element<A, T>& rhs);

  /**
   * In place concatenation of two automata.
   *
   * This function modifies lhs to concatenate the language L(rhs) to its
   * language.
   *
   * It returns the concatenation of two automata using epsilon
   * transitions.
   *
   * @param lhs The first automaton.
   * @param rhs The second automaton.
   *
   * @see concatenate()
   * @author Yann Regis-Gianas.
   *
   */
  template <class A, class T>
  void
  concatenate_here(Element<A, T>& lhs, const Element<A, T>& rhs);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/concatenate.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_CONCATENATE_HH
