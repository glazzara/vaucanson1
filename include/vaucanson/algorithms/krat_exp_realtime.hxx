// krat_exp_linearize.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and 
// Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX

# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>

namespace vcsn {

  namespace algebra {

    template <class Series, class T, class Dispatch>
    struct KRatExpRealtime : algebra::KRatExpIdentity<
      KRatExpRealtime<Series, T, Dispatch>,
      Series, 
      T,
      Dispatch
      >
    {
      typedef KRatExpRealtime<Series, T, Dispatch>      self_t;
      typedef Element<Series, T>                        return_type;
      typedef typename Element<Series, T>::weight_t     weight_t;
      typedef typename weight_t::value_t		      weight_value_t;
      typedef typename Element<Series, T>::monoid_elt_t monoid_elt_t;
      typedef typename monoid_elt_t::value_t	      monoid_value_t;
      typedef typename monoid_elt_t::set_t	      monoid_t;
      typedef typename monoid_t::alphabet_t	      alphabet_t;
      typedef typename alphabet_t::letter_t	      letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, weight_t, Dispatch);

      KRatExpRealtime(const Element<Series, T>& exp) :
	KRatExpIdentity<KRatExpRealtime<Series, T, Dispatch>,
			Series, 
			T,
			Dispatch
			>(exp)
      {}

      MATCH_(Constant, m)
      {
	Element<Series, T> acu(exp_.set());
	monoid_elt_t w(exp_.set().monoid());
	acu = exp_.set().identity(SELECT(T));
	Element<Series, T> s(exp_.set());
	for (typename monoid_value_t::const_iterator i = m.begin();
	     i != m.end(); ++i)
	  {
	    w = *i;
	    s = w;
	    acu = acu * s;
	  }
	return acu;
      }
      END
    };

  } // algebra
  
  template <class Series, class T>
  Element<Series, T>
  realtime(const Element<Series, T>& exp) 
  {
    algebra::KRatExpRealtime<Series, T, algebra::DispatchFunction<T> > 
      matcher(exp);
    return matcher.match(exp);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX
