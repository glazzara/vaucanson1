// krat_exp_pattern.hh
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

#ifndef VCSN_ALGEBRA_CONCRETE_KRAT_EXP_PATTERN_HH
# define VCSN_ALGEBRA_CONCRETE_KRAT_EXP_PATTERN_HH

# include <vaucanson/fundamental/element.hh>
# include <vaucanson/algebra/concrete/series/series.hh>
# include <iostream>
# include <utility>
# include <cassert>

namespace vcsn {

  namespace algebra {
    
    /*---------.
    | BinaryOp |
    `---------*/
    //! BinaryOp is a generic class which symbolised binary operator.
    /*! BinaryOp is integrated in the pattern matching system to permit
      a factorization of the accessors.
    */
    template <class T, class U>
    struct BinaryOp
    {
      typedef T lhs_node_type;
      typedef U rhs_node_type;

      BinaryOp();
      BinaryOp(const BinaryOp& b);
      BinaryOp(const T& lhs, const U& rhs);
      T&		lhs();
      const T&		lhs() const;
      U&		rhs();
      const U&		rhs() const;
      
    private:
      T lhs_;
      U rhs_;
    };

    /*--------.
    | UnaryOp |
    `--------*/
    //! UnaryOp is a generic class which symbolised binary operator.
    /*! UnaryOp is integrated in the pattern matching system to permit
      a factorization of the accessors.
    */
    template <class T>
    struct UnaryOp
    {
      typedef T value_type;
      
      UnaryOp();
      UnaryOp(const UnaryOp& b);
      UnaryOp(const T& node);
      T&		value();
      const T&		value() const;
      
    private:
      T node_;
    };

    /*------.
    | Value |
    `------*/
    //! Value is a generic class which symbolised leaf of AST.
    /*! Value is integrated into the pattern matching system to permit 
      a factorization of the accessors.
    */
    template <class T>
    struct Value
    {
      typedef T value_type;
      
      Value();
      Value(const Value& v);
      Value(const T& v);
      const T&	value() const;
      T&	value();
      
    private:
      T v_;
    };

    /*---------------.
    | GenericMatcher |
    `---------------*/
    //! GenericMatcher manages the dispatch of pattern matching.
    /*! GenericMatcher delegates the dispatch of pattern matching to a
      function-object: if you want to write an algorithm based on
      pattern matching, inherit from this class.
    */
    template <class Self, class T, class U, class F>
    struct GenericMatcher
    {
      typedef U return_type;

      U
      match(const T& ast);
      
    protected:
      GenericMatcher();
    };

#define DecBinaryOp(N, T, U)					\
struct N     : public BinaryOp<T, U>				\
{								\
  N(const T& lhs, const U& rhs) : BinaryOp<T, U>(lhs, rhs)	\
  {}								\
};

#define DecUnaryOp(N, T)			\
struct N     : public UnaryOp<T>		\
{						\
  N(const T& node) : UnaryOp<T>(node)		\
  {}						\
};

#define DecLeaf(N, U)				\
  struct N : public Value<U>			\
  {						\
    N(const U& v) :				\
      Value<U>(v)				\
    {}						\
  };

#define DecFinalLeaf(N)				\
  struct N					\
  {						\
    N()						\
    {}						\
  };

#define MATCH__(N, Lhs, Rhs)			\
return_type					\
match_node##N(const N& p____) 		\
{						\
  typename N::lhs_node_type Lhs = p____.lhs();	\
  typename N::rhs_node_type Rhs = p____.rhs();
  
#define MATCH_(N, Val)				\
return_type					\
match_node##N(const N& p____) 		\
{						\
  typename N::value_type Val(p____.value());

#define MATCH(N)					\
return_type						\
match_node##N(const N&)					\
{						
   
#define END }


    template <class Self, class T, class U, class F>
    struct KRatExpMatcher : public GenericMatcher<Self, T, U, F>
    {
      typedef U                          return_type;
      typedef typename T::weight_value_t weight_value_t;
      typedef typename T::monoid_value_t monoid_value_t;

      DecBinaryOp(Product, T, T);
      DecBinaryOp(Sum, T, T);
      DecUnaryOp(Star, T);
      DecBinaryOp(LeftWeight, weight_value_t, T);
      DecBinaryOp(RightWeight, T, weight_value_t);
      DecLeaf(Constant, monoid_value_t);
      DecFinalLeaf(One);
      DecFinalLeaf(Zero);
      
    protected:
      KRatExpMatcher() {}
    };

#define INHERIT_CONSTRUCTORS(Self, T, U, F) \
   typedef vcsn::algebra::KRatExpMatcher<Self, T, U, F> krat_exp_matcher_t; \
   typedef typename krat_exp_matcher_t::Product		Product;             \
   typedef typename krat_exp_matcher_t::Sum		Sum;                \
   typedef typename krat_exp_matcher_t::Star		Star;                \
   typedef typename krat_exp_matcher_t::LeftWeight     	LeftWeight;          \
   typedef typename krat_exp_matcher_t::RightWeight     RightWeight;         \
   typedef typename krat_exp_matcher_t::Constant       	Constant;            \
   typedef typename krat_exp_matcher_t::One       	One;                 \
   typedef typename krat_exp_matcher_t::Zero       	Zero;           

    template <class T>
      struct DispatchFunction;

      template <class Self, class Series, class T, class Dispatch>
	struct KRatExpIdentity : algebra::KRatExpMatcher<
	Self,
	T, 
	Element<Series, T>,
	Dispatch
	>
	{
	  typedef Self				            self_t;
	  typedef Element<Series, T>                        return_type;
	  typedef typename Element<Series, T>::weight_t     weight_t;
	  typedef typename weight_t::value_t		    weight_value_t;
	  typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
	  typedef typename monoid_elt_t::set_t		    monoid_t;
	  typedef typename monoid_t::alphabet_t		    alphabet_t;
	  typedef typename alphabet_t::letter_t		    letter_t;
	  INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

	  KRatExpIdentity(const Element<Series, T>& exp) :
	    exp_(exp)
	  {}

	  MATCH__(Product, lhs, rhs)
	  {
	    return match(lhs) * match(rhs);
	  }
	  END

	  MATCH__(Sum, lhs, rhs)
	  {
	    return match(lhs) + match(rhs);
	  }
	  END

	  MATCH_(Star, e)
	  {
	    return match(e).star();
	  }
	  END

	  MATCH__(LeftWeight, w, e)
	  {
	    return  weight_t(w) * match(e);
	  }
	  END

	  MATCH__(RightWeight, e, w)
	  {
	    return match(e) * weight_t(w);
	  }
	  END

	  MATCH_(Constant, m)
	  {
	    Element<Series, T> s(exp_.set());
	    s = monoid_elt_t(m);
	    return s;
	  }
	  END

	  MATCH(Zero)
	  {
	    return exp_.set().zero(SELECT(T));	  
	  }
	  END

	  MATCH(One)
	  {
	    return exp_.set().identity(SELECT(T));	  
	  }
	  END

	protected:
	  Element<Series, T>  exp_;
	};

      
    } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hxx>

#endif // VCSN_ALGEBRA_CONCRETE_KRAT_EXP_PATTERN_HH
