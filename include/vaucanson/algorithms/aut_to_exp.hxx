// aut_to_exp.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_AUT_TO_EXP_HXX
# define VCSN_ALGORITHMS_AUT_TO_EXP_HXX

# include <vaucanson/algorithms/aut_to_exp.hh>

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/algorithms/normalized.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/misc/limits.hh>
# include <vaucanson/misc/random.hh>
# include <vaucanson/automata/concept/automata_base.hh>

# include <list>
# include <set>
# include <vector>

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

      unsigned n = utility::random::generate((unsigned) 0,
					     a.states().size() -
					     (n_init + n_final));

      typename Auto_::state_iterator k = a.states().begin();
      unsigned kk = 0;
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


  /*-----------------------.
  |    Heuristic chooser:  |
  | Edge Number Heuristic  |
  `-----------------------*/

  struct HChooser
  {
    template <class Auto_>
    hstate_t
    operator()(const Auto_& a) const
    {
      assertion(a.states().size() > 0);

      std::set<hedge_t> delta_in;
      std::set<hedge_t> delta_out;

      typename Auto_::state_iterator s = a.states().begin();
      unsigned int d_in = 0;
      unsigned int d_out = 0;
      unsigned int max = INT_MAX;
      bool has_loop = false;
      bool has_loop_old = false;

      for (typename Auto_::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i)
      {
	if (a.is_final(*i) || a.is_initial(*i))
	  continue;
	has_loop = false;

	a.deltac(delta_out, *i, delta_kind::edges());
	a.rdeltac(delta_in, *i, delta_kind::edges());
	for (typename std::set<hedge_t>::iterator j = delta_out.begin();
	     j != delta_out.end();
	     ++j)
	  if (*i == a.aim_of(*j))
	    has_loop = true;

	//FIXME : If the state has several loops
	if (has_loop)
	  d_in = delta_in.size() - 1;
	else
	  d_in = delta_in.size();
	d_out = delta_out.size();

	//We prefer to delete a state that has no loop transition
	if (d_in * d_out < max ||
	    (d_in * d_out == max &&
	     has_loop_old && not has_loop))
	{
	  s = i;
	  max = d_in * d_out;
	  has_loop_old = has_loop;
	}
	delta_out.clear();
	delta_in.clear();
      }
      return *s;
    }
  };


  /*-------------------------.
  | Heuristic chooser:       |
  | from Delgado & Morais    |
  | (Proposed in CIAA 2004)  |
  `-------------------------*/
 struct DMChooser
  {
    template <class Auto_>
    hstate_t
    operator()(const Auto_& a) const
    {
      assertion(a.states().size() > 0);

      std::set<hedge_t> delta_in;
      std::set<hedge_t> delta_out;
      typename Auto_::state_iterator s = a.states().begin();

      unsigned int weight_min = INT_MAX;
      for (typename Auto_::state_iterator i = a.states().begin();
	   i != a.states().end();
	   ++i)
      {
	if (a.is_final(*i) || a.is_initial(*i))
	  continue;
	unsigned int n_loops = 0;
	unsigned int in = 0;
	unsigned int out = 0;

	unsigned int weight = 0;

	delta_in.clear();
	delta_out.clear();
	a.deltac(delta_out, *i, delta_kind::edges());
	a.rdeltac(delta_in, *i, delta_kind::edges());

	for (typename std::set<hedge_t>::iterator j = delta_out.begin();
	     j != delta_out.end();
	     ++j)
	  if (*i == a.aim_of(*j))
	    ++n_loops;

	in = delta_in.size() - n_loops;
	out = delta_out.size() - n_loops;

	// Compute SUM(Win(k) * (Out - 1))
	for (typename std::set<hedge_t>::iterator j = delta_in.begin();
	     j != delta_in.end();
	     ++j)
	  if (*i != a.aim_of(*j))
	  {
	    weight += a.series_value_of(*j).length() * (out - 1);
	  }

	// Compute SUM(Wout(k) * (In - 1))
	for (typename std::set<hedge_t>::iterator j = delta_out.begin();
	     j != delta_out.end();
	     ++j)
	  if (*i != a.aim_of(*j))
	  {
	    weight += a.series_value_of(*j).length() * (in - 1);
	  }

	// Compute Wloop * (In * Out - 1)
	for (typename std::set<hedge_t>::iterator j = delta_out.begin();
	     j != delta_out.end();
	     ++j)
	  if (*i == a.aim_of(*j))
	  {
	    weight += a.series_value_of(*j).length() * (in  * out - 1);
	  }

	if (weight < weight_min)
	{
	  s = i;
	  weight_min = weight;
	}
      }
      return *s;
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
	//Slow
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
