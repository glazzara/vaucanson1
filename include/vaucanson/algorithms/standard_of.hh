// standard_of.hh
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

#ifndef VCSN_ALGORITHMS_STANDARD_OF_HH
# define VCSN_ALGORITHMS_STANDARD_OF_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>

namespace vcsn {

  /**
   * @file   standard_of.hh
   * @author Yann Régis-Gianas <yann@lrde.epita.fr>
   * @date   Tue Jun 24 20:46:53 2003
   * 
   * @brief  This file provides a converter from expression to standard automaton.
   * 
   */


  /*! \addtogroup algorithms */  /* @{ */

  /** 
   * @brief Convert a rational expression into a standard automaton.
   * 
   * @param  e the expression to convert.
   * @param  a the automaton to store the result.
   *
   * @note the automaton is used to enable the use of different series
   * from the expression.
   */
  template <typename A, typename T, typename Exp>
  void
  standard_of(Element<A, T>& a, const Exp& e);

  /** 
   * @brief Convert a rational expression into a standard automaton.
   * 
   * @param  e the expression to convert.
   * @return a standard automaton.
   * @note the automaton is defined using the series of the expression.
   */
  template <typename A, typename T, typename Exp>
  Element<A, T>
  standard_of(const Exp& e);
  
  /*! @} */

} // vcsn

# include <vaucanson/algorithms/standard_of.hxx>

#endif // VCSN_ALGORITHMS_STANDARD_OF_HH
