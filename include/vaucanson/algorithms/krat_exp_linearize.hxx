// krat_exp_linearize.hxx
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

#ifndef VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HXX

# define LINEAR_INDEX_START	1

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_linearize.hh>

namespace vcsn {

  // The Matcher building the linearized expression
  // FIXME: The alphabet should not be good, but it cannot be tested:
  // the alphabet returned is strangely empty
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
    typedef typename return_type::value_t			exp_impl_t;
    typedef typename return_type::monoid_value_t		l_monoid_value_t;
    typedef typename return_type::set_t				l_serie_t;
    typedef typename l_serie_t::monoid_t			l_monoid_t;
    typedef typename l_serie_t::weights_t			l_weights_t;
    typedef typename l_monoid_t::alphabet_t			l_alphabet_t;
    typedef typename l_monoid_t::letter_t			l_letter_t;
    typedef typename return_type::monoid_elt_t			l_monoid_elt_t;
    typedef typename return_type::weight_t			l_weight_t;
    // Types of the source expression
    typedef KRatExpLinearize<Series, T, Dispatch>		self_t;
    typedef typename Element<Series, T>::weight_t		weight_t;
    typedef typename Element<Series, T>::monoid_elt_t		monoid_elt_t;
    typedef typename monoid_elt_t::value_t	      		monoid_value_t;
    INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

    KRatExpLinearize(const Element<Series, T>& exp) :
      index_(LINEAR_INDEX_START), exp_(exp)
    {
      // Build a serie with the new type
      l_alphabet_t	l_alpha;
      l_monoid_t	l_monoid(l_alpha);
      l_weights_t	l_semiring;
      l_serie_ = l_serie_t(l_semiring, l_monoid);
    }

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

    MATCH_(Star, e)
    {
      return match(e).star();
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      return l_weight_t(w) * match(e);
    }
    END

    MATCH__(RightWeight, e, w)
    {
      return match(e) * l_weight_t(w);
    }
    END

    MATCH_(Constant, m)
    {
      // Build new constant
      l_monoid_value_t	res;
      typedef typename monoid_value_t::const_iterator	const_iterator;
      for (const_iterator i = m.begin(); i != m.end(); ++i)
      {
	l_serie_.monoid().alphabet().insert(l_letter_t(*i, index_));
	res.push_back(l_letter_t(*i, index_));
	index_++;
      }
      // Transform it in the good type
      return_type	s(l_serie_);
      s = l_monoid_elt_t(res);
      return s;
    }
    END

    MATCH(Zero)
    {
      return l_serie_.zero(SELECT(exp_impl_t));
    }
    END

    MATCH(One)
    {
      return l_serie_.identity(SELECT(exp_impl_t));
    }
    END

  private:
    index_t		index_;
    Element<Series, T>	exp_;
    l_serie_t		l_serie_;
  };

  template <class Series, class T>
  typename linearize_element<Series, T>::element_t
  linearize(const Element<Series, T>& exp)
  {
    typename linearize_element<Series, T>::element_t tmp;
    KRatExpLinearize<Series, T, algebra::DispatchFunction<T> >
      matcher(exp);
    return matcher.match(exp);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HXX
