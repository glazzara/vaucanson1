// complete.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_COMPLETE_HH
# define VCSN_ALGORITHMS_COMPLETE_HH

/** @addtogroup algorithms */  /** @{ */
/**
 * @file   complete.hh
 *
 * Completion algorithm for deterministic and boolean automaton.
 *
 * @see complete(), complete_here(), is_complete()
 */
/** @} */

// INTERFACE: void complete_here(Automaton& a) { return vcsn::complete_here(*a); }
// INTERFACE: void complete_here(GenAutomaton& a) { return vcsn::complete_here(*a); }

// INTERFACE: Automaton complete(const Automaton& a) { return vcsn::complete(*a); }
// INTERFACE: GenAutomaton complete(const GenAutomaton& a) { return vcsn::complete(*a); }

// INTERFACE: bool is_complete(const Automaton& a) { return vcsn::is_complete(*a); }
// INTERFACE: bool is_complete(const GenAutomaton& a) { return vcsn::is_complete(*a); }

# include <vaucanson/design_pattern/element.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

  /**
   * Make the transition function of an automaton total w.r.t alphabet.
   *
   * @note This algorithm works in place.
   *
   * @param a the deterministic and boolean automaton to complete.
   *
   * @see complete(), is_complete()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename T>
  void
  complete_here(Element<A, T>& a);

  /**
   * Make the transition function of an automaton total w.r.t alphabet.
   *
   * @note This algorithm returns a fresh automaton.
   *
   * @param a the deterministic and boolean automaton to complete.
   *
   * @see complete_here(), is_complete()
   * @author Yann Régis-Gianas
   */
  template <typename A, typename T>
  Element<A, T>
  complete(const Element<A, T>& a);

  /**
   * Test if the transition function is complete for each state.
   *
   * @param a The boolean automaton to test.
   *
   * @return true if the transition function of e is complete w.r.t alphabet.
   *
   * @see complete(), complete_here()
   * @author Yann Régis-Gianas
   */
  template <class A, class T>
  bool
  is_complete(const Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/complete.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_COMPLETE_HH
