// initial_derivation.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_INITIAL_DERIVATION_HXX
# define VCSN_ALGORITHMS_INITIAL_DERIVATION_HXX

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

# include <list>

namespace vcsn
{

  /**
   * Visitor to have an initial set of partial derivatives terms
   * from an expression.
   *
   * @bug FIXME: The algorithm  is correct, but the implementation may
   *             not be efficient!
   */
  template <class Series, class T, class Dispatch>
  struct KRatExpInitialDerivation : algebra::KRatExpMatcher<
    KRatExpInitialDerivation<Series, T, Dispatch>,
    T,
    std::list< Element<Series, T> >,
    Dispatch
    >
  {
    typedef Element<Series, T>				exp_t;
    typedef std::list<exp_t>				list_t;
    typedef std::list<exp_t>				return_type;
    typedef typename list_t::iterator			iterator_t;
    typedef KRatExpInitialDerivation<Series, T, Dispatch>	self_t;
    typedef typename Element<Series, T>::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
    typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
    INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

    KRatExpInitialDerivation(const Element<Series, T>& exp) :
      exp_(exp)
    {}

    // Useful functions:
  private:
    list_t apply_sum(list_t explist)
    {
      if (explist.size() != 1)
      {
	iterator_t	i = explist.begin();
	exp_t		res = *i;
	for (i++; i != explist.end(); ++i)
	{
	  res += *i;
	}
	explist.clear();
	explist.push_back(res);
      }
      return explist;
    }

    list_t& put_in(list_t& s, exp_t e)
    {
      s.clear();
      s.push_back(e);
      return s;
    }

   public:

    // Matches:
    MATCH__(Product, lhs, rhs)
    {
      list_t llist = match(lhs);
      Element<Series, T> s (exp_.structure(), rhs);
      list_t res;
      for (typename list_t::const_iterator it = llist.begin();
	   it != llist.end(); ++it)
	res.push_back(*it * s);
      return res;
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      list_t llist = match(lhs);
      list_t rlist = match(rhs);
      list_t res;
      merge(llist.begin(), llist.end(),
		rlist.begin(), rlist.end(),
		inserter(res, res.begin()));
      return res;
    }
    END

    MATCH_(Star, e)
    {
      list_t	res;
      Element<Series, T> s (exp_.structure(), e.star());
      res.push_back(s);
      return res;
    }
    END

    MATCH__(LeftWeight, w, e)
    {
      list_t	clist = apply_sum(match(e));
      put_in(clist, semiring_elt_t(w) * *clist.begin());
      return clist;
    }
    END

    MATCH__(RightWeight, e, w)
    {
      list_t	clist = apply_sum(match(e));
      put_in(clist, *clist.begin() * semiring_elt_t(w));
      return clist;
    }
    END

    MATCH_(Constant, m)
    {
      list_t	res;
      Element<Series, T> s (exp_.structure(), m);
      res.push_back(s);
      return res;
    }
    END

    MATCH(Zero)
    {
      list_t	res;
      res.push_back(exp_.structure().zero(SELECT(T)));
      return res;
    }
    END

    MATCH(One)
    {
      list_t	res;
      res.push_back(exp_.structure().identity(SELECT(T)));
      return res;
    }
    END

  private:
    Element<Series, T>	exp_;
  };

}

#endif // ! VCSN_ALGORITHMS_INITIAL_DERIVATION_HXX
