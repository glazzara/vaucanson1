// fundamental/elements_ops.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_FUNDAMENTAL_ELEMENTS_OPS_HH
# define VCSN_FUNDAMENTAL_ELEMENTS_OPS_HH

# include <vaucanson/config/system.hh>
# include <vaucanson/fundamental/predefs.hh>
# include <vaucanson/fundamental/op_traits.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/misc/static.hh>

namespace vcsn {

  /*! @addtogroup fundamental */ /*! @{ */
  /*! @addtogroup operators   */ /*! @{ */

  /*! equality operator between two different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator==(const vcsn::Element<S1, T1>& e1,	
		  const vcsn::Element<S2, T2>& e2);	

  /*! difference operator between two different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator!=(const vcsn::Element<S1, T1>& e1,	
		  const vcsn::Element<S2, T2>& e2);	

  /*! strict less operator between two different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator<(const vcsn::Element<S1, T1>& e1,	
		 const vcsn::Element<S2, T2>& e2);	

  /*! strict more operator between two different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator>(const vcsn::Element<S1, T1>& e1,	
		 const vcsn::Element<S2, T2>& e2);	

  /*! less operator between two different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator<=(const vcsn::Element<S1, T1>& e1,	
		  const vcsn::Element<S2, T2>& e2);	

  /*! more operator between two different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator>=(const vcsn::Element<S1, T1>& e1,	
		  const vcsn::Element<S2, T2>& e2);	

  /*! equality operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator ==(const vcsn::Element<S, T>& e,
		   const U& v);

  /*! equality operator between an element and an
    implementation. (right version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator ==(const U& v,
		   const vcsn::Element<S, T>& e);

  /*! difference operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator !=(const vcsn::Element<S, T>& e,
		   const U& v);
  /*! difference operator between an element and an
    implementation. (right version) */
  template<typename U, typename S, typename T>
  static inline
  bool operator !=(const U& v,
		   const vcsn::Element<S, T>& e);

  /*! strict less operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator <(const vcsn::Element<S, T>& e,
		  const U& v);

  /*! strict less operator between an element and an
    implementation. (right version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator <(const U& v,
		  const vcsn::Element<S, T>& e);

  /*! strict more operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator >(const vcsn::Element<S, T>& e,
		  const U& v);

  /*! strict more operator between an element and an
    implementation. (right version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator >(const U& v,
		  const vcsn::Element<S, T>& e);

  /*! more operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator >=(const vcsn::Element<S, T>& e,
		   const U& v);

  /*! more operator between an element and an
    implementation. (right version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator >=(const U& v,
		   const vcsn::Element<S, T>& e);

  /*! less operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator <=(const vcsn::Element<S, T>& e,
		   const U& v);

  /*! less operator between an element and an
    implementation. (right version) */
  template<typename S, typename T, typename U>
  static inline
  bool operator <=(const U& v,
		   const vcsn::Element<S, T>& e);

  /*! addition operator between two a priori different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	      	
  static inline					     			
  typename vcsn::op_add_traits<S1, S2, T1, T2>::ret_t	
  operator+(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				
									
  /*! addition operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>	       			
  static inline vcsn::Element<S, T>					
  operator +(const vcsn::Element<S, T>& e,				
	     const U& v);			       			
	
  /*! addition operator between an element and an
    implementation. (right version) */
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator +(const U& v,			          		
	     const vcsn::Element<S, T>& e);

  /*! substraction operator between two a priori different elements. */
  template<typename S1, typename T1, typename S2, typename T2> 		
  static inline						       		
  typename vcsn::op_sub_traits<S1, S2, T1, T2>::ret_t	
  operator-(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /*! substraction operator between an element and an
    implementation. (left version) */ 
  template<typename S, typename T, typename U>		       		
  static inline vcsn::Element<S, T>					
  operator-(const vcsn::Element<S, T>& e,				
	    const U& v);				       		
  /*! substraction operator between an element and an
    implementation. (right version) */
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator-(const U& v,					     		
	    const vcsn::Element<S, T>& e);

  /*! multiplication operator between two a priori different elements. */
  template<typename S1, typename T1, typename S2, typename T2> 		
  static inline						       		
  typename vcsn::op_mul_traits<S1, S2, T1, T2>::ret_t	
  operator*(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /*! multiplication operator between an element and an
    implementation. (left version) */ 	
  template<typename S, typename T, typename U>			       	
  static inline vcsn::Element<S, T>					
  operator*(const vcsn::Element<S, T>& e,			       
	    const U& v);					     	

  /*! multiplication operator between an element and an
    implementation. (right version) */
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator*(const U& v,					     		
	    const vcsn::Element<S, T>& e);

  /*! division operator between two a priori different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	       	
  static inline						       		
  typename vcsn::op_div_traits<S1, S2, T1, T2>::ret_t	
  operator/(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /*! division operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>			       	
  static inline vcsn::Element<S, T>					
  operator/(const vcsn::Element<S, T>& e,			       
	    const U& v);					       	

  /*! division operator between an element and an
    implementation. (right version) */
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator/(const U& v,					     		
	    const vcsn::Element<S, T>& e);

  /*! modulo operator between two a priori different elements. */
  template<typename S1, typename T1, typename S2, typename T2>	       	
  static inline						       		
  typename vcsn::op_mod_traits<S1, S2, T1, T2>::ret_t	
  operator%(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /*! modulo operator between an element and an
    implementation. (left version) */
  template<typename S, typename T, typename U>		       		
  static inline vcsn::Element<S, T>					
  operator%(const vcsn::Element<S, T>& e,				
	    const U& v);				       		
  /*! modulo operator between an element and an
    implementation. (right version) */		
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator%(const U& v,					     		
	    const vcsn::Element<S, T>& e);

  // FIXME: find an explanation for this !
  template<typename S1, typename T1, typename S2, typename T2>
  static inline void /* do not use or specialize */
  operator <<(const vcsn::Element<S1, T1>& e1,
	      const vcsn::Element<S2, T2>& e2);
  
  /*! output stream operator. */
  template<typename St, typename S, typename T>
  static inline St& 
  operator <<(St& s, const vcsn::Element<S, T>& e);

  /*! input stream operator. */
  template<typename St, typename S, typename T>
  static inline St& 
  operator >>(St& s, const vcsn::Element<S, T>& e);

  /*! unary operator for element. */
  template<typename S, typename T>
  static inline vcsn::Element<S, T> 
  operator-(const vcsn::Element<S, T>& e);

  /*! @} @} */

} // std

namespace vcsn {

  /*! @addtogroup fundamental */ /*! @{ */
  /*! @addtogroup operators   */ /*! @{ */

  /*! standard swap between two a priori different elements. */
  template<typename S1, typename T1, typename S2, typename T2>
  void swap(vcsn::Element<S1, T1>& e1, 
	    vcsn::Element<S2, T2>& e2);

  /*! standard swap between two a priori different implementation. */
  template<typename S, typename T1, typename T2>
  void swap(vcsn::Element<S, T1>& e1, 
	    vcsn::Element<S, T2>& e2);

  /*! standard swap between an element and something else. (left version) */
  template<typename S, typename T, typename U>
  void swap(vcsn::Element<S, T>& e1, U& v);

  /*! standard swap between an element and something else. (right version) */
  template<typename U, typename S, typename T>
  void swap(U& v, vcsn::Element<S, T>& e);

  /*! @} @} */  

} // vcsn

# include <vaucanson/fundamental/element_ops.hxx>

#endif // VCSN_FUNDAMENTAL_ELEMENTS_OPS_HH


