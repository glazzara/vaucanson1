// standard.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_STANDARD_HXX
# define VCSN_ALGORITHMS_STANDARD_HXX

# include <vaucanson/algorithms/standard.hh>

# include <vaucanson/algorithms/sum.hh>
# include <vaucanson/algorithms/accessible.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <set>

namespace vcsn {

  /*---------.
  | standard |
  `---------*/
  template <class A_, typename Auto_>
  void
  do_in_standardize(const AutomataBase<A_>& ,
		    Auto_&		    a)
  {
    AUTOMATON_TYPES(Auto_);
    hstate_t i = a.add_state();
    std::set<hedge_t> edge_oi;
    for_each_initial_state(oi, a)
      {
	series_set_elt_t s = a.get_initial(*oi);
	std::set<hedge_t> edge_oi;
	edge_oi.clear();
	a.deltac(edge_oi, *oi, delta_kind::edges());
	for_all_const_(std::set<hedge_t>, oil, edge_oi)
	  {
	    series_set_elt_t t = s*a.series_of(*oil);
	    a.add_series_edge(i,a.aim_of(*oil),t);
	  }
      }
    a.clear_initial();
    a.set_initial(i);
    accessible_here(a);
  }

  template<typename A, typename T>
  void
  standardize(Element<A, T>& a)
  {
    do_in_standardize(a.structure(), a);
  }

  /*---------------.
  | standard_union |
  `---------------*/

  template <typename A, typename lhs_t, typename rhs_t>
  void do_union_of_standard_here(const AutomataBase<A>& ,
				 lhs_t& lhs,
				 const rhs_t& rhs)
  {
    typedef typename std::set<hedge_t>		edelta_ret_t;
    edelta_ret_t	aim;
    hstate_t		new_i, old_i;

    new_i = *lhs.initial().begin();
    sum_here(lhs, rhs);
    for (typename lhs_t::initial_iterator i = lhs.initial().begin();
	 i != lhs.initial().end();
	   ++i)
      {
	// FIXME : is there something like an iterator over the
	// support of initial ?
	if (*i != new_i)
	  {
	    old_i = *i;
	    lhs.set_final(new_i,
			  lhs.get_final(new_i) +
			  lhs.get_final(old_i));
	    aim.clear();
	    lhs.deltac(aim, old_i, delta_kind::edges());
	    for (typename edelta_ret_t::const_iterator d = aim.begin();
		 d != aim.end();
		 ++d)
	      {
		lhs.add_edge(new_i,
			     lhs.aim_of(*d),
			     lhs.label_of(*d));
		lhs.del_edge(*d);
	      }
	      aim.clear();
	      lhs.rdeltac(aim, old_i, delta_kind::edges());
	      for (typename edelta_ret_t::const_iterator d = aim.begin();
		   d != aim.end();
		   ++d)
		{
		  lhs.add_edge(lhs.origin_of(*d),
				     new_i,
				     lhs.label_of(*d));
		  lhs.del_edge(*d);
		}
	      lhs.del_state(old_i);
	  }
      }
  }

