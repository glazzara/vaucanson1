// default_ops.hxx: this file is part of the Vaucanson project.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_DESIGN_PATTERN_DEFAULT_OPS_HXX
# define VCSN_DESIGN_PATTERN_DEFAULT_OPS_HXX

# include <vaucanson/design_pattern/default_ops.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn {

  /*--------------------.
  | Structure::contains |
  `--------------------*/

  template<typename S, typename T>
  bool op_contains(const Structure<S>&, const T&)
  { 
    return false; 
  }

  /*--------------------.
  | Standard comparison |
  `--------------------*/

  template<typename S, typename T, typename U>
  bool op_eq(const Structure<S>&,
	     const T& v1, 
	     const U& v2)
  { 
    return v1 == v2; 
  }

  template<typename S, typename T, typename U>
  bool op_lt(const Structure<S>&,
	     const T& v1, 
	     const U& v2)
  {
    return v1 < v2; 
  }


  template<typename S, typename V, typename T, typename U>
  bool op_eq(const Structure<S>&,
	     const Structure<V>&,
	     const T& v1, 
	     const U& v2)
  { 
    return v1 == v2; 
  }

  template<typename S, typename V, typename T, typename U>
  bool op_lt(const Structure<S>&,
	     const Structure<V>&,
	     const T& v1, 
	     const U& v2)
  {
    return v1 < v2; 
  }

  /*------------.
  | Conversions |
  `------------*/

  template<typename S, typename R, typename T>
  R op_convert(const Structure<S> &, 
	       SELECTOR(R), const T& data)
  {
    return static_cast<R>(data);
  }
      
  template<typename S, typename T>
  const T& op_convert(const Structure<S>&,
		      SELECTOR(T), const T& from_data)
  { 
    return from_data;
  }

  template<typename S, typename T>
  const T& op_convert(const Structure<S>& s1, SELECTOR(T), 
		      const Structure<S>& s2, const T& from_data)
  {
    precondition(& s1 == & s2);
    return from_data;
  }

  template<typename S, typename T>
  const S& op_convert(const Structure<S>&, const Structure<T>&)
  {
    static_error_(no_convertion_operator_available);
  }

  /*---------------------.
  | Default construction |
  `---------------------*/

  template<typename S, typename T>
  T op_default(const Structure<S>&, SELECTOR(T))
  { 
    return T(); 
  }

  /*-----.
  | Swap |
  `-----*/

  template<typename S, typename T>
  void op_swap(const Structure<S>&,
	       T& v1, 
	       T& v2)
  { 
    std::swap(v1, v2); 
  }

  /*-----------.
  | Assignment |
  `-----------*/


  template<typename S, typename T, typename U>
  void op_assign(const Structure<S>&, 
		 T& dst, const U& src)
  { 
    dst = src; 
  }

  template<typename S, typename T, typename U>
  void op_assign(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst, 
		 const U& src)
  { 
    precondition(& s1 == & s2);
    op_assign(s1.self(), dst, src); 
  }

#define INOP_IMPL(Name)						\
    template<typename S, typename T, typename U>		\
    void op_in_ ## Name (const Structure<S>& s1, 	\
			 const Structure<S>& s2,	\
			 T& dst,				\
			 const U& arg)				\
    { 								\
      precondition(& s1 == & s2);			\
      return op_in_ ## Name (s1.self(), dst, arg); 		\
    }
      
  INOP_IMPL(add);
  INOP_IMPL(sub);
  INOP_IMPL(mul);
  INOP_IMPL(div);
  INOP_IMPL(mod);
#undef INOP_IMPL



#define BINOP_IMPL(Name)					\
    template<typename S, typename T, typename U>		\
    T op_ ## Name (const Structure<S>& s1,			\
		   const Structure<S>& s2,			\
		   const T& v1,					\
		   const U& v2)					\
    { 								\
      precondition(& s1 == & s2); 			\
      return op_ ## Name(s1.self(), v1, v2); 			\
    }

  BINOP_IMPL(add);
  BINOP_IMPL(sub);
  BINOP_IMPL(mul);
  BINOP_IMPL(div);
  BINOP_IMPL(mod);
#undef BINOP_IMPL

  template<typename S, typename St, typename T>
  St& op_rin(const Structure<S>& s, St& st, const T& v)
  { 
    return st >> v; 
  }

  template<typename S, typename St, typename T>
  St& op_rout(const Structure<S>&, St& st, const T& v)
  { 
    st << v; 
    return st; 
  }

} // vcsn

#endif // ! VCSN_DESIGN_PATTERN_DEFAULT_OPS_HXX
