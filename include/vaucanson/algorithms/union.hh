// union.hh
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

#ifndef VCSN_ALGORITHMS_UNION_HH
# define VCSN_ALGORITHMS_UNION_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! Add the states and edges of 'rhs' to 'lhs'.
  template<typename A, typename T, typename U>
  void 
  auto_in_union(Element<A, T>& lhs, 
		const Element<A, U>& rhs);

  //! Return the fresh union of 'lhs' and 'rhs'.
  template<typename A, typename T, typename U>
  Element<A, T> 
  auto_union(const Element<A, T>& lhs, 
	     const Element<A, U>& rhs);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/union.hxx>

#endif // VCSN_ALGORITHMS_UNION_HH