  template<typename A, typename T, typename U>
  void union_of_standard_here(Element<A, T>& lhs,
			      const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    do_union_of_standard_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T>
  union_of_standard(const Element<A, T>& lhs,
		    const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    Element<A, T> ret(lhs);
    do_union_of_standard_here(ret.structure(), ret, rhs);
    return ret;
  }

  /*------------.
  | is_standard |
  `------------*/
  template <typename A, typename auto_t>
  bool
  do_is_standard(const AutomataBase<A>& ,
		 const auto_t& a)
  {
    typedef typename auto_t::series_set_elt_value_t	series_set_elt_value_t;

    // Check there is only one initial state.
    if (a.initial().size() != 1)
      return false;

    // Check there is no input transition on the initial state.
    hstate_t		s = *a.initial().begin();
    std::set<hstate_t>	delta_ret;
    a.rdeltac(delta_ret, s, vcsn::delta_kind::states());
    if (delta_ret.size() != 0)
      return false;

    // Check the multiplicity of the initial state.
    return
      a.get_initial(s) == a.series().identity(SELECT(series_set_elt_value_t));
  }

  template<typename A, typename T>
  bool
  is_standard(const Element<A, T>& a)
  {
    return do_is_standard(a.structure(), a);
  }

  /*----------------.
  | standard_concat |
  `----------------*/
  template <typename A, typename lhs_t, typename rhs_t>
  void do_concat_of_standard_here(const AutomataBase<A>& ,
				     lhs_t& lhs,
				  const rhs_t& rhs)
  {
    typedef std::map<hstate_t, hstate_t>	map_t;
    typedef std::set<hedge_t>			delta_ret_t;

    /*-----------------.
    | Concat of states |
    `-----------------*/
    map_t	map_h;
    delta_ret_t	aim;
    hstate_t	new_state;

    // Add states except the initial one
    for (typename rhs_t::state_iterator s = rhs.states().begin();
	 s != rhs.states().end();
	 ++s)
      if (!rhs.is_initial(*s))
	{
	  new_state = lhs.add_state();
	  map_h[*s] = new_state;
	}

    // Add edges
    hstate_t rhs_i = *rhs.initial().begin();
    aim.clear();
    rhs.deltac(aim, rhs_i, delta_kind::edges());
    for (typename lhs_t::final_iterator f = lhs.final().begin();
	 f != lhs.final().end();
	 ++f)
      {
	typename lhs_t::series_set_elt_t weight = lhs.get_final(*f);
	for (typename delta_ret_t::const_iterator d = aim.begin();
	     d != aim.end();
	     ++d)
	  lhs.add_series_edge(*f,
			      map_h[rhs.aim_of(*d)],
			      weight * rhs.label_of(*d));
      }

    for (typename lhs_t::state_iterator s = lhs.states().begin();
	 s != lhs.states().end();
	 ++s)
      lhs.set_final(*s, lhs.get_final(*s) * rhs.get_final(rhs_i));

    for (typename map_t::const_iterator nf = map_h.begin();
	 nf != map_h.end();
	 ++nf)
      if (rhs.is_final(nf->first))
	lhs.set_final(nf->second);

    /*----------------.
    | Concat of edges |
    `----------------*/
    for (typename rhs_t::state_iterator i = rhs.states().begin();
	 i != rhs.states().end();
	 ++i)
      if (!rhs.is_initial(*i))
	{
	  aim.clear();
	  rhs.deltac(aim, *i, delta_kind::edges());
	  for (typename delta_ret_t::const_iterator d = aim.begin();
	       d != aim.end();
	       ++d)
	    lhs.add_edge(map_h[*i],
			 map_h[rhs.aim_of(*d)],
			 rhs.label_of(*d));
	}
  }

  template<typename A, typename T, typename U>
  void concat_of_standard_here(Element<A, T>& lhs,
			       const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    do_concat_of_standard_here(lhs.structure(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T>
  concat_of_standard(const Element<A, T>& lhs,
		     const Element<A, U>& rhs)
  {
    // assertion(lhs.structure() == rhs.structure())
    Element<A, T> ret(lhs);
    do_concat_of_standard_here(ret.structure(), ret, rhs);
    return ret;
  }

  /*--------------.
  | standard_star |
  `--------------*/
  template <typename A, typename auto_t>
  void do_star_of_standard_here(const AutomataBase<A>& ,
				auto_t& a)
  {
    AUTOMATON_TYPES(auto_t);

    typedef std::set<hedge_t>		edelta_ret_t;
    edelta_ret_t			aim;

    hstate_t				new_i = *a.initial().begin();
    series_set_elt_t			out_mult = a.get_final(new_i);
    out_mult.star();

    a.deltac(aim, new_i, delta_kind::edges());

    for (typename auto_t::final_iterator f = a.final().begin();
	 f != a.final().end();
	 ++f)
      {
	if (*f != new_i)
	  for (typename edelta_ret_t::iterator d = aim.begin();
	       d != aim.end();
	       ++d)
	    // FIXME: it is wanted that we can create two similar edges.
	    // FIXME: is it a good thing ?
	    a.add_edge(*f, a.aim_of(*d), a.label_of(*d));

      }

    for (typename edelta_ret_t::iterator d = aim.begin();
	 d != aim.end();
	 ++d)
      {
	series_set_elt_t st = out_mult * a.series_of(*d);
	hstate_t to = a.aim_of(*d);
	a.del_edge(*d);
	a.add_series_edge(new_i, to, st);
      }

    a.set_final(new_i, out_mult);
  }

  template<typename A, typename T>
  void star_of_standard_here(Element<A, T>& a)
  {
    do_star_of_standard_here(a.structure(), a);
  }

  template<typename A, typename T>
  Element<A, T>
  star_of_standard(const Element<A, T>& a)
  {
    // assertion(lhs.structure() == rhs.structure())
    Element<A, T> ret(a);
    do_star_of_standard_here(ret.structure(), ret);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_STANDARD_HXX
