// product.hh
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

#ifndef VCSN_ALGORITHMS_PRODUCT_HH
# define VCSN_ALGORITHMS_PRODUCT_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! Returns a fresh automaton that is the product of the two input ones.
  template<typename A, typename T, typename U>
  Element<A, T> 
  auto_product(const Element<A, T>& lhs, const Element<A, U>& rhs);

  //! In-place diagonal extraction.
  template <typename A, typename T>
  void
  auto_in_diagonal(Element<A, T>&);

  //! Return a fresh automaton that is the diagonal of the input one.
  template <typename A, typename T>
  Element<A, T>
  auto_diagonal(const Element<A, T>&);

  /*! @} */

} // vcsn

# include <vaucanson/algorithms/product.hxx>

#endif // VCSN_ALGORITHMS_PRODUCT_HH
