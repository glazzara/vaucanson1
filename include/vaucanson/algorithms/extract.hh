// extract.hh
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

#ifndef VCSN_ALGORITHMS_EXTRACT_HH
# define VCSN_ALGORITHMS_EXTRACT_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */
 
  //! Returns a fresh automaton that is the sub-automaton defined by a set.
  template<typename A, typename T, typename StatesSet>
  Element<A, T> 
  auto_extract(const Element<A, T>& a, const StatesSet& s, 
	       bool check_states = true);

  //! Modify the input to obtain the sub-automaton defined by a set of states.
  template<typename A, typename T, typename StatesSet>
  void auto_in_extract(Element<A, T>& a, const StatesSet& s, 
		       bool check_states = true);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/extract.hxx>

#endif // VCSN_ALGORITHMS_EXTRACT_HH
