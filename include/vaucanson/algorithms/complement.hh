// complement.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_COMPLEMENT_HH
# define VCSN_ALGORITHMS_COMPLEMENT_HH

/**
 * @file   complement.hh
 * @brief  Complementation algorithm for boolean automaton.
 */

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  /** 
   * Complement in place the set of final states.
   * 
   * @param a the deterministic boolean automaton to complement.
   * @note the input automaton must be complete and deterministic.
   * @see complement.
   */
  template <typename A, typename T>
  void
  complement_here(Element<A, T>& a);

  /** 
   * Complement in place the set of final states.
   * 
   * @param a the deterministic boolean automaton to complement.
   * @note the input automaton must be complete and deterministic.
   * @see complement_here.
   */  
  template <typename A, typename T>
  Element<A, T>
  complement(const Element<A, T>& a);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/complement.hxx>

#endif // VCSN_ALGORITHMS_COMPLEMENT_HH
