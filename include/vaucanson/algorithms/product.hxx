// product.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_PRODUCT_HXX
# define VCSN_ALGORITHMS_PRODUCT_HXX

# include <set>
# include <map>
# include <queue>
# include <stack>

# include <vaucanson/algorithms/product.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/automata/implementation/geometry.hh>
# include <vaucanson/misc/static.hh>

# define if_(cond, then_clause, else_clause)			\
  utility::static_if_simple<cond, then_clause, else_clause>::t

# define eq_(type1, type2)			\
  utility::static_eq<type1, type2>::value


namespace vcsn {

  namespace geom {

    // Some little graphic tools
    struct grphx {

	// Diagonal alignement with a depth-first traversal
	template<typename I>
	static
	void align(const I& a)
	{
	  AUTOMATON_TYPES(I);
	  int x = 0;
	  std::map<hstate_t,bool> visited;
	  std::stack<hstate_t> stack;

	  for_each_state(i, a) {
	    visited[*i] = false;
	    // ensure inaccessible states will be visited
	    stack.push(*i);
	  }

	  for_each_initial_state(i, a)
	    stack.push(*i);

	  while (!stack.empty()) {
	    hstate_t i = stack.top();
	    stack.pop();

	    if (!visited[i]) {
	      visited[i] = true;

	      a.geometry()[i] = std::make_pair(x, x);
	      x++;

	      std::list<htransition_t> aim;
	      a.deltac(aim, i, delta_kind::transitions());
	      for_all_const_(std::list<htransition_t>, j, aim)
		stack.push(a.aim_of(*j));
	    }
	  }
	}


	template <typename Output, typename Lhs, typename Rhs>
	static
	void setcoordfrom(Output& a,
			  const Lhs& lhs,
			  const Rhs& rhs,
			  const hstate_t state,
			  const hstate_t x_state,
			  const hstate_t y_state)
	{
	  std::map<hstate_t, std::pair<double, double> >::const_iterator iter;
	  double x = 0, y = 0;

	  iter = lhs.geometry().states().find(x_state);
	  if (iter != lhs.geometry().states().end())
	    x = iter->second.first;

	  iter = rhs.geometry().states().find(y_state);
	  if (iter != rhs.geometry().states().end())
	    y = iter->second.second;

	  a.geometry().states()[state] = std::make_pair(x, y);
	}

    };

    struct no_grphx
    {
	template <typename Output, typename Lhs, typename Rhs>
	static
	void setcoordfrom(Output& a,
			  const Lhs& lhs,
			  const Rhs& rhs,
			  const hstate_t state,
			  const hstate_t x_state,
			  const hstate_t y_state)
	{}

    };

  } // ! geom


  /*--------.
  | product |
  `--------*/

