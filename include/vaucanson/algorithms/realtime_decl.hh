// realtime_decl.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_REALTIME_DECL_HH
# define VCSN_ALGORITHMS_REALTIME_DECL_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file  realtime_decl.hh
 *
 * Declaration of the realtime() function.
 *
 * Actually,  the  realtime()  function  may appear  in  two  headers:
 * realtime.hh  and krat_exp_realtime.hh. In  both header  files, this
 * function has the same prototype, but different meanings, and expect
 * to be called with different types.
 *
 * This file contains the unique declaration of realtime(), which will
 * then do  the dispatch onto  the right do_realtime() in  function of
 * its parameter.
 *
 * *Please note that you should not include this file directly. Use
 * realtime.hh or krat_exp_realtime.hh*.
 *
 * @see realtime(), realtime.hh, krat_exp_realtime.hh
 */
/** @} */

# include <vaucanson/design_pattern/element.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Calls the do_realtime function for rational expression or automata.
   *
   * This function  is a wrapper  which select a realtime  either from
   * realtime.hh or from krat_exp_realtime.hh.
   *
   * When called  upon an automaton, this function  uses the functions
   * declared in realtime.hh to make this automaton realtime using the
   * forward_realtime() algorithm.
   *
   * When  called   with  a  rational  expression,   a  function  from
   * krat_exp_realtime.hh   is  selected  to   expand  words   in  the
   * expression as a product of a letter.
   *
   * @see krat_exp_realtime.hh, realtime.hh
   */
  template<typename S, typename T>
  Element<S, T>
  realtime(const Element<S, T>& e);

  /**
   * Calls the do_realtime_here function for rational expression or automata.
   *
   * This function  is a wrapper  which select a realtime  either from
   * realtime.hh or from krat_exp_realtime.hh.
   *
   * It behaves exactly as realtime(), but do the operation in place.
   *
   * @see realtime()
   */
  template <typename S, typename T>
  void
  realtime_here(Element<S, T>& e);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/realtime_decl.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_REALTIME_DECL_HH
