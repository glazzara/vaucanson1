// krat_exp_pattern.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PATTERN_HH
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PATTERN_HH

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <iostream>
# include <utility>
# include <vaucanson/misc/contract.hh>

namespace vcsn {

  namespace algebra {

    /*---------.
    | BinaryOp |
    `---------*/
    /// BinaryOp is a generic class which symbolised binary operator.
    /** BinaryOp is integrated in the pattern matching system to permit
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
    /// UnaryOp is a generic class which symbolised binary operator.
    /** UnaryOp is integrated in the pattern matching system to permit
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
    /// Value is a generic class which symbolised leaf of AST.
    /** Value is integrated into the pattern matching system to permit
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

    /**
     * GenericMatcher manages the dispatch of pattern matching.
     *
     * GenericMatcher delegates the dispatch of pattern matching to a
     * function-object: if you want to write an algorithm based on
     * pattern matching, inherit from this class.
     */
    template <class Self, class T, class U, class F>
    struct GenericMatcher
    {
      typedef U return_type;

      /**
       * Effectively performs the match.
       *
       * @param ast The object to perform the match on.
       *
       * @see DispatchVisitor::DispatchVisitor
       */
      U
      match(const T& ast);

    protected:
      GenericMatcher();
    };

#define DecBinaryOp(N, T, U)					\
struct N     : public vcsn::algebra::BinaryOp<T, U>		\
{								\
  N(const T& lhs, const U& rhs) : vcsn::algebra::BinaryOp<T, U>(lhs, rhs) \
  {}								\
};

#define DecUnaryOp(N, T)				\
struct N     : public vcsn::algebra::UnaryOp<T>		\
{							\
  N(const T& node) : vcsn::algebra::UnaryOp<T>(node)	\
  {}							\
};

#define DecLeaf(N, U)				\
  struct N : public vcsn::algebra::Value<U>	\
  {						\
    N(const U& v) :				\
      vcsn::algebra::Value<U>(v)		\
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
match_node##N(const N&) 			\
{

#define END }


    template <class Self, class T, class U, class F>
    struct KRatExpMatcher : public GenericMatcher<Self, T, U, F>
    {
      typedef U                          return_type;
      typedef typename T::semiring_elt_value_t semiring_elt_value_t;
      typedef typename T::monoid_value_t monoid_value_t;

      DecBinaryOp(Product, T, T);
      DecBinaryOp(Sum, T, T);
      DecUnaryOp(Star, T);
      DecBinaryOp(LeftWeight, semiring_elt_value_t, T);
      DecBinaryOp(RightWeight, T, semiring_elt_value_t);
      DecLeaf(Constant, monoid_value_t);
      DecFinalLeaf(One);
      DecFinalLeaf(Zero);

    protected:
      KRatExpMatcher() {}
    };

#define INHERIT_CONSTRUCTORS(Self, T, U, F) \
   typedef ::vcsn::algebra::KRatExpMatcher<Self, T, U, F> krat_exp_matcher_t; \
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
	struct KRatExpIdentity : vcsn::algebra::KRatExpMatcher<
	Self,
	T,
	Element<Series, T>,
	Dispatch
	>
	{
	  typedef Self				            self_t;
	  typedef Element<Series, T>                        return_type;
	  typedef typename Element<Series, T>::semiring_elt_t     semiring_elt_t;
	  typedef typename semiring_elt_t::value_t		    semiring_elt_value_t;
	  typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
	  typedef typename monoid_elt_t::set_t		    monoid_t;
	  typedef typename monoid_t::alphabet_t		    alphabet_t;
	  typedef typename alphabet_t::letter_t		    letter_t;
	  INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

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
	    return_type r (match(e));
	    r.star();
	    return r;
	  }
	  END

	  MATCH__(LeftWeight, w, e)
	  {
	    semiring_elt_t welt (exp_.set().semiring(), w);
	    return  welt * match(e);
	  }
	  END

	  MATCH__(RightWeight, e, w)
	  {
	    semiring_elt_t welt (exp_.set().semiring(), w);
	    return match(e) * welt;
	  }
	  END

	  MATCH_(Constant, m)
	  {
	    monoid_elt_t melt (exp_.set().monoid(), m);
	    return Element<Series, T> (exp_.set(), melt);
	  }
	  END

	  MATCH(Zero)
	  {
	    return zero_as<T>::of(exp_.set());
	  }
	  END

	  MATCH(One)
	  {
	    return identity_as<T>::of(exp_.set());
	  }
	  END

	protected:
	  Element<Series, T>  exp_;
	};


    } // algebra

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/series/krat_exp_pattern.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PATTERN_HH