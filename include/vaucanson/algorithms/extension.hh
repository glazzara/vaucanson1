// extension.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_EXTENSION_HH
#define  VCSN_ALGORITHMS_EXTENSION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file extension.hh
 *
 * This file contains declarations for extension().
 *
 * @see extension()
 */
/** @} */

#include <vaucanson/automata/concept/automata.hh>
#include <vaucanson/automata/concept/transducer.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Extend an automaton to a transducer.
   *
   * Extend  an automaton to  a transducer  whose multiplicity  is the
   * series of the automaton.
   */
  template <typename S,
	    typename T>
  typename identity_transducer_helper<S, T>::ret
  extension(const Element<S, T>&);


  /**
   * Extend an automaton to a transducer.
   *
   * Extend  an automaton  to a  transducer whose  set is  the  one of
   * another transducer passed in  the second argument. This extension
   * is required if  we want to make a product of  an automaton with a
   * transducer.  If  this  is  not  the case,  we  need  simply  call
   * extension(automaton_t) above.
   */
  template <typename SA, typename TA,
	    typename ST, typename TT>
  Element<ST, TT>
  extension(const Element<SA, TA>&,
	    const Element<ST, TT>&);

  /** @} */

}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/extension.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif  // VCSN_ALGORITHMS_EXTENSION_HH