  template <typename A, typename lhs_t, typename rhs_t, typename output_t>
  void
  product(const AutomataBase<A>&,
	  output_t&			output,
	  const lhs_t&			lhs,
	  const rhs_t&			rhs,
	  std::map< hstate_t, std::pair<hstate_t, hstate_t> >& m,
	  const bool use_geometry = false)
  {
    AUTOMATON_TYPES(output_t);

    typedef std::pair<hstate_t, hstate_t>		pair_hstate_t;
    typedef std::set<htransition_t>				delta_ret_t;
    typedef std::map<pair_hstate_t, hstate_t>		visited_t;
    typedef typename series_set_elt_t::support_t	support_t;

    const series_set_t&	series	 = output.structure().series();
    const monoid_t&	monoid	 = series.monoid();
    const semiring_t&	semiring = series.semiring();

    const semiring_elt_t  semiring_zero =
      semiring.zero(SELECT(semiring_elt_value_t));

    visited_t			visited;
    std::queue<pair_hstate_t>	to_process;


    /*----------------------------------.
    | Get initial states of the product |
    `----------------------------------*/
    for_each_initial_state(lhs_s, lhs)
      for_each_initial_state(rhs_s, rhs)
    {
      const hstate_t		new_state = output.add_state();
      const pair_hstate_t	new_pair (*lhs_s, *rhs_s);

      m[new_state] = new_pair;
      visited[new_pair] = new_state;
      to_process.push(new_pair);

      if (use_geometry)
	if_(eq_(typename output_t::geometry_t, geometry) and	\
	    eq_(typename rhs_t::geometry_t, geometry) and	\
	    eq_(typename lhs_t::geometry_t, geometry),	\
	    geom::grphx, geom::no_grphx)
	  ::setcoordfrom(output, lhs, rhs, new_state, *lhs_s, *rhs_s);
    }

    /*-----------.
    | Processing |
    `-----------*/
    while (not to_process.empty())
    {
      const pair_hstate_t current_pair	= to_process.front();
      to_process.pop();

      const hstate_t lhs_s	     = current_pair.first;
      const hstate_t rhs_s	     = current_pair.second;
      const hstate_t current_state = visited[current_pair];

      output.set_initial(current_state,
			 lhs.get_initial(lhs_s) * rhs.get_initial(rhs_s));
      output.set_final(current_state,
		       lhs.get_final(lhs_s) * rhs.get_final(rhs_s));

      delta_ret_t transition_lhs;
      delta_ret_t transition_rhs;
      lhs.deltac(transition_lhs, lhs_s, delta_kind::transitions());
      rhs.deltac(transition_rhs, rhs_s, delta_kind::transitions());

      for_all_const_(delta_ret_t, l, transition_lhs)
	for_all_const_(delta_ret_t, r, transition_rhs)
      {
	const series_set_elt_t	left_series  = lhs.series_of(*l);
	const series_set_elt_t	right_series = rhs.series_of(*r);
	series_set_elt_t	    prod_series (series);

	bool		    prod_is_null (true);
	for_all_(support_t, supp, left_series.supp())
	{
	  const monoid_elt_t   supp_elt (monoid, *supp);
	  const semiring_elt_t l = left_series.get(supp_elt);
	  const semiring_elt_t r = right_series.get(supp_elt);
	  const semiring_elt_t p = l * r;
	  if (p != semiring_zero)
	  {
	    prod_series.assoc(*supp, p.value());
	    prod_is_null = false;
	  }
	}

	if (not prod_is_null)
	{
	  const pair_hstate_t new_pair (lhs.aim_of(*l), rhs.aim_of(*r));

	  typename visited_t::const_iterator found =
	    visited.find(new_pair);

	  hstate_t aim;
	  if (found == visited.end())
	  {
	    aim = output.add_state();
	    visited[new_pair] = aim;
	    m[aim] = new_pair;
	    to_process.push(new_pair);

	    if (use_geometry)
	      if_(eq_(typename output_t::geometry_t, geometry) and  \
		  eq_(typename rhs_t::geometry_t, geometry) and	    \
		  eq_(typename lhs_t::geometry_t, geometry),	    \
		  geom::grphx, geom::no_grphx)
		::setcoordfrom(output, lhs, rhs, aim,
			       new_pair.first, new_pair.second);
	  }
	  else
	    aim = found->second;
	  output.add_series_transition(current_state, aim, prod_series);
	}
      }
    }
  }

  // wrappers
  template<typename A, typename T, typename U>
  Element<A, T>
  product(const Element<A, T>& lhs, const Element<A, U>& rhs,
	  const bool use_geometry)
  {
    std::map<hstate_t, std::pair<hstate_t, hstate_t> > m;
    // assertion(lhs.structure() == rhs.structure())
    Element<A, T> ret(rhs.structure());
    product(ret.structure(), ret, lhs, rhs, m, use_geometry);
    return ret;
  }

  template<typename A, typename T, typename U>
  Element<A, T>
  product(const Element<A, T>& lhs, const Element<A, U>& rhs,
	  std::map<hstate_t, std::pair<hstate_t, hstate_t> >& m,
	  const bool use_geometry)
  {
    Element<A, T> ret(rhs.structure());
    product(ret.structure(), ret, lhs, rhs, m, use_geometry);
    return ret;
  }

} // End of namespace vcsn.


#undef if_
#undef eq_


#endif // ! VCSN_ALGORITHMS_PRODUCT_HXX
