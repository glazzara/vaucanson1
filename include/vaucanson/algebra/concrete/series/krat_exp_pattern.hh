// krat_exp_pattern.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#include <iostream>
#include <utility>
#include <cassert>

namespace vcsn {

  namespace algebra {
    
    /*------.
    | BinaryOp |
    `------*/
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
      match(const T& ast) const;
      
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
match_node(const N& p____) const		\
{						\
  typename N::lhs_node_type Lhs = p____.lhs();	\
  typename N::rhs_node_type Rhs = p____.rhs();
  
#define MATCH_(N, Val)				\
return_type					\
match_node(const N& p____) const		\
{						\
  typename N::value_type Val(p____.value());

#define MATCH(N)					\
return_type						\
match_node(const N& p____) const			\
{						

  
#define END }

    } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hxx>

#endif // VCSN_ALGEBRA_CONCRETE_KRAT_EXP_PATTERN_HH
