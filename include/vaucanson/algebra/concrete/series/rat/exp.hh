// exp.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_RAT_EXP_HH
# define VCSN_ALGEBRA_CONCRETE_SERIES_RAT_EXP_HH

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>
# include <vaucanson/algebra/concrete/series/rat/depth_visitor.hh>
# include <vaucanson/algebra/concrete/series/transpose.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/misc/deferrer.hh>

# include <algorithm>
# include <iostream>

namespace vcsn {

  namespace rat {

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
      typedef LetterT monoid_value_t;
      typedef WeightT semiring_elt_value_t;

      exp();
      exp(node_t* p);
      exp(const node_t* p);
      exp(const exp& other);
      exp& operator=(const exp& other);
      exp& swap(exp& otether);
      exp& operator+=(const exp& other);
      exp& operator*=(const exp& other);
      exp& star();
      void accept(ConstNodeVisitor<monoid_value_t, semiring_elt_value_t>& v) const;
      size_t depth() const;
      ~exp();
      node_t* &base();
      node_t* const &base() const;
      bool operator==(const exp& other) const;
      bool operator!=(const exp& other) const;
      bool operator<(const exp& other) const;
      exp clone() const;
      static exp one();
      static exp zero();
      static exp constant(const monoid_value_t& l);
      static bool starable();

    protected:
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

    // FIXME: this is an evil hack, but without it there is an ambiguity
    // in calls to exp * number or num * exp
    // FIXME: high level fixme !

    template<typename M, typename S, typename T>
    exp<M, Element<S, T> >
    operator*(const Element<S, T>& lhs,
	      const exp<M, Element<S, T> >& rhs);

    template<typename M, typename S, typename T>
    exp<M, Element<S, T> >
    operator*(const exp<M, Element<S, T> >& lhs,
	      const Element<S, T>& rhs);

  } // rat

  namespace algebra {

    template <typename S, typename M, typename W>
    struct DefaultTransposeFun<S, rat::exp<M, W> >
    {
      rat::exp<M, W>&
      operator()(const S&, const rat::exp<M, W>& exp);
    };

    template <class Matcher, class Monoid, class Semiring>
    class DispatchVisitor :
      public rat::DefaultMutableNodeVisitor<Monoid, Semiring>
    {
    public:
      typedef Matcher					matcher_t;
      typedef typename Matcher::return_type		return_type;
      typedef Monoid					monoid_value_t;
      typedef Semiring					semiring_elt_value_t;
      typedef rat::Node<monoid_value_t, semiring_elt_value_t>	node_t;

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
      constant(const monoid_value_t& m);

      virtual void
      zero();

      virtual void
      one();

      return_type get_ret();

    private:
      matcher_t&			matcher_;
      utility::Deferrer<return_type>	ret_;
    };

    /**
     * Classical dispatch function for rat::exp.
     *
     * @param matcher The matcher to use for the dispatching.
     * @param exp The exp to dispatch the matcher on.
     */
    template <class M, class W>
    struct DispatchFunction<rat::exp<M, W> >
    {
      template <class Matcher>
      static inline
      typename Matcher::return_type
      d(Matcher& matcher, const rat::exp<M, W>& exp);
    };

  } // algebra

} // vcsn


namespace vcsn {

  template <class Monoid_, class Semiring_>
  class ReverseVisitor :
    public rat::DefaultMutableNodeVisitor<Monoid_, Semiring_>
  {
  public:
    virtual void
    product(rat::Node<Monoid_, Semiring_>* lhs,
	    rat::Node<Monoid_, Semiring_>* rhs);
  };

} // vcsn


#include <vaucanson/algebra/concrete/series/rat/dump_visitor.hh>

namespace std
{
  template<typename M_, typename W_>
  std::ostream& operator<<(std::ostream& o, const vcsn::rat::exp<M_, W_>& exp);

  template<typename M, typename W>
  void swap(vcsn::rat::exp<M, W>& lhs,
	    vcsn::rat::exp<M, W>& rhs);

} // std


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/concrete/series/rat/exp.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_ALGEBRA_CONCRETE_SERIES_RAT_EXP_HH
