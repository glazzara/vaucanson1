// dispatch_visitor.hxx: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DISPATCH_VISITOR_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DISPATCH_VISITOR_HXX

# include <vaucanson/algebra/implementation/series/rat/dispatch_visitor.hh>

namespace vcsn
{

  namespace algebra
  {

    template <class Matcher, class Monoid, class Semiring>
    DispatchVisitor<Matcher, Monoid, Semiring>::DispatchVisitor(Matcher& m) :
      matcher_(m)
    {}

    template <class Matcher, class Monoid, class Semiring>
    DispatchVisitor<Matcher, Monoid, Semiring>::~DispatchVisitor()
    {}

    template <class Matcher, class Monoid, class Semiring>
    void
    DispatchVisitor<Matcher, Monoid, Semiring>::
    product(const node_t* lhs, const node_t* rhs)
    {
      ret_ = matcher_.match_nodeProduct(typename Matcher::Product(lhs, rhs));
    }

    template <class Matcher, class Monoid, class Semiring>
    void
    DispatchVisitor<Matcher, Monoid, Semiring>::
    sum(const node_t* lhs, const node_t* rhs)
    {
      ret_ = matcher_.match_nodeSum(typename Matcher::Sum(lhs, rhs));
    }

    template <class Matcher, class Monoid, class Semiring>
    void
    DispatchVisitor<Matcher, Monoid, Semiring>::
    star(const node_t* node)
    {
      ret_ = matcher_.match_nodeStar(typename Matcher::Star(node));
    }

    template <class Matcher, class Monoid, class Semiring>
    void
    DispatchVisitor<Matcher, Monoid, Semiring>::
    left_weight(const semiring_elt_value_t& w, const node_t* node)
    {
      ret_ = matcher_.match_nodeLeftWeight(typename Matcher::LeftWeight(w,
									node));
    }

    template <class Matcher, class Monoid, class Semiring>
    void
    DispatchVisitor<Matcher, Monoid, Semiring>::
    right_weight(const semiring_elt_value_t& w, const node_t* node)
    {
      ret_ = matcher_.match_nodeRightWeight(typename
					    Matcher::RightWeight(node, w));
    }

    template <class Matcher, class Monoid, class Semiring>
    void
    DispatchVisitor<Matcher, Monoid, Semiring>::
    constant(const monoid_elt_value_t& m)
    {
      ret_ = matcher_.match_nodeConstant(typename Matcher::Constant(m));
    }

    template <class Matcher, class Monoid, class Semiring>
    void
    DispatchVisitor<Matcher, Monoid, Semiring>::
    zero()
    {
      ret_ = matcher_.match_nodeZero(typename Matcher::Zero());
    }

    template <class Matcher, class Monoid, class Semiring>
    void
    DispatchVisitor<Matcher, Monoid, Semiring>::
    one()
    {
      ret_ = matcher_.match_nodeOne(typename Matcher::One());
    }

    template <class Matcher, class Monoid, class Semiring>
    typename DispatchVisitor<Matcher, Monoid, Semiring>::return_type
    DispatchVisitor<Matcher, Monoid, Semiring>::
    get_ret()
    {
      return ret_;
    }

    template <class M, class W>
    template <class Matcher>
    typename Matcher::return_type
    DispatchFunction< rat::exp<M, W> >::d(Matcher& matcher,
					  const rat::exp<M, W>& exp)
    {
      DispatchVisitor<Matcher, M, W> v(matcher);
      exp.accept(v);
      return v.get_ret ();
    }

  } // End of namespace algebra.

} // End of namespace vcsn.

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DISPATCH_VISITOR_HXX
