// krat_exp_partial_derivation.hxx
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

#ifndef VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HXX

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
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
      typedef typename Element<Series, T>::weight_t		weight_t;
      typedef typename weight_t::value_t				weight_value_t;
      typedef typename Element<Series, T>::monoid_elt_t		monoid_elt_t;
      typedef typename monoid_elt_t::value_t			monoid_elt_value_t;
      typedef typename monoid_elt_t::set_t			monoid_t;
      typedef typename monoid_t::alphabet_t			alphabet_t;
      typedef typename alphabet_t::letter_t			letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

      KRatExpPartialDerivation(const Element<Series, T>& exp, 
			       letter_t                  a) :
	undefined(false),
	exp_(exp),
	a_(a)
      {}

      Element<Series, T> series(const T& e)
      {
	return Element<Series, T>(exp_.set(), e);
      }

      MATCH__(Product, lhs, rhs)
      {
	std::pair<weight_t, bool> ret = constant_term(series(lhs));
	if (ret.second == false)
	  {
	    undefined = true;
	    return return_type();
	  }
	if ( ret.first != exp_.set().weights().zero(SELECT(weight_value_t)) )
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
	std::pair<weight_t, bool> ret = constant_term(series(e));
	if ((ret.second == false) || (ret.first.stareable() == false))
	  {
	    undefined = true;
	    return return_type();
	  }
	return ret.first.star() ^ (match(e) ^ e.clone().star());
      }
      END

      MATCH__(LeftWeight, w, e)
      {
	return weight_t(w) ^ match(e);
      }
      END

      MATCH__(RightWeight, e, w)
      {
	return match(e) ^ weight_t(w);
      }
      END

      MATCH_(Constant, m)
      {
	return_type	res;
	if (m[0] == a_)
	  {
	    if (m.length() == 1)
	      res.insert(algebra::identity_as<T>::of(exp_.set()));
	    else
	      res.insert(Element<Series, T> (exp_.set(), m.substr(1)));
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
    std::set<Element<Series, T> > ret = matcher.match(exp);
    if (matcher.undefined)
      return std::make_pair(ret, false);
    return std::make_pair(ret, true);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_PARTIAL_DERIVATION_HXX
