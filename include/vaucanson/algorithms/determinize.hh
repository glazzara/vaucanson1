// determinize.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_DETERMINIZE_HH
# define VCSN_ALGORITHMS_DETERMINIZE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   determinize.hh
 *
 * This file provides the determinization algorithm for Boolean automata.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 19:13:10 2003
 *
 * @see determinize(), is_deterministic()
 */
/** @} */

// INTERFACE: Automaton determinize(const Automaton& a) { return vcsn::determinize(*a); }

// INTERFACE: bool is_deterministic(const Automaton& a) { return vcsn::is_deterministic(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <map>
# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// @name Determinization algorithms
  //@{
  /**
   * Returns the determinized of a Boolean automaton.
   *
   * @param a The Boolean automaton to determinize.
   *
   * @return A fresh Boolean automaton that is the determinization of 'a'.
   */
  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a);

  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a,
	      std::map<hstate_t, std::set<hstate_t> >&);
  //@}

  /**
   * Test if an automaton is deterministic.
   *
   * @param a A Boolean automaton.
   *
   * @return true if 'a' is deterministic.
   */
  template<typename A, typename T>
  bool
  is_deterministic(const Element<A, T>& a);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/determinize.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGORITHMS_DETERMINIZE_HH
