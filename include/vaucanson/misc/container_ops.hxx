// container_ops.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_MISC_CONTAINER_OPS_HXX
# define VCSN_MISC_CONTAINER_OPS_HXX

# include <algorithm>

# include <vaucanson/misc/container_ops.hh>
# include <vaucanson/fundamental/predecls.hh>

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


#endif // VCSN_MISC_CONTAINER_OPS_HXX
