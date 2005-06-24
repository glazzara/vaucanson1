// reverse_visitor.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HH

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/concept/semiring_base.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>

namespace vcsn
{

  namespace rat
  {

    template <class Semiring, class Word, class Weight>
    class ReverseVisitor :
      public rat::DefaultMutableNodeVisitor<Word, Weight>
    {
    public:
      ReverseVisitor(const algebra::SemiringBase<Semiring>& s);

      virtual
      void
      product(rat::Node<Word, Weight>* lhs,
	      rat::Node<Word, Weight>* rhs);

      virtual
      void
      constant(Word& w);

      virtual
      void
      left_weight(Weight& w);

      virtual
      void
      right_weight(Weight& w);

    protected:
      template <class S>
      static
      Weight
      transpose(const algebra::SeriesBase<S>&, const Weight&);

      template <class S>
      static
      Weight
      transpose(const algebra::SemiringBase<S>&, const Weight&);

      const Semiring& s_;
    };

  } // End of namespace rat.

  namespace algebra
  {

    template <typename S, typename T>
    struct DefaultTransposeFun;

    template <typename S, typename Word, typename Weight>
    struct DefaultTransposeFun< S, rat::exp<Word, Weight> >
    {
      rat::exp<Word, Weight>&
      operator () (const S&, const rat::exp<Word, Weight>& exp);
    };

  } // End of namespace algebra.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/series/rat/reverse_visitor.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HH
