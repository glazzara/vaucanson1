// eval.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_EVAL_HXX
# define VCSN_ALGORITHMS_EVAL_HXX

# include <vaucanson/algorithms/eval.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>
# include <algorithm>
# include <vector>

namespace vcsn {

  /*--------.
  | Eval |
  `--------*/
  // precondition : the automaton is realtime
  //
  // author: Yann Regis-Gianas.
  template <typename A, typename auto_t, 
	    typename semiring_elt_t, typename input_t>
  void 
  do_eval(const AutomataBase<A>&,
	     const auto_t&	    a,
	     const input_t&	    word, 
	     semiring_elt_t&		    result)
  {
    // FIXME: for the moment, we use large vectors because the set of hstate_t
    // FIXME: can be sparsed. We wanted to be as general as possible.
    // FIXME: Variants of eval will be available soon of course.
    typedef typename auto_t::monoid_elt_t monoid_elt_t;

    hstate_t max_hstate_t = 0;
    for (typename auto_t::state_iterator i = a.states().begin();
	 i != a.states().end();
	 ++i)
      max_hstate_t = std::max(*i, max_hstate_t);

    std::vector<semiring_elt_t>	v1(max_hstate_t + 1,
				   semiring_elt_t (a.series().semiring()));
    std::vector<semiring_elt_t>	v2(max_hstate_t + 1,
				   semiring_elt_t (a.series().semiring()));
    std::list<hedge_t>		delta_ret;
    const typename semiring_elt_t::set_t &semiring = a.series().semiring();
    semiring_elt_t zero =
      semiring.zero(SELECT(typename semiring_elt_t::value_t));
    typename auto_t::monoid_elt_t empty(a.series().monoid());

    /*-------------------.
    | Initialize the set |
    `-------------------*/
    std::fill(v1.begin(), v1.end(), zero);

    /*--------.
    | Initial |
    `--------*/
    // FIXME: here we assume that there is only weight in the initial app.
    for (typename auto_t::initial_iterator i = a.initial().begin();
	 i != a.initial().end();
	 ++i)
      v1[*i] = a.get_initial(*i).get(empty);

    /*------------.
    | Computation |
    `------------*/

    for (typename input_t::const_iterator e = word.begin();
	 e != word.end();
	 ++e)
      {
 	std::fill(v2.begin(), v2.end(), zero);
	for (unsigned i = 0; i < v1.size(); ++i)
	  if (v1[i] != zero)
	  {
	    // FIXME : use the other version of delta to be more efficient !
	    delta_ret.clear();
	    a.letter_deltac(delta_ret, i, *e, delta_kind::edges());
	    for (typename std::list<hedge_t>::const_iterator l = 
		   delta_ret.begin();
		 l != delta_ret.end();
		 ++l)
	      v2[a.aim_of(*l)] += v1[i] * a.serie_of(*l).get(monoid_elt_t(*e));
	  }
	std::swap(v1, v2);
      }

    /*-----------------.
    | Final and Result |
    `-----------------*/
    result = zero;
    for (unsigned i = 0; i < v1.size(); ++i)
      if (v1[i] != zero)
	result += v1[i] * a.get_final(i).get(empty);
  }

  /*--------.
  | Wrapper |
  `--------*/
  template<typename A, typename T, typename W>
  typename Element<A, T>::semiring_elt_t
  eval(const Element<A, T>& a, const W& word)
  {
    typename Element<A, T>::semiring_elt_t ret(a.set().series().semiring());

    do_eval(a.set(), a, word, ret);
    return ret;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_EVAL_HXX
