// sub_automaton.hh
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

#ifndef VCSN_ALGORITHMS_SUB_AUTOMATON_HH
# define VCSN_ALGORITHMS_SUB_AUTOMATON_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /**
   * @file   sub_automaton.hh
   * @author Yann Régis-Gianas <yann@lrde.epita.fr>
   * @date   Tue Jun 24 20:37:59 2003
   * 
   * @brief  This file provides the extraction of sub automaton.
   * 
   * 
   */


  /*! \addtogroup algorithms */  /* @{ */
 
  /** 
   *  @brief Returns a fresh automaton that is the sub-automaton defined by a set.
   * 
   * @param a the automaton into which we have to extract the sub-automaton.
   * @param s the set of states of the sub-automaton included in the state of 'a'.
   * @param check_states a flag to enable/disable the inclusion checking.
   * @see sub_automaton_here.
   * @return a fresh sub-automaton.
   */
  template<typename A, typename T, typename StatesSet>
  Element<A, T> 
  sub_automaton(const Element<A, T>& a, const StatesSet& s, 
		bool check_states = true);

  /** 
   *  @brief Select a sub-automaton into a given automaton.
   * 
   * @param a the automaton into which we have to extract the sub-automaton.
   * @param s the set of states of the sub-automaton included in the state of 'a'.
   * @param check_states a flag to enable/disable the inclusion checking.
   * @see sub_automaton.
   */
  template<typename A, typename T, typename StatesSet>
  void sub_automaton_here(Element<A, T>& a, const StatesSet& s, 
			  bool check_states = true);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/sub_automaton.hxx>

#endif // VCSN_ALGORITHMS_SUB_AUTOMATON_HH
