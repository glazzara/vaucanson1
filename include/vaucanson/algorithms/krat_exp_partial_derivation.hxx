// krat_exp_partial_derivation.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HXX

# include <vaucanson/algorithms/krat_exp_partial_derivation.hh>

# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  namespace algebra {

    // Some operators are defined in order to make algorithm clearer
    // and efficient

    // operator^ apply * between each element of the set and the other
    // argument
    template <typename T, typename U>
    std::set<T>	operator^ (std::set<T> set, U other)
    {
      typedef typename std::set<T>::iterator	iterator;
      std::set<T>	result;
      for (iterator i = set.begin(); i != set.end(); ++i)
	result.insert(*i * other);
      return result;
    }

    template <typename T, typename U>
    std::set<T>	operator^ (U other, std::set<T> set)
    {
      typedef typename std::set<T>::iterator	iterator;
      std::set<T>	result;
      for (iterator i = set.begin(); i != set.end(); ++i)
	result.insert(other * *i);
      return result;
    }

    // operator+ make the union of two set
    template <typename T>
    std::set<T>	operator+ (std::set<T> s1, std::set<T> s2)
    {
      std::set<T>	result;
      merge(s1.begin(), s1.end(),
	    s2.begin(), s2.end(),
	    inserter(result, result.begin()));
      return result;
    }

    // It is a first implementation of partial derivate.
    // It simply apply the definition of partial derivates.
    template <class Series, class T, class Dispatch>
    struct KRatExpPartialDerivation : algebra::KRatExpMatcher<
      KRatExpPartialDerivation<Series, T, Dispatch>,
      T,
      std::set<Element<Series, T> >,
      Dispatch
      >
    {
      typedef KRatExpPartialDerivation<Series, T, Dispatch>	self_t;
      typedef Element<Series, T>					exp_t;
      typedef std::set<exp_t>					set_t;
      typedef set_t						return_type;
      typedef typename set_t::iterator	iterator;
      typedef typename Element<Series, T>::semiring_elt_t		semiring_elt_t;
      typedef typename semiring_elt_t::value_t				semiring_elt_value_t;
      typedef typename Element<Series, T>::monoid_elt_t		monoid_elt_t;
      typedef typename monoid_elt_t::value_t			monoid_elt_value_t;
      typedef typename monoid_elt_t::set_t			monoid_t;
      typedef typename monoid_t::alphabet_t			alphabet_t;
      typedef typename alphabet_t::letter_t			letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

      KRatExpPartialDerivation(const Element<Series, T>& exp,
			       letter_t                  a) :
	undefined(false),
	exp_(exp),
	a_(a)
      {}

      Element<Series, T> series(const T& e)
      {
	return Element<Series, T>(exp_.structure(), e);
      }

      MATCH__(Product, lhs, rhs)
      {
	std::pair<semiring_elt_t, bool> ret = constant_term(series(lhs));
	if (ret.second == false)
	  {
	    undefined = true;
	    return return_type();
	  }
	if (ret.first !=
	    exp_.structure().semiring().zero(SELECT(semiring_elt_value_t)))
	  return (match(lhs) ^ rhs) + (ret.first ^ match(rhs));
	else
	  return (match(lhs) ^ rhs);
      }
      END

      MATCH__(Sum, lhs, rhs)
      {
	return match(lhs) + match(rhs);
      }
      END

      MATCH_(Star, e)
      {
	std::pair<semiring_elt_t, bool> ret = constant_term(series(e));
	if ((ret.second == false) || (ret.first.starable() == false))
	  {
	    undefined = true;
	    return return_type();
	  }
	return ret.first.star() ^ (match(e) ^ e.clone().star());
      }
      END

      MATCH__(LeftWeight, w, e)
      {
	return semiring_elt_t(w) ^ match(e);
      }
      END

      MATCH__(RightWeight, e, w)
      {
	return match(e) ^ semiring_elt_t(w);
      }
      END

      MATCH_(Constant, m)
      {
	return_type	res;
	if (m[0] == a_)
	  {
	    if (m.length() == 1)
	      res.insert(algebra::identity_as<T>::of(exp_.structure()));
	    else
	      res.insert(Element<Series, T> (exp_.structure(), m.substr(1)));
	  }
	return res;
      }
      END

      MATCH(Zero)
      {
	return return_type();
      }
      END

      MATCH(One)
      {
	return return_type();
      }
      END

      bool undefined;

    private:
      Element<Series, T>  exp_;
      letter_t		a_;
    };

  } // algebra

  template <class Series, class T, class Letter>
  std::pair<std::set<Element<Series, T> >, bool>
  partial_derivate(const Element<Series, T>& exp,
	  	   Letter a)
  {
    algebra::KRatExpPartialDerivation<Series, T, algebra::DispatchFunction<T> >
      matcher(exp, a);
    std::set<Element<Series, T> > ret = matcher.match(exp.value());
    if (matcher.undefined)
      return std::make_pair(ret, false);
    return std::make_pair(ret, true);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HXX
