// derivatives_automaton.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HH
# define VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>

namespace vcsn {

  /**
   * @file   derivatives_automaton.hh
   * @author Yann Régis-Gianas <yann@lrde.epita.fr>
   * @date   Tue Jun 24 17:58:19 2003
   * 
   * @brief  This file provides a converter from expression to automaton based on derivatives.
   * 
   */


  /*! \addtogroup algorithms */  /* @{ */

  //! Convert a krat expression into an automaton using Brzozowski construction.

  /** 
   * @brief Convert a krat expression into an automaton using derivatives.
   * 
   * @param a an automaton to store the results.
   * @param e the expression to convert.
   *
   * @note 'a' is generally an empty automaton. It enables the choice
   * of the series to work with. Thus, the series can be different
   * from the expresion ones.
   */
  template <typename A, typename T, typename Exp>
  void
  derivatives_automaton(Element<A, T>& a, const Exp& e);
  
  /** 
   * @brief Convert a krat expression into an automaton using derivatives.
   * 
   * @param e the expression to convert.
   * 
   * @return a fresh automaton which recognizes the language denoted by 'e'.
   *
   * @note The series of the expression are used to define the automaton.
   */
  template <typename A, typename T, typename Exp>
  Element<A, T>
  derivatives_automaton(const Exp& e);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/derivatives_automaton.hxx>

#endif // VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HH
