// container_ops.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TOOLS_CONTAINER_OPS_HH
# define VCSN_TOOLS_CONTAINER_OPS_HH

# include <algorithm>

# include <vaucanson/design_pattern/predecls.hh>

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
  typename T::const_iterator op_begin_const(const Structure<S>& s,
					    const T& v);

  template<typename S, typename T>
  typename T::const_iterator op_end_const(const Structure<S>& s,
					  const T& v);

  template<typename S, typename T>
  typename T::reverse_iterator op_rbegin(const Structure<S>& s,
					 T& v);

  template<typename S, typename T>
  typename T::reverse_iterator op_rend(const Structure<S>& s,
				       T& v);

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rbegin_const(const Structure<S>& s,
					       const T& v);

  template<typename S, typename T>
  typename T::const_reverse_iterator op_rend_const(const Structure<S>& s,
					     const T& v);

  template<typename S, typename T>
  bool op_empty(const Structure<S>& s,
		const T& v);

  template<typename S, typename T>
  size_t op_size(const Structure<S>& s,
		 const T& v);

  template<typename S, typename T>
  size_t op_max_size(const Structure<S>& s,
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


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/tools/container_ops.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_TOOLS_CONTAINER_OPS_HH
