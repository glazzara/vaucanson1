// krat_exp_support.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_SUPPORT_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_SUPPORT_HXX

# include <utility>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_is_finite_app.hxx>

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
    typedef Element<Series, T>				series_elt_t;
    typedef typename series_elt_t::monoid_elt_t		monoid_elt_t;
    typedef typename monoid_elt_t::value_t		monoid_value_t;
    typedef typename series_elt_t::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
    typedef std::list<monoid_value_t>			support_t;
    typedef std::list<std::pair<semiring_elt_value_t, monoid_value_t> >
							ext_support_t;
    INHERIT_CONSTRUCTORS(self_t, T, return_type, Dispatch);

    SupportMatcher(const series_t& s):
      series_(s)
    {}

    MATCH__(Product, lhs, rhs)
    {
      ext_support_t old_supp_ = supp_;
      supp_.clear();
      match(lhs);
      ext_support_t lhs_s = supp_;
      supp_.clear();
      match(rhs);
      ext_support_t ret;
      for_each_const_(ext_support_t, c, lhs_s)
	for_each_const_(ext_support_t, d, supp_)
	{
	  monoid_elt_t mc(series_.monoid(), c->second);
	  monoid_elt_t md(series_.monoid(), d->second);
	  semiring_elt_t wc(series_.semiring(), c->first);
	  semiring_elt_t wd(series_.semiring(), d->first);
	  ret.push_back(std::make_pair((wc * wd).value(),
				       (mc * md).value()));
	}
      supp_ = ret;
      supp_.insert(supp_.begin(), old_supp_.begin(), old_supp_.end());
      return 0;
    }
    END

    MATCH__(Sum, lhs, rhs)
    {
      match(lhs);
      match(rhs);
      return 0;
    }
    END

    MATCH_(Star, node)
    {
      // undefined case.
      assertion(!"valid");
      return 0;
    }
    END

    MATCH__(LeftWeight, w, node)
    {
      ext_support_t old_supp_ = supp_;
      supp_.clear();
      match(node);
      for_each_(ext_support_t, c, supp_)
	c->first = op_mul(series_.semiring(), w, c->first);
      supp_.insert(supp_.begin(), old_supp_.begin(), old_supp_.end());
      return 0;
    }
    END

    MATCH__(RightWeight, node, w)
    {
      ext_support_t old_supp_ = supp_;
      supp_.clear();
      match(node);
      for_each_(ext_support_t, c, supp_)
	c->first = op_mul(series_.semiring(), c->first, w);
      supp_.insert(supp_.begin(), old_supp_.begin(), old_supp_.end());
      return 0;
    }
    END

    MATCH_(Constant, m)
    {
      supp_.push_back(std::make_pair
		      (identity_value(series_.semiring(),
				      SELECT(semiring_elt_value_t)),
		       m));
      return 0;
    }
    END

    MATCH(Zero)
    {
      return 0;
    }
    END

    MATCH(One)
    {
      supp_.push_back(std::make_pair
		      (identity_value(series_.semiring(),
				      SELECT(semiring_elt_value_t)),
		       identity_value(series_.monoid(),
				      SELECT(monoid_value_t))));
      return 0;
    }
    END

    support_t get()
    {
      support_t ret;
      ext_support_t s = ext_get();
      for_each_const_(ext_support_t, c, s)
	ret.push_back(c->second);
      return ret;
    }

    ext_support_t& ext_get()
    {
      // Now join same words.
      typedef std::map<monoid_value_t, semiring_elt_value_t> tmap_t;
      tmap_t v;
      typename tmap_t::iterator f;
      for_each_const_(ext_support_t, c, supp_)
	{
	  if ((f = v.find(c->second)) == v.end())
	    v[c->second] = c->first;
	  else
	    v[c->second] = op_add(series_.semiring(), v[c->second], c->first);
	}
      supp_.clear();
      for_each_const_(tmap_t, m, v)
	supp_.push_back(std::make_pair(m->second, m->first));
      return supp_;
    }

  private:
    ext_support_t	        supp_;
    const series_t&		series_;
  };

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_SUPPORT_HXX
