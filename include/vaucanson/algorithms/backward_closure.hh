// backward_closure.hh
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

#ifndef  VCSN_ALGORITHMS_BACKWARD_CLOSURE_HH
# define VCSN_ALGORITHMS_BACKWARD_CLOSURE_HH

/**
 * @file   backward_closure.hh
 * @brief  Backward closure algorithm.
 */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  /** 
   * Complete in place the given automaton to make it close over
   * epsilon transition. 
   * 
   * @param a the weighted automaton to close.
   *
   * @see forward_closure_here
   * @see forward_closure
   * @see backward_closure_here
   */
  template<typename A, typename T>
  void
  backward_closure_here(Element<A, T>& a);

  /** 
   * Complete the given automaton into a copy to make it close over
   * epsilon transition. 
   *
   * @param a the weighted automaton to close.
   *
   * @see forward_closure
   * @see forward_closure_here
   * @see backward_closure_here
   */
  template<typename A, typename T>
  Element<A, T>
  backward_closure(const Element<A, T>& a);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/backward_closure.hxx>

#endif // VCSN_ALGORITHMS_BACKWARD_CLOSURE_HH
