// realtime_to_fmp.hh: this file is part of the Vaucanson project.
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
//    * Robert Bigaignon <robert.bigaignon@lrde.epita.fr>
//

#ifndef VCSN_ALGORITHMS_REALTIME_TO_FMP_HH
# define VCSN_ALGORITHMS_REALTIME_TO_FMP_HH

# include <vaucanson/design_pattern/design_pattern.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   realtime_to_fmp.hh
 *
 * This file provides a transformation function that computes
 * the equivalent FMP automaton of a tranducer.
 *
 * @author Robert Bigaignon <robert.bigaignon@lrde.epita.fr>
 * @date   Mon Mar 16 16:15:15 2005
 *
 * @see realtime_to_fmp()
 */
/** @} */

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

  /// @name Realtime transducer to FMP automaton algorithm
  //@{
  /// Compute the equivalent FMP automaton of a transducer.
  /// Please note that for the moment this function works
  /// only if the support of each edge is finite.
  ///
  /// Preconditions :
  /// The transducer is realtime.
  /// The weight of each edge must have a finite support.
  template<typename S, typename T,
	   typename SS, typename TT>
  Element<SS, TT>&
  realtime_to_fmp(const Element<S, T>& trans,
		  Element<SS, TT>& res);

  //@}

  /** @} */
}

# include <vaucanson/algorithms/realtime_to_fmp.hxx>

#endif // !VCSN_ALGORITHMS_REALTIME_TO_FMP_HH
