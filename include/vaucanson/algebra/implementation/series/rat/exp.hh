// exp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_EXP_HH
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_EXP_HH

# include <vaucanson/algebra/implementation/series/rat/nodes.hh>
# include <vaucanson/design_pattern/element.hh>

namespace vcsn {

  namespace rat {

    /// Implementation of rational expression.
    template<typename LetterT, typename WeightT>
    class exp
    {
    public:
      typedef rat::Node<LetterT, WeightT>			node_t;
      typedef typename rat::Node<LetterT, WeightT>::type        type;
      typedef rat::Zero<LetterT, WeightT>			n_zero_t;
      typedef rat::One<LetterT, WeightT>			n_one_t;
      typedef rat::Sum<LetterT, WeightT>			n_sum_t;
      typedef rat::Product<LetterT, WeightT>			n_prod_t;
      typedef rat::Star<LetterT, WeightT>			n_star_t;
      typedef rat::Constant<LetterT, WeightT>			n_const_t;

    public:
      typedef LetterT monoid_elt_value_t;
      typedef WeightT semiring_elt_value_t;

      /// Constructors.
      //@{
      exp();
      exp(node_t* p);
      exp(const node_t* p);
      exp(const exp& other);
      //@}

      /// Destructor.
      ~exp();

      /// Classical operations.
      //@{
      exp& operator = (const exp& other);
      exp& operator += (const exp& other);
      exp& operator *= (const exp& other);
      //@}

      /// Star an expression.
      exp& star();

      /// Swap with another expression.
      exp& swap(exp& otether);

      /// Facility to accept a visitor on the root node.
      void
      accept(ConstNodeVisitor<monoid_elt_value_t, semiring_elt_value_t>& v)
	const;

      /// Compute the depth of the expression.
      size_t depth() const;

      /// Get the root node of the expression.
      //@{
      node_t*		&base();
      node_t* const	&base() const;
      //@}

      /// Comparisons operators.
      //@{
      bool operator == (const exp& other) const;
      bool operator != (const exp& other) const;
      bool operator < (const exp& other) const;
      //@}

      /// Copy the expression.
      exp clone() const;

      /// Basic expressions.
      //@{
      static exp one();
      static exp zero();
      static exp constant(const monoid_elt_value_t& l);
      //@}

      /// Always returns true, since a expression is always starable.
      static bool starable();

    protected:
      /// Root node.
      node_t *base_;
    };

    template<typename M, typename W>
    const exp<M, W> operator*(const exp<M, W>& lhs,
			      const exp<M, W>& rhs);

    template<typename M, typename W>
    exp<M, W> operator+(const exp<M, W>& lhs,
			const exp<M, W>& rhs);

    template<typename M, typename W>
    exp<M, W> operator*(const W& lhs,
			const exp<M, W>& rhs);

    template<typename M, typename W>
    exp<M, W> operator*(const exp<M, W>& lhs,
			const W& rhs);

    // FIXME: This is an *evil* hack, but without it there is an ambiguity
    // FIXME: in calls to exp * number or number * exp.

    template<typename M, typename S, typename T>
    exp<M, Element<S, T> >
    operator*(const Element<S, T>& lhs,
	      const exp<M, Element<S, T> >& rhs);

    template<typename M, typename S, typename T>
    exp<M, Element<S, T> >
    operator*(const exp<M, Element<S, T> >& lhs,
	      const Element<S, T>& rhs);

    template<typename M, typename W>
    void swap(vcsn::rat::exp<M, W>& lhs,
	      vcsn::rat::exp<M, W>& rhs);

  } // End of namespace rat.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/implementation/series/rat/exp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_RAT_EXP_HH
