// dispatch_visitor.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
