// misc/static.hh
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

#ifndef MISC_STATIC_HH
# define MISC_STATIC_HH

# include <cstddef>

namespace utility {

  template<typename T>
  struct remove_reference
  {
    typedef T t;
  };
  
  template<typename T>
  struct remove_reference<T&>
  {
    typedef T t;
  };

  template<bool b, typename T, typename U>
  struct static_if
  { 
    typedef T t; 

    static typename remove_reference<T>::t& 
    choose(typename remove_reference<T>::t& p1, 
	   typename remove_reference<U>::t& p2);
  };

  template<typename T, typename U>
  struct static_if<false, T, U>
  { 
    typedef U t; 

    static typename remove_reference<U>::t& 
    choose(typename remove_reference<T>::t& p1, 
	   typename remove_reference<U>::t& p2);

  };

  template<typename T, typename U>
  struct static_eq
  { 
    static const bool value = false; 
  };

  template<typename T>
  struct static_eq<T, T>
  { 
    static const bool value = true; 
  };

  template<size_t N, size_t P, bool pair_p = false>
  struct static_pow_compute
  { 
    static const size_t value = 
    N * static_pow_compute<N, P-1, (((P-1) % 2) == 0)>::value ; 
  };

  template<size_t N, size_t P>
  struct static_pow_compute<N, P, true>
  { 
    static const size_t temp = 
    static_pow_compute<N, P/2, (((P/2) % 2) == 0)>::value;
    static const size_t value = temp * temp;
  };
    
  template<size_t N>
  struct static_pow_compute<N, 0, true>
  { 
    static const size_t value = 1; 
  };

  template<size_t N, size_t P>
  struct static_pow
  {
    static const size_t value = 
    static_pow_compute<N, P, ((P % 2) == 0)>::value ;
  };

  template<size_t N, size_t P>
  struct static_pow_minus_one
  {
    static const size_t value = 
    static_pow_compute<N, P, ((P % 2) == 0)>::value - 1;
  };

} // utility

# include <vaucanson/misc/static.hxx>

#endif // MISC_STATIC_HH
