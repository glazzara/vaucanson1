// container_ops.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TOOLS_CONTAINER_OPS_HXX
# define VCSN_TOOLS_CONTAINER_OPS_HXX

# include <algorithm>

# include <vaucanson/tools/container_ops.hh>
# include <vaucanson/design_pattern/predecls.hh>

namespace vcsn
{

  template<typename S, typename T>
  typename T::iterator op_begin(const Structure<S>&,
				T& v)
  {
    return v.begin();
  }

  template<typename S, typename T>
  typename T::iterator op_end(const Structure<S>&,
			      T& v)
  {
    return v.end();
  }

  template<typename S, typename T>
  typename T::const_iterator op_begin_const(const Structure<S>&,
					    const T& v)
  {
    return v.begin();
  }

  template<typename S, typename T>
  typename T::const_iterator op_end_const(const Structure<S>&,
					  const T& v)
  {
    return v.end();
  }

  template<typename S, typename T>
  typename T::reverse_iterator op_rbegin(const Structure<S>&,
					 T& v)
  {
    return v.rbegin();
  }

  template<typename S, typename T>
  typename T::reverse_iterator op_rend(const Structure<S>&,
				       T& v)
  {
    return v.rend();
  }

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rbegin_const(const Structure<S>&,
						     const T& v)
  {
    return v.rbegin();
  }

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rend_const(const Structure<S>&,
						   const T& v)
  {
    return v.rend();
  }

  template<typename S, typename T>
  bool op_empty(const Structure<S>&,
		const T& v)
  {
    return v.empty();
  }

  template<typename S, typename T>
  size_t op_size(const Structure<S>&,
		 const T& v)
  {
    return v.size();
  }

  template<typename S, typename T>
  size_t op_max_size(const Structure<S>&,
		     const T& v)
  {
    return v.max_size();
  }

  template<typename S, typename T, typename U>
  bool op_contains_e(const Structure<S>&, const T& v,
		     const U& c)
  {
    return std::find(v.begin(), v.end(), c) != v.end();
  }

  template<typename S, typename T, typename U>
  void op_insert(const Structure<S>&, T& v,
		 const U& c)
  {
    v.insert(c);
  }

  template<typename S, typename T>
  bool op_is_finite(const Structure<S>&,
		    const T&)
  {
    return false;
  }

} // vcsn


#endif // ! VCSN_TOOLS_CONTAINER_OPS_HXX
