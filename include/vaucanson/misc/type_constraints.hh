// type_constraints.hh
//
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


#ifndef UTILITY_TYPE_CONSTRAINTS_HH
# define UTILITY_TYPE_CONSTRAINTS_HH

#include <vaucanson/misc/constraints.hh>

namespace utility
{
  namespace concepts
  {



    /*-----------------------------.
    | DefaultConstructible concept |
    `-----------------------------*/

    template <typename T>
    struct DefaultConstructible
    {
      void constraints() { T a UnusedConceptVar; }
    };

    /*-------------------.
    | Assignable concept |
    `-------------------*/

    template <typename T, typename From = T>
    struct Assignable
    {
      T a;
      From b;
      void constraints()
      {
	(void)check();
	(void)const_constraints(b);
      }
      T& check() { return (a = b) ; }
      T& const_constraints(const From& c) { return (a = c); }
    };

    /*--------------------------.
    | CopyConstructible concept |
    `--------------------------*/

    template <typename T>
    struct CopyConstructible
    {
      T b;
      void constraints() 
      {
	T a(b) UnusedConceptVar;               // require copy constructor
	// T* ptr UnusedConceptVar = &a;       // require address of operator
	const_constraints(a);
      }
      void const_constraints(const T& a)
      {
	T c(a) UnusedConceptVar;           // require const copy constructor
	// const T* ptr = &c;    // require const address of operator
      }
    };

    /*--------------------.
    | Convertible concept |
    `--------------------*/

    template <typename From, typename To>
    struct Convertible
    {
      From x;
      void constraints() 
      {
	function_requires<Assignable<To, From> >();
	(void)check();  
      }
      To check() { return x; }
    };


    /*------------------.
    | Operator concepts |
    `------------------*/

#define UTILITY_DEFINE_BINOP_CONSTRAINT(Operator, Name)		\
    template <typename T, typename U = T>			\
    struct Name							\
    {								\
      static const T x; static const U y;					\
      void constraints() { (void)test_bool(); }			\
      bool test_bool()						\
      {  return x Operator y; }	\
    }

    UTILITY_DEFINE_BINOP_CONSTRAINT(==, EqualityComparable);
    UTILITY_DEFINE_BINOP_CONSTRAINT(!=, DifferenceComparable);
    UTILITY_DEFINE_BINOP_CONSTRAINT(<, LessThanComparable);
    UTILITY_DEFINE_BINOP_CONSTRAINT(>, GreaterThanComparable);
    UTILITY_DEFINE_BINOP_CONSTRAINT(<=, LessOrEqualComparable);
    UTILITY_DEFINE_BINOP_CONSTRAINT(>=, GreaterOrEqualComparable);

#undef UTILITY_DEFINE_BINOP_CONSTRAINT
#define UTILITY_DEFINE_BINOP_CONSTRAINT(Operator, Name)		\
    template <typename R, typename T = R, typename U = T>	\
    struct Name							\
    {								\
      static const T x; static const U y;					\
      void constraints() { (void)check(); }			\
      R check() { return x Operator y; }			\
    }

    UTILITY_DEFINE_BINOP_CONSTRAINT(*, Multipliable);
    UTILITY_DEFINE_BINOP_CONSTRAINT(+, Addable);

#undef UTILITY_DEFINE_BINOP_CONSTRAINT
#define UTILITY_DEFINE_BINOP_CONSTRAINT(Operator, Name)		\
    template <typename T, typename U = T>			\
    struct Name							\
    {								\
      static T x; static const U y;						\
      void constraints() { (void)check(); }			\
      T& check() { return x Operator y; }			\
    }

    UTILITY_DEFINE_BINOP_CONSTRAINT(*=, InplaceMultipliable);
    UTILITY_DEFINE_BINOP_CONSTRAINT(+=, InplaceAddable);

#undef UTILITY_DEFINE_BINOP_CONSTRAINT

    template <typename T>
    struct PreIncrementable
    {
      T x;
      void constraints() { (void)check(); }
      T& check() { return ++x; }
    };

    template <typename T>
    struct PostIncrementable
    {
      T x;
      void constraints() { (void)check(); }
      T check() { return x++; }
    };

    template <typename T>
    struct Incrementable
    {
      void constraints() 
      { 
	function_requires<PreIncrementable<T> >();
	function_requires<PostIncrementable<T> >();
      }
    };

    template <typename T, typename R>
    struct Dereferenceable
    {
      T x;
      void constraints() { (void)check(); }
      R check() { return (R)(*x); }
    };


  }
}

#endif
