// fundamental/elements_ops.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_FUNDAMENTAL_ELEMENTS_OPS_HXX
# define VCSN_FUNDAMENTAL_ELEMENTS_OPS_HXX

/** @addtogroup fundamental *//** @{ */
/** @addtogroup operators   *//** @{ */
/**
 * @file element_ops.hxx
 * @brief Implementations of external operators standard delegations for @c Element
 */
/** @} @} */

# include <vaucanson/fundamental/element_ops.hh>
# include <vaucanson/misc/selectors.hh>

namespace vcsn {

  /*-------------------------.
  | Operator prototype forms |
  `-------------------------*/

#define ELEMENT_OP_PROTO_SYM(Op, Ret)				\
template<typename S1, typename T1, typename S2, typename T2>	\
static inline							\
Ret operator Op(const Element<S1, T1>& e1,			\
		const Element<S2, T2>& e2)

#define ELEMENT_OP_PROTO_LEFT_FOREIGN(Op, Ret)			\
template<typename S1, typename T1, typename T2>			\
static inline							\
Ret operator Op(const Element<S1, T1>& e1, const T2& v2)

#define ELEMENT_OP_PROTO_LEFT(Op, Ret)				\
template<typename S1, typename T1>				\
static inline							\
Ret operator Op(const Element<S1, T1>& e1, const T1& v2)

#define ELEMENT_OP_PROTO_RIGHT_FOREIGN(Op, Ret)			\
template<typename T1, typename S2, typename T2>			\
static inline							\
Ret operator Op(const T1& v1, const Element<S1, T1>& e2)

#define ELEMENT_OP_PROTO_RIGHT(Op, Ret)				\
template<typename T1, typename S1>				\
static inline							\
Ret operator Op(const T1& v1, const Element<S1, T1>& e2)

  /*--------------------------.
  | Standard delegation forms |
  `--------------------------*/

#define DELEGATE_SYM(OpName) \
 return op_ ## OpName(e1.set(), e2.set(), e1.value(), e2.value())
#define DELEGATE_LEFT(OpName) \
 return op_ ## OpName(e1.set(), e1.value(), v2) 
#define DELEGATE_RIGHT(OpName) \
 return op_ ## OpName(e2.set(), v1, e2.value())
#define DELEGATE_LEFT_FOREIGN(OpName) \
 return op_ ## OpName(e1.set(), e1.value(), op_convert(e1.set(), SELECT(T1), v2)) 
#define DELEGATE_RIGHT_FOREIGN(OpName) \
 return op_ ## OpName(e2.set(), op_convert(e2.set(), SELECT(T2), v1), e2.value())


  /*-----------------------------.
  | Standard boolean delegations |
  `-----------------------------*/

#define BOOLEAN_DELEGATION(Op, OpName)						\
  ELEMENT_OP_PROTO_SYM(Op, bool) { DELEGATE_SYM(OpName); }			\
  ELEMENT_OP_PROTO_LEFT(Op, bool) { DELEGATE_LEFT(OpName); }			\
  ELEMENT_OP_PROTO_RIGHT(Op, bool) { DELEGATE_RIGHT(OpName); }			\
  ELEMENT_OP_PROTO_LEFT_FOREIGN(Op, bool) { DELEGATE_LEFT_FOREIGN(OpName); }	\
  ELEMENT_OP_PROTO_RIGHT_FOREIGN(Op, bool) { DELEGATE_RIGHT_FOREIGN(OpName); }

