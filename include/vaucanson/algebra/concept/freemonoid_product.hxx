// freemonoid_product.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HXX
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HXX

# include <vaucanson/algebra/concept/freemonoid_product.hh>

namespace vcsn
{
  namespace algebra
  {
    template <typename F, typename S>
    monoid_rep<FreeMonoidProduct<F, S> >::monoid_rep() :
    open_par("("),
    sep(","),
    close_par(")")
    {
      maybe_epsilon.clear();

      // Sane defaults.
      maybe_epsilon.push_back("1");
      maybe_epsilon.push_back("e");

      // Trying with more than one char.
      maybe_epsilon.push_back("_e");
      maybe_epsilon.push_back("eps");

      empty = *(maybe_epsilon.begin());
      concat = "";
    }

    template <typename Semiring, typename F, typename S>
    series_rep<Semiring, FreeMonoidProduct<F, S> >::series_rep() :
	open_par("("),
	close_par(")"),
	plus("+"),
	times("."),
	star("*"),
	zero("0"),
	open_weight("{"),
	close_weight("}")
    {
      spaces.push_back(" ");
    }

    template <typename Semiring, typename F, typename S>
    series_rep<Semiring, F>&
    series_rep<Semiring, FreeMonoidProduct<F, S> >::first_representation()
    {
      return first_representation_;
    }

    template <typename Semiring, typename F, typename S>
    const series_rep<Semiring, F>&
    series_rep<Semiring, FreeMonoidProduct<F, S> >::first_representation() const
    {
      return first_representation_;
    }

    template <typename Semiring, typename F, typename S>
    series_rep<Semiring, S>&
    series_rep<Semiring, FreeMonoidProduct<F, S> >::second_representation()
    {
      return second_representation_;
    }

    template <typename Semiring, typename F, typename S>
    const series_rep<Semiring, S>&
    series_rep<Semiring, FreeMonoidProduct<F, S> >::second_representation() const
    {
      return second_representation_;
    }

    template <typename F, typename S>
    bool
    operator==(boost::shared_ptr<monoid_rep<FreeMonoidProduct<F, S> > > lhs,
	       boost::shared_ptr<monoid_rep<FreeMonoidProduct<F, S> > > rhs)
    {
      return (lhs->open_par == rhs->open_par &&
	      lhs->sep == rhs->sep &&
	      lhs->close_par == rhs->close_par &&
	      lhs->empty == rhs->empty &&
	      lhs->concat == rhs->concat &&
	      lhs->maybe_epsilon == rhs->maybe_epsilon);
    }

    template <typename Semiring, typename F, typename S>
    bool
    operator==(boost::shared_ptr<series_rep<Semiring, FreeMonoidProduct<F, S> > > lhs,
	       boost::shared_ptr<series_rep<Semiring, FreeMonoidProduct<F, S> > > rhs)
    {
      // Type helpers.
      typedef series_rep<Semiring, F> first_rep_t;
      typedef series_rep<Semiring, S> second_rep_t;

      // FIXME: we should provide operator== for the pointed to types.
      boost::shared_ptr<first_rep_t> lhs_first(new first_rep_t());
      boost::shared_ptr<second_rep_t> lhs_second(new second_rep_t());
      boost::shared_ptr<first_rep_t> rhs_first(new first_rep_t());
      boost::shared_ptr<second_rep_t> rhs_second(new second_rep_t());

      *lhs_first = lhs->first_representation();
      *lhs_second = lhs->second_representation();
      *rhs_first = rhs->first_representation();
      *rhs_second = rhs->second_representation();

      return (lhs_first == rhs_first &&
	      lhs_second == rhs_second &&
	      lhs->open_par == rhs->open_par &&
	      lhs->close_par == rhs->close_par &&
	      lhs->plus == rhs->plus &&
	      lhs->times == rhs->times &&
	      lhs->star == rhs->star &&
	      lhs->zero == rhs->zero &&
	      lhs->open_weight == rhs->open_weight &&
	      lhs->close_weight == rhs->close_weight &&
	      lhs->spaces == rhs->spaces);
    }

    /*------------------------.
    | FreeMonoidProduct<F, S> |
    `------------------------*/

    template <class F, class S>
    FreeMonoidProduct<F, S>::FreeMonoidProduct(const F& a, const S& b) :
      first_monoid_ (a), second_monoid_ (b),
      rep_(monoid_rep_default<FreeMonoidProduct<F, S> >::get_instance())
    {}

    template <class F, class S>
    FreeMonoidProduct<F, S>::FreeMonoidProduct(const F& a, const S& b,
					       monoid_rep<FreeMonoidProduct<F, S> > mr) :
      first_monoid_ (a), second_monoid_ (b),
      rep_(boost::shared_ptr<monoid_rep<FreeMonoidProduct<F, S> > >(new monoid_rep<FreeMonoidProduct<F, S> >(mr)))
    {}

    template <class F, class S>
    FreeMonoidProduct<F, S>::FreeMonoidProduct(const FreeMonoidProduct& w) :
      FreeMonoidProductBase<FreeMonoidProduct<F, S> >(w),
      first_monoid_(w.first_monoid_),
      second_monoid_(w.second_monoid_),
      rep_(w.rep_)
    {}

    template <class F, class S>
    typename FreeMonoidProduct<F, S>::first_monoid_t&
    FreeMonoidProduct<F, S>::first_monoid()
    {
      return first_monoid_;
    }

    template <class F, class S>
    const typename FreeMonoidProduct<F, S>::first_monoid_t&
    FreeMonoidProduct<F, S>::first_monoid() const
    {
      return first_monoid_;
    }

    template <class F, class S>
    typename FreeMonoidProduct<F, S>::second_monoid_t&
    FreeMonoidProduct<F, S>::second_monoid()
    {
      return second_monoid_;
    }

    template <class F, class S>
    const typename FreeMonoidProduct<F, S>::second_monoid_t&
    FreeMonoidProduct<F, S>::second_monoid() const
    {
      return second_monoid_;
    }

    template <typename F, typename S>
    const boost::shared_ptr<monoid_rep<FreeMonoidProduct<F, S> > >
    FreeMonoidProduct<F, S>::representation() const
    {
      return rep_;
    }

    template <typename F, typename S>
    void
    FreeMonoidProduct<F, S>::set_representation(monoid_rep<FreeMonoidProduct<F, S> > mr)
    {
      rep_ = boost::shared_ptr<monoid_rep<FreeMonoidProduct<F, S> > >(new monoid_rep<FreeMonoidProduct<F, S> > (mr));
    }

    template<class F, class S>
    bool operator==(const FreeMonoidProduct<F, S>& a,
		    const FreeMonoidProduct<F, S>& b)
    {
      return (a.first_monoid() == b.first_monoid()) and
	     (a.second_monoid() == b.second_monoid());
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HXX
