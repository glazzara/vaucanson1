// product.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_PRODUCT_HXX
# define VCSN_ALGORITHMS_PRODUCT_HXX

# include <vaucanson/algorithms/product.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <set>
# include <map>
# include <queue>
# include <stack>

namespace vcsn {

  // Some little graphic tools
  namespace grphx {

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

	  std::list<hedge_t> aim;
	  a.deltac(aim, i, delta_kind::edges());
	  for_all_const_(std::list<hedge_t>, j, aim)
	    stack.push(a.aim_of(*j));
	}
      }
    }

    template <typename Output, typename Lhs, typename Rhs>
    static
    void setcoordfrom(Output& a,
		      Lhs& lhs,
		      Rhs& rhs,
		      hstate_t state,
		      hstate_t x_state,
		      hstate_t y_state)
    {
      double x = lhs.geometry().find(x_state)->second.first;
      double y = rhs.geometry().find(y_state)->second.second;
      a.geometry()[state] = std::make_pair(x, y);
    }


  }


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
    typedef std::set<hedge_t>				delta_ret_t;
    typedef std::map<pair_hstate_t, hstate_t>		visited_t;
    typedef typename series_set_elt_t::support_t	support_t;

    const series_set_t&	series   = output.structure().series();
    const monoid_t&	monoid   = series.monoid();
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
	  grphx::setcoordfrom(output, lhs, rhs, new_state, *lhs_s, *rhs_s);
      }

    /*-----------.
    | Processing |
    `-----------*/
    while (not to_process.empty())
      {
	const pair_hstate_t current_pair  = to_process.front();
	to_process.pop();

	const hstate_t lhs_s	     = current_pair.first;
	const hstate_t rhs_s	     = current_pair.second;
	const hstate_t current_state = visited[current_pair];

	output.set_initial(current_state,
			   lhs.get_initial(lhs_s) * rhs.get_initial(rhs_s));
	output.set_final(current_state,
			 lhs.get_final(lhs_s) * rhs.get_final(rhs_s));

	delta_ret_t edge_lhs;
	delta_ret_t edge_rhs;
	lhs.deltac(edge_lhs, lhs_s, delta_kind::edges());
	rhs.deltac(edge_rhs, rhs_s, delta_kind::edges());

	for_all_const_(delta_ret_t, l, edge_lhs)
	  for_all_const_(delta_ret_t, r, edge_rhs)
	  {
	    const series_set_elt_t  left_series  = lhs.series_of(*l);
	    const series_set_elt_t  right_series = rhs.series_of(*r);
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
		      grphx::setcoordfrom(output, lhs, rhs, aim, 
					  new_pair.first, new_pair.second);
		  }
		else
		  aim = found->second;
		output.add_series_edge(current_state, aim, prod_series);
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

#endif // ! VCSN_ALGORITHMS_PRODUCT_HXX
