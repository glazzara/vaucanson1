// structure.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef FUNDAMENTAL_STRUCTURE_HXX
# define FUNDAMENTAL_STRUCTURE_HXX

# include <vaucanson/fundamental/structure.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/internal/traits.hh>

namespace vcsn {
    
  /*----------.
  | Structure |
  `----------*/

  template <typename Self>
  template <typename T>
  bool 
  Structure<Self>::contains(const Element<Self, T>& elt) const
  { 
    return op_contains(self(), elt.value()); 
  }

  template <class Self>
  template <class T>
  Element<Self, T>
  Structure<Self>::choose(SELECTOR(T)) const
  {
    return op_choose(self(), SELECT(T));
  }

  template <typename Self>
  template <typename T>
  bool 
  Structure<Self>::contains(const T& elt_value) const
  { 
    return op_contains(self(), elt_value); 
  }
    
  template <typename Self>
  template <typename S, typename T>
  bool 
  Structure<Self>::contains(const Element<S, T>& other) const
  { 
    return false; 
  }
    
  // static inheritance stuff below
  template <typename Self>
  Self&        
  Structure<Self>::self()
  { 
    return static_cast<self_t&>(*this); 
  }
    
  template <typename Self>
  const Self&  
  Structure<Self>::self() const 
  { 
    return static_cast<const self_t&>(*this); 
  }
    
  template <typename Self>
  Structure<Self>::Structure()
  {}

  template <typename Self>
  Structure<Self>::Structure(const Structure&)
  {}


} // vcsn


/*--------------------.
| default comparisons |
`--------------------*/
template<typename S>
bool operator==(const vcsn::Structure<S>& a,
		const vcsn::Structure<S>& b)
{ 
  return true; 
}

template<typename S>
bool operator!=(const vcsn::Structure<S>& a,
		const vcsn::Structure<S>& b)
{ 
  return !(a == b); 
}

#endif // FUNDAMENTAL_STRUCTURE_HXX
