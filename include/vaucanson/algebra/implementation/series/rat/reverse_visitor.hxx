// reverse_visitor.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HXX

# include <vaucanson/algebra/implementation/series/rat/reverse_visitor.hh>

namespace vcsn
{

  namespace rat
  {

    template <class Semiring, class Word, class Weight>
    ReverseVisitor<Semiring, Word, Weight>::
    ReverseVisitor(const algebra::SemiringBase<Semiring>& s) : s_ (s)
    {}

    template <class Semiring, class Word, class Weight>
    void
    ReverseVisitor<Semiring, Word, Weight>::
    product(rat::Node<Word, Weight>* lhs, rat::Node<Word, Weight>* rhs)
    {
      lhs->accept(*this);
      rhs->accept(*this);
      swap(lhs, rhs);
    }

    template <class Semiring, class Word, class Weight>
    void
    ReverseVisitor<Semiring, Word, Weight>::left_weight(Weight& w)
    {
      w = transpose(w);
    }

    template <class Semiring, class Word, class Weight>
    void
    ReverseVisitor<Semiring, Word, Weight>::right_weight(Weight& w)
    {
      w = transpose(s_, w);
    }

    template <class Semiring, class Word, class Weight>
    void
    ReverseVisitor<Semiring, Word, Weight>::constant(Word& w)
    {
      w = mirror(w);
    }

    template <class Semiring, class Word, class Weight>
    template <class S>
    Weight
    ReverseVisitor<Semiring, Word, Weight>::
    transpose(const algebra::SeriesBase<S>& s, const Weight& w)
    {
      Element<S, Weight> e (s, w);
      e.transpose();
      return e.value();
    }

    template <class Semiring, class Word, class Weight>
    template <class S>
    Weight
    ReverseVisitor<Semiring, Word, Weight>::
    transpose(const algebra::SemiringBase<S>&, const Weight& w)
    {
      return w;
    }

  } // End of namespace rat.

  namespace algebra
  {

    template <typename S, typename Word, typename Weight>
    rat::exp<Word, Weight>&
    DefaultTransposeFun< S, rat::exp<Word, Weight> >::
    operator () (const S& s, const rat::exp<Word, Weight>& exp)
    {
      rat::exp<Word, Weight>* rexp = new rat::exp<Word, Weight> (exp);
      rat::ReverseVisitor<typename S::semiring_t, Word, Weight>
	rv (s.semiring());

      rexp.accept(rv);
      return *rexp;
    }

  } // End of namespace algebra.

} // End of namespace vcsn.

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_REVERSE_VISITOR_HXX
