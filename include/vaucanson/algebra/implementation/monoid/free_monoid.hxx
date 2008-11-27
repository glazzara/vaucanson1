// free_monoid.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HXX

# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>

namespace vcsn
{
  namespace algebra
  {
    /*--------------.
    | FreeMonoid<A> |
    `--------------*/

    template <class A>
    FreeMonoid<A>::FreeMonoid(const A& a) :
	rep_(MonoidRepDefault<FreeMonoid<A> >::get_instance()),
	alph_(a)
    {
      rep_->disambiguate(*this, rep_);
    }

    template <class A>
    FreeMonoid<A>::FreeMonoid(const A& a, MonoidRep<FreeMonoid<A> > mr) :
	rep_(boost::shared_ptr<MonoidRep<FreeMonoid<A> > >(new MonoidRep<FreeMonoid<A> > (mr))),
	alph_(a)
    {
    }

    template <class A>
    FreeMonoid<A>::FreeMonoid(const FreeMonoid& w) :
      FreeMonoidBase<FreeMonoid<A> >(w),
      rep_(w.rep_),
      alph_(w.alph_)
    {
    }

    template <class A>
    const boost::shared_ptr<MonoidRep<FreeMonoid<A> > >
    FreeMonoid<A>::representation() const
    {
      return rep_;
    }

    template <class A>
    void
    FreeMonoid<A>::set_representation(MonoidRep<FreeMonoid<A> > mr)
    {
      rep_ = boost::shared_ptr<MonoidRep<FreeMonoid<A> > >(new MonoidRep<FreeMonoid<A> > (mr));
    }

    template <class A>
    A& FreeMonoid<A>::alphabet()
    {
      return alph_;
    }

    template <class A>
    const A& FreeMonoid<A>::alphabet() const
    {
      return alph_;
    }

    template <typename A>
    bool
    operator==(const FreeMonoid<A>& lhs,
	       const FreeMonoid<A>& rhs)
    {
      return (lhs.alphabet() == rhs.alphabet() &&
	      lhs.representation() == rhs.representation());
    }

  } // ! algebra

} // ! vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_MONOID_FREE_MONOID_HXX
