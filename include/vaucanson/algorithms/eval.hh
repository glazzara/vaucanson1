// eval.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_EVAL_HH
# define VCSN_ALGORITHMS_EVAL_HH

# include <vaucanson/design_pattern/element.hh>

namespace vcsn {

  /**
   * @file   eval.hh
   * @author Yann Régis-Gianas <yann@lrde.epita.fr>
   * @date   Tue Jun 24 17:50:38 2003
   * 
   * @brief  This file provides the evaluation of a word w.r.t an automaton.
   * 
   */

  /*! \addtogroup algorithms */  /* @{ */

  //! Return the image of the word in the automaton.

  /*! eval(a, w) returns a serie that is the image of the word 'w'
    in the automaton. This version of computation is the most general
    one : it works on every types of automaton, deterministic or not. 
    Yet, the automaton must be realtime.
  */

  /** 
   * @brief Compute the image of a word into an automaton.
   *
   * eval(a, w) returns a weight that is the image of the word 'w' in
   * the automaton. This algorithm works an weighted deterministic or
   * not realtime automata.
   * 
   * @param a the automaton.
   * @param word the word to give as an input to the automaton.
   * 
   * @return the weight associated to the word
   */
  // INTERFACE: int eval(const Automaton& a, const std::string& s) { return vcsn::eval(*a, Serie::monoid_elt_t((*a).set().series().monoid(), s)).value(); }
  // INTERFACE: int eval(const GenAutomaton& a, const std::string& s) { return vcsn::eval(*a, Serie::monoid_elt_t((*a).set().series().monoid(), s)).value(); }
  template<typename A, typename T, typename W>
  typename Element<A, T>::semiring_elt_t
  eval(const Element<A, T>& a, const W& word);

  /*! @} */

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algorithms/eval.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_ALGORITHMS_EVAL_HH
