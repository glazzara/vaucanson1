// forward_closure.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_FORWARD_CLOSURE_HH
# define VCSN_ALGORITHMS_FORWARD_CLOSURE_HH

/**
 * @file   forward_closure.hh
 * @brief  Forward closure algorithm.
 */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  /** 
   * Complete the given automaton into a copy to make it close over
   * epsilon transition. 
   *
   * @param a the weighted automaton to close.
   *
   * @see forward_closure
   * @see backward_closure
   * @see backward_closure_here
   */
  template<typename A, typename T>
  void
  forward_closure_here(Element<A, T>& a);

  /** 
   * Complete the given automaton into a copy to make it close over
   * epsilon transition. 
   *
   * @param a the weighted automaton to close.
   *
   * @see forward_closure
   * @see backward_closure
   * @see backward_closure_here
   */
  template<typename A, typename T>
  Element<A, T>
  forward_closure(const Element<A, T>& a);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/forward_closure.hxx>

#endif // VCSN_ALGORITHMS_FORWARD_CLOSURE_HH
