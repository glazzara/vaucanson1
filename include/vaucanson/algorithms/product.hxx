// product.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_PRODUCT_HXX
# define VCSN_ALGORITHMS_PRODUCT_HXX

# include <set>
# include <map>
# include <queue>
# include <stack>

# include <vaucanson/algorithms/product.hh>
# include <vaucanson/algorithms/sub_automaton.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <vaucanson/xml/infos.hh>

namespace vcsn {

  /// \bug FIXME: This should be defined differently.
  # define PRODUCT_EVENT	"product"


  // Some little graphic tools
  namespace grphx {

    // Default routines, no Xml tag.
    template <typename Tag>
    struct if_tag
    {
      template<typename I>
      static
      Tag align(const I& a)
      {
        return a.tag();
      }
      template <typename Auto>
      static
      void setcoordfrom(const Auto& a, hstate_t,
                        Tag, hstate_t,
                        Tag, hstate_t)
      {
      }
    };

    // Specialisation for Xml tag.
    template <>
    struct if_tag<xml::XmlInfosTag>
    {
      // Diagonal alignement with a depth-first traversal
      template<typename I>
      static
      xml::XmlInfosTag align(const I& a)
      {
        AUTOMATON_TYPES(I);
	xml::XmlInfosTag tag;
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

            tag.states[i]().x = tag.states[i]().y = x++;

	    std::list<hedge_t> aim;
            a.deltac(aim, i, delta_kind::edges());
            for_all_const_(std::list<hedge_t>, j, aim)
              stack.push(a.aim_of(*j));
          }
        }
        return tag;
      }

      template <typename Auto>
      static
      void setcoordfrom(Auto& a, hstate_t state,
                        xml::XmlInfosTag x_tag, hstate_t x_state,
                        xml::XmlInfosTag y_tag, hstate_t y_state)
      {
        a.tag().states[state]().x = x_tag.states[x_state]().x;
        a.tag().states[state]().y = y_tag.states[y_state]().y;
      }
    };

    template <typename Tag, typename I>
    Tag align(const I& a)
    {
      return if_tag<Tag>::align(a);
    }

    template <typename Auto, typename Tag>
    void setcoordfrom(Auto& a, hstate_t state,
                      Tag x_tag, hstate_t x_state,
                      Tag y_tag, hstate_t y_state)
    {
      if_tag<Tag>::setcoordfrom(a, state, x_tag, x_state, y_tag, y_state);
    }
  }


  /*--------.
  | product |
  `--------*/

  template <typename A, typename lhs_t, typename rhs_t, typename output_t>
  void 
  product(const AutomataBase<A>&	,
	  output_t&			output,
	  const lhs_t&			lhs,
	  const rhs_t&			rhs,
	  std::map<hstate_t, std::pair<hstate_t, hstate_t> >& m)
  {
    typedef std::pair<hstate_t, hstate_t>		pair_hstate_t;
    typedef std::set<hedge_t>				delta_ret_t;
    typedef std::map<pair_hstate_t, hstate_t>		visited_t;
    AUTOMATON_TYPES(output_t);
    typedef typename series_elt_t::support_t		support_t;

    delta_ret_t					edge_lhs; 
    delta_ret_t					edge_rhs;
    visited_t					visited;
    std::queue<pair_hstate_t>			to_process;
    series_elt_t				series_zero
      = output.set().series().zero(SELECT(typename series_elt_t::value_t));

    tag_t lhs_tag = grphx::align<tag_t>(lhs);
    tag_t rhs_tag = grphx::align<tag_t>(rhs);

    /*----------------------------------.
    | Get initial states of the product |
    `----------------------------------*/
    for_each_initial_state(lhs_s, lhs)
      for_each_initial_state(rhs_s, rhs)
	{
	  hstate_t  new_state = output.add_state();
	  grphx::setcoordfrom(output, new_state,
                              lhs_tag, *lhs_s,
                              rhs_tag, *rhs_s);
	  pair_hstate_t new_pair(*lhs_s, *rhs_s);
	  m[new_state] = new_pair;
	  visited[new_pair] = new_state;
	  to_process.push(new_pair);
	}

    /*-----------.
    | Processing |
    `-----------*/
    while (!to_process.empty())
      {
	pair_hstate_t current_pair  = to_process.front();
	to_process.pop();

	hstate_t lhs_s	        = current_pair.first;
	hstate_t rhs_s	        = current_pair.second;
	hstate_t current_state  = visited[current_pair];

	output.set_initial(current_state, 
			   lhs.get_initial(lhs_s) * rhs.get_initial(rhs_s));
	output.set_final(current_state, 
			 lhs.get_final(lhs_s) * rhs.get_final(rhs_s));
	
	edge_lhs.clear();
	lhs.deltac(edge_lhs, lhs_s, delta_kind::edges()); 
	edge_rhs.clear();
	rhs.deltac(edge_rhs, rhs_s, delta_kind::edges()); 

	for_all_const_(delta_ret_t, iel, edge_lhs)
	  {
	    series_elt_t s     = lhs.serie_of(*iel);

	    for_all_const_(delta_ret_t, ier, edge_rhs)
	      {
		series_elt_t s_  = rhs.serie_of(*ier);
		series_elt_t s__ = s;
		pair_hstate_t new_pair(lhs.aim_of(*iel), rhs.aim_of(*ier));
		
		for_all_(support_t, supp, s.supp())
		  s__.value_set(monoid_elt_t(*supp).value(), 
		       (s_.get(*supp) * s.get(*supp)).value());

		if (s__ != series_zero)
		  {
		    typename visited_t::const_iterator found =
		      visited.find(new_pair);
		    hstate_t aim;

		    if (found == visited.end())
		      {
			aim = output.add_state();
			grphx::setcoordfrom(output, aim,
                                            lhs_tag, new_pair.first,
                                            rhs_tag, new_pair.second);
			visited[new_pair] = aim;
			m[aim] = new_pair;
			to_process.push(new_pair);
		      }
		    else
		      aim = found->second;
		    hedge_t new_edge = output.add_serie_edge(current_state,
							     aim, s__);
		  }
	      }
	  }
      }
  }

  // wrappers
  template<typename A, typename T, typename U>
  Element<A, T> 
  product(const Element<A, T>& lhs, const Element<A, U>& rhs)
  {
    std::map<hstate_t, std::pair<hstate_t, hstate_t> > m;
    // assertion(lhs.set() == rhs.set())
    Element<A, T> ret(rhs.set());
    product(ret.set(), ret, lhs, rhs, m);
    return ret;
  }

  template<typename A, typename T, typename U>
  Element<A, T> 
  product(const Element<A, T>& lhs, const Element<A, U>& rhs,
	  std::map<hstate_t, std::pair<hstate_t, hstate_t> >& m)
  {
    Element<A, T> ret(rhs.set());
    product(ret.set(), ret, lhs, rhs, m);
    return ret;
  }
  
} // vcsn

#endif // VCSN_ALGORITHMS_PRODUCT_HXX
