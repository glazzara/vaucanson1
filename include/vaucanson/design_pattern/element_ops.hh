// element_ops.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_FUNDAMENTAL_ELEMENT_OPS_HH
# define VCSN_FUNDAMENTAL_ELEMENT_OPS_HH

/** @addtogroup design_pattern *//** @{ */
/** @addtogroup operators   *//** @{ */
/**
 * @file element_ops.hh
 * @brief Declarations of standard external operator delegations for @c Element
 */
/** @} @} */

# include <vaucanson/design_pattern/element_op_traits.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */
  /** @addtogroup operators   *//** @{ */

  /*-------------------.
  | Ordered comparison |
  `-------------------*/

  /// Comparison between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator<(const vcsn::Element<S1, T1>& e1,	
		 const vcsn::Element<S2, T2>& e2);	

  /// Comparison between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator>(const vcsn::Element<S1, T1>& e1,	
		 const vcsn::Element<S2, T2>& e2);	

  /// Comparison between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator<=(const vcsn::Element<S1, T1>& e1,	
		  const vcsn::Element<S2, T2>& e2);	

  /// Comparison between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator>=(const vcsn::Element<S1, T1>& e1,	
		  const vcsn::Element<S2, T2>& e2);	

  /// Comparison between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static inline
  bool operator <(const vcsn::Element<S, T>& e,
		  const U& v);

  /// Comparison between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static inline
  bool operator >(const vcsn::Element<S, T>& e,
		  const U& v);

  /// Comparison between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static inline
  bool operator >=(const vcsn::Element<S, T>& e,
		   const U& v);

  /// Comparison between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static inline
  bool operator <=(const vcsn::Element<S, T>& e,
		   const U& v);

  /// Comparison between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static inline
  bool operator <(const U& v,
		  const vcsn::Element<S, T>& e);

  /// Comparison between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static inline
  bool operator >(const U& v,
		  const vcsn::Element<S, T>& e);

  /// Comparison between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static inline
  bool operator >=(const U& v,
		   const vcsn::Element<S, T>& e);

  /// Comparison between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static inline
  bool operator <=(const U& v,
		   const vcsn::Element<S, T>& e);

  /*---------.
  | Equality |
  `---------*/

  /// Equality between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator ==(const vcsn::Element<S1, T1>& e1,	
		  const vcsn::Element<S2, T2>& e2);	

  /// Equality between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static inline
  bool operator ==(const vcsn::Element<S, T>& e,
		   const U& v);

  /// Equality between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static inline
  bool operator ==(const U& v,
		   const vcsn::Element<S, T>& e);

  /*-----------.
  | Difference |
  `-----------*/

  /// Difference between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	
  static inline							
  bool operator !=(const vcsn::Element<S1, T1>& e1,	
		  const vcsn::Element<S2, T2>& e2);	

  /// Difference between Element and foreign values (left version)
  template<typename S, typename T, typename U>
  static inline
  bool operator !=(const vcsn::Element<S, T>& e,
		   const U& v);

  /// Difference between Element and foreign values (right version)
  template<typename U, typename S, typename T>
  static inline
  bool operator !=(const U& v,
		   const vcsn::Element<S, T>& e);

  /*---------.
  | Addition |
  `---------*/

  /// Addition between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	      	
  static inline					     			
  typename vcsn::op_add_traits<S1, S2, T1, T2>::ret_t	
  operator+(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /// Addition between Element and foreign values (left)
  template<typename S, typename T, typename U>	       			
  static inline vcsn::Element<S, T>					
  operator +(const vcsn::Element<S, T>& e,				
	     const U& v);			       			

  /// Addition between Element and foreign values (right)
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator +(const U& v,			          		
	     const vcsn::Element<S, T>& e);

  /*-------------.
  | Substraction |
  `-------------*/

  /// Substraction between Element instances
  template<typename S1, typename T1, typename S2, typename T2> 		
  static inline						       		
  typename vcsn::op_sub_traits<S1, S2, T1, T2>::ret_t	
  operator-(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /// Substraction between Element and foreign values (left)
  template<typename S, typename T, typename U>		       		
  static inline vcsn::Element<S, T>					
  operator-(const vcsn::Element<S, T>& e,				
	    const U& v);				       		

  /// Substraction between Element and foreign values (right)
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator-(const U& v,					     		
	    const vcsn::Element<S, T>& e);

  /*---------------.
  | Multiplication |
  `---------------*/

  /// Multiplication between Element instances
  template<typename S1, typename T1, typename S2, typename T2> 		
  static inline						       		
  typename vcsn::op_mul_traits<S1, S2, T1, T2>::ret_t	
  operator*(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /// Multiplication between Element and foreign values (left)
  template<typename S, typename T, typename U>			       	
  static inline vcsn::Element<S, T>					
  operator*(const vcsn::Element<S, T>& e,			       
	    const U& v);					     	

  /// Multiplication between Element and foreign values (right)
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator*(const U& v,					     		
	    const vcsn::Element<S, T>& e);

  /*---------.
  | Division |
  `---------*/

  /// Division between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	       	
  static inline						       		
  typename vcsn::op_div_traits<S1, S2, T1, T2>::ret_t	
  operator/(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /// Division between Element and foreign values (left)
  template<typename S, typename T, typename U>			       	
  static inline vcsn::Element<S, T>					
  operator/(const vcsn::Element<S, T>& e,			       
	    const U& v);					       	

  /// Division between Element and foreign values (right)
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator/(const U& v,					     		
	    const vcsn::Element<S, T>& e);

  /*--------.
  | Modulus |
  `--------*/

  /// Modulus between Element instances
  template<typename S1, typename T1, typename S2, typename T2>	       	
  static inline						       		
  typename vcsn::op_mod_traits<S1, S2, T1, T2>::ret_t	
  operator%(const vcsn::Element<S1, T1>& e1,			
	    const vcsn::Element<S2, T2>& e2);				

  /// Modulus between Element and foreign values (left)
  template<typename S, typename T, typename U>		       		
  static inline vcsn::Element<S, T>					
  operator%(const vcsn::Element<S, T>& e,				
	    const U& v);				       		

  /// Modulus between Element and foreign values (right
  template<typename U, typename S, typename T>				       
  static inline vcsn::Element<S, T>					
  operator%(const U& v,					     		
	    const vcsn::Element<S, T>& e);

  /*---------------.
  | Unary negation |
  `---------------*/
 
  /// Unary negation of Element instances
  template<typename S, typename T>
  static inline vcsn::Element<S, T> 
  operator -(const vcsn::Element<S, T>&);

  /*-----------------.
  | Input and Output |
  `-----------------*/

  /// Output to stream
  template<typename St, typename S, typename T>
  static inline St& 
  operator <<(St& s, const vcsn::Element<S, T>& e);

  /// Input from stream
  template<typename St, typename S, typename T>
  static inline St& 
  operator >>(St& s, const vcsn::Element<S, T>& e);

  // This operator does not exist.

//   template<typename S1, typename T1, typename S2, typename T2>
//   static inline void /* do not use or specialize */
//   operator <<(const vcsn::Element<S1, T1>& e1,
// 	      const vcsn::Element<S2, T2>& e2);
  

  /** @} @} */

} // vcsn

namespace std {

  /** @addtogroup design_pattern *//** @{ */
  /** @addtogroup operators   *//** @{ */

  /*-----.
  | Swap |
  `-----*/

  /** Swap to Element instances with the same structure.
   * Calling this operators is valid only if the structural elements
   * of the two Element instances are equal.
   */
  template<typename S, typename T1, typename T2>
  void swap(vcsn::Element<S, T1>& e1, 
	    vcsn::Element<S, T2>& e2);

  /// Swap between Element and foreign values (left) 
  template<typename S, typename T>
  void swap(vcsn::Element<S, T>& e1, T& v2);

  /// Swap between Element and foreign values (right) 
  template<typename T, typename S>
  void swap(T& v1, vcsn::Element<S, T>& e2);

  /** @} @} */

} // std


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/design_pattern/element_ops.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_FUNDAMENTAL_ELEMENT_OPS_HH