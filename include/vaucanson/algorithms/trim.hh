// trim.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_TRIM_HH
# define VCSN_ALGORITHMS_TRIM_HH

# include <set>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */
  
  //! Returns a useful states of the automaton (start reachable and final co-).
  template<typename A, typename T>
  std::set<hstate_t>
  useful_states(const Element<A, T>& a);

  //! Return a fresh automaton in which non useful states are removed.
  template<typename A, typename T>
  Element<A, T>
  trim(const Element<A, T>& a);
    
  /*! @} */

} // vcsn

# include <vaucanson/algorithms/trim.hxx>

#endif // VCSN_ALGORITHMS_TRIM_HH
