// krat_exp_realtime.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX

# include <vaucanson/algorithms/krat_exp_realtime.hh>

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn {

  namespace algebra
  {
    template <class Exp_,
	      class Dispatch_>
    class KRatExpIsRealtime :
      public algebra::KRatExpMatcher<
      KRatExpIsRealtime<Exp_, Dispatch_>,
      Exp_,
      bool,
      Dispatch_
      >
    {
    public :
      typedef KRatExpIsRealtime<Exp_, Dispatch_>	this_class;
      typedef bool					return_type;
      typedef typename Exp_::monoid_elt_value_t		monoid_elt_value_t;
      typedef typename Exp_::semiring_elt_value_t	semiring_elt_value_t;
      INHERIT_CONSTRUCTORS(this_class, Exp_, bool, Dispatch_);

      MATCH__(Sum, l, r)
      {
	return match(l) and match(r);
      }
      END

      MATCH__(Product, l, r)
      {
	return match(l) and match(r);
      }
      END

      MATCH_(Star, e)
      {
	return match(e);
      }
      END

      MATCH__(LeftWeight, w, e)
      {
	w = w; // Avoid warning.
	return match(e);
      }
      END

      MATCH__(RightWeight, e, w)
      {
	w = w; // Avoid warning.
	return match(e);
      }
      END

      MATCH_(Constant, m)
      {
	typename monoid_elt_value_t::const_iterator i = m.begin();
	return ++i == m.end();
      }
      END

      MATCH(Zero)
      {
	return true;
      }
      END

      MATCH(One)
      {
	return true;
      }
      END
    };

  } // End of namespace algebra.

  template <class Exp_, class S_>
  bool
  do_is_realtime(const algebra::SeriesBase<S_>&, const Exp_& exp)
  {
    typedef S_				S;
    typedef typename Exp_::value_t	T;

    algebra::KRatExpIsRealtime< T, algebra::DispatchFunction<T> >
      matcher;
    return matcher.match(exp.value());
  }


  namespace algebra {

    template <class Series, class T, class Dispatch>
    struct KRatExpRealtime : algebra::KRatExpIdentity<
      KRatExpRealtime<Series, T, Dispatch>,
      Series,
      T,
      Dispatch
      >
    {
      typedef KRatExpRealtime<Series, T, Dispatch>	self_t;
      typedef Element<Series, T>			return_type;
      typedef typename Element<Series, T>::semiring_elt_t semiring_elt_t;
      typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
      typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
      typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
      typedef typename monoid_elt_t::set_t		monoid_t;
      typedef typename monoid_t::alphabet_t		alphabet_t;
      typedef typename alphabet_t::letter_t		letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

      KRatExpRealtime(const Element<Series, T>& exp) :
	KRatExpIdentity<KRatExpRealtime<Series, T, Dispatch>,
			Series,
			T,
			Dispatch
			>(exp)
      {}

      MATCH_(Constant, m)
      {
	return_type	exp = identity_as<T>::of(exp_.set());
	return_type	tmp (exp_.set());
	monoid_elt_t	letter (exp_.set().monoid());
	for (typename monoid_elt_value_t::const_iterator i = m.begin();
	     i != m.end(); ++i)
	  {
	    letter = *i;
	    tmp = letter;
	    exp *= tmp;
	  }
	return exp;
      }
      END
    };



  } // algebra

  template <class Exp_, class S_>
  Exp_
  do_realtime(const algebra::SeriesBase<S_>&, const Exp_& exp)
  {
    typedef S_				S;
    typedef typename Exp_::value_t	T;

    algebra::KRatExpRealtime< S, T, algebra::DispatchFunction<T> >
      matcher(exp);
    return matcher.match(exp.value());
  }

  template <class Exp_, class S_>
  void
  do_realtime_here(const algebra::SeriesBase<S_>&, Exp_& exp)
  {
    typedef S_				S;
    typedef typename Exp_::value_t	T;

    algebra::KRatExpRealtime< S, T, algebra::DispatchFunction<T> >
      matcher(exp);
    exp = matcher.match(exp.value());
  }

} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_REALTIME_HXX
