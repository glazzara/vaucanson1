// compute.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef ALGORITHMS_COMPUTE_HXX
# define ALGORITHMS_COMPUTE_HXX

# include <algorithm>
# include <vector>
# include <vaucanson/algorithms/compute.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>

namespace vcsn {

  /*--------.
  | Compute |
  `--------*/
  // precondition : the automaton is realtime
  //
  //
  template <typename A, typename auto_t, 
	    typename serie_t, typename input_t>
  void 
  do_compute(const AutomataBase<A>& a_set,
	     const auto_t&	    a,
	     const input_t&	    word, 
	     serie_t&		    result)
  {
    // FIXME: for the moment, we use large vectors because the set of hstate_t
    // FIXME: can be sparsed. We wanted to be as general as possible.
    // FIXME: Variants of compute will be available soon of course.

    hstate_t max_hstate_t = 0;
    for (typename auto_t::state_iterator i = a.states().begin();
	 i != a.states().end();
	 ++i)
      max_hstate_t = std::max(*i, unsigned(max_hstate_t));

    std::vector<serie_t>		v1(max_hstate_t + 1);
    std::vector<serie_t>		v2(max_hstate_t + 1);
    std::list<hedge_t>			delta_ret;
    const typename serie_t::set_t	&serie_set = result.set();

    
    /*-------------------.
    | Initialize the set |
    `-------------------*/
     std::fill(v1.begin(), v1.end(), 
	       serie_set.zero(SELECT(typename serie_t::value_t)));

    /*--------.
    | Initial |
    `--------*/
    for (typename auto_t::initial_iterator i = a.initial().begin();
	 i != a.initial().end();
	 ++i)
      v1[*i] = a.get_initial(*i);

    /*------------.
    | Computation |
    `------------*/
    for (typename input_t::const_iterator e = word.begin();
	 e != word.end();
	 ++e)
      {
 	std::fill(v2.begin(), v2.end(), 
 		  serie_set.zero(SELECT(typename serie_t::value_t)));
	for (unsigned i = 0; i < v1.size(); ++i)
	  if (v1[i] != serie_set.zero(SELECT(typename serie_t::value_t)))
	  {
	    // FIXME : use the other version of delta to be more efficient !
	    delta_ret.clear();
	    a.letter_deltac(delta_ret, i, *e, delta_kind::edges());
	    for (typename std::list<hedge_t>::const_iterator l = 
		   delta_ret.begin();
		 l != delta_ret.end();
		 ++l)
	      v2[a.aim_of(*l)] += v1[i] * a.label_of(*l) ;
	  }
	std::swap(v1, v2);
      }

    /*-----------------.
    | Final and Result |
    `-----------------*/
    for (unsigned i = 0; i < v1.size(); ++i)
      if (v1[i] != serie_set.zero(SELECT(typename serie_t::value_t)))
	result += v1[i] * a.get_final(i);    
  }

  /*--------.
  | Wrapper |
  `--------*/
  template<typename A, typename T, typename W>
  typename Element<A, T>::series_elt_t
  compute(const Element<A, T>& a, const W& word)
  {
    typename Element<A, T>::series_elt_t ret;

    do_compute(a.set(), a, word, ret);
    return ret;
  }

} // vcsn

#endif // ALGORITHMS_COMPUTE_HXX
