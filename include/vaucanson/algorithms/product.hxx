// product.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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


#ifndef ALGORITHMS_PRODUCT_HXX
# define ALGORITHMS_PRODUCT_HXX

# include <set>
# include <map>
# include <queue>

# include <vaucanson/algorithms/product.hh>
# include <vaucanson/algorithms/extract.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/automata/concept/history.hh>

namespace vcsn {

  // FIXME : this should be defined differently :
  # define PRODUCT_EVENT	"product"

  /*--------.
  | product |
  `--------*/

  template <typename A, typename lhs_t, typename rhs_t, typename output_t>
  void auto_do_product(const AutomataBase<A>&	a_set,
		       output_t&	       	output,
		       const lhs_t&	       	lhs,
		       const rhs_t&		rhs)
  {
    typedef std::pair<hstate_t, hstate_t>		pair_hstate_t;
    typedef std::set<hedge_t>				delta_ret_t;
    typedef std::map<pair_hstate_t, hstate_t>		visited_t;
    typedef typename output_t::series_t			series_t;
    typedef typename output_t::series_elt_t		series_elt_t;
    typedef typename series_elt_t::monoid_elt_t		monoid_elt_t;
    typedef typename series_elt_t::weight_t		weight_t;
    typedef typename series_elt_t::value_t		series_value_t;

    delta_ret_t					edge_lhs; 
    delta_ret_t					edge_rhs;
    visited_t					visited;
    std::queue<pair_hstate_t>			to_process;
    series_elt_t				series_zero
      = output.series().zero(SELECT(typename series_elt_t::value_t));

    // FIXME : log history : it should be optional
    output.history().set_auto_event_about(PRODUCT_EVENT, lhs, rhs);
    
    /*----------------------------------.
    | Get initial states of the product |
    `----------------------------------*/
    for (typename lhs_t::initial_iterator lhs_s = lhs.initial().begin();
	 lhs_s != lhs.initial().end();
	 ++lhs_s)
      for (typename rhs_t::initial_iterator rhs_s = rhs.initial().begin();
	   rhs_s != rhs.initial().end();
	   ++rhs_s)
	{
	  hstate_t  new_state = output.add_state();
	  pair_hstate_t new_pair(*lhs_s, *rhs_s);
				 
	  // Log history : FIXME it should be optional.
	  // what about added a static information in the automaton type ?
	  // log_history(history::product_kind(), output, new_state, *lhs_s, *rhs_s);
	  output.history().set_state_event_about(PRODUCT_EVENT, new_state, *lhs_s, *rhs_s);

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
	
	// FIXME : use a new version of delta !
	edge_lhs.clear();
	lhs.deltac(edge_lhs, lhs_s, delta_kind::edges()); 
	edge_rhs.clear();
	rhs.deltac(edge_rhs, rhs_s, delta_kind::edges()); 

	for (typename delta_ret_t::const_iterator iel = edge_lhs.begin();
	     iel != edge_lhs.end();
	     ++iel)
	  {
	    series_elt_t s     = lhs.serie_of(*iel);

	    for (typename delta_ret_t::const_iterator ier = edge_rhs.begin();
		 ier != edge_rhs.end();
		 ++ier)
	      {
		series_elt_t s_  = rhs.serie_of(*ier);
		series_elt_t s__ = s;
		pair_hstate_t new_pair(lhs.aim_of(*iel), rhs.aim_of(*ier));

		for (typename series_value_t::iterator supp = s.supp().begin();
		     supp != s.supp().end();
		     ++supp)
		  s__.value_set(monoid_elt_t(supp->first).value(), 
			  (weight_t(supp->second) * s_.get(supp->first)).value());

		if (s__ != series_zero)
		  {
		    typename visited_t::const_iterator found = visited.find(new_pair);
		    hstate_t aim;

		    if (found == visited.end())
		      {
			aim = output.add_state();		      
			
			// Log history : FIXME : it should be optional
			// log_history(history::product_kind(), 
			//             output, aim, lhs_s, rhs_s);
			output.history().set_state_event_about(PRODUCT_EVENT, 
							       aim, 
							       lhs_s, 
							       rhs_s);
			
			visited[new_pair] = aim;
			to_process.push(new_pair);
		      }
		    else
		      aim = found->second;
		    hedge_t new_edge = output.add_serie_edge(current_state, aim, s__);
		    // Log history : FIXME it should be optional !
		    // log_history(history::product_kind(), output, new_e, *iel, *ier);
		    output.history().set_edge_event_about(PRODUCT_EVENT, 
							  new_edge, 
							  *iel, 
							  *ier);
		  }
	      }
	  }
      }
  }

  // wrappers
  template<typename A, typename T, typename U>
  Element<A, T> 
  auto_product(const Element<A, T>& lhs, const Element<A, U>& rhs)
  {
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(rhs.set());
    ret.create();
    ret.series() = lhs.series();
    auto_do_product(ret.set(), ret, lhs, rhs);
    return ret;
  }


    /*---------.
    | Diagonal |
    `----------*/

  template <typename A, typename auto_t>
  void do_auto_diagonal(const AutomataBase<A>&	a_set,
			auto_t&			a)
  {
    if (a.history().get_auto_event_about(PRODUCT_EVENT) == 0)
      {
	std::cerr << "Warning : trying to get the diagonal of an non product automaton."
		  << std::endl;
	return;
      }

    std::set<hstate_t>				diagonal_states;
    const history::BinaryEvent<hstate_t>*	b_event;

    for (typename auto_t::state_iterator s = a.states().begin();
	 s != a.states().end();
	 ++s)
      {
	b_event = dynamic_cast<const history::BinaryEvent<hstate_t> *>
	  (a.history().get_state_event_about(PRODUCT_EVENT, *s));
	assert(b_event);
	if (b_event->get_first() == b_event->get_second())
	  diagonal_states.insert(*s);
      }
    auto_in_extract(a, diagonal_states);
  }

  template <typename A, typename T>
  void
  auto_in_diagonal(Element<A, T>& a)
  {
    do_auto_diagonal(a.set(), a);
  }


  template<typename A, typename T>
  Element<A, T> 
  auto_diagonal(const Element<A, T>& a)
  {
    Element<A, T>    ret(a);
    
    ret.emancipate();
    auto_in_diagonal(ret.set(), ret);
    return ret;
  }


} // vcsn

#endif // ALGO_PRODUCT_HXX
