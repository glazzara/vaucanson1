// minimization_hopcroft.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HH
# define VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   minimization_hopcroft.hh
 *
 * This file provides minimization and quotient algorithms.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 21:08:54 2003
 *
 * @see minimization_hopcroft(), quotient()
 */
/** @} */

// INTERFACE: Automaton minimization_hopcroft(const Automaton& a) { return vcsn::minimization_hopcroft(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {


  /** @addtogroup algorithms *//** @{ */

  /**
   * Return the minimal automaton using the hopcroft algorithm.
   *
   * @param a The deterministic Boolean automaton to minimize.
   *
   * @return A fresh automaton that is the canonical minimal automaton of 'a'.
   */
  template<typename A, typename T>
  Element<A, T>
  minimization_hopcroft(const Element<A, T>& a);

  /**
   * Return the quotient of a non deterministic acceptor.
   *
   * @param a The Boolean automaton to minimize.
   *
   * @return A fresh automaton that is the quotient of 'a'.
   */
  template<typename A, typename T>
  Element<A, T>
  quotient(const Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/minimization_hopcroft.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HH
