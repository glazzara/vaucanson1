// aut_to_exp.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_AUT_TO_EXP_HXX
# define VCSN_ALGORITHMS_AUT_TO_EXP_HXX

# include <vaucanson/algorithms/aut_to_exp.hh>

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/algorithms/normalized.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/misc/contract.hh>

# include <list>
# include <set>

# include <stdlib.h>
# include <time.h>

namespace vcsn {

  /*---------------.
  | DefaultChooser |
  `---------------*/

  /**
   * Default chooser for aut_to_exp().
   *
   * @pre There must be at least one state in the automaton.
   * @see aut_to_exp()
   */
  struct DefaultChooser
  {
    template <class Auto_>
    hstate_t
    operator()(const Auto_& a) const
    {
      assertion(a.states().size() > 0);
      typename Auto_::state_iterator s = a.states().begin();
      typename Auto_::state_iterator k = s;
      while ((k != a.states().end()) &&
	     ((a.is_initial(*k)) || (a.is_final(*k))))
	++k;
      s = k;
      return *s;
    }
  };


/*--------------.
| RandomChooser |
`--------------*/

/**
 * Choose randomly a state between all currently choosable
 * @pre There must be at least one state in the automaton.
 * @see aut_to_exp()
 */

  struct RandomChooser
  {
    template <class Auto_>
    hstate_t
    operator()(const Auto_& a) const
    {
      assertion(a.states().size() > 0);
      srand((unsigned)time( NULL ));

      int n_init = 0;
      int n_final = 0;
      for (typename Auto_::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i)
      {
	if (a.is_initial(*i))
	  ++n_init;
	if (a.is_final(*i))
	  ++n_final;
      }

      int n = (rand() % (a.states().size() - n_init - n_final));

      typename Auto_::state_iterator k = a.states().begin();
      int kk = 0;
      while (kk <= n ||
	     ((a.is_initial(*k)) || (a.is_final(*k))) || k == a.states().end())
	{
	  if (k == a.states().end())
	    {
	      k = a.states().begin();
	      continue;
	    }
	  ++k;
	  ++kk;
	}
      return *k;
    }
  };

  /*------------.
  | ListChooser |
  `------------*/

  /**
   * Chooser for aut_to_exp().
   *
   * This chooser  is built  using a std::list<hstate_t>.   It returns
   * the states of the automaton with the same order as in the list.
   *
   * @see aut_to_exp().
   */
  class ListChooser
  {
  public :
    ListChooser(const std::list<hstate_t>& l) :
      list_(l),
      pos_(l.begin())
    {}

    template <class Auto_>
    hstate_t operator() (const Auto_&)
    {
      assertion(pos_ != list_.end());
      return *pos_++;
    }

  private :
    std::list<hstate_t>	list_;
    std::list<hstate_t>::const_iterator pos_;
  };

  /*-----------.
  | aut_to_exp |
  `-----------*/

  template <class A_, typename Auto_, typename Chooser_>
  typename Auto_::series_set_elt_t
  do_in_aut_to_exp(const AutomataBase<A_>&  a_set,
		    Auto_&		    a,
		    Chooser_	            chooser)
  {
    AUTOMATON_TYPES(Auto_);
    typedef Auto_				automaton_t;
    typedef typename automaton_t::series_set_t      series_set_t;
    typedef typename automaton_t::series_set_elt_t  series_set_elt_t;

    typedef typename std::set<hedge_t>			hedge_set_t;
    typedef std::map<hstate_t, series_set_elt_t>	      	sums_t;

    typename hedge_set_t::const_iterator		i, j;
    hstate_t					        q;
    hedge_set_t						edges;
    std::list<hedge_t> edges_to_remove;
    normalize_here(a);
    precondition(is_normalized(a));

    while (a.states().size() != 2)
      {
	series_set_elt_t loop_sum(a_set.series());
	sums_t       in_sums, out_sums;

	q = chooser(a);
	if (a.is_initial(q) || a.is_final(q))
	  continue;

	edges.clear();
	// FIXME: use a new version of delta!
	a.deltac(edges, q, delta_kind::edges());
	for (i = edges.begin(); i != edges.end(); i = j)
	  {
	    j = i; ++j;

	    if (a.aim_of(*i) == q)
		loop_sum += a.series_of(*i);
	    else
	      {
		typename sums_t::iterator f = out_sums.find(a.aim_of(*i));
		if (f == out_sums.end())
		  f = out_sums.insert
		    (std::make_pair(a.aim_of(*i),
				    series_set_elt_t(a_set.series()))).first;
	        f->second += a.series_of(*i);
	      }
	    a.del_edge(*i);
	  }

	edges.clear();
	// FIXME: use a new version of delta!
	a.rdeltac(edges, q, delta_kind::edges());
	for (i = edges.begin(); i != edges.end(); i = j)
	  {
	    j = i; ++j;
	    // Here all loops have already been removed.
	    typename sums_t::iterator f = in_sums.find(a.origin_of(*i));
	    if (f == in_sums.end())
	      f = in_sums.insert
		(std::make_pair(a.origin_of(*i),
				series_set_elt_t(a_set.series()))).first;

	    f->second += a.series_of(*i);
	    a.del_edge(*i);
	  }

	loop_sum.star();
	for_each_const_(sums_t, in, in_sums)
	  for_each_const_(sums_t, out, out_sums)
	  {
	    series_set_elt_t res = in->second * loop_sum * out->second;
	    a.add_series_edge(in->first, out->first, res);
	  }
	a.del_state(q);
      }
    series_set_elt_t final(a_set.series());
    for_each_edge(i, a)
      final += a.label_of(*i);
    return final;
  }

  /*-----------.
  | aut_to_exp |
  `-----------*/

  template<typename A, typename T, typename Chooser_>
  typename Element<A, T>::series_set_elt_t
  aut_to_exp(const Element<A, T>& a, const Chooser_& c)
  {
    Element<A, T> ret(a);
    return do_in_aut_to_exp(ret.structure(), ret, c);
  }

  template<typename A, typename T>
  typename Element<A, T>::series_set_elt_t
  aut_to_exp(const Element<A, T>& a)
  {
    return aut_to_exp(a, DefaultChooser());
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_AUT_TO_EXP_HXX
