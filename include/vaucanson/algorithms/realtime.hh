// realtime.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_REALTIME_HH
# define VCSN_ALGORITHMS_REALTIME_HH

/**
 * @file  realtime.hh
 * @brief General algorithms concerning realtime aspect of automata.
 *
 * This file contains algorithms concerning realtime aspect of automata, i.e.
 * presence or absence of epsilon transitions in the automaton.
 */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Enum to indicate which kind of realtime algorithms must be used.
  enum realtime_type { forward, backward };
  
  /**
   * @brief Test whether an automaton is realtime.
   *
   * This function returns true if the input automaton is realtime.
   *
   * @param a The automaton to test.
   *
   * @see realtime
   */
  // INTERFACE: bool is_realtime(Automaton& a) { return vcsn::is_realtime(*a); }
  // INTERFACE: bool is_realtime(GenAutomaton& a) { return vcsn::is_realtime(*a); }
  template<typename A, typename T>
  bool
  is_realtime(const Element<A, T>& a);

  /**
   * @brief In place modification of the automaton to make it realtime.
   *
   * This algorithm makes an automaton realtime. It calls
   * @c forward_realtime or @c backward_realtime according to type given.
   * The type may not be precised, it is the @c forward_realtime which is
   * used by default.
   *
   * @param a The automaton to make realtime.
   * @param type The type of algorithm used.
   *
   * @see realtime
   * @see forward_realtime_here
   * @see backward_realtime_here
   */
  template<typename A, typename T>
  void
  realtime_here(Element<A, T>& a, realtime_type type = forward);

  /**
   * @brief Returns a fresh realtime automaton.
   *
   * As @c realtime_here, it build a realtime automaton, but it returns a new one
   * instead of changing those given.
   *
   * @param a The automaton to make realtime.
   * @param type The type of algorithm used.
   * 
   * @see realtime_here
   * @see forward_realtime
   * @see backward_realtime
   */
  template<typename A, typename T>
  Element<A, T>
  realtime(const Element<A, T>& a, realtime_type type = forward);

  /** @} */
  
} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algorithms/realtime.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_ALGORITHMS_REALTIME_HH
