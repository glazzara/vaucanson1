// sub-normalize.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_SUB_NORMALIZE_HH
# define VCSN_ALGORITHMS_SUB_NORMALIZE_HH

/**
 * @file sub-normalize.hh
 *
 * Sub-normalization algorithm for FMP transducers.
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/automata/concept/copy.hh>
# include <vaucanson/algorithms/cut_up.hh>
# include <vector>

namespace vcsn
{
  /**
   * @brief Sub-normalize a FMP transducer.
   *
   * @arg a	Input automaton.
   * @return	Sub-normalized automaton.
   *
   */
  template <class S, class T>
  Element<S, T>
  sub_normalize(const Element<S, T>& a);

  /**
   * @brief Sub-normalize a FMP transducer.
   *
   * @arg a	Input automaton.
   * @arg res	Output automaton.
   *
   */
  template <class S, class T1, class T2>
  void
  sub_normalize(const Element<S, T1>& a, Element<S, T2>& res);

  /**
   * @brief Check if a FMP transducer is sub-normalized.
   *
   * @arg a	Input automaton.
   * @return	boolean.
   *
   */
  template <class S, class T>
  bool is_sub_normalized(const Element<S, T>& a);

} // ! vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/sub_normalize.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_SUB_NORMALIZE_HH