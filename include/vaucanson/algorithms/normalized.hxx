// normalized.hxx
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

#ifndef ALGORITHMS_NORMALIZED_HXX
# define ALGORITHMS_NORMALIZED_HXX

# include <vaucanson/algorithms/normalized.hh>

# include <stack>

# include <vaucanson/algorithms/sum.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*-----------.
  | normalized |
  `-----------*/
  template <class A_, typename Auto_>
  void
  do_in_normalize(const AutomataBase<A_>& a_set,
	       Auto_&			 a)
  {
    typedef Auto_				automaton_t;
    typedef typename automaton_t::series_t      series_t;
    typedef typename automaton_t::series_elt_t  series_elt_t;
    typedef typename series_elt_t::monoid_elt_t	monoid_elt_t;
    typedef typename series_t::monoid_t		monoid_t;

    hstate_t h = a.add_state();

    for (typename automaton_t::initial_iterator i = a.initial().begin();
	 i != a.initial().end();
	 ++i)
      a.add_serie_edge(h, *i, a.get_initial(*i));

    a.clear_initial();
    a.set_initial(h);

    h = a.add_state();

    for (typename automaton_t::final_iterator i = a.final().begin();
	 i != a.final().end();
	 ++i)
      a.add_serie_edge(*i, h, a.get_final(*i));

    a.clear_final();
    a.set_final(h);
  }

  template<typename A, typename T>
  void
  normalize(Element<A, T>& a)
  {
    do_in_normalize(a.set(), a);
  }


  /*-----------------.
  | normalized_union |
  `-----------------*/

  template <typename A, typename lhs_t, typename rhs_t>
  void do_normalized_auto_in_union(const AutomataBase<A>& a_set,
				   lhs_t& lhs,
				   const rhs_t& rhs)
  {
    sum_here(lhs, rhs);
    hstate_t new_i = lhs.add_state();
    hstate_t new_f = lhs.add_state();

    std::stack<hstate_t> init;

    for (typename lhs_t::initial_iterator i = lhs.initial().begin();
	 i != lhs.initial().end();
	 ++i)
      {
	lhs.add_spontaneous(new_i, *i);
	init.push(*i);
      }
    while (!init.empty())
      {
	lhs.unset_initial(init.top());
	init.pop();
      }

    for (typename lhs_t::final_iterator f = lhs.final().begin();
	 f != lhs.final().end();
	 ++f)
      {
	lhs.add_spontaneous(*f, new_f);
	init.push(*f);
      }
    while (!init.empty())
      {
	lhs.unset_final(init.top());
	init.pop();
      }
    lhs.set_final(new_f);
    lhs.set_initial(new_i);
  }

  template<typename A, typename T, typename U>
  void normalized_auto_in_union(Element<A, T>& lhs, 
				const Element<A, U>& rhs)
  {
    // assert (lhs.set() == rhs.set())
    do_normalized_auto_in_union(lhs.set(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T> 
  normalized_auto_union(const Element<A, T>& lhs, 
			const Element<A, U>& rhs)
  {
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(lhs);
    ret.emancipate();
    do_normalized_auto_in_union(ret.set(), ret, rhs);
    return ret;
  }

  /*--------------.
  | is_normalized |
  `--------------*/
  template <typename A, typename auto_t>
  bool
  do_is_normalized(const AutomataBase<A>& a_set,
		   const auto_t& a)
  {
    if (a.initial().size() != 1)
      return false;
    if (a.final().size() != 1)
      return false;
    std::set<hstate_t> delta_ret;
    a.rdeltac(delta_ret, *a.initial().begin(), delta_kind::states());
    a.deltac(delta_ret, *a.final().begin(), delta_kind::states());
    if (delta_ret.size() != 0)
      return false;
    return true;
  }

  template<typename A, typename T>
  bool
  is_normalized(const Element<A, T>& a)
  {
    return do_is_normalized(a.set(), a);
  }

  /*-------------------.
  | normalized_concat |
  `-------------------*/
  template <typename A, typename lhs_t, typename rhs_t>
  void do_normalized_auto_in_concat(const AutomataBase<A>& a_set,
				     lhs_t& lhs,
				     const rhs_t& rhs)
  {
    typedef std::map<hstate_t, hstate_t>	       map_lhs_rhs_t;
    typedef std::set<hedge_t>			       delta_ret_t;

    hstate_t	glue_state = *lhs.final().begin();

    /*-----------------.
    | Concat of states |
    `-----------------*/
    map_lhs_rhs_t	map_h;
    for (typename rhs_t::state_iterator s = rhs.states().begin();
	 s != rhs.states().end();
	 ++s)
      {
	hstate_t new_state;

	if (rhs.is_initial(*s))
	  new_state = glue_state;
	else
	  new_state = lhs.add_state();

	map_h[*s] = new_state;
	lhs.set_final(new_state, rhs.get_final(*s));
      }

    /*----------------.
    | Concat of edges |
    `----------------*/
    delta_ret_t	aim;
    for (typename rhs_t::state_iterator i = rhs.states().begin();
	 i != rhs.states().end();
	 ++i)
      {
	aim.clear();
	rhs.deltac(aim, *i, delta_kind::edges());
	for (typename delta_ret_t::const_iterator d = aim.begin();
	     d != aim.end();
	     ++d)
	  lhs.add_edge(map_h[rhs.origin_of(*d)], 
		       map_h[rhs.aim_of(*d)],		       
		       rhs.label_of(*d));
		       
      }
  }

  template<typename A, typename T, typename U>
  void normalized_auto_in_concat(Element<A, T>& lhs, 
				 const Element<A, U>& rhs)
  {
    // assert (lhs.set() == rhs.set())
    do_normalized_auto_in_concat(lhs.set(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T> 
  normalized_auto_concat(const Element<A, T>& lhs, 
			 const Element<A, U>& rhs)
  {
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(lhs);
    ret.emancipate();
    do_normalized_auto_in_concat(ret.set(), ret, rhs);
    return ret;
  }

  /*----------------.
  | normalized_star |
  `----------------*/
  template <typename A, typename auto_t>
  void do_normalized_auto_in_star(const AutomataBase<A>& a_set,
				  auto_t& a)
  {    
    a.add_spontaneous(*a.final().begin(), *a.initial().begin());
    hstate_t old_i = *a.initial().begin();
    hstate_t old_f = *a.final().begin();
    hstate_t new_i = a.add_state();
    hstate_t new_f = a.add_state();
    a.add_spontaneous(new_i, old_i);
    a.add_spontaneous(old_f, new_f);
    a.add_spontaneous(new_i, new_f);
    a.set_final(new_f);
    a.unset_final(old_f);
    a.set_initial(new_i);
    a.unset_initial(old_i);
 }

  template<typename A, typename T>
  void normalized_auto_in_star(Element<A, T>& a)
  {
    do_normalized_auto_in_star(a.set(), a);
  }

  template<typename A, typename T>
  Element<A, T> 
  normalized_auto_star(const Element<A, T>& a)
  {
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(a);
    ret.emancipate();
    do_normalized_auto_in_star(ret.set(), ret);
    return ret;
  }


} // vcsn

#endif // ALGORITHMS_NORMALIZED_HXX
