// fmp_to_transducer.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_FMP_TO_TRANSDUCER_HH
# define VCSN_ALGORITHMS_FMP_TO_TRANSDUCER_HH

# include <vaucanson/design_pattern/design_pattern.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   fmp_to_transducer.hh
 *
 * This file provides a transformation function that computes
 * the equivalent transducer of a FMP automaton.
 *
 * @author Robert Bigaignon <robert.bigaignon@lrde.epita.fr>
 * @date   Mon Mar 16 16:15:15 2005
 *
 * @see fmp_to_trans()
 */
/** @} */

namespace vcsn
{
  /** @addtogroup algorithms *//** @{ */

  /// @name Transducer to FMP automaton algorithm.
  //@{
  /// Compute the equivalent transducer of a FMP automaton.
  /// Please note that for the moment this function works
  /// only if the support of each edge is finite.
  ///
  /// Algorithm :
  /// If the FMP contains edges with "complex" expression (E),
  ///    i.e. infinite support,
  ///    then Thompson of E.
  /// With the resulting automaton apply a conversion.
  ///    i.e. (a,x) -> a|x

  template<typename S, typename T,
	   typename SS, typename TT>
  Element<SS, TT>&
  fmp_to_trans(const Element<S, T>& fmp,
	       Element<SS, TT>& res);
  //@}

  /** @} */
}

# include <vaucanson/algorithms/fmp_to_transducer.hxx>

#endif // !VCSN_ALGORITHMS_FMP_TO_TRANSDUCER_HH
