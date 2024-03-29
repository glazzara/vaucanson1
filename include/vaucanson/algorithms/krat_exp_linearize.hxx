// krat_exp_linearize.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HXX

// LINEAR_INDEX_START must be != 0
# define LINEAR_INDEX_START	1

# include <vaucanson/algorithms/krat_exp_linearize.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn {

  // The Matcher building the linearized expression
  template <class Series, class T, class Dispatch>
  struct KRatExpLinearize : algebra::KRatExpMatcher<
    KRatExpLinearize<Series, T, Dispatch>,
    T,
    typename linearize_element<Series, T>::element_t,
    Dispatch
    >
  {
    // Types of the resulting expression
    typedef typename linearize_element<Series, T>::index_t	index_t;
    typedef typename linearize_element<Series, T>::element_t	return_type;
    typedef typename return_type::value_t		exp_impl_t;
    typedef typename return_type::monoid_elt_value_t	l_monoid_elt_value_t;
    typedef typename return_type::set_t			l_series_set_elt_t;
    typedef typename l_series_set_elt_t::monoid_t	l_monoid_t;
    typedef typename l_series_set_elt_t::semiring_t	l_semiring_t;
    typedef typename l_monoid_t::alphabet_t		l_alphabet_t;
    typedef typename l_monoid_t::letter_t		l_letter_t;
    typedef typename return_type::monoid_elt_t		l_monoid_elt_t;
    typedef typename return_type::semiring_elt_t	l_semiring_elt_t;
    // Types of the source expression
    typedef KRatExpLinearize<Series, T, Dispatch>	self_t;
    typedef typename Element<Series, T>::semiring_elt_t	semiring_elt_t;
    typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
    typedef typename monoid_elt_t::value_t	      	monoid_elt_value_t;
    INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

    KRatExpLinearize(const Element<Series, T>& exp) :
      index_(LINEAR_INDEX_START),
      exp_(exp),
      l_alpha_(),
      l_series_(l_semiring_t (), l_monoid_t (l_alpha_))
    {
    }

    return_type linearize()
    {
      // Build a Element with the correct alphabet.
      return_type	result = this->match(exp_.value());
      l_monoid_t	l_monoid(l_alpha_);
      l_semiring_t	l_semiring;
      return return_type (l_series_set_elt_t (l_semiring, l_monoid),
			  result.value());
    }

    MATCH__(Product, lhs, rhs)
    {
      return this->match(lhs) * this->match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return this->match(lhs) + this->match(rhs);
    }
    END

    MATCH_(Star, e)
    {
      return this->match(e).star();
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      return l_semiring_elt_t(w) * this->match(e);
    }
    END

    MATCH__(RightWeight, e, w)
    {
      return this->match(e) * l_semiring_elt_t(w);
    }
    END

    MATCH_(Constant, m)
    {
      // Build new constant and update alphabet
      l_monoid_elt_value_t	res;
      typedef typename monoid_elt_value_t::const_iterator	const_iterator;
      for (const_iterator i = m.begin(); i != m.end(); ++i)
      {
	l_alpha_.insert(l_letter_t(*i, index_));
	res.push_back(l_letter_t(*i, index_));
	index_++;
      }
      // Transform it in the good type
      return return_type(l_series_, res);
    }
    END

    MATCH(Zero)
    {
      return l_series_.zero(SELECT(exp_impl_t));
    }
    END

    MATCH(One)
    {
      return l_series_.identity(SELECT(exp_impl_t));
    }
    END

  private:
    index_t		index_;
    Element<Series, T>	exp_;
    l_alphabet_t	l_alpha_;
    l_series_set_elt_t		l_series_;
  };

  template <class Series, class T>
  typename linearize_element<Series, T>::element_t
  linearize(const Element<Series, T>& exp)
  {
    KRatExpLinearize<Series, T, algebra::DispatchFunction<T> >
      matcher(exp);
    return matcher.linearize();
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HXX
