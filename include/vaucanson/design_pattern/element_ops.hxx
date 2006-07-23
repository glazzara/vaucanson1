// element_ops.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_DESIGN_PATTERN_ELEMENT_OPS_HXX
# define VCSN_DESIGN_PATTERN_ELEMENT_OPS_HXX

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
 return op_ ## OpName(x1.structure(), x2.structure(), x1.value(), x2.value())

#define DELEGATE_LEFT_FOREIGN(OpName) \
  return op_ ## OpName(x1.structure(),					\
		       x1.value(),					\
		       op_convert(x1.structure(), SELECT(T1), x2))

#define DELEGATE_RIGHT_FOREIGN(OpName) \
  return op_ ## OpName(x2.structure(),					\
		       op_convert(x2.structure(), SELECT(T2), x1),	\
		       x2.value())


  /*-----------------------------.
  | Standard Boolean delegations |
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
  const bool want_s1 = misc::static_eq<S1, typename ret_t::set_t>::value;		\
  typedef typename misc::static_if<want_s1, S1, S2>::t ret_set_t;			\
  const ret_set_t& s = misc::static_if<want_s1, const S1, const S2>::     \
    choose(e1.structure(), e2.structure());				     \
											\
  /* Delegate */									\
  return Element<ret_set_t, typename ret_t::value_t>					\
    (s, op_##HookName(e1.structure(),					     \
		      e2.structure(),					     \
		      e1.value(),					     \
		      e2.value()));					     \
}											\
											\
template<typename S, typename T, typename U>						\
static Element<S, T>								\
operator Op(const Element<S, T>& e, const U& v)						\
{											\
  return Element<S, T> (e.structure(),					     \
			op_##HookName(e.structure(),			     \
				      e.value(),					\
				      op_convert(e.structure(),		     \
						 SELECT(T), v)));	     \
}											\
											\
template<typename U, typename S, typename T>						\
static Element<S, T>								\
operator Op(const U& v, const Element<S, T>& e)						\
{											\
  return Element<S, T> (e.structure(),					     \
			op_ ## HookName(e.structure(),			     \
					op_convert(e.structure(),	     \
						   SELECT(T), v),	     \
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
operator << (St& s, const Element<S, T>& e)
{
  return op_rout(e.structure(), s, e.value());
}

template<typename St, typename S, typename T>
static St&
operator >> (St& s, Element<S, T>& e)
{
  S structure = e.structure();
  op_rin(structure, s, e.value());
  e.attach(structure);
  return s;
}

/*------------------------------------------.
| Implementation of the negation delegation |
`------------------------------------------*/

template<typename S, typename T>
static Element<S, T>
operator-(const Element<S, T>& e)
{
  return Element<S, T>(e.structure(), op_neg(e.structure(), e.value()));
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
    assertion(&e1.structure() == &e2.structure());
    op_swap(e1.structure(), e1.value(), e2.value());
  }

  template<typename S, typename T>
  void swap(vcsn::Element<S, T>& e1, T& v2)
  {
    op_swap(e1.structure(), e1.value(), v2);
  }

  template<typename T, typename S>
  void swap(T& v1, vcsn::Element<S, T>& e2)
  {
    op_swap(e2.structure(), v1, e2.value());
  }
} // std

#endif // ! VCSN_DESIGN_PATTERN_ELEMENT_OPS_HXX
