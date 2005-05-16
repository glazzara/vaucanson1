// cut_up.hh: this file is part of the Vaucanson project.
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
//

#ifndef VCSN_ALGORITHMS_CUT_UP_HH
# define VCSN_ALGORITHMS_CUT_UP_HH

/**
 * @file cut_up.hh
 *
 * Cut-up algorithm.
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

# include <vaucanson/automata/concept/copy.hh>
# include <vaucanson/automata/implementation/generalized.hh>
# include <vaucanson/algebra/implementation/series/rat/nodes.hh>
# include <vaucanson/algorithms/standard_of.hh>


namespace vcsn
{

  /**
   * @brief Check if labels are series with one element.
   *
   * @arg a	Input automaton.
   * @return	is cut-up.
   *
   */
  template <class S, class T>
  bool is_cut_up(const Element<S, T>& a);


  /**
   * @brief Transform an automaton labeled with series to an automaton
   * where all labels are series with one and only one element.
   *
   * @comment No cut-up work is done on input and output transitions.
   *
   * Works on all automata and transducers labeled with polynomial series,
   * and on automata labeled with rational series.
   *
   * @arg a	Input automaton.
   * @return	Output automaton.
   *
   */
  template <class S, class T>
  Element<S, T>
  cut_up(const Element<S, T>& a);


  /**
   * @brief Transform an automaton labeled with series to an automaton
   * where all labels are series with one and only one element.
   *
   * @comment No cut-up work is done on input and output transitions.
   *
   * Works on all automata and transducers labeled with polynomial series,
   * and on automata labeled with rational series.
   *
   * @arg a	Input automaton.
   * @arg res	Output automaton.
   *
   */
  template <class S, class T>
  void
  cut_up(const Element<S, T>& a, Element<S, T>& res);

} // ! vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/cut_up.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_ALGORITHMS_CUT_UP_HH
