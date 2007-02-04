// krat_coefficient.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_COEFFICIENT_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_COEFFICIENT_HXX

# include <utility>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn {

  namespace algebra {

    template <class Series, class T, class Dispatch>
    class CoefficientEval : public algebra::KRatExpMatcher<
      CoefficientEval<Series, T, Dispatch>,
      T,
      std::pair<typename Element<Series, T>::semiring_elt_t,
		Element<Series, T> >,
      Dispatch
      >
    {
    public:
      typedef ConstantTermEval<Series, T, Dispatch>	self_t;
      typedef typename Element<Series, T>::semiring_elt_t     semiring_elt_t;
      typedef std::pair<semiring_elt_t, Element<Series, T> >  return_type;
      typedef typename semiring_elt_t::value_t	        semiring_elt_value_t;
      INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

      CoefficientEval(const Element<Series, T>& exp) :
	exp_(exp)
      {}

      semiring_elt_t	one()
      {
	return
	  exp_.structure().semiring().identity(SELECT(semiring_elt_value_t));
      }

      semiring_elt_t zero()
      {
	return
	  exp_.structure().semiring().zero(SELECT(semiring_elt_value_t));
      }

      MATCH__(Product, lhs, rhs)
      {
	return return_type(one(), lhs * rhs);
      }
      END

      MATCH__(Sum, lhs, rhs)
      {
	return return_type(one(), lhs + rhs);
      }
      END

      MATCH_(Star, node)
      {
	return return_type(one(), node.star());
      }
      END

      MATCH__(LeftWeight, w, node)
      {
	return return_type(w, node);
      }
      END

      MATCH__(RightWeight, node, w)
      {
	return return_type(w, node);
      }
      END

      MATCH_(Constant, m)
      {
	return return_type(one(), m);
      }
      END

      MATCH(Zero)
      {
	return return_type(zero(), zero_as<T>::of(exp_.structure()));
      }
      END

      MATCH(One)
      {
	return return_type(one(), identity_as<T>::of(exp_.structure()));
      }
      END

    private:
      Element<Series, T> exp_;
    };

    template <class Series, class T>
    std::pair<typename Element<Series, T>::semiring_elt_t, Element<Series, T> >
    coefficient(const Element<Series, T>& exp)
    {
      CoefficientEval<Series, T, algebra::DispatchFunction<T> > matcher(exp);
      return matcher.match(exp.value());
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_COEFFICIENT_HXX
