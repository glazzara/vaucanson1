// minimization_moore.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_ALGORITHMS_MINIMIZATION_MOORE_HH
# define VCSN_ALGORITHMS_MINIMIZATION_MOORE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file minimization_moore.hh
 *
 * This file containes the declaration of minimization_moore().
 *
 * @see minimization_moore(), minimization_moore_here()
 */
/** @} */

// INTERFACE: Automaton minimization_moore(const Automaton& a) { return vcsn::minimization_moore(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Returns the minimal deterministic automaton associated to the input one.
   *
   * Use   Moore's  algorithm  to   compute  the   minimal  equivalent
   * deterministic  automaton.  The complexity  of  this algorithm  is
   * O(n2). See  minimize_hopcroft for O(nlogn).
   *
   * @see http://cs.engr.uky.edu/~lewis/essays/compilers/min-fa.html
   * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
   * @bug Put the precondition.
   */
  template<typename A, typename T>
  Element<A, T>
  minimization_moore(const Element<A, T>& a);

  /**
   * Minimalize the deterministic input automaton.
   *
   * Use Moore's algorithm to minimalize (in place) the input
   * automaton. The complexity of this algorithm is O(n2). See
   * minimize_hopcroft for O(nlogn).
   *
   * @see http://cs.engr.uky.edu/~lewis/essays/compilers/min-fa.html
   * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
   */
  template<typename A, typename T>
  void
  minimization_moore_here(Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/minimization_moore.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_MINIMIZATION_MOORE_HH
