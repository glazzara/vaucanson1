// thompson.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_THOMPSON_HH
# define VCSN_ALGORITHMS_THOMPSON_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file thompson.hh
 *
 * The thompson automaton.
 *
 * This  file  contains functions  to  build  automata from  rationnal
 * expressions, using thompson algorithm.
 *
 * @see thompson_of()
 */
/** @} */

// INTERFACE: void thompson_of_here(Automaton& a, const Exp& e) { return vcsn::thompson_of(*a, e.value()); }
// INTERFACE: void thompson_of_here(GenAutomaton& a, const Exp& e) { return vcsn::thompson_of(*a, e.value()); }

# include <vaucanson/algebra/concrete/series/rat/exp.hh>
# include <vaucanson/automata/concept/automata.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * The Thompson automaton associated to the krat expression.
   *
   * This  function build  the  automaton associated  to the  rational
   * expression implemented by a krat_exp, using Thompson algorithm.
   *
   * @param out The resulting automaton
   * @param kexp The rational expression
   */
  template<typename A,      typename T,
	   typename Letter, typename Weight>
  void
  thompson_of(Element<A, T>& out, const rat::exp<Letter, Weight>& kexp);

  /**
   * The Thompson automaton associated to the krat expression.
   *
   * This  function build  the  automaton associated  to the  rational
   * expression   implemented   by    a   krat_exp,   using   Thompson
   * algorithm. The kind of returned automaton is a default one.
   *
   * @param exp The rational expression
   */
  template <class AutoType, class S, class T>
  Element<Automata<S>, AutoType>
  thompson_of(const Element<S, T>& exp);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/thompson.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_THOMPSON_HH
