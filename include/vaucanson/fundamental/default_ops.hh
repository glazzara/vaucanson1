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

# include <vaucanson/config/system.hh>
# include <cassert>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/fundamental/predefs.hh>

namespace vcsn {

/** \addtogroup fundamental
 * \@{
 */

  /** test
   * test
   */
  void test(void);

  /** operator over Structure<S> that checks if a value is in a set.
   *  op_contains is an operator appliable on every structure which
   *  is the "is in" relation.
   */
  template<typename S, typename T>
  bool op_contains(const Structure<S>& set, const T& value);

  /*! operator over Structure<S> that returns a random element in the set.
   *  
   */
  template <typename S, typename T>
  Element<S, T> op_choose(const Structure<S>& set, SELECTOR(T));

  /*! equality operator on two elements of a Structure<S>.
   *
   */
  template<typename S, typename T, typename U>
  bool op_eq(SELECTOR(Structure<S>),
	     const T& v1, 
	     const U& v2);

  /*! difference operator on two elements of a Structure<S>.
   *
   */
  template<typename S, typename T, typename U>
  bool op_xeq(SELECTOR(Structure<S>),
	      const T& v1,
	      const U& x2);

  /*! comparison operator that is true if v1 is less than v2.
   *
   */
  template<typename S, typename T, typename U>
  bool op_lt(SELECTOR(Structure<S>),
	     const T& v1, 
	     const U& v2);

  /*! comparison operator that is true if v1 is less thant v2.
   *  
   */
  // FIXME: < is "typely" symmetrical. Why have we two versions ?
  template<typename S, typename T, typename U>
  bool op_llt(SELECTOR(Structure<S>),
	      const T& v1,
	      const U& x2);

  /*! comparison operator that is true if v1 is less thant v2.
   *  
   */
  // FIXME: < is "typely" symmetrical. Why have we two versions ?
  template<typename S, typename T, typename U>
  bool op_rlt(SELECTOR(Structure<S>),
	      const T& x1,
	      const U& v2);


  /*! conversion operator from T to R.
   *
   */
  template<typename R, typename S, typename T>
  R op_convert(SELECTOR(R), 
	       SELECTOR(Structure<S>), const T& data);
      
  template<typename S, typename T>
  const T& op_convert(SELECTOR(T),
		      SELECTOR(Structure<S>), const T& data);

  template<typename S, typename T>
  const T& op_convert(SELECTOR(T), SELECTOR(Structure<S>), 
		      SELECTOR(Structure<S>), const T& data);

  /*! default constructor of T using Structure<S>.
   *
   */
  template<typename S, typename T>
  T op_default(SELECTOR(Structure<S>), SELECTOR(T));


  /*! swap operator between two implementations of a Structure<S>.
   *
   */
  template<typename S, typename T>
  void op_swap(SELECTOR(Structure<S>),
	       T& v1, 
	       T& v2);

  /*! swap operator between two implementations of a Structure<S>.
   *
   */
  template<typename S, typename T, typename U>
  void op_xswap(SELECTOR(Structure<S>),
		const T& v1,
		const U& x2);

  /*! assignement operator between two implementations of a Structure<S>.
   *
   */
  template<typename S, typename T, typename U>
  void op_assign(const Structure<S>& s, 
		 T& dst, const U& src);

  /*! assignement operator between two implementations of two differents structures.
   *
   */
  template<typename S, typename T, typename U>
  void op_assign(const Structure<S>& s1,
		 const Structure<S>& s2,
		 T& dst, 
		 const U& src);

  /*! addition in place operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  void op_in_add(const Structure<S>& s1, 	
		 const Structure<S>& s2,	
		 T& dst,				
		 const U& arg);			        

  /*! substraction in place operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  void op_in_sub(const Structure<S>& s1, 	
		 const Structure<S>& s2,	
		 T& dst,				
		 const U& arg);			        

  /*! multiplication in place operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  void op_in_mul(const Structure<S>& s1, 	
		 const Structure<S>& s2,	
		 T& dst,				
		 const U& arg);			        

  /*! division in place operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  void op_in_div(const Structure<S>& s1, 	
		 const Structure<S>& s2,	
		 T& dst,				
		 const U& arg);			        

  /*! modulo in place operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  void op_in_mod(const Structure<S>& s1, 	
		 const Structure<S>& s2,	
		 T& dst,				
		 const U& arg);			        

  /*! addition operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  T op_add(const Structure<S>& s1, 		
	   const Structure<S>& s2,		
	   const T& v1,				
	   const U& v2);			

  /*! substraction operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  T op_sub(const Structure<S>& s1, 		
	   const Structure<S>& s2,		
	   const T& v1,				
	   const U& v2);			

  /*! multiplication operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  T op_mul(const Structure<S>& s1, 		
	   const Structure<S>& s2,		
	   const T& v1,				
	   const U& v2);			

  /*! division operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  T op_div(const Structure<S>& s1, 		
	   const Structure<S>& s2,		
	   const T& v1,				
	   const U& v2);			

  /*! modulo operator between two different elements.
   *
   */
  template<typename S, typename T, typename U>		
  T op_mod(const Structure<S>& s1, 		
	   const Structure<S>& s2,		
	   const T& v1,				
	   const U& v2);			
  
  /*! input stream operator.
   * 
   */
  template<typename S, typename St, typename T>
  St& op_rin(const Structure<S>& s, St& st, const T& v);

  /*! output stream operator.
   *
   */
  template<typename S, typename St, typename T>
  St& op_rout(const Structure<S>& s, St& st, const T& v);

/** 
 * \@}
 */ 


} // vcsn

# include <vaucanson/fundamental/default_ops.hxx>

#endif // FUNDAMENTAL_DEFAULT_OPS_HH
