// normalized.hh
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

#ifndef VCSN_ALGORITHMS_NORMALIZED_HH
# define VCSN_ALGORITHMS_NORMALIZED_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*! \addtogroup algorithms */  /* @{ */

  //! In-place Thompson normalization of the automaton.
  template<typename A, typename T>
  void
  normalize(Element<A, T>& a);

  //! Returns true if the input automaton is normalized.
  template<typename A, typename T>
  bool
  is_normalized(const Element<A, T>& a);

  //! In-place union of two normalized automata.
  template<typename A, typename T, typename U>
  void 
  normalized_auto_in_union(Element<A, T>& lhs, 
			   const Element<A, U>& rhs);

  //! Returns the fresh union of two normalized automata.
  template<typename A, typename T, typename U>
  Element<A, T> 
  normalized_auto_union(const Element<A, T>& lhs, 
			const Element<A, U>& rhs);

  //! In-place concatenation of two normalized automata.
  template<typename A, typename T, typename U>
  void 
  normalized_auto_in_concat(Element<A, T>& lhs, 
			     const Element<A, U>& rhs);

  //! Returns the fresh concatenation of two normalized automata.
  template<typename A, typename T, typename U>
  Element<A, T> 
  normalized_auto_concat(const Element<A, T>& lhs, 
			  const Element<A, U>& rhs);

  //! In-place star transformation of the input normalized automaton.
  template<typename A, typename T>
  void 
  normalized_auto_in_star(Element<A, T>& a);

  //! Returns the fresh star transformation of the input normalized automaton.
  template<typename A, typename T>
  Element<A, T> 
  normalized_auto_star(const Element<A, T>& a);

  /*! @} */
  
} // vcsn

# include <vaucanson/algorithms/normalized.hxx>

#endif // VCSN_ALGORITHMS_NORMALIZED_HH
