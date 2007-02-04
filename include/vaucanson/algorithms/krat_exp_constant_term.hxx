// krat_exp_constant_term.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HXX

# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn {

  /**
   * @brief This is the visitor that really computes the constant term.
   *
   * This class should be used  only in constant_term() and should not
   * be instanciated from elsewhere.
   *
   * @see constant_term()
   */
  template <class Series, class T, class Dispatch>
  class ConstantTermEval : public algebra::KRatExpMatcher<
    ConstantTermEval<Series, T, Dispatch>,
    T,
    typename Element<Series, T>::semiring_elt_t,
    Dispatch
    >
  {
  public:
    typedef ConstantTermEval<Series, T, Dispatch>	self_t;
    typedef typename Element<Series, T>::semiring_elt_t       return_type;
    typedef typename Element<Series, T>::semiring_elt_t       semiring_elt_t;
    typedef typename semiring_elt_t::value_t		        semiring_elt_value_t;
    INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

    ConstantTermEval(const Element<Series, T>& exp) :
      undefined(false),
      exp_(exp)
    {}

    MATCH__(Product, lhs, rhs)
    {
      return match(lhs) * match(rhs);
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return match(lhs) + match(rhs);
    }
    END

    MATCH_(Star, node)
    {
      semiring_elt_t ret = match(node);
      if (ret.starable())
	return star(ret);
      undefined = true;
      return ret;
    }
    END

    MATCH__(LeftWeight, w, node)
    {
      return w * match(node);
    }
    END

    MATCH__(RightWeight, node, w)
    {
      return match(node) * w;
    }
    END

    MATCH_(Constant, m)
    {
      return exp_.structure().semiring().zero(SELECT(semiring_elt_value_t));
    }
    END

    MATCH(Zero)
    {
      return exp_.structure().semiring().zero(SELECT(semiring_elt_value_t));
    }
    END

    MATCH(One)
    {
      return exp_.structure().semiring().identity(SELECT(semiring_elt_value_t));
    }
    END

    bool undefined;

  private:
    Element<Series, T> exp_;
  };

  template <class Series, class T>
  std::pair<typename Element<Series, T>::semiring_elt_t, bool>
  constant_term(const Element<Series, T>& exp)
  {
    typedef typename Element<Series, T>::semiring_elt_t     semiring_elt_t;
    ConstantTermEval<Series, T, algebra::DispatchFunction<T> > matcher(exp);
    semiring_elt_t v = matcher.match(exp.value());
    if (matcher.undefined)
      return std::make_pair(v, false);
    return std::make_pair(v, true);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_CONSTANT_TERM_HXX
