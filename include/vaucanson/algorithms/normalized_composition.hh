// normalized_composition.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HH
# define VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HH

# include <vaucanson/automata/concept/automata_base.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file normalized_composition.hh
 *
 * @brief Composition for normalized and sub-normalized transducers
 * seen as automata over a free monoid product.
 *
 * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
 *
 * @see normalized_composition()
 */
/** @} */

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

 /**
   * Composition for normalized and sub-normalized transducers, seen
   * as automata over a free monoid product.
   *
   * @param  lhs The left hand side transducer.
   * @param  rhs The right hand side transducer.
   * @param  ret The result transducer.
   *
   */

  template <typename S, typename T>
  void
  normalized_composition(const Element<S, T>& lhs,
			 const Element<S, T>& rhs,
			 Element<S, T>& ret);

 /**
   * Composition for normalized and sub-normalized transducers, seen
   * as automata over a free monoid product.
   *
   * @param  lhs The left hand side transducer.
   * @param  rhs The right hand side transducer.
   *
   */

  template <typename S, typename T>
  Element<S, T>
  normalized_composition(const Element<S, T>& lhs,
			 const Element<S, T>& rhs);


  /** @} */

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/normalized_composition.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // !VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HH
