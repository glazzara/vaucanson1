// forward_realtime.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_FORWARD_REALTIME_HH
# define VCSN_ALGORITHMS_FORWARD_REALTIME_HH

/**
 * @file forward_realtime.hh
 * @brief Algorithms to make an automaton realtime.
 *
 * This file contains algorithms to build realtime automaton. These algorithms
 * use the forward version of closure.
 */


# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */
  
  /**
   * @brief In place modification of the automaton to make it realtime.
   *
   * This function make an automaton realtime, using forward version of closure
   * for building.
   *
   * @param a The automaton to make realtime.
   *
   * @see realtime
   * @see forward_realtime
   * @see backward_realtime_here
   */
  // INTERFACE: void forward_realtime_here(Automaton& a) { return vcsn::forward_realtime_here(*a); }
  // INTERFACE: void forward_realtime_here(GenAutomaton& a) { return vcsn::forward_realtime_here(*a); }
  template<typename A, typename T>
  void
  forward_realtime_here(Element<A, T>& a);

  /**
   * @brief Returns a fresh realtime automaton.
   *
   * This fonction build a fresh realtime automaton from those given, using
   * forward version of closure.
   *
   * @param a The automaton to make realtime.
   *
   * @see realtime
   * @see forward_realtime_here
   * @see backward_realtime
   */
  // INTERFACE: Automaton forward_realtime(const Automaton& a) { return vcsn::forward_realtime(*a); }
  // INTERFACE: GenAutomaton forward_realtime(const GenAutomaton& a) { return vcsn::forward_realtime(*a); }
  template<typename A, typename T>
  Element<A, T>
  forward_realtime(const Element<A, T>& a);
  
  /** @} */
  
} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algorithms/forward_realtime.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_ALGORITHMS_FORWARD_REALTIME_HH
