// krat_exp_cderivation.hxx
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

#ifndef VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HXX

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

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
    typedef typename Element<Series, T>::weight_t     weight_t;
    typedef typename weight_t::value_t		      weight_value_t;
    typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
    typedef typename monoid_elt_t::set_t	      monoid_t;
    typedef typename monoid_t::alphabet_t	      alphabet_t;
    typedef typename alphabet_t::letter_t	      letter_t;
    INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

    KRatExpCDerivation(const Element<Series, T>& exp,
		       letter_t                  a) :
      exp_(exp),
      a_(a)
    {}

    Element<Series, T> series(const T& e)
    {
      return Element<Series, T>(exp_.set(), e);
    }

    MATCH__(Product, lhs, rhs)
    {
      return_type match_lhs = match(lhs);
      
      // FIXME: Following code only valid for series over boolean semirings.
      if (match_lhs != Element<Series, T>())
      	return match(lhs) * rhs;
      else
	{
	  std::pair<weight_t, bool> ret = constant_term(series(lhs));
	  return ret.first * match(rhs);
	}
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      return_type match_lhs = match(lhs);
      
      // FIXME: Following code only valid for series over boolean semirings.
      if (match_lhs != Element<Series, T>())
	return match_lhs;
      else
	return match(rhs);
    }
    END

    MATCH_(Star, e)
    {
      // FIXME: Following code only valid for series over boolean semirings.
      return match(e) * e.star();
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      return weight_t(w) * match(e);
    }
    END

    MATCH__(RightWeight, e, w)
    {
      return match(e) * weight_t(w);
    }
    END

    MATCH_(Constant, m)
    {
      if (m[0] == a_)
	return exp_.set().weights().identity(SELECT(weight_value_t));
      else
	return exp_.set().weights().zero(SELECT(weight_value_t));
    }
    END

    MATCH(Zero)
    {
      return exp_.set().weights().zero(SELECT(weight_value_t));
    }
    END

    MATCH(One)
    {
      return exp_.set().weights().zero(SELECT(weight_value_t));
    }
    END

  private:
    Element<Series, T>	exp_;
    letter_t		a_;
  };

  template <class Series, class T, class Letter>
  Element<Series, T>
  cderivate(const Element<Series, T>& exp,
	    Letter a)
  {
    KRatExpCDerivation<Series, T, algebra::DispatchFunction<T> >
      matcher(exp, a);
    return matcher.match(exp);
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
	KRatExpCDerivation<Series, T, algebra::DispatchFunction<T> >
	  matcher(exp, *a);
	ret = matcher.match(ret);
      }
    return ret;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_CDERIVATION_HXX
