// evaluation.hh: this file is part of the Vaucanson project.
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
#ifndef VAUCANSON_ALGORITHMS_EVALUATION_HH
# define VAUCANSON_ALGORITHMS_EVALUATION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file evaluation.hh
 *
 * Undocumented stuff.
 *
 * @see evaluation()
 * @bug FIXME: Document!
 */
/** @} */

#include<vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Evaluate for a "letterized" automaton and a realtime transducer.
  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename SARET, typename TARET>
  void
  evaluation(const Element<SA, TA>&,
	     const Element<ST, TT>&,
	     Element<SARET, TARET>&);

  /// @name Evalutation algorithm's internals
  //@{
  /// The following functions are absolutely not for public calls.
  template<typename SE, typename TE,
	   typename ST, typename TT,
	   typename M>
  void
  partial_evaluation(const Element<SE, TE>& exp,
		     const Element<ST, TT>& trans,
		     M& state_exp_pair);

  template<typename SA, typename TA,
	   typename M>
  void
  partial_elimination(const Element<SA, TA>& a,
		      M& state_exp_pair);

  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename M>
  void
  partial_1(const Element<SA, TA>&,
	    const Element<ST, TT>&, M&);

  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename Exp>
  void
  partial_2(const Element<SA, TA>&,
	    const Element<ST, TT>&,
	    const hstate_t, Exp&);

  template<typename SA, typename TA,
	   typename ST, typename TT,
	   typename M>
  void
  partial_3(const Element<SA, TA>&,
	    const Element<ST, TT>&,
	    const hstate_t, M&);

  //@}

  /** @} */

}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include<vaucanson/algorithms/evaluation.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VAUCANSON_ALGORITHMS_EVALUATION_HH
