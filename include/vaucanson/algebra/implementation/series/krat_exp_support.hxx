// krat_exp_support.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2011 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_SUPPORT_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_SUPPORT_HXX

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
      typedef int					return_type;
      typedef Series					series_set_t;
      typedef Element<Series, T>			series_set_elt_t;
      typedef typename series_set_elt_t::monoid_elt_t	monoid_elt_t;
      typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
      typedef typename series_set_elt_t::semiring_elt_t	semiring_elt_t;
      typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
      typedef std::list<monoid_elt_value_t>		support_t;
      typedef std::list<std::pair<semiring_elt_value_t, monoid_elt_value_t> >
      ext_support_t;
      INHERIT_CONSTRUCTORS(self_t, T, return_type, Dispatch);

      SupportMatcher(const series_set_t& s):
	series_(s)
      {}

      MATCH__(Product, lhs, rhs)
      {
	ext_support_t old_supp_ = supp_;
	supp_.clear();
	this->match(lhs);
	ext_support_t lhs_s = supp_;
	supp_.clear();
	this->match(rhs);
	ext_support_t ret;
	for_all_const_(ext_support_t, c, lhs_s)
	  for_all_const_(ext_support_t, d, supp_)
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
	this->match(lhs);
	this->match(rhs);
	return 0;
      }
      END

      MATCH_(Star, node)
      {
	result_not_computable("undefined case (star) in krat_exp_support");
	return 0;
      }
      END

      MATCH__(LeftWeight, w, node)
      {
	ext_support_t old_supp_ = supp_;
	supp_.clear();
	this->match(node);
	for_all_(ext_support_t, c, supp_)
	  c->first = op_mul(series_.semiring(), w, c->first);
	supp_.insert(supp_.begin(), old_supp_.begin(), old_supp_.end());
	return 0;
      }
      END

      MATCH__(RightWeight, node, w)
      {
	ext_support_t old_supp_ = supp_;
	supp_.clear();
	this->match(node);
	for_all_(ext_support_t, c, supp_)
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
					SELECT(monoid_elt_value_t))));
	return 0;
      }
      END

      support_t get()
      {
	support_t ret;
	ext_support_t s = ext_get();
	for_all_const_(ext_support_t, c, s)
	  ret.push_back(c->second);
	return ret;
      }

      ext_support_t& ext_get()
      {
	// Now join same words.
	typedef std::map<monoid_elt_value_t, semiring_elt_value_t> tmap_t;
	tmap_t v;
	typename tmap_t::iterator f;
	for_all_const_(ext_support_t, c, supp_)
	{
	  if ((f = v.find(c->second)) == v.end())
	    v[c->second] = c->first;
	  else
	    v[c->second] = op_add(series_.semiring(), v[c->second], c->first);
	}
	supp_.clear();
	for_all_const_(tmap_t, m, v)
	  supp_.push_back(std::make_pair(m->second, m->first));
	return supp_;
      }

    private:
      ext_support_t		supp_;
      const series_set_t&	series_;
  };

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_SUPPORT_HXX
