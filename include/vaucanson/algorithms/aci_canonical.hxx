// aci_canonical.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_ACI_CANONICAL_HXX
# define VCSN_ALGORITHMS_ACI_CANONICAL_HXX

# include <vaucanson/algorithms/aci_canonical.hh>

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

# include <set>

namespace vcsn
{

  /**
   * Visitor to build a canonical form of an expression, following aci-rules.
   *
   * @see canonical()
   *
   * @bug FIXME: The algorithm  is correct, but the implementation may
   *             not be efficient!
   */
  template <class Series, class T, class Dispatch>
  struct KRatExpAciCanonical : algebra::KRatExpMatcher<
    KRatExpAciCanonical<Series, T, Dispatch>,
    T,
    std::set< Element<Series, T> >,
    Dispatch
    >
  {
    typedef Element<Series, T>				exp_t;
    typedef std::set<exp_t>				set_t;
    typedef std::set<exp_t>				return_type;
    typedef typename set_t::iterator			iterator_t;
    typedef KRatExpAciCanonical<Series, T, Dispatch>	self_t;
    typedef typename Element<Series, T>::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
    typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
    typedef typename monoid_elt_t::set_t		monoid_t;
    typedef typename monoid_t::alphabet_t		alphabet_t;
    typedef typename alphabet_t::letter_t		letter_t;
    INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

    KRatExpAciCanonical(const Element<Series, T>& exp) :
      exp_(exp)
    {}

    // Useful functions:
  private:
    set_t apply_sum(set_t expset)
    {
      if (expset.size() != 1)
      {
	iterator_t	i = expset.begin();
	exp_t		res = *i;
	for (i++; i != expset.end(); ++i)
	{
	  res += *i;
	}
	expset.clear();
	expset.insert(res);
      }
      return expset;
    }

    set_t& put_in(set_t& s, exp_t e)
    {
      s.clear();
      s.insert(e);
      return s;
    }

  public:
    exp_t set2exp(set_t expset)
    {
      expset = apply_sum(expset);
      return *expset.begin();
    }

    // Matches:
    MATCH__(Product, lhs, rhs)
    {
      set_t lset = apply_sum(match(lhs));
      set_t rset = apply_sum(match(rhs));
      put_in(lset, *lset.begin() * *rset.begin());
      return lset;
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      set_t lset = match(lhs);
      set_t rset = match(rhs);
      set_t res;
      merge(lset.begin(), lset.end(),
		rset.begin(), rset.end(),
		inserter(res, res.begin()));
      return res;
    }
    END

    MATCH_(Star, e)
    {
      set_t cset = apply_sum(match(e));
      exp_t exp = *cset.begin();
      put_in(cset, exp.star());
      return cset;
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      set_t	cset = apply_sum(match(e));
      put_in(cset, semiring_elt_t(w) * *cset.begin());
      return cset;
    }
    END

    MATCH__(RightWeight, e, w)
    {
      set_t	cset = apply_sum(match(e));
      put_in(cset, *cset.begin() * semiring_elt_t(w));
      return cset;
    }
    END

    MATCH_(Constant, m)
    {
      set_t	res;
      Element<Series, T> s (exp_.structure(), m);
      res.insert(s);
      return res;
    }
    END

    MATCH(Zero)
    {
      set_t	res;
      res.insert(exp_.structure().zero(SELECT(T)));
      return res;
    }
    END

    MATCH(One)
    {
      set_t	res;
      res.insert(exp_.structure().identity(SELECT(T)));
      return res;
    }
    END

  private:
    Element<Series, T>	exp_;
  };

  template <class Series_, class Exp_>
  Exp_
  do_canonical(const algebra::SeriesBase<Series_>&, const Exp_& exp)
  {
    typedef Series_			S;
    typedef typename Exp_::value_t	T;

    KRatExpAciCanonical< S, T, algebra::DispatchFunction<T> >	matcher(exp);
    return matcher.set2exp(matcher.match(exp.value()));
  }

  template <class Series, class T>
  Element<Series, T>
  canonical(const Element<Series, T>& exp)
  {
    return do_canonical(exp.structure(), exp);
  }

}

#endif // ! VCSN_ALGORITHMS_ACI_CANONICAL_HXX
