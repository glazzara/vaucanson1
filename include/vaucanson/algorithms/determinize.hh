// determinize.hh
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

#ifndef VCSN_ALGORITHMS_DETERMINIZE_HH
# define VCSN_ALGORITHMS_DETERMINIZE_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn {

  /**
   * @file   determinize.hh
   * @author Yann Régis-Gianas <yann@lrde.epita.fr>
   * @date   Tue Jun 24 19:13:10 2003
   * 
   * @brief  This file provides the determinization algorithm for boolean automata.
   * 
   */


  /*! \addtogroup algorithms */  /* @{ */

  //! Return a fresh determinist automaton associated to the input.

  /** 
   * @brief Returns the determinized of a boolean automaton.
   * 
   * @param a the boolean automaton to determinize.
   * 
   * @return a fresh boolean automaton that is the determinization of 'a'.
   */
  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a);

  /** 
   * @brief Test if an automaton is deterministic.
   * 
   * @param a a boolean automaton.
   * 
   * @return true if 'a' is deterministic.
   */
  template<typename A, typename T>
  bool
  is_deterministic(const Element<A, T>& a);
  
  /*! @} */

} // vcsn

# include <vaucanson/algorithms/determinize.hxx>

#endif // VCSN_ALGORITHMS_DETERMINIZE_HH

