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
    | BinOp |
    `------*/
    //! BinOp is a generic class which symbolised binary operator.
    /*! BinOp is integrated in the pattern matching system to permit
      a factorization of the accessors.
    */
    template <class T>
    struct BinOp
    {
      typedef T node_type;
      
      BinOp();
      BinOp(const BinOp& b);
      BinOp(const T& lhs, const T& rhs);
      T&		lhs();
      const T&		lhs() const;
      T&		rhs();
      const T&		rhs() const;
      
    private:
      T lhs_, rhs_;
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
      U
      match(const T& ast) const;
      
    protected:
      GenericMatcher();
    };

#define DecBinOp(N, T)					\
struct N     : public BinOp<T>				\
{							\
  N(const T& lhs, const T& rhs) : BinOp<T>(lhs, rhs)	\
  {}							\
};

#define DecLeaf(N, U)				\
  struct N : public Value<U>			\
  {						\
    N(const U& v) :				\
      Value<U>(v)				\
    {}						\
  };


#define MATCH__(N, lhs, rhs)			\
U						\
match_node(const N& p____) const		\
{						\
  typename N::node_type lhs = p____.lhs_;	\
  typename N::node_type rhs = p____.rhs_;
  
#define MATCH_(N, v)				\
U						\
match_node(const N& p____) const		\
{						\
  typename N::value_type v = p____.v_;
  
#define END }

    } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_KRAT_EXP_PATTERN_HH
