// evaluation.hxx: this file is part of the Vaucanson project.
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

#ifndef VAUCANSON_ALGORITHMS_EVALUATION_HXX
# define VAUCANSON_ALGORITHMS_EVALUATION_HXX

# include <set>
# include <vaucanson/algorithms/evaluation.hh>
# include <vaucanson/algorithms/product.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/algorithms/extension.hh>
# include <vaucanson/algorithms/projection.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>

namespace vcsn {
  
  template <typename SA, typename ST, typename SRET,
	    typename Auto_t, typename Trans_t, typename Ret_t>
  void
  do_evaluation(const AutomataBase<SA>&,
		const TransducerBase<ST>&,
		const AutomataBase<SRET>&,
		const Auto_t& a,
		const Trans_t& t,
		Ret_t& ret)
  {
    Trans_t tt(t.set());
    tt = extension(a, t);
    Trans_t pro(t.set());
    pro = product(tt, t);
    pro = trim(pro);
    output_projection(pro, ret);
  }
  
  template<typename SA, typename TA, typename ST, 
	   typename TT, typename SRET, typename TRET>
  void
  evaluation(const Element<SA, TA>& a, const Element<ST, TT>& t, 
	     Element<SRET, TRET>& ret)
  {
    do_evaluation(a.set(), t.set(), ret.set(), a, t, ret);
  }

  template<typename E, typename S, typename Trans_t, typename M>
  void
  do_partial_evaluation(const E& exp,
			const TransducerBase<S>&,
			const Trans_t& t,
			M& state_exp_pair_set)
  {
    typedef typename Trans_t::value_t T;
    typedef typename output_projection_helper<S, T>::ret Auto_t;
    typedef typename Auto_t::set_t::series_t      Auto_series_t;
    typename Auto_t::set_t 
      auto_set(Auto_series_t(t.set().series().semiring()));
    Auto_t tmp_auto(auto_set);

    AUTOMATON_TYPES(Auto_t);
    monoid_elt_t empty = tmp_auto.series().monoid().empty_;
    standard_of(tmp_auto, exp.get(empty).value()); 
    partial_1(tmp_auto, t, state_exp_pair_set);
  }
  
  /* Input : an expression, a transducer.
     Output : a set of pair (hstate_t, expression)*/  
  template<typename S1, typename T1,
	   typename S2, typename T2,
	   typename M>
  void
  partial_evaluation(const Element<S1, T1>& exp, 
		     const Element<S2, T2>& trans,  
		     M& state_exp_pair_set)
  {
    do_partial_evaluation(exp, trans.set(), trans, state_exp_pair_set);
  }
  
