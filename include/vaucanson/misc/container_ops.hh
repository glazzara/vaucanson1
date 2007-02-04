// container_ops.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TOOLS_CONTAINER_OPS_HH
# define VCSN_TOOLS_CONTAINER_OPS_HH

# include <algorithm>

# include <vaucanson/design_pattern/predecls.hh>

/**
 * @file container_ops.hh
 *
 * @brief Generic operators for containers.
 *
 * This file contains generic implementation of the op_ operators for
 * containers Element.
 */

namespace vcsn
{

  template<typename S, typename T>
  struct op_begin_traits
  {
      typedef typename T::iterator ret_t;
      typedef typename T::const_iterator const_ret_t;
  };

  template<typename S, typename T>
  struct op_rbegin_traits
  {
      typedef typename T::reverse_iterator ret_t;
      typedef typename T::const_reverse_iterator const_ret_t;
  };

  template<typename S, typename T>
  typename T::iterator op_begin (const Structure<S>& s,
				 T& v);

  template<typename S, typename T>
  typename T::iterator op_end (const Structure<S>& s,
			       T& v);

  template<typename S, typename T>
  typename T::const_iterator op_begin_const (const Structure<S>& s,
					     const T& v);

  template<typename S, typename T>
  typename T::const_iterator op_end_const (const Structure<S>& s,
					   const T& v);

  template<typename S, typename T>
  typename T::reverse_iterator op_rbegin (const Structure<S>& s,
					  T& v);

  template<typename S, typename T>
  typename T::reverse_iterator op_rend (const Structure<S>& s,
					T& v);

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rbegin_const (const Structure<S>& s,
						      const T& v);

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rend_const (const Structure<S>& s,
						    const T& v);

  template<typename S, typename T>
  bool op_empty (const Structure<S>& s,
		 const T& v);

  template<typename S, typename T>
  size_t op_size (const Structure<S>& s,
		  const T& v);

  template<typename S, typename T>
  size_t op_max_size (const Structure<S>& s,
		      const T& v);

  template<typename S, typename T, typename U>
  bool op_contains_e (const Structure<S>& s, const T& v,
		      const U& c);

  template<typename S, typename T, typename U>
  void op_insert (const Structure<S>& s, T& v,
		  const U& c);

  template<typename S, typename T>
  bool op_is_finite (const Structure<S>& s,
		     const T& a);

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/container_ops.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_TOOLS_CONTAINER_OPS_HH
