// derivatives_automaton.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HH
# define VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   derivatives_automaton.hh
 *
 * Provides a converter from expression to automaton based on derivatives.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 17:58:19 2003
 *
 * @see derivatives_automaton()
 */
/** @} */

// INTERFACE: void derivatives_automaton(Automaton& a, const Exp& e) { return vcsn::derivatives_automaton(*a, e); }
// INTERFACE: void derivatives_automaton(GenAutomaton& a, const Exp& e) { return vcsn::derivatives_automaton(*a, e); }

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Convert a krat expression into an automaton using derivatives.
   *
   * This algorithm produces an automaton from an expression using the
   * Brzozowski  construction.   This  construction involves  multiple
   * derivations on the initial expression.
   *
   * @param a An automaton to store the results.
   * @param e The expression to convert.
   *
   * @note 'a' is generally an  empty automaton. It enables the choice
   * of the  series to  work with. Thus,  the series can  be different
   * from the expresion ones.
   */
  template <typename A, typename T, typename Exp>
  void
  derivatives_automaton(Element<A, T>& a, const Exp& e);

  /**
   * Convert a krat expression into an automaton using derivatives.
   *
   * @param e The expression to convert.
   *
   * @return A fresh automaton which recognizes the language denoted by 'e'.
   *
   * @note The series of the expression are used to define the automaton.
   */
  template <typename A, typename T, typename Exp>
  Element<A, T>
  derivatives_automaton(const Exp& e);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/derivatives_automaton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HH