  BOOLEAN_DELEGATION(==, eq)
  BOOLEAN_DELEGATION(<, lt)
#undef BOOLEAN_DELEGATION

#define BOOLEAN_CANONICAL_DELEGATION(Op, Not, X1, Del, X2)				\
  ELEMENT_OP_PROTO_SYM(Op, bool) { return Not (e ## X1 Del e ## X2); }			\
  ELEMENT_OP_PROTO_LEFT(Op, bool) { return Not (e ## X1 Del v ## X2); }			\
  ELEMENT_OP_PROTO_RIGHT(Op, bool) { return Not (v ## X1 Del e ## X2); }		\
  ELEMENT_OP_PROTO_LEFT_FOREIGN(Op, bool) { return Not (e ## X1 Del v ## X2); }		\
  ELEMENT_OP_PROTO_RIGHT_FOREIGN(Op, bool) { return Not (v ## X1 Del e ## X2); }

  BOOLEAN_CANONICAL_DELEGATION(!=, !, 1, ==, 2)
  BOOLEAN_CANONICAL_DELEGATION(> ,  , 2, <, 1)
  BOOLEAN_CANONICAL_DELEGATION(>=, !, 1, <, 2)
  BOOLEAN_CANONICAL_DELEGATION(<=, !, 2, <, 1)
#undef BOOLEAN_CANONICAL_DELEGATION

    /*----------------------------------.
    | Standard arithmetical delegations |
    `----------------------------------*/

#define ELEMENT_OPERATOR(Op, HookName)							\
template<typename S1, typename T1, typename S2, typename T2>				\
static inline										\
typename op_##HookName##_traits<S1, S2, T1, T2>::ret_t					\
operator Op(const Element<S1, T1>& e1, const Element<S2, T2>& e2)			\
{											\
  // Compute return Element type							\
  typedef typename op_##HookName##_traits<S1, S2, T1, T2>::ret_t ret_t;			\
											\
  // Compute return structural element from return Element type				\
  const bool want_s1 = utility::static_eq<S1, typename ret_t::set_t>::value;		\
  typedef typename utility::static_if<want_s1, S1, S2>::t ret_set_t;			\
  const ret_set_t& s = 									\
    utility::static_if<want_s1, const S1, const S2>::choose(e1.set(), e2.set());	\
											\
  // Delegate										\
  return Element<ret_set_t, typename ret_t::value_t>					\
    (avoid_uniquify(s), op_##HookName(e1.set(), e2.set(), e1.value(), e2.value()));	\
}											\
											\
template<typename S, typename T, typename U>						\
static inline Element<S, T>								\
operator Op(const Element<S, T>& e, const U& v)						\
{											\
  return Element<S, T> (avoid_uniquify(e.set()),					\
			op_##HookName(e.set(),						\
				      e.value(),					\
				      op_convert(e.set(), SELECT(T), v)));		\
}											\
											\
template<typename U, typename S, typename T>						\
static inline Element<S, T>								\
operator Op(const U& v, const Element<S, T>& e)						\
{											\
  return Element<S, T> (avoid_uniquify(e.set()),					\
			op_ ## HookName(e.set(),					\
					op_convert(e.set(), SELECT(T), v),		\
					e.value()));					\
}

ELEMENT_OPERATOR(+, add);
ELEMENT_OPERATOR(-, sub);
ELEMENT_OPERATOR(*, mul);
ELEMENT_OPERATOR(/, div);
ELEMENT_OPERATOR(%, mod);

#undef ELEMENT_OPERATOR

/*-----------------------------------------------.
| Implementation of input and output delegations |
`-----------------------------------------------*/

template<typename St, typename S, typename T>
static inline St& 
operator <<(St& s, const Element<S, T>& e)
{ 
  return op_rout(e.set(), s, e.value()); 
}

template<typename St, typename S, typename T>
static inline St& 
operator >>(St& s, const Element<S, T>& e)
{ 
  return op_rin(e.set(), s, e.value()); 
}

/*------------------------------------------.
| Implementation of the negation delegation |
`------------------------------------------*/

template<typename S, typename T>
static inline Element<S, T> 
operator-(const Element<S, T>& e)
{ 
  return Element<S, T>(avoid_uniquify(e.set()), op_neg(e.set(), e.value())); 
}

} // vcsn


/*--------------------------------------.
| Implementation of the swap delegation |
`--------------------------------------*/

namespace std
{
  template<typename S, typename T1, typename T2>
  void swap(vcsn::Element<S, T1>& e1, 
	    vcsn::Element<S, T2>& e2)
  { 
    assert(&e1.set() == &e2.set());
    vcsn::op_swap(e1.set(), e1.value(), e2.value()); 
  } 

  template<typename S, typename T>
  void swap(vcsn::Element<S, T>& e1, T& v2)
  { 
    vcsn::op_swap(e1.set(), e1.value(), v2);
  }

  template<typename T, typename S>
  void swap(T& v1, vcsn::Element<S, T>& e2)
  { 
    vcsn::op_swap(e2.set(), v1, e2.value());
  }
} // std

#endif // VCSN_FUNDAMENTAL_ELEMENTS_OPS_HXX


