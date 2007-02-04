// krat_exp_cderivation.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HXX

# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  namespace algebra {

    template <class Series, class T, class Dispatch>
    struct KRatExpCDerivation : algebra::KRatExpMatcher<
      KRatExpCDerivation<Series, T, Dispatch>,
      T,
      Element<Series, T>,
      Dispatch
      >
    {
      typedef KRatExpCDerivation<Series, T, Dispatch>   self_t;
      typedef Element<Series, T>                        return_type;
      typedef typename Element<Series, T>::semiring_elt_t     semiring_elt_t;
      typedef typename semiring_elt_t::value_t		      semiring_elt_value_t;
      typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
      typedef typename monoid_elt_t::value_t	      monoid_elt_value_t;
      typedef typename monoid_elt_t::set_t	      monoid_t;
      typedef typename monoid_t::alphabet_t	      alphabet_t;
      typedef typename alphabet_t::letter_t	      letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

      KRatExpCDerivation(const Element<Series, T>& exp,
			 letter_t                  a) :
	exp_(exp),
	a_(a)
      {}

      Element<Series, T> series(const T& e)
      {
	return Element<Series, T>(exp_.structure(), e);
      }

      MATCH__(Product, lhs, rhs)
      {
	return_type match_lhs = match(lhs);

	// FIXME: Following code only valid for series over Boolean semirings.
	if (match_lhs != zero_as<T>::of(exp_.structure()))
	  return match_lhs * rhs;
	else
	  {
	    std::pair<semiring_elt_t, bool> ret = constant_term(series(lhs));
	    return ret.first * match(rhs);
	  }
      }
      END

      MATCH__(Sum, lhs, rhs)
      {
	return_type match_lhs = match(lhs);

	// FIXME: Following code only valid for series over Boolean semirings.
	if (match_lhs != zero_as<T>::of(exp_.structure()))
	  return match_lhs;
	else
	  return match(rhs);
      }
      END

      MATCH_(Star, e)
      {
	// FIXME: Following code only valid for series over Boolean semirings.
	return match(e) * e.clone().star();
      }
      END

      MATCH__(LeftWeight, w, e)
      {
	return semiring_elt_t(w) * match(e);
      }
      END

      MATCH__(RightWeight, e, w)
      {
	return match(e) * semiring_elt_t(w);
      }
      END

      MATCH_(Constant, m)
      {
	if (m[0] == a_)
	  {
	    if (m.length() == 1)
	      return identity_as<T>::of(exp_.structure());
	    else
	      return Element<Series, T> (exp_.structure(), m.substr(1));
	  }
	else
	  return zero_as<T>::of(exp_.structure());
      }
      END

      MATCH(Zero)
      {
	return zero_as<T>::of(exp_.structure());
      }
      END

      MATCH(One)
      {
	return zero_as<T>::of(exp_.structure());
      }
      END

    private:
      Element<Series, T>	exp_;
      letter_t		a_;
    };

  } // algebra

  template <class Series, class T, class Letter>
  Element<Series, T>
  cderivate(const Element<Series, T>& exp,
	    Letter a)
  {
    algebra::KRatExpCDerivation<Series, T, algebra::DispatchFunction<T> >
      matcher(exp, a);
    return matcher.match(exp.value());
  }

  template <class Series, class T, class Word>
  Element<Series, T>
  word_cderivate(const Element<Series, T>& exp,
		 Word w)
  {
    Element<Series, T> ret(exp);
    for (typename Word::reverse_iterator a = w.rbegin();
	 a != w.rend(); ++a)
      {
	algebra::KRatExpCDerivation<Series, T, algebra::DispatchFunction<T> >
	  matcher(exp, *a);
	ret = matcher.match(ret.value());
      }
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HXX
