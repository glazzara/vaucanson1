// dispatch_visitor.hh: this file is part of the Vaucanson project.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DISPATCH_VISITOR_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DISPATCH_VISITOR_HH

# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/misc/deferrer.hh>

namespace vcsn
{

  namespace algebra
  {

    template <class Matcher, class Monoid, class Semiring>
    class DispatchVisitor :
      public rat::DefaultMutableNodeVisitor<Monoid, Semiring>
    {
    public:
      typedef Matcher					matcher_t;
      typedef typename Matcher::return_type		return_type;
      typedef Monoid					monoid_elt_value_t;
      typedef Semiring					semiring_elt_value_t;
      typedef rat::Node<monoid_elt_value_t, semiring_elt_value_t>	node_t;

      DispatchVisitor(Matcher& m);

      virtual
      ~DispatchVisitor();

      virtual void
      product(const node_t* lhs, const node_t* rhs);

      virtual void
      sum(const node_t* lhs, const node_t* rhs);

      virtual void
      star(const node_t* node);

      virtual void
      left_weight(const semiring_elt_value_t& w, const node_t* node);

      virtual void
      right_weight(const semiring_elt_value_t& w, const node_t* node);

      virtual void
      constant(const monoid_elt_value_t& m);

      virtual void
      zero();

      virtual void
      one();

      return_type get_ret();

    private:
      matcher_t&			matcher_;
      utility::Deferrer<return_type>	ret_;
    };

    template <class T>
    struct DispatchFunction;

    /**
     * Classical dispatch function for rat::exp.
     *
     * @param matcher The matcher to use for the dispatching.
     * @param exp The exp to dispatch the matcher on.
     */
    template <class M, class W>
    struct DispatchFunction< rat::exp<M, W> >
    {
      template <class Matcher>
      static
      typename Matcher::return_type
      d(Matcher& matcher, const rat::exp<M, W>& exp);
    };

  } // End of namespace algebra.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/series/rat/dispatch_visitor.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_DISPATCH_VISITOR_HH
