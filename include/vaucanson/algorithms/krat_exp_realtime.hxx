// krat_exp_realtime.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX

# include <vaucanson/algorithms/krat_exp_realtime.hh>

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn {

  namespace algebra
  {
    template <class Exp_,
	      class Dispatch_>
    class KRatExpIsRealtime :
      public algebra::KRatExpMatcher<
      KRatExpIsRealtime<Exp_, Dispatch_>,
      Exp_,
      bool,
      Dispatch_
      >
    {
    public :
      typedef KRatExpIsRealtime<Exp_, Dispatch_>	this_class;
      typedef bool					return_type;
      typedef typename Exp_::monoid_elt_value_t		monoid_elt_value_t;
      typedef typename Exp_::semiring_elt_value_t	semiring_elt_value_t;
      INHERIT_CONSTRUCTORS(this_class, Exp_, bool, Dispatch_);

      MATCH__(Sum, l, r)
      {
	return match(l) and match(r);
      }
      END

      MATCH__(Product, l, r)
      {
	return match(l) and match(r);
      }
      END

      MATCH_(Star, e)
      {
	return match(e);
      }
      END

      MATCH__(LeftWeight, w, e)
      {
	w = w; // Avoid warning.
	return match(e);
      }
      END

      MATCH__(RightWeight, e, w)
      {
	w = w; // Avoid warning.
	return match(e);
      }
      END

      MATCH_(Constant, m)
      {
	typename monoid_elt_value_t::const_iterator i = m.begin();
	return ++i == m.end();
      }
      END

      MATCH(Zero)
      {
	return true;
      }
      END

      MATCH(One)
      {
	return true;
      }
      END
    };

  } // End of namespace algebra.

  template <class Exp_, class S_>
  bool
  do_is_realtime(const algebra::SeriesBase<S_>&, const Exp_& exp)
  {
    typedef S_				S;
    typedef typename Exp_::value_t	T;

    algebra::KRatExpIsRealtime< T, algebra::DispatchFunction<T> >
      matcher;
    return matcher.match(exp.value());
  }


  namespace algebra {

    template <class Series, class T, class Dispatch>
    struct KRatExpRealtime : algebra::KRatExpIdentity<
      KRatExpRealtime<Series, T, Dispatch>,
      Series,
      T,
      Dispatch
      >
    {
      typedef KRatExpRealtime<Series, T, Dispatch>	self_t;
      typedef Element<Series, T>			return_type;
      typedef typename Element<Series, T>::semiring_elt_t semiring_elt_t;
      typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
      typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
      typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
      typedef typename monoid_elt_t::set_t		monoid_t;
      typedef typename monoid_t::alphabet_t		alphabet_t;
      typedef typename alphabet_t::letter_t		letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

      KRatExpRealtime(const Element<Series, T>& exp) :
	KRatExpIdentity<KRatExpRealtime<Series, T, Dispatch>,
			Series,
			T,
			Dispatch
			>(exp)
      {}

      MATCH_(Constant, m)
      {
	return_type	exp = identity_as<T>::of(this->exp_.structure());
	return_type	tmp (this->exp_.structure());
	monoid_elt_t	letter (this->exp_.structure().monoid());
	for (typename monoid_elt_value_t::const_iterator i = m.begin();
	     i != m.end(); ++i)
	  {
	    letter = *i;
	    tmp = letter;
	    exp *= tmp;
	  }
	return exp;
      }
      END
    };



  } // algebra

  template <class Exp_, class S_>
  Exp_
  do_realtime(const algebra::SeriesBase<S_>&, const Exp_& exp)
  {
    typedef S_				S;
    typedef typename Exp_::value_t	T;

    algebra::KRatExpRealtime< S, T, algebra::DispatchFunction<T> >
      matcher(exp);
    return matcher.match(exp.value());
  }

  template <class Exp_, class S_>
  void
  do_realtime_here(const algebra::SeriesBase<S_>&, Exp_& exp)
  {
    typedef S_				S;
    typedef typename Exp_::value_t	T;

    algebra::KRatExpRealtime< S, T, algebra::DispatchFunction<T> >
      matcher(exp);
    exp = matcher.match(exp.value());
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX
