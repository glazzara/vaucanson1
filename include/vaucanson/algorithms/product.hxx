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

# include <vaucanson/algorithms/product.hh>
# include <vaucanson/algorithms/sub_automaton.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/automata/concept/history.hh>

namespace vcsn {

  /// \bug FIXME: This should be defined differently.
  # define PRODUCT_EVENT	"product"

  /*--------.
  | product |
  `--------*/

  template <typename A, typename lhs_t, typename rhs_t, typename output_t>
  void 
  product(const AutomataBase<A>&	,
	  output_t&			output,
	  const lhs_t&			lhs,
	  const rhs_t&			rhs)
  {
    typedef std::pair<hstate_t, hstate_t>		pair_hstate_t;
    typedef std::set<hedge_t>				delta_ret_t;
    typedef std::map<pair_hstate_t, hstate_t>		visited_t;
    typedef typename output_t::series_t			series_t;
    typedef typename output_t::series_elt_t		series_elt_t;
    typedef typename series_elt_t::monoid_elt_t		monoid_elt_t;
    typedef typename series_elt_t::weight_t		weight_t;
    typedef typename series_elt_t::value_t		series_value_t;
    typedef typename series_elt_t::support_t		support_t;

    delta_ret_t					edge_lhs; 
    delta_ret_t					edge_rhs;
    visited_t					visited;
    std::queue<pair_hstate_t>			to_process;
    series_elt_t				series_zero
      = output.set().series().zero(SELECT(typename series_elt_t::value_t));

    /// \bug FIXME: Log history: It should be optional.
//     output.history().set_auto_event_about(PRODUCT_EVENT, lhs, rhs);
    
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
				 
	  /// \bug FIXME: Log history: It should be optional.
	  // What about adding static information in the automaton type ?
// 	  log_history(history::product_kind(), output, new_state,
// 		      *lhs_s, *rhs_s);
// 	  output.history().set_state_event_about(PRODUCT_EVENT, new_state,
// 						 *lhs_s, *rhs_s);

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
	
	/// \bug FIXME: Use a new version of delta.
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

		for (typename support_t::iterator supp = s.supp().begin();
		     supp != s.supp().end();
		     ++supp)
		  s__.value_set(monoid_elt_t(*supp).value(), 
		       (s_.get(*supp) * s_.get(*supp)).value());

		if (s__ != series_zero)
		  {
		    typename visited_t::const_iterator found =
		      visited.find(new_pair);
		    hstate_t aim;

		    if (found == visited.end())
		      {
			aim = output.add_state();		      
			
			/// \bug FIXME: Log history: It should be optional.
// 			log_history(history::product_kind(), 
// 				    output, aim, lhs_s, rhs_s);
// 			output.history().set_state_event_about(PRODUCT_EVENT, 
// 							       aim, 
// 							       lhs_s, 
// 							       rhs_s);
			
			visited[new_pair] = aim;
			to_process.push(new_pair);
		      }
		    else
		      aim = found->second;
		    hedge_t new_edge = output.add_serie_edge(current_state,
							     aim, s__);
		    /// \bug FIXME: Log history: It should be optional.
// 		    log_history(history::product_kind(), output, new_e,
// 				*iel, *ier);
// 		    output.history().set_edge_event_about(PRODUCT_EVENT, 
// 							  new_edge, 
// 							  *iel, 
// 							  *ier);
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
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(rhs.set());
    product(ret.set(), ret, lhs, rhs);
    return ret;
  }


    /*---------.
    | Diagonal |
    `----------*/

  template <typename A, typename auto_t>
  void do_diagonal_here(const AutomataBase<A>&	a_set,
			auto_t&			a)
  {
//     if (a.history().get_auto_event_about(PRODUCT_EVENT) == 0)
//       {
// 	std::cerr << "Warning : trying to get the diagonal of an"
// 	  " non product automaton."
// 		  << std::endl;
// 	return;
//       }

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
    sub_automaton_here(a, diagonal_states);
  }

  template <typename A, typename T>
  void
  diagonal_here(Element<A, T>& a)
  {
    do_diagonal_here(a.set(), a);
  }


  template<typename A, typename T>
  Element<A, T> 
  diagonal(const Element<A, T>& a)
  {
    Element<A, T>    ret(a);
    
    ret.emancipate();
    do_diagonal_here(ret.set(), ret);
    return ret;
  }


} // vcsn

#endif // VCSN_ALGORITHMS_PRODUCT_HXX
