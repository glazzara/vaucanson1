// sum.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_SUM_HH
# define VCSN_ALGORITHMS_SUM_HH

/**
 * @file sum.hh
 * 
 * @brief Summing of automata.
 * 
 * This file contains functions to sum two automata.
 */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief In place summing of two automata.
   * 
   * This function adds states and edges of an automaton to states and edges
   * of a second automaton.
   *
   * @param lhs Destination of the summing
   * @param rhs Source of summing
   *
   * @see sum
   */
  template<typename A, typename T, typename U>
  void 
  sum_here(Element<A, T>& lhs, const Element<A, U>& rhs);

  /**
   * @brief Summing of two automata.
   *
   * This function returns the fresh union of two automata. It put edges and
   * states of the two automata together, and create a news one with the
   * result.
   *
   * @param lhs First automaton to sum
   * @param rhs Second automaton to sum
   *
   * @see sum_here
   */
  template<typename A, typename T, typename U>
  Element<A, T> 
  sum(const Element<A, T>& lhs, const Element<A, U>& rhs);

  /** @} */

} // vcsn

# include <vaucanson/algorithms/sum.hxx>

#endif // VCSN_ALGORITHMS_SUM_HH
