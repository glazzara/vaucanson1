// concat.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_CONCAT_HH
# define VCSN_ALGORITHMS_CONCAT_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  /*! Return the concatenation of two automata using epsilon transitions. */
  template <class A, class T>
  Element<A, T> 
  auto_concat(const Element<A, T>& lhs, const Element<A, T>& rhs);

  /*! Return the concatenation of two automata using epsilon transitions. */
  template <class A, class T>
  void
  auto_in_concat(Element<A, T>& lhs, const Element<A, T>& rhs);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/concat.hxx>

#endif // VCSN_ALGORITHMS_CONCAT_HH
