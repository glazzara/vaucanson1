// element_ops.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_FUNDAMENTAL_ELEMENT_OPS_HXX
# define VCSN_FUNDAMENTAL_ELEMENT_OPS_HXX

/** @addtogroup design_pattern *//** @{ */
/** @addtogroup operators   *//** @{ */
/**
 * @file element_ops.hxx
 * @brief Implementations of external operators standard delegations for @c Element
 */
/** @} @} */

# include <vaucanson/design_pattern/element_ops.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/misc/static.hh>
# include <vaucanson/misc/unique.hh>

namespace vcsn {

  /*-------------------------.
  | Operator prototype forms |
  `-------------------------*/

#define ELEMENT_OP_PROTO_SYM(Op, Ret)				\
template<typename S1, typename T1, typename S2, typename T2>	\
Ret operator Op(const Element<S1, T1>& x1,			\
		const Element<S2, T2>& x2)

#define ELEMENT_OP_PROTO_LEFT_FOREIGN(Op, Ret)			\
template<typename S1, typename T1, typename T2>			\
Ret operator Op(const Element<S1, T1>& x1, const T2& x2)

#define ELEMENT_OP_PROTO_RIGHT_FOREIGN(Op, Ret)			\
template<typename T1, typename S2, typename T2>			\
Ret operator Op(const T1& x1, const Element<S2, T2>& x2)

  /*--------------------------.
  | Standard delegation forms |
  `--------------------------*/

#define DELEGATE_SYM(OpName) \
 return op_ ## OpName(x1.set(), x2.set(), x1.value(), x2.value())
#define DELEGATE_LEFT_FOREIGN(OpName) \
 return op_ ## OpName(x1.set(), x1.value(), op_convert(x1.set(), SELECT(T1), x2))
#define DELEGATE_RIGHT_FOREIGN(OpName) \
 return op_ ## OpName(x2.set(), op_convert(x2.set(), SELECT(T2), x1), x2.value())


  /*-----------------------------.
  | Standard boolean delegations |
  `-----------------------------*/

#define BOOLEAN_DELEGATION(Op, OpName)						\
  ELEMENT_OP_PROTO_SYM(Op, bool) { DELEGATE_SYM(OpName); }			\
  ELEMENT_OP_PROTO_LEFT_FOREIGN(Op, bool) { DELEGATE_LEFT_FOREIGN(OpName); }	\
  ELEMENT_OP_PROTO_RIGHT_FOREIGN(Op, bool) { DELEGATE_RIGHT_FOREIGN(OpName); }

  BOOLEAN_DELEGATION(==, eq)
  BOOLEAN_DELEGATION(<, lt)
#undef BOOLEAN_DELEGATION

#define BOOLEAN_CANONICAL_DELEGATION(Op, Not, X1, Del, X2)				\
  ELEMENT_OP_PROTO_SYM(Op, bool) { return Not (x ## X1 Del x ## X2); }			\
  ELEMENT_OP_PROTO_LEFT_FOREIGN(Op, bool) { return Not (x ## X1 Del x ## X2); }		\
  ELEMENT_OP_PROTO_RIGHT_FOREIGN(Op, bool) { return Not (x ## X1 Del x ## X2); }

  BOOLEAN_CANONICAL_DELEGATION(!=, !, 1, ==, 2)
  BOOLEAN_CANONICAL_DELEGATION(> ,  , 2, <, 1)
  BOOLEAN_CANONICAL_DELEGATION(>=, !, 1, <, 2)
  BOOLEAN_CANONICAL_DELEGATION(<=, !, 2, <, 1)
#undef BOOLEAN_CANONICAL_DELEGATION

#undef ELEMENT_PROTO_SYM
#undef ELEMENT_PROTO_LEFT_FOREIGN
#undef ELEMENT_PROTO_RIGHT_FOREIGN
#undef DELEGATE_SYM
#undef DELEGATE_LEFT_FOREIGN
#undef DELEGATE_RIGHT_FOREIGN

    /*----------------------------------.
    | Standard arithmetical delegations |
    `----------------------------------*/

#define ELEMENT_OPERATOR(Op, HookName)							\
template<typename S1, typename T1, typename S2, typename T2>				\
static 										\
typename op_##HookName##_traits<S1, S2, T1, T2>::ret_t					\
operator Op(const Element<S1, T1>& e1, const Element<S2, T2>& e2)			\
{											\
  /* Compute return Element type */							\
  typedef typename op_##HookName##_traits<S1, S2, T1, T2>::ret_t ret_t;			\
											\
  /* Compute return structural element from return Element type	*/			\
  const bool want_s1 = utility::static_eq<S1, typename ret_t::set_t>::value;		\
  typedef typename utility::static_if<want_s1, S1, S2>::t ret_set_t;			\
  const ret_set_t& s = 									\
    utility::static_if<want_s1, const S1, const S2>::choose(e1.set(), e2.set());	\
											\
  /* Delegate */									\
  return Element<ret_set_t, typename ret_t::value_t>					\
    (s, op_##HookName(e1.set(), e2.set(), e1.value(), e2.value()));		\
}											\
											\
template<typename S, typename T, typename U>						\
static Element<S, T>								\
operator Op(const Element<S, T>& e, const U& v)						\
{											\
  return Element<S, T> (e.set(),					\
			op_##HookName(e.set(),						\
				      e.value(),					\
				      op_convert(e.set(), SELECT(T), v)));		\
}											\
											\
template<typename U, typename S, typename T>						\
static Element<S, T>								\
operator Op(const U& v, const Element<S, T>& e)						\
{											\
  return Element<S, T> (e.set(),					\
			op_ ## HookName(e.set(),					\
					op_convert(e.set(), SELECT(T), v),		\
					e.value()));					\
}

ELEMENT_OPERATOR(+, add)
ELEMENT_OPERATOR(-, sub)
ELEMENT_OPERATOR(*, mul)
ELEMENT_OPERATOR(/, div)
ELEMENT_OPERATOR(%, mod)

#undef ELEMENT_OPERATOR

/*-----------------------------------------------.
| Implementation of input and output delegations |
`-----------------------------------------------*/

template<typename St, typename S, typename T>
static St&
operator <<(St& s, const Element<S, T>& e)
{
  return op_rout(e.set(), s, e.value());
}

template<typename St, typename S, typename T>
static St&
operator >>(St& s, Element<S, T>& e)
<<<<<<< .working
{
  return op_rin(e.set(), s, e.value());
=======
{ 
  S set = S();
  if (e.bound())
     set = S(e.set());
  op_rin(set, s, e.value());
  e = Element<S, T>(utility::unique::get(S(set)), e.value());
  return s;
>>>>>>> .merge-right.r558
}

/*------------------------------------------.
| Implementation of the negation delegation |
`------------------------------------------*/

template<typename S, typename T>
static Element<S, T>
operator-(const Element<S, T>& e)
{
  return Element<S, T>(e.set(), op_neg(e.set(), e.value()));
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
    assertion(&e1.set() == &e2.set());
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

#endif // VCSN_FUNDAMENTAL_ELEMENT_OPS_HXX
