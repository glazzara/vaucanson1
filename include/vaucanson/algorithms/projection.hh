// projection.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_PROJECTION_HH
# define VCSN_ALGORITHMS_PROJECTION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file projection.hh
 *
 * Undocumented stuff.
 *
 * @bug FIXME: Document!
 */
/** @} */

#include <vaucanson/automata/concept/transducer.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  // Erase input.
  template <class ST, class TT,
	    class SA, class TA>
  void
  output_projection(const Element<ST, TT>&,
		    Element<SA, TA>&);

  template <class S, class T>
  typename output_projection_helper<S, T>::ret
  output_projection(const Element<S, T>&,
		    std::map<hstate_t, hstate_t>& m);

  template <class S, class T>
  typename output_projection_helper<S, T>::ret
  output_projection(const Element<S, T>&);

  /** @} */

}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/projection.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_PROJECTION_HH
