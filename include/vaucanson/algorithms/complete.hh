// complete.hh
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

#ifndef VCSN_ALGORITHMS_COMPLETE_HH
# define VCSN_ALGORITHMS_COMPLETE_HH

# include <vaucanson/automata/concept/automata_base.hh>

/**
 * @file   complete.hh
 * @brief  Completion algorithm for deterministic and boolean automaton.
 */

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  /** 
   * Make the transition function of an automaton total w.r.t alphabet.
   * Work in place.
   *
   * @param a the deterministic and boolean automaton to complete.
   * @see complete.
   * @see is_complete.
   */ 
  template <typename A, typename T>
  void
  complete_here(Element<A, T>& a);

  /** 
   * Make the transition function of an automaton total w.r.t alphabet.
   * Return a fresh automaton.
   *
   * @param a the deterministic and boolean automaton to complete.
   * @see complete_here.
   * @see is_complete.
   */ 
  template <typename A, typename T>
  Element<A, T>
  complete(const Element<A, T>&);

  /** 
   * Test if the transition function is complete for each state.
   * 
   * @param a the boolean automaton to test.
   * @return true is the transition function of e is complete w.r.t alphabet.
   * @see complete.
   * @see complete_here.
   */
  template <class A, class T>
  bool
  is_complete(const Element<A, T>& e);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/complete.hxx>

#endif // VCSN_ALGORITHMS_COMPLETE_HH
