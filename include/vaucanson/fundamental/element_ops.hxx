// fundamental/elements_ops.hxx
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

#ifndef FUNDAMENTAL_ELEMENTS_OPS_HXX
# define FUNDAMENTAL_ELEMENTS_OPS_HXX

# include <vaucanson/config/system.hh>
# include <vaucanson/fundamental/predefs.hh>
# include <vaucanson/fundamental/op_traits.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/misc/static.hh>

namespace vcsn {

#define ELEMENT_OPERATOR(Op)					\
template<typename S1, typename T1, typename S2, typename T2>	\
static inline							\
bool operator Op(const vcsn::Element<S1, T1>& e1,	\
		 const vcsn::Element<S2, T2>& e2)	\
{  using namespace std; return e1.value() Op e2.value(); }

  ELEMENT_OPERATOR(==);
  ELEMENT_OPERATOR(!=);
  ELEMENT_OPERATOR(<);
  ELEMENT_OPERATOR(>);
  ELEMENT_OPERATOR(<=);
  ELEMENT_OPERATOR(>=);

#undef ELEMENT_OPERATOR

    template<typename S, typename T, typename U>
    static inline
    bool operator ==(const vcsn::Element<S, T>& e,
		     const U& v)
    { 
      return vcsn::op_xeq(SELECT(S), e.value(), v); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator ==(const U& v,
		     const vcsn::Element<S, T>& e)
    { 
      return vcsn::op_xeq(SELECT(S), e.value(), v); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator !=(const vcsn::Element<S, T>& e,
		     const U& v)
    { 
      return !vcsn::op_xeq(SELECT(S), e.value(), v); 
    }

    template<typename U, typename S, typename T>
    static inline
    bool operator !=(const U& v,
		     const vcsn::Element<S, T>& e)
    { 
      return !vcsn::op_xeq(SELECT(S), e.value(), v); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator <(const vcsn::Element<S, T>& e,
		    const U& v)
    { 
      return vcsn::op_llt(SELECT(S), e.value(), v); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator <(const U& v,
		    const vcsn::Element<S, T>& e)
    { 
      return vcsn::op_rlt(SELECT(S), v, e.value()); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator >(const vcsn::Element<S, T>& e,
		    const U& v)
    { 
      return vcsn::op_rlt(SELECT(S), v, e.value()); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator >(const U& v,
		    const vcsn::Element<S, T>& e)
    { 
      return vcsn::op_llt(SELECT(S), e.value(), v); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator >=(const vcsn::Element<S, T>& e,
		     const U& v)
    { 
      return !vcsn::op_llt(SELECT(S), e.value(), v); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator >=(const U& v,
		     const vcsn::Element<S, T>& e)
    { 
      return !vcsn::op_rlt(SELECT(S), v, e.value()); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator <=(const vcsn::Element<S, T>& e,
		     const U& v)
    { 
      return !vcsn::op_rlt(SELECT(S), v, e.value()); 
    }

    template<typename S, typename T, typename U>
    static inline
    bool operator <=(const U& v,
		     const vcsn::Element<S, T>& e)
    { 
      return !vcsn::op_llt(SELECT(S), e.value(), v); 
    }


#define ELEMENT_OPERATOR(Op, HookName)						\
template<typename S1, typename T1, typename S2, typename T2>			\
static inline									\
typename vcsn::op_ ## HookName ## _traits<S1, S2, T1, T2>::ret_t	\
operator Op(const vcsn::Element<S1, T1>& e1,				\
	    const vcsn::Element<S2, T2>& e2)				\
{										\
  typedef typename vcsn::						\
    op_ ## HookName ## _traits<S1, S2, T1, T2>::ret_t ret_t;			\
										\
  const bool want_s1 = utility::static_eq<S1, typename ret_t::set_t>::value;	\
										\
  typedef typename utility::static_if<want_s1, S1, S2>::t ret_set_t;		\
										\
  const ret_set_t& s = utility::static_if<want_s1, const S1, const S2>::	\
    choose(e1.set(), e2.set());							\
										\
  return vcsn::Element<ret_set_t, typename ret_t::value_t>		\
    (s, vcsn::op_ ## HookName(e1.set(), e2.set(),			\
				       e1.value(), e2.value()));		\
}										\
										\
template<typename S, typename T, typename U>					\
static inline vcsn::Element<S, T>					\
operator Op(const vcsn::Element<S, T>& e,				\
	    const U& v)								\
{										\
  return vcsn::Element<S, T>						\
    (e.set(), 									\
     vcsn::								\
     op_ ## HookName(e.set(), 							\
		     e.value(), 						\
		     op_convert(SELECT(T), SELECT(S), v)));			\
}										\
										\
template<typename U, typename S, typename T>					\
static inline vcsn::Element<S, T>					\
operator Op(const U& v,								\
	    const vcsn::Element<S, T>& e)				\
{										\
  return vcsn::Element<S, T>						\
    (e.set(), 									\
     vcsn::								\
     op_ ## HookName(e.set(), 							\
		     op_convert(SELECT(T), SELECT(S), v),			\
		     e.value()));						\
}

ELEMENT_OPERATOR(+, add);
ELEMENT_OPERATOR(-, sub);
ELEMENT_OPERATOR(*, mul);
ELEMENT_OPERATOR(/, div);
ELEMENT_OPERATOR(%, mod);

#undef ELEMENT_OPERATOR

template<typename S1, typename T1, typename S2, typename T2>
static inline void /* do not use or specialize */
operator <<(const vcsn::Element<S1, T1>& e1,
	    const vcsn::Element<S2, T2>& e2);

template<typename St, typename S, typename T>
static inline St& 
operator <<(St& s, const vcsn::Element<S, T>& e)
{ 
  return vcsn::op_rout(e.set(), s, e.value()); 
}

template<typename St, typename S, typename T>
static inline St& 
operator >>(St& s, const vcsn::Element<S, T>& e)
{ 
  return vcsn::op_rin(e.set(), s, e.value()); 
}

template<typename S, typename T>
static inline vcsn::Element<S, T> 
operator-(const vcsn::Element<S, T>& e)
{ 
  return vcsn::op_neg(e.set(), e.value()); 
}

} // std



namespace vcsn
{
  template<typename S1, typename T1, typename S2, typename T2>
  void swap(vcsn::Element<S1, T1>& e1, 
	    vcsn::Element<S2, T2>& e2)
  { 
    vcsn::op_swap(SELECT(S1), SELECT(S2), e1.value(), e2.value()); 
  } 

  template<typename S, typename T1, typename T2>
  void swap(vcsn::Element<S, T1>& e1, 
	    vcsn::Element<S, T2>& e2)
  { 
    vcsn::op_swap(SELECT(S), e1.value(), e2.value()); 
  }

  template<typename S, typename T, typename U>
  void swap(vcsn::Element<S, T>& e1, U& v)
  { 
    vcsn::op_xswap(SELECT(S), e1.value(), v); 
  }

  template<typename U, typename S, typename T>
  void swap(U& v, vcsn::Element<S, T>& e)
  { 
    vcsn::op_xswap(SELECT(S), e.value(), v); 
  }
} // vcsn

#endif // FUNDAMENTAL_ELEMENTS_OPS_HXX


