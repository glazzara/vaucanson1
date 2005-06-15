// projections_fmp.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_PROJECTIONS_FMP_HH
# define VCSN_ALGORITHMS_PROJECTIONS_FMP_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file projections_fmp.hh
 *
 * @brief Domain and Image projection for transducers seen as automata
 * over a free monoid product.
 *
 * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
 */
/** @} */

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algebra/implementation/free_monoid/words.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/series/series.hh>

namespace vcsn
{
  /*-------.
  | Domain |
  `-------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  domain(const Element<S,T>& aut, Element<S2, T2>& res);

  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  domain(const Element<S,T>& aut);


  /*------.
  | Image |
  `------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  image(const Element<S,T>& aut, Element<S2, T2>& res);

  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  image(const Element<S,T>& aut);


  /*---------.
  | Identity |
  `---------*/

  template <typename S, typename S2, typename T, typename T2>
  void
  identity(const Element<S,T>& aut, Element<S2, T2>& res);

  template <typename S, typename S2, typename T, typename T2>
  Element<S2, T2>
  identity(const Element<S,T>& aut);

} // End of namespace vcsn.


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/projections_fmp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_PROJECTIONS_FMP_HH
