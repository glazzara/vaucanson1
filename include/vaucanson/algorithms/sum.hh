// sum.hh
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

#ifndef VCSN_ALGORITHMS_SUM_HH
# define VCSN_ALGORITHMS_SUM_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! Add the states and edges of 'rhs' to 'lhs'.
  template<typename A, typename T, typename U>
  void 
  sum_here(Element<A, T>& lhs, 
	   const Element<A, U>& rhs);

  //! Return the fresh union of 'lhs' and 'rhs'.
  template<typename A, typename T, typename U>
  Element<A, T> 
  sum(const Element<A, T>& lhs, 
      const Element<A, U>& rhs);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/sum.hxx>

#endif // VCSN_ALGORITHMS_SUM_HH
