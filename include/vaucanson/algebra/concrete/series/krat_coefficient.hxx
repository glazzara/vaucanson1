// krat_coefficient.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef ALGEBRA_KRAT_COEFFICIENT_HXX
# define ALGEBRA_KRAT_COEFFICIENT_HXX

# include <utility>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>

namespace vcsn {

  namespace algebra {

    template <class Series, class T, class Dispatch>
    class CoefficientEval : public algebra::KRatExpMatcher<
      CoefficientEval<Series, T, Dispatch>,
      T,
      std::pair<typename Element<Series, T>::weight_t, Element<Series, T> >,
      Dispatch
      >
    {
    public:
      typedef ConstantTermEval<Series, T, Dispatch>	self_t;
      typedef typename Element<Series, T>::weight_t     weight_t;
      typedef std::pair<weight_t, Element<Series, T> >  return_type;
      typedef typename weight_t::value_t	        weight_value_t;
      INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);
  
      CoefficientEval(const Element<Series, T>& exp) :
	exp_(exp)
      {}

      weight_t	one()
      { return exp_.set().weights().identity(SELECT(weight_value_t)); }

      weight_t zero()
      { return exp_.set().weights().zero(SELECT(weight_value_t)); }

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
	return return_type(zero(), zero_as<T>::of(exp_.set()));
      }
      END
  
      MATCH(One)
      {
	return return_type(one(), identity_as<T>::of(exp_.set()));
      }
      END
  
    private:
      Element<Series, T> exp_;
    };
  
    template <class Series, class T>
    std::pair<typename Element<Series, T>::weight_t, Element<Series, T> >
    coefficient(const Element<Series, T>& exp)
    {
      CoefficientEval<Series, T, algebra::DispatchFunction<T> > matcher(exp);
      return matcher.match(exp);
    }

  } // algebra

} // vcsn

#endif // ALGEBRA_KRAT_COEFFICIENT_HXX
