// hopcroft_minimization.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_HOPCROFT_MINIMIZATION_HH
# define VCSN_ALGORITHMS_HOPCROFT_MINIMIZATION_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /**
   * @file   hopcroft_minimization.hh
   * @author Yann R�gis-Gianas <yann@lrde.epita.fr>
   * @date   Tue Jun 24 21:08:54 2003
   * 
   * @brief  This file provides minimization and quotient algorithms.
   * 
   */


  /*! \addtogroup algorithms */  /* @{ */

  //! The canonical minimal automaton of the deterministic input automaton.

  /** 
   * @brief Return the minimal automaton using the hopcroft algorithm.
   * 
   * @param a the deterministic boolean automaton to minimize.
   * 
   * @return a fresh automaton that is the canonical minimal automaton of 'a'.
   */
  // INTERFACE: Automaton minimization_hopcroft(const Automaton& a) { return vcsn::minimization_hopcroft(*a); }
  template<typename A, typename T>
  Element<A, T>
  minimization_hopcroft(const Element<A, T>& a);

  //! The canonical minimal automaton of the input automaton. (EXPERIMENTAL)
  
  /** 
   * @brief Return the quotient of a non deterministic acceptor.
   * 
   * @param a the boolean automaton to minimize.
   * 
   * @return a fresh automaton that is the quotient of 'a'.
   */
  template<typename A, typename T>
  Element<A, T>
  quotient(const Element<A, T>& a);
  
  /*! @} */

} // vcsn

# include <vaucanson/algorithms/hopcroft_minimization.hxx>

#endif // VCSN_ALGORITHMS_HOPCROFT_MINIMIZATION_HH