  template<typename S, typename Auto_t, typename M, typename Chooser_t>
  void
  do_partial_elimination(const AutomataBase<S>&,
			 const Auto_t& a,
			 Chooser_t chooser,
			 M& state_exp_pair_set)
  {    
    AUTOMATON_TYPES(Auto_t);
    typedef typename std::set<hedge_t>			hedge_set_t;
    typedef std::map<hstate_t, series_elt_t>	      	sums_t;

    typename hedge_set_t::const_iterator		i, j;
    hstate_t					        q;
    hedge_set_t						edges;

    Auto_t b = a;
    standardize(b);

    int num = b.final().size() + 1; // all final states and the initial state.
    
    while (int(b.states().size()) != num)
      {
	series_elt_t loop_sum(b.series());
	sums_t       in_sums, out_sums;
	typename sums_t::iterator f;
	q = chooser(b);
	if (b.is_initial(q) || b.is_final(q))
	  continue;
	
	edges.clear();
	// FIXME : use a new version of delta !
	b.deltac(edges, q, delta_kind::edges());
	for (i = edges.begin(); i != edges.end(); i = j)
	  {
	    j = i; ++j;
	    
	    if (b.aim_of(*i) == q)
	      loop_sum += b.serie_of(*i);
	    else if ((f = out_sums.find(b.aim_of(*i))) !=
		     out_sums.end())
	      f->second += b.serie_of(*i);
	    else
	      out_sums[b.aim_of(*i)] = b.serie_of(*i);
	    b.del_edge(*i);
	  }
	edges.clear();
	// FIXME : use a new version of delta !
	b.rdeltac(edges, q, delta_kind::edges());
	for (i = edges.begin(); i != edges.end(); i = j)
	  {
	    j = i; ++j;
	    // here all loops have already been removed
	    if ((f = in_sums.find(b.origin_of(*i))) !=
		     in_sums.end())
	      f->second += b.serie_of(*i);
	    else
	      in_sums[b.origin_of(*i)] = b.serie_of(*i);
	    b.del_edge(*i);
	  }
	loop_sum.star();
	for_each_const_(sums_t, in, in_sums)
	  for_each_const_(sums_t, out, out_sums)
	  {
	    series_elt_t res = in->second * loop_sum * out->second;
	    b.add_serie_edge(in->first, out->first, res);
	  }
	b.del_state(q);
      }
    
    typedef std::map<hstate_t, series_elt_t>   se_map_t;
    typedef std::pair<hstate_t, series_elt_t>  state_exp_pair_t;
    se_map_t se_m;

    // maybe there are more than one edge comming to one final state
    // we must sum the labels
    for_each_edge(e, b)
      {
	hstate_t aim = b.aim_of(*e);
	if (se_m.find(aim) == se_m.end())
	  se_m[aim] = b.label_of(*e);
	else 
	  se_m[aim] += b.label_of(*e);
      }
    
    for_each_final_state(p, b)
      {
	if (se_m.find(*p) != se_m.end())
	  {
	    state_exp_pair_t mypair;
	    mypair.first = *p;
	    mypair.second = se_m[*p];
	    state_exp_pair_set.insert(mypair);
	  }
      }    
  }

  /*------------.
  | elimination |
  `------------*/
  // preconditions :
  //   - hope that automaton's labels are sufficient to support "star"
  //     => in fact, generalized automaton are generally expected here.
  // 
  
  template<typename A, typename T, typename M>
  void
  partial_elimination(const Element<A, T>& a,
		      M& state_exp_pair_set)
  {
    do_partial_elimination(a.set(), a, DefaultChooser(), state_exp_pair_set);
  }

  ////////////////////////////////////////////////////////////
  /* partial_1 */
  template<typename SA, typename ST,
	   typename Auto_t, typename Trans_t,
	   typename M>
  void
  do_partial_1(const AutomataBase<SA>&,
	       const TransducerBase<ST>&,
	       const Auto_t& a,
	       const Trans_t& t,
	       M& state_exp_pair_set)
  {    
    typedef typename Trans_t::value_t T;
    typedef typename output_projection_helper<ST, T>::ret Auto_ret_t;
    typedef typename Auto_ret_t::set_t::series_t      Auto_ret_series_t;
    typename Auto_ret_t::set_t 
      auto_set(Auto_ret_series_t(t.set().series().semiring()));

    AUTOMATON_TYPES_(Auto_t, a_);
    AUTOMATON_TYPES_(Trans_t, t_);
    AUTOMATON_TYPES_(Auto_ret_t, ret_);

    typedef std::map<hstate_t, std::pair<hstate_t, hstate_t> > 
      state_pair_map_t;
    typedef std::map<hstate_t, hstate_t> state_state_map_t;
    typedef std::pair<hstate_t, ret_series_elt_t> se_pair_t;

    Trans_t tmp_trans(t.set());
    tmp_trans = extension(a, t);

    Trans_t pro(t.set());
    state_pair_map_t sp_m; 
    pro = product(tmp_trans, t, sp_m);
    Auto_ret_t auto_p(auto_set);
    std::map<hstate_t, hstate_t> proj_m;
    auto_p = output_projection(pro, proj_m);

    /* unset final all the final states of auto_p */
    auto_p.clear_final();
    
    /* for each state u of t, add one final state to 'auto_p' */
    state_state_map_t final_of, is_final_of;
    for(t_state_iterator u = t.states().begin(); u != t.states().end(); ++u)
      {
	hstate_t new_state = auto_p.add_state();
	final_of[*u] = new_state;
	is_final_of[new_state] = *u;
	auto_p.set_final(new_state);
      }

    for(a_state_iterator u = auto_p.states().begin(); 
	u != auto_p.states().end(); ++u)
      {
	if (!auto_p.is_final(*u))
	  {
	    hstate_t p = sp_m[proj_m[*u]].first;
	    hstate_t q = sp_m[proj_m[*u]].second;

	    if (tmp_trans.is_final(p))
	      auto_p.add_spontaneous(*u, final_of[q]);
	  }
      }

    M se;
    partial_elimination(auto_p, se);

    state_exp_pair_set.clear();
    for_each_(M, p, se)
      {
	se_pair_t my_pair;
	my_pair.first = is_final_of[(*p).first];
	my_pair.second = (*p).second; // checking type compatibility
	state_exp_pair_set.insert(my_pair);
      }    
  }

