// default_ops.hh
//
// $Id$
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

#ifndef FUNDAMENTAL_DEFAULT_OPS_HH
# define FUNDAMENTAL_DEFAULT_OPS_HH

# include <cassert>

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/fundamental/predefs.hh>

namespace vcsn
{
  /*---------------------------------------.
  | default implementation for op_contains |
  `---------------------------------------*/
  template<typename S, typename T>
  bool op_contains(const Structure<S>& set, const T& value);

  template <typename S, typename T>
  Element<S, T> op_choose(const Structure<S>& set, SELECTOR(T));

  /*--------------------------.
  | default value comparisons |
  `--------------------------*/
  // let E10,11 and E20,21 be of type Element<S1, T,U> and Element<S2, T,U>, resp.
  // let x1 and x2 be of type T and U, resp.
    
  // E10 == E10 -> call to v1 == v1
  // E10 == E11 -> call to op_eq(S1, v1, v2)
  // E10 == x1/x2 -> call to op_xeq(S1, v1, x)
  // E10 == E20 -> call to op_eq(S1, S2, v1, v2)

  // this function is called when E10 == E11 is evaluated.
  template<typename S, typename T, typename U>
  bool op_eq(SELECTOR(Structure<S>),
	     const T& v1, 
	     const U& v2);

  // this function is called when E10 == x2 or x2 == E10 is evaluated
  template<typename S, typename T, typename U>
  bool op_xeq(SELECTOR(Structure<S>),
	      const T& v1,
	      const U& x2);

  // E10 < E10 -> call to v1 < v1
  // E10 < E11 -> call to op_lt(S1, v1, v2)
  // E10 < x1 -> call to op_llt(S1, v1, x1)
  // x1 < E10 -> call to op_rlt(S1, x1, v1)
  // E10 < E20 -> call to op_lt(S1, S2, v1, v2)

  // this function is called when E10 < E11 is evaluated.
  template<typename S, typename T, typename U>
  bool op_lt(SELECTOR(Structure<S>),
	     const T& v1, 
	     const U& v2);

  // this function is called when E10 < x2 is evaluated
  template<typename S, typename T, typename U>
  bool op_llt(SELECTOR(Structure<S>),
	      const T& v1,
	      const U& x2);

  // this function is called when x1 < E11 is evaluated
  template<typename S, typename T, typename U>
  bool op_rlt(SELECTOR(Structure<S>),
	      const T& x1,
	      const U& v2);

  /*-------------------.
  | default conversion |
  `-------------------*/
  template<typename R, typename S, typename T>
  R op_convert(SELECTOR(R), 
	       SELECTOR(Structure<S>), const T& data);
      
  // and a useful specialization...
  template<typename S, typename T>
  const T& op_convert(SELECTOR(T),
		      SELECTOR(Structure<S>), const T& data);

  template<typename S, typename T>
  const T& op_convert(SELECTOR(T), SELECTOR(Structure<S>), 
		      SELECTOR(Structure<S>), const T& data);

  /*-------------------------------.
  | structured default constructor |
  `-------------------------------*/
  template<typename S, typename T>
  T op_default(SELECTOR(Structure<S>), SELECTOR(T));

  /*--------------.
  | operator swap |
  `--------------*/

  // this function is called when swap(E10, E10) is evaluated.
  template<typename S, typename T>
  void op_swap(SELECTOR(Structure<S>),
	       T& v1, 
	       T& v2);

  // this function is called when swap(E10, x1) or swap(x1, E10) is evaluated
  template<typename S, typename T, typename U>
  void op_xswap(SELECTOR(Structure<S>),
		const T& v1,
		const U& x2);

  /*--------------------.
  | default assignation |
  `--------------------*/

  // this is called when evaluating E10 = x2
  template<typename S, typename T, typename U>
  void op_assign(const Structure<S>& s, 
		 T& dst, const U& src);

  // this is called wh
  template<typename S, typename T, typename U>
  void op_assign(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst, 
		 const U& src);

  /*------------.
  | arithmetics |
  `------------*/

#define INOP_IMPL(Name)						\
    template<typename S, typename T, typename U>		\
    void op_in_ ## Name (const Structure<S>& s1, 	\
			 const Structure<S>& s2,	\
			 T& dst,				\
			 const U& arg);				\
      
  INOP_IMPL(add);
  INOP_IMPL(sub);
  INOP_IMPL(mul);
  INOP_IMPL(div);
  INOP_IMPL(mod);
#undef INOP_IMPL



#define BINOP_IMPL(Name)					\
    template<typename S, typename T, typename U>		\
    T op_ ## Name (const Structure<S>& s1, 		\
		   const Structure<S>& s2,		\
		   const T& v1,					\
		   const U& v2);					\

  BINOP_IMPL(add);
  BINOP_IMPL(sub);
  BINOP_IMPL(mul);
  BINOP_IMPL(div);
  BINOP_IMPL(mod);
#undef BINOP_IMPL

  /*----------------------.
    | default I/O operators |
    `----------------------*/

  template<typename S, typename St, typename T>
  St& op_rin(const Structure<S>& s, St& st, const T& v);

  template<typename S, typename St, typename T>
  St& op_rout(const Structure<S>& s, St& st, const T& v);

}

# include <vaucanson/fundamental/default_ops.hxx>

#endif // FUNDAMENTAL_DEFAULT_OPS_HH
