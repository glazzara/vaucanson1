// accessible.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_ACCESSIBLE_HH
# define VCSN_ALGORITHMS_ACCESSIBLE_HH

/**
 * @file accessible.hh
 *
 * @brief Algorithms for accessible/coaccessible states computation.
 *
 * This file contains a few algorithms to get accessible or coaccessible
 * states from an automaton.
 *
 * @see accessible_states(), accessible(), accessible_here(),
 *      coaccessible_states(), coaccessible(), coaccessible_here()
 */

# include <vaucanson/automata/concept/automata_base.hh>
# include <set>

namespace vcsn {

  /** @addtogroup algorithms */  /* @{ */

  /**
   * @brief Return accessible states.
   *
   * This functions returns the accessible states set of its input automaton.
   *
   * @param a The input automaton.
   *
   * @see accessible(), coaccessible(), coaccessible_states()
   */
  template<typename A, typename T>
  std::set<hstate_t>
  accessible_states(const Element<A, T>& a);

  /**
   * @brief Extract the sub-automaton composed of accessible states.
   *
   * This function returns a fresh sub-automaton of its input
   * containing only accessible states.
   *
   * @param a The input automaton.
   *
   * @see accessible_here(), accessible_states(), coaccessible(),
   *      coaccessible_states()
   */
  template<typename A, typename T>
  Element<A, T>
  accessible(const Element<A, T>& a);

  /**
   * @brief In-place extract the sub-automaton of accessible states.
   *
   * This function computes the sub-autmaton of accessible states from
   * its input automaton. The operation is performed in-place.
   *
   * @param a An in/out parameter which contains the automaton to work on as
   *          input and the result as output.
   *
   * @see accessible(), accessible_states(), coaccessible(), coaccessible_states()
   */
  template<typename A, typename T>
  void
  accessible_here(Element<A, T>& a);
  
  /**
   * @brief Return co-accessible states.
   *
   * This functions returns the co-accessible states set of its input automaton,
   * i.e. states which are accessible from final states.
   *
   * @param a The input automaton.
   *
   * @see coaccessible(), accessible(), accessible_states()
   */
  template<typename A, typename T>
  std::set<hstate_t>
  coaccessible_states(const Element<A, T>& a);
  
  /**
   * @brief Extract the sub-automaton composed of co-accessible states.
   *
   * This function returns a fresh sub-automaton of its input
   * containing only co-accessible states, i.e. states which are accessible
   * from final states.
   *
   * @param a The input automaton.
   *
   * @see coaccessible_here(), coaccessible_states(), accessible(),
   *      accessible_states()
   */
  template<typename A, typename T>
  Element<A, T>
  coaccessible(const Element<A, T>& a);
  
  /**
   * @brief In-place extract the sub-automaton of co-accessible states.
   *
   * This function computes the sub-autmaton of co-accessible states from
   * its input automaton. The operation is performed in-place.
   *
   * @param a An in/out parameter which contains the automaton to work on as
   *          input and the result as output.
   *
   * @see coaccessible(), coaccessible_states(), accessible(), accessible_states()
   */
  template<typename A, typename T>
  void
  coaccessible_here(Element<A, T>& a);

  /** @} */
  
} // vcsn

# include <vaucanson/algorithms/accessible.hxx>

#endif // VCSN_ALGORITHMS_ACCESSIBLE_HH
