// krat_exp_support.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_SUPPORT_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_SUPPORT_HXX

# include <utility>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>

namespace vcsn {

  template <class Series, class T, class Dispatch>
  class SupportMatcher : public algebra::KRatExpMatcher<
    SupportMatcher<Series, T, Dispatch>,
    T, 
    int,
    Dispatch
    >
  {
  public:
    typedef IsFiniteAppMatcher<Series, T, Dispatch>	self_t;
    typedef int					        return_type;
    typedef Series					series_t;
    typedef Element<Series, T>				serie_t;
    typedef typename serie_t::monoid_elt_t		monoid_elt_t;
    typedef typename monoid_elt_t::value_t		monoid_value_t;
    typedef typename serie_t::semiring_elt_t			semiring_elt_t;
    typedef typename semiring_elt_t::value_t			semiring_elt_value_t;
    typedef std::list<monoid_value_t>			support_t;
    typedef std::list<std::pair<semiring_elt_value_t, monoid_value_t> > 
							ext_support_t;
    INHERIT_CONSTRUCTORS(self_t, T, return_type, Dispatch);

    SupportMatcher(const series_t& s):
      series_(s)
    {}

    MATCH__(Product, lhs, rhs)
    {
      match(lhs);
      ext_support_t lhs_s = supp_;
      match(rhs);
      ext_support_t ret;
      for_each_const_(ext_support_t, c, lhs_s)
	for_each_const_(ext_support_t, d, supp_)
	{
	  monoid_elt_t mc(series_.monoid(), c->second);
	  monoid_elt_t md(series_.monoid(), d->second);
	  //	  ret.push_back((mc * md).value());
	  semiring_elt_t wc(series_.semiring(), c->first);
	  semiring_elt_t wd(series_.semiring(), d->first);
	  ret.push_back(std::make_pair((wc * wd).value(), 
				       (mc * md).value()));
	}
      supp_ = ret;
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      // FIXME: this is bogus.
      // The current version says (k1.a + b) + k2.a = k1.a + k2.a + b
      // whereas it should say    (k1.a + b) + k2.a = (k1+k2).a + b
      match(lhs);
      match(rhs);
    }
    END

    MATCH_(Star, node)
    {
      // undefined case.
      assertion(!"valid");
    }
    END

    MATCH__(LeftWeight, w, node)
    {
      // FIXME: this is bogus.
      // The current version says (a + k.b) = k.a + k.b
      // whereas it should say    (a + k.b) = a + k.b
      // (it does not save the current support before recurring)
      match(node);
      for_each_(ext_support_t, c, supp_)
	c->first = op_mul(series_.semiring(), w, c->first);
    }
    END

    MATCH__(RightWeight, node, w)
    {
      // FIXME: this is bogus. See before.
      match(node);
      for_each_(ext_support_t, c, supp_)
	c->first = op_mul(series_.semiring(), c->first, w);
    }
    END

    MATCH_(Constant, m)
    {
      supp_.push_back(std::make_pair
		      (identity_value(series_.semiring(), 
				      SELECT(semiring_elt_value_t)),
		       m));
    }
    END

    MATCH(Zero)
    {
    }
    END

    MATCH(One)
    {
      supp_.push_back(std::make_pair
		      (identity_value(series_.semiring(), 
				      SELECT(semiring_elt_value_t)),
		       identity_value(series_.monoid(), 
				      SELECT(monoid_value_t))));
    }
    END

    support_t get() const
    {
      support_t ret;
      for_each_const_(ext_support_t, c, supp_)
	ret.push_back(c->second);
      return ret;
    }
      
    const ext_support_t& ext_get() const
    {
      return supp_;
    }

  private:
    ext_support_t	        supp_;
    const series_t&		series_;
  };
  
} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_SUPPORT_HXX
