// misc/static.hxx
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

#ifndef MISC_STATIC_HXX
# define MISC_STATIC_HXX

# include <cstddef>

# include <vaucanson/misc/static.hh>

namespace utility {

  // max : virage des statics 

  template<bool b, typename T, typename U>
  typename remove_reference<T>::t& 
  static_if<b, T, U>::choose(typename remove_reference<T>::t& p1, 
			     typename remove_reference<U>::t& p2)
  { 
    return p1; 
  }
  
  template<typename T, typename U>
  typename remove_reference<U>::t& 
  static_if<false, T, U>::choose(typename remove_reference<T>::t& p1, 
				 typename remove_reference<U>::t& p2)
  { 
    return p2; 
  }

} // utility

#endif // MISC_STATIC_HXX
