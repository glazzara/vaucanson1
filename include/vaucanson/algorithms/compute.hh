// compute.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_COMPUTE_HH
# define VCSN_ALGORITHMS_COMPUTE_HH

# include <vaucanson/fundamental/element.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! Return the image of the word in the automaton.

  /*! compute(a, w) returns a serie that is the image of the word 'w'
    in the automaton. This version of computation is the most general
    one : it works on every types of automaton, deterministic or not. 
    Yet, the automaton must be realtime since epsilon transition could
    imply non termination.
  */

  template<typename A, typename T, typename W>
  typename Element<A, T>::weight_t
  compute(const Element<A, T>& a, const W& word);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/compute.hxx>

#endif // VCSN_ALGORITHMS_COMPUTE_HH
