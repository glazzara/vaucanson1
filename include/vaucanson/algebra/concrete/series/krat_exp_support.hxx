// krat_exp_support.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_KRAT_EXP_SUPPORT_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_SUPPORT_HXX

# include <utility>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>

namespace vcsn {

  template <class Series, class T, class Dispatch>
  class SupportMatcher : public algebra::KRatExpMatcher<
    SupportMatcher<Series, T, Dispatch>,
    T, 
    void,
    Dispatch
    >
  {
  public:
    typedef IsFiniteAppMatcher<Series, T, Dispatch>	self_t;
    typedef void				        return_type;
    typedef Series					series_t;
    typedef Element<Series, T>				serie_t;
    typedef typename serie_t::monoid_elt_t		monoid_elt_t;
    typedef typename monoid_elt_t::value_t		monoid_value_t;
    typedef std::list<monoid_value_t>			support_t;
    INHERIT_CONSTRUCTORS(self_t, T, return_type, Dispatch);

    SupportMatcher(const series_t& s):
      series_(s)
    {}

    MATCH__(Product, lhs, rhs)
    {
      match(lhs);
      support_t lhs_s = supp_;
      match(rhs);
      support_t ret;
      for_each_const_(support_t, c, lhs_s)
	for_each_const_(support_t, d, supp_)
	{
	  monoid_elt_t mc(*c, series_.monoid());
	  monoid_elt_t md(*d, series_.monoid());
	  ret.push_back((*c * *d).value());
	}
      supp_ = ret;
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      match(lhs);
      match(rhs);
    }
    END

    MATCH_(Star, node)
    {
      // undefined case.
      assert(0);
    }
    END

    MATCH__(LeftWeight, w, node)
    {
      match(node);
    }
    END

    MATCH__(RightWeight, node, w)
    {
      match(node);
    }
    END

    MATCH_(Constant, m)
    {
      supp_.push_back(m);
    }
    END

    MATCH(Zero)
    {
    }
    END

    MATCH(One)
    {
      supp_.push_back(identity_as<monoid_value_t>
		      ::of(series_.monoid()).value());
    }
    END

    support_t get() const
    {
      return supp_;
    }

  private:
    support_t	      supp_;
    const series_t&   series_;
  };
  
} // vcsn

#endif // VCSN_ALGORITHMS_KRAT_EXP_SUPPORT_HXX
