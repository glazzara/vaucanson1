// closure.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
//
#ifndef VCSN_ALGORITHMS_CLOSURE_HH
# define VCSN_ALGORITHMS_CLOSURE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   closure.hh
 *
 * This files declares the backward and forward closure algorithm.
 *
 * @see backward_closure(), backward_closure_here(), forward_closure(),
 * forward_closure_here(), closure(), closure_here()
 */
/** @} */


// INTERFACE: void forward_closure_here(Automaton& a) { return vcsn::forward_closure_here(*a); }
// INTERFACE: void forward_closure_here(GenAutomaton& a) { return vcsn::forward_closure_here(*a); }

// INTERFACE: Automaton forward_closure(const Automaton& a) { return vcsn::forward_closure(*a); }
// INTERFACE: GenAutomaton forward_closure(const GenAutomaton& a) { return vcsn::forward_closure(*a); }

// INTERFACE: void backward_closure_here(Automaton& a) { return vcsn::backward_closure_here(*a); }
// INTERFACE: void backward_closure_here(GenAutomaton& a) { return vcsn::backward_closure_here(*a); }

// INTERFACE: Automaton backward_closure(const Automaton& a) { return vcsn::backward_closure(*a); }
// INTERFACE: GenAutomaton backward_closure(const GenAutomaton& a) { return vcsn::backward_closure(*a); }

// INTERFACE: void closure_here(Automaton& a) { return vcsn::closure_here(*a); }
// INTERFACE: void closure_here(GenAutomaton& a) { return vcsn::closure_here(*a); }

// INTERFACE: Automaton closure(const Automaton& a) { return vcsn::closure(*a); }
// INTERFACE: GenAutomaton closure(const GenAutomaton& a) { return vcsn::closure(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * In place closure of an automaton (default is backward closure).
   *
   * This algorithm completes in place  the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   * @param bck The type of closure to call (true is backward, false is
   * forward).
   *
   * @see closure(), forward_closure(), forward_closure_here(),
   * backward_closure(), backward_closure_here()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  void
  closure_here(Element<A, T>& a, bool bck = true);


  /**
   * Closure of an automaton (default is backward closure).
   *
   * This algorithm completes the given  automaton into a copy to make
   * it close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   * @param bck The type of closure to call (true is backward, false is
   * forward).
   *
   * @see closure_here(), forward_closure(), forward_closure_here(),
   * backward_closure(), backward_closure_here()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  Element<A, T>
  closure(const Element<A, T>& a, bool bck = true);


  /**
   * In place backward closure of an automaton.
   *
   * This algorithm completes in place  the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see backward_closure(), closure_here(), closure(),
   * forward_closure_here(), forward_closure()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  void
  backward_closure_here(Element<A, T>& a);


  /**
   * Backward closure of an automaton.
   *
   * This algorithm completes in place  the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see backward_closure_here(), closure(), closure_here(),
   * forward_closure(), forward_closure_here()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  Element<A, T>
  backward_closure(const Element<A, T>& a);


  /**
   * In place forward closure of an automaton.
   *
   * This algorithm completes in place  the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see forward_closure(), closure_here(), closure(),
   * backward_closure_here(), backward_closure()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  void
  forward_closure_here(Element<A, T>& a);


  /**
   * Forward closure of an automaton.
   *
   * This algorithm completes in place  the given automaton to make it
   * close over epsilon transition.
   *
   * It is based on the Floyd/McNaughton/Yamada algorithm.
   *
   * @param a The weighted automaton to close.
   *
   * @see forward_closure_here(), closure(), closure_here(),
   * backward_closure(), backward_closure_here()
   * @author Sylvain Lombardy
   */
  template<typename A, typename T>
  Element<A, T>
  forward_closure(const Element<A, T>& a);

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/closure.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_CLOSURE_HH
