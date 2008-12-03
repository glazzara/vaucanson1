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
    MonoidRep<FreeMonoidProduct<F, S> >::MonoidRep() :
	open_par("("),
	sep(","),
	close_par(")")
    {}

    template <typename Semiring, typename F, typename S>
    void
    SeriesRep<Semiring, FreeMonoidProduct<F, S> >::
    disambiguate(const monoid_t& monoid, pointer_t& p)
    {
      // Pointer types.
      typedef boost::shared_ptr<first_rep_t>		first_p_t;
      typedef boost::shared_ptr<second_rep_t>		second_p_t;

      first_p_t first_rep(new first_rep_t(p->first_representation()));
      second_p_t second_rep(new second_rep_t(p->second_representation()));

      // Backup old pointers.
      first_p_t first_rep_orig = first_rep;
      second_p_t second_rep_orig = second_rep;

      // Real work done here.
      first_rep->disambiguate(monoid.first_monoid(), first_rep);
      second_rep->disambiguate(monoid.second_monoid(), second_rep);

      // Copy on write.
      if (first_rep_orig != first_rep || second_rep_orig != second_rep)
      {
	self_t new_rep(*p);
	new_rep.first_representation() = *first_rep;
	new_rep.second_representation() = *second_rep;
	p = pointer_t(new self_t(new_rep));
      }
    }

    template <typename Semiring, typename F, typename S>
    SeriesRep<Semiring, F>&
    SeriesRep<Semiring, FreeMonoidProduct<F, S> >::first_representation()
    {
      return first_representation_;
    }

    template <typename Semiring, typename F, typename S>
    const SeriesRep<Semiring, F>&
    SeriesRep<Semiring, FreeMonoidProduct<F, S> >::first_representation() const
    {
      return first_representation_;
    }

    template <typename Semiring, typename F, typename S>
    SeriesRep<Semiring, S>&
    SeriesRep<Semiring, FreeMonoidProduct<F, S> >::second_representation()
    {
      return second_representation_;
    }

    template <typename Semiring, typename F, typename S>
    const SeriesRep<Semiring, S>&
    SeriesRep<Semiring, FreeMonoidProduct<F, S> >::second_representation() const
    {
      return second_representation_;
    }

    template <typename F, typename S>
    bool
    operator==(boost::shared_ptr<MonoidRep<FreeMonoidProduct<F, S> > > lhs,
	       boost::shared_ptr<MonoidRep<FreeMonoidProduct<F, S> > > rhs)
    {
      // Type helpers.
      typedef MonoidRepBase<MonoidRep, FreeMonoidProduct<F, S> >
	monoid_rep_base_t;
      typedef boost::shared_ptr<monoid_rep_base_t>	p_t;

      return (lhs->open_par == rhs->open_par &&
	      lhs->sep == rhs->sep &&
	      lhs->close_par == rhs->close_par &&
	      static_cast<p_t>(lhs) == static_cast<p_t>(rhs));
    }

    template <typename Semiring, typename F, typename S>
    bool
    operator==(boost::shared_ptr<SeriesRep<Semiring, FreeMonoidProduct<F, S> > > lhs,
	       boost::shared_ptr<SeriesRep<Semiring, FreeMonoidProduct<F, S> > > rhs)
    {
      // Type helpers.
      typedef SeriesRep<Semiring, F> first_rep_t;
      typedef SeriesRep<Semiring, S> second_rep_t;
      typedef SeriesRepBase<SeriesRep, Semiring, FreeMonoidProduct<F, S> >
	series_rep_base_t;

      // Pointer types.
      typedef boost::shared_ptr<first_rep_t>		first_p_t;
      typedef boost::shared_ptr<second_rep_t>		second_p_t;
      typedef boost::shared_ptr<series_rep_base_t>	p_t;

      // FIXME: we should provide operator== for the pointed to types.
      first_p_t lhs_first(new first_rep_t());
      second_p_t lhs_second(new second_rep_t());
      first_p_t rhs_first(new first_rep_t());
      second_p_t rhs_second(new second_rep_t());

      *lhs_first = lhs->first_representation();
      *lhs_second = lhs->second_representation();
      *rhs_first = rhs->first_representation();
      *rhs_second = rhs->second_representation();

      return (lhs_first == rhs_first &&
	      lhs_second == rhs_second &&
	      static_cast<p_t>(lhs) == static_cast<p_t>(rhs));
    }

    /*------------------------.
    | FreeMonoidProduct<F, S> |
    `------------------------*/

    // FIXME: This facility is a HACK. Explanations: when a high level
    // structural element (a structure inheriting from Structure) is
    // instantiated (say a series_set_t), the underlying monoid is only
    // accessible via const methods.  Unfortunately it means that when a
    // FreeMonoidProduct is instantiated (not as a non-const object) the
    // shared_ptr holding the pointers to the first and second monoid
    // representations can't be changed. And, because we originally planned to
    // use singleton (see get_instance()) and other clever tricks, an FMP<F, S>
    // with F == S will use the SAME representation for both the monoid.
    // (simply putted, changing the epsilon representation for the first monoid
    // will pass on to the second one). A lot of works needs to be done to
    // solve this problem elegantly but AFAIK it all revolve around improving
    // the MonoidRepBase to be more like an alphabet (with dynamic data stored
    // in some chosen implementation). As for now the implemented solution has
    // the least impact on Vaucanson. It could have been done more compact but
    // the choice was made to choose the code that most visibly explains why it
    // is done.  We ensure _when creating the FMP_ that if the two
    // representations match, we create a new one for the second monoid, while
    // preserving adaptive behavior. WARNING: it obviously defeat the purpose
    // of the shared_ptr.
    template <typename F, typename S>
    void
    split_monoid_(F&, S&)
    {}

    template <typename F>
    void
    split_monoid_(F& first_monoid, F& second_monoid)
    {
      if (first_monoid.representation().get() == second_monoid.representation().get())
      {
	typename F::monoid_rep_t second = *(second_monoid.representation());
	second_monoid.set_representation(second);
      }
    }

    template <class F, class S>
    FreeMonoidProduct<F, S>::FreeMonoidProduct(const F& a, const S& b) :
	first_monoid_(a), second_monoid_(b),
	rep_(MonoidRepDefault<FreeMonoidProduct<F, S> >::get_instance())
    {
      split_monoid_(first_monoid_, second_monoid_);
    }

    template <class F, class S>
    FreeMonoidProduct<F, S>::FreeMonoidProduct(const F& a, const S& b,
					       MonoidRep<FreeMonoidProduct<F, S> > mr) :
	first_monoid_(a), second_monoid_(b),
	rep_(boost::shared_ptr<MonoidRep<FreeMonoidProduct<F, S> > >(new MonoidRep<FreeMonoidProduct<F, S> >(mr)))
    {
      split_monoid_(first_monoid_, second_monoid_);
    }

    template <class F, class S>
    FreeMonoidProduct<F, S>::FreeMonoidProduct(const FreeMonoidProduct& w) :
      FreeMonoidProductBase<FreeMonoidProduct<F, S> >(w),
      first_monoid_(w.first_monoid_),
      second_monoid_(w.second_monoid_),
      rep_(w.rep_)
    {
      split_monoid_(first_monoid_, second_monoid_);
    }

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
    const boost::shared_ptr<MonoidRep<FreeMonoidProduct<F, S> > >
    FreeMonoidProduct<F, S>::representation() const
    {
      return rep_;
    }

    template <typename F, typename S>
    void
    FreeMonoidProduct<F, S>::set_representation(MonoidRep<FreeMonoidProduct<F, S> > mr)
    {
      rep_ = boost::shared_ptr<MonoidRep<FreeMonoidProduct<F, S> > >(new MonoidRep<FreeMonoidProduct<F, S> > (mr));
    }

    template <typename F, typename S>
    bool
    operator==(const FreeMonoidProduct<F, S>& lhs,
	       const FreeMonoidProduct<F, S>& rhs)
    {
      return (lhs.first_monoid() == rhs.first_monoid() &&
	      lhs.second_monoid() == rhs.second_monoid() &&
	      lhs.representation() == rhs.representation());
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_CONCEPT_FREEMONOID_PRODUCT_HXX