  template<typename SA, typename TA, 
	   typename ST, typename TT, 
	   typename M>
  void
  partial_1(const Element<SA, TA>& a, 
	    const Element<ST, TT>& t, 
	    M& state_exp_pair_set)
  {
    do_partial_1(a.set(), t.set(), a, t, state_exp_pair_set);
  }

  ////////////////////////////////////////////////////////////
  /* partial_2 */
  template<typename SA, typename ST,
	   typename Auto_t, typename Trans_t,
	   typename Exp>
  void
  do_partial_2(const AutomataBase<SA>&,
	       const TransducerBase<ST>&,
	       const Auto_t& a,
	       const Trans_t& t,
	       const hstate_t p,
	       Exp& exp)
  {   
    typedef typename Trans_t::value_t T;
    typedef typename output_projection_helper<ST, T>::ret    Auto_ret_t;
    typedef typename Auto_ret_t::set_t::series_t      Auto_ret_series_t;

    typename Auto_ret_t::set_t 
      auto_set(Auto_ret_series_t(t.set().series().semiring()));

    Trans_t tt = t;
    tt.clear_initial();
    tt.set_initial(p);

    Trans_t tmp_trans(tt.set());
    tmp_trans = extension(a, tt);
        
    Trans_t pro(t.set());
    pro = trim(product(tmp_trans, tt));
    Auto_ret_t auto_p(auto_set);
    auto_p = output_projection(pro);

    exp = aut_to_exp(auto_p);
  }

  template<typename SA, typename TA, 
	   typename ST, typename TT, 
	   typename Exp>
  void
  partial_2(const Element<SA, TA>& a, 
	    const Element<ST, TT>& t, 
	    const hstate_t p, Exp& exp)
  {
    do_partial_2(a.set(), t.set(), a, t, p, exp);
  }

  ////////////////////////////////////////////////////////////

  template<typename SA, typename ST,
	   typename Auto_t, typename Trans_t,
	   typename M>
  void
  do_partial_3(const AutomataBase<SA>&,
	       const TransducerBase<ST>&,
	       const Auto_t& a,
	       const Trans_t& t,
	       const hstate_t p,
	       M& state_exp_pair_set)
  {    
    Trans_t tt = t;
    tt.clear_initial();
    tt.set_initial(p);
    tt=trim(tt);
    partial_1(a, tt, state_exp_pair_set);
  }

  template<typename SA, typename TA, 
	   typename ST, typename TT, 
	   typename M>
  void
  partial_3(const Element<SA, TA>& a, 
	    const Element<ST, TT>& t, 
	    const hstate_t p, 
	    M& state_exp_pair_set)
  {
    do_partial_3(a.set(), t.set(), a, t, p, state_exp_pair_set);
  }

}

#endif // VAUCANSON_ALGORITHMS_EVALUATION_HH