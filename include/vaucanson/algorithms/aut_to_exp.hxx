// aut_to_exp.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

#ifndef ALGORITHMS_AUT_TO_EXP_HXX
# define ALGORITHMS_AUT_TO_EXP_HXX

# include <vaucanson/algorithms/aut_to_exp.hh>

# include <algorithm>
# include <set>
# include <queue>
# include <cassert>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algorithms/accessible.hh>
# include <vaucanson/algorithms/normalized.hh>

namespace vcsn {

  /*---------------.
  | DefaultChooser |
  `---------------*/
  // description : a chooser is intended to respond what is the next
  // state to eliminate. 
  // precondition : there must be at least one state in the automaton
  //
  struct DefaultChooser
  {
    template <class Auto_>
    hstate_t
    operator()(const Auto_& a) const
    {
      assert(a.states().size() > 0);
      typename Auto_::state_iterator s = a.states().begin();
      while ((s != a.states().end()) &&
	     ((a.is_initial(*s)) || (a.is_final(*s))))
	++s;
     
      return *s;
    }
  };

  /*------------.
  | ListChooser |
  `------------*/
  // FIXME : could be extended to continue if the list is empty and there
  //	     remain states in the automaton ;
  //
  class ListChooser
  {
  public :
    ListChooser(const std::list<hstate_t>& l) :
      list_(l),
      pos_(l.begin())
    {}
    
    template <class Auto_>
    hstate_t operator()(const Auto_& a) 
    {
      assert(pos_ != list_.end());
      return *pos_++;
    }

  private :
    std::list<hstate_t>	list_;
    std::list<hstate_t>::const_iterator pos_;
  };

  /*------------.
  | aut_to_exp |
  `------------*/
  // preconditions :
  //   - hope that automaton's labels are sufficient to support "star"
  //     => in fact, generalized automaton are generally expected here.
  //  

  template <class A_, typename Auto_, typename Chooser_>
  typename Auto_::series_elt_t  
  do_in_aut_to_exp(const AutomataBase<A_>& a_set,
		    Auto_&		    a, 
		    Chooser_	            chooser)
  {
    typedef Auto_				automaton_t;
    typedef typename automaton_t::series_t      series_t;
    typedef typename automaton_t::series_elt_t  series_elt_t;
    typedef typename series_elt_t::monoid_elt_t	monoid_elt_t;
    typedef typename series_t::monoid_t		monoid_t;

    typedef typename std::set<hedge_t>			hedge_set_t;
    typedef std::map<hstate_t, series_elt_t>	      	sums_t;

    typename hedge_set_t::const_iterator		i, j;
    hstate_t					        q;
    hedge_set_t						edges;

    normalize(a);

    while (a.states().size() != 2)
      {
	series_elt_t loop_sum;
	sums_t       in_sums, out_sums;

	q = chooser(a);
	if (a.is_initial(q) || a.is_final(q))
	  continue;
	
	edges.clear();
	// FIXME : use a new version of delta !
	a.deltac(edges, q, delta_kind::edges());
	for (i = edges.begin(); i != edges.end(); i = j)
	  {
	    j = i; ++j;

	    if (a.aim_of(*i) == q)
		loop_sum += a.serie_of(*i);
	    else
	        out_sums[a.aim_of(*i)] += a.serie_of(*i);
	    a.del_edge(*i);
	  }
	edges.clear();
	// FIXME : use a new version of delta !
	a.rdeltac(edges, q, delta_kind::edges());
	for (i = edges.begin(); i != edges.end(); i = j)
	  {
	    j = i; ++j;
	    // here all loops have already been removed
	    in_sums[a.origin_of(*i)] += a.serie_of(*i);
	    a.del_edge(*i);
	  }
	loop_sum.star();
	for (typename sums_t::const_iterator in = in_sums.begin();
	     in != in_sums.end();
	     ++in)
	  for (typename sums_t::const_iterator out = out_sums.begin();
	       out != out_sums.end();
	       ++out)
	    {
	      series_elt_t res = in->second * loop_sum * out->second;
	      a.add_serie_edge(in->first, out->first, res);
	    }
	a.del_state(q);
      }
    series_elt_t final;
    for (typename Auto_::edge_iterator i = a.edges().begin(); 
	 i != a.edges().end(); ++i)
      final += a.label_of(*i);
    return final;
  }

  /*------------.
  | aut_to_exp |
  `------------*/
  // preconditions :
  //   - hope that automaton's labels are sufficient to support "star"
  //     => in fact, generalized automaton are generally expected here.
  //  
 
  template<typename A, typename T, typename Chooser_>
  inline
  typename Element<A, T>::series_elt_t
  aut_to_exp(const Element<A, T>& a, const Chooser_& c)
  {
    Element<A, T> ret(a);
    return do_in_aut_to_exp(ret.set(), ret, c);
  }
  
  template<typename A, typename T>
  inline
  typename Element<A, T>::series_elt_t
  aut_to_exp(const Element<A, T>& a)
  {
    return aut_to_exp(a, DefaultChooser());
  }

} // vcsn

#endif // ALGORITHMS_AUT_TO_EXP_HXX
