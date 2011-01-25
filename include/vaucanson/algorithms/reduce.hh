// reduce.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

#ifndef VCSN_ALGORITHMS_REDUCE_HH
# define VCSN_ALGORITHMS_REDUCE_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/misc/direction.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   reduce.hh
 *
 * This files declares the reduce algorithm.
 *
 * @see reduce(), semi_reduce()
 */
/** @} */

// INTERFACE: Automaton reduce(const Automaton& a, vcsn::misc::direction_type dir) { return vcsn::reduce(*a); }

// INTERFACE: Automaton semi_reduce(const Automaton& a) { return vcsn::semi_reduce(*a); }

namespace vcsn {

  /**
   * Reduce of an automaton (default right_left)
   *
   * This algorithm computes the reduce representation of an automaton with
   * weights in a division ring.
   *
   * A technical report about this algorithm is available here :
   * http://www.lrde.epita.fr/cgi-bin/twiki/view/Publications/200901-Seminar-Delmon
   * Proof and explanations are also available in ETA Chapter 3, Sec 4.3
   *
   * @param a    The weighted automaton to reduce.
   * @param dir  The order in which reductions are computed.
   * @pre The automaton @a a must be realtime.
   * @pre The weights of the automaton @a a must be defined in a division ring.
   *
   * @see semi_reduce()
   *
   * @author Vivien Delmon, Sylvain Lombardy
   */
  template<typename A, typename AI>
  Element<A, AI>
  reduce(const Element<A, AI>& a, misc::direction_type dir = misc::right_left);

  /**
   * Semi reduction of an automaton
   *
   * This algorithm computes the (left) semi reduction of an automaton with
   * weights in a division ring.
   *
   * A technical report about this algorithm is available here :
   * http://www.lrde.epita.fr/cgi-bin/twiki/view/Publications/200901-Seminar-Delmon
   * Proof and explanations are also available in ETA Chapter 3, Sec 4.3
   *
   * @param a    The weighted automaton to reduce.
   * @param dir  The order in which reductions are computed.
   * @pre The automaton @a a must be realtime.
   * @pre The weights of the automaton @a a must be defined in a division ring.
   *
   * @see reduce()
   *
   * @author Vivien Delmon, Sylvain Lombardy
   */
  template<typename A, typename AI>
  Element<A, AI>
  semi_reduce(const Element<A, AI>& a);

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/reduce.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_ALGORITHMS_REDUCE_HH //
