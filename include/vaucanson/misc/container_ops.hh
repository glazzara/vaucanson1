// container_ops.hh
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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


#ifndef FUNDAMENTAL_CONTAINER_OPS_HH
# define FUNDAMENTAL_CONTAINER_OPS_HH

# include <algorithm>

# include <vaucanson/fundamental/predefs.hh>

namespace vcsn
{

  template<typename S, typename T>
  struct op_begin_traits
  {
    typedef typename T::iterator		ret_t;
    typedef typename T::const_iterator		const_ret_t;
  };
  
  template<typename S, typename T>
  struct op_rbegin_traits
  {
    typedef typename T::reverse_iterator	 ret_t;
    typedef typename T::const_reverse_iterator	 const_ret_t;
  };
  
  template<typename S, typename T>
  typename T::iterator op_begin(const Structure<S>& s, 
				T& v);
  
  template<typename S, typename T>
  typename T::iterator op_end(const Structure<S>& s, 
			      T& v);

  template<typename S, typename T>
  typename T::const_iterator op_begin(const Structure<S>& s,
				      const T& v);

  template<typename S, typename T>
  typename T::const_iterator op_end(const Structure<S>& s, 
				    const T& v);

  template<typename S, typename T>
  typename T::reverse_iterator op_rbegin(const Structure<S>& s, 
					 T& v);

  template<typename S, typename T>
  typename T::reverse_iterator op_rend(const Structure<S>& s, 
				       T& v);

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rbegin(const Structure<S>& s,
					       const T& v);

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rend(const Structure<S>& s,
					     const T& v);

  template<typename S, typename T>
  bool op_empty(const Structure<S>& s,
		const T& v);
    
  template<typename S, typename T>
  size_t op_size(const Structure<S>& s, 
		 const T& v);
    
  template<typename S, typename T, typename U>
  bool op_contains_e(const Structure<S>& s, const T& v, 
		     const U& c);
  
  template<typename S, typename T, typename U>
  void op_insert(const Structure<S>& s, T& v,
		 const U& c);

  template<typename S, typename T>
  bool op_is_finite(const Structure<S>& s,
		    const T& a);

      
} // vcsn

# include <vaucanson/misc/container_ops.hxx>

#endif // FUNDAMENTAL_CONTAINER_OPS_HH

