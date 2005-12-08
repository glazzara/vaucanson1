// krat_exp_flatten.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HXX

# include <vaucanson/algorithms/krat_exp_flatten.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn
{
  /** @addtogroup algorithms */ /** @{ */

  template <class Series, class T, class Dispatch>
  struct KRatExpFlatten : algebra::KRatExpMatcher<
    KRatExpFlatten<Series, T, Dispatch>,
    T,
    std::list<typename Series::monoid_t::alphabet_t::letter_t>,
    Dispatch
    >
  {
    typedef KRatExpFlatten<Series, T, Dispatch>		self_t;
    typedef typename Element<Series, T>::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
    typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
    typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
    typedef typename monoid_elt_t::set_t		monoid_t;
    typedef typename monoid_t::alphabet_t		alphabet_t;
    typedef typename alphabet_t::letter_t		letter_t;
    typedef std::list<typename Series::monoid_t::alphabet_t::letter_t>
							return_type;
    INHERIT_CONSTRUCTORS(self_t, T, return_type, Dispatch);

    KRatExpFlatten(const Element<Series, T>& exp) : exp_(exp), res_ ()
    {
    }

    return_type
    flatten()
    {
      return match(exp_.value());
    }

    MATCH__(Product, lhs, rhs)
    {
      match(lhs);
      match(rhs);
      return res_;
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      match(lhs);
      match(rhs);
      return res_;
    }
    END

    MATCH_(Star, e)
    {
      match(e);
      return res_;
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      w = w; // Dirty trick to avoid warinings.
      match(e);
      return res_;
    }
    END

    MATCH__(RightWeight, e, w)
    {
      w = w; // Dirty trick to avoid warinings.
      match(e);
      return res_;
    }
    END

    MATCH_(Constant, m)
    {
      for (size_t i = 0; i < m.length(); ++i)
	res_.push_back(m[i]);
      return res_;
    }
    END

    MATCH(Zero)
    {
      return res_;
    }
    END

    MATCH(One)
    {
      return res_;
    }
    END

  private:
    Element<Series, T>	exp_;
    return_type		res_;
  };

  template <class Series, class T>
  std::list<typename Series::monoid_t::alphabet_t::letter_t>
  flatten(const Element<Series, T>& exp)
  {
    KRatExpFlatten< Series, T, algebra::DispatchFunction<T> > matcher(exp);
    return matcher.flatten();
  }

  /** @} */

} // end of namepsace vcsn

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_FLATTEN_HXX
