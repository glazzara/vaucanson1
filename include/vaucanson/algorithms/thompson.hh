// thompson.hh
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

#ifndef VCSN_ALGORITHMS_THOMPSON_HH
# define VCSN_ALGORITHMS_THOMPSON_HH

/***
 * @file thompson.hh
 * @brief The thompson automaton.
 *
 * This file contains functions to build automata from rationnal expressions,
 * using thompson algorithm.
 */

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * @brief The Thompson automaton associated to the krat expression.
   *
   * This function build the automaton associated to the rationnal expression
   * implemented by a krat_exp, using Thompson algorithm.
   *
   * @param out The resulting automaton
   * @param kexp The rationnal expression
   */
  template<typename A,      typename T, 
	   typename Letter, typename Weight>
  void
  thompson_of(Element<A, T>& out, const rat::exp<Letter, Weight>& kexp);
  
  /**
   * @brief The Thompson automaton associated to the krat expression.
   *
   * This function build the automaton associated to the rationnal expression
   * implemented by a krat_exp, using Thompson algorithm. The kind of returned
   * automaton is a default one.
   * 
   * @param exp The rationnal expression
   */
  template <class AutoType, class S, class T>
  Element<Automata<S>, AutoType>
  thompson_of(const Element<S, T>& exp)

  /** @} */

} // vcsn

# include <vaucanson/algorithms/thompson.hxx>

#endif // VCSN_ALGORITHMS_THOMPSON_HH
