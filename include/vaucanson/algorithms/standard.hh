// standard.hh
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

#ifndef VCSN_ALGORITHMS_STANDARD_HH
# define VCSN_ALGORITHMS_STANDARD_HH

# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  //! Returns a standard automaton associated to the input.
  template<typename A, typename T>
  void
  standardize(Element<A, T>& a);

  //! Returns true if the input automaton is standard.
  template<typename A, typename T>
  bool
  is_standard(const Element<A, T>& a);

  //! In-place union of two standard automata.
  template<typename A, typename T, typename U>
  void 
  standard_auto_in_union(Element<A, T>& lhs, 
			 const Element<A, U>& rhs);

  //! Return a fresh union of two standard automata.
  template<typename A, typename T, typename U>
  Element<A, T> 
  standard_auto_union(const Element<A, T>& lhs, 
		      const Element<A, U>& rhs);

  //! In-place concatenation of two standard automata.
  template<typename A, typename T, typename U>
  void 
  standard_auto_in_concat(Element<A, T>& lhs, 
			  const Element<A, U>& rhs);

  //! Return a fresh concatenation of two standard automata.
  template<typename A, typename T, typename U>
  Element<A, T> 
  standard_auto_concat(const Element<A, T>& lhs, 
		       const Element<A, U>& rhs);

  //! In-place star transformation of a standard automata.
  template<typename A, typename T>
  void 
  standard_auto_in_star(Element<A, T>& a);

  //! Return the fresh star transformation of a standard automata.
  template<typename A, typename T>
  Element<A, T> 
  standard_auto_star(const Element<A, T>& a);
  
} // vcsn

# include <vaucanson/algorithms/standard.hxx>

#endif // VCSN_ALGORITHMS_STANDARD_HH
