// standard.hxx
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

#ifndef VCSN_ALGORITHMS_STANDARD_HXX
# define VCSN_ALGORITHMS_STANDARD_HXX

# include <iostream>

# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algorithms/sum.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn {

  /*---------.
  | standard |
  `---------*/
  template <class A_, typename Auto_>
  void
  do_in_standardize(const AutomataBase<A_>& ,
		    Auto_&		    a)
  {
    std::cerr << "not implemented yed." << std::endl;
  }

  template<typename A, typename T>
  void
  standardize(Element<A, T>& a)
  {
    do_in_standardize(a.set(), a);
  }

  /*---------------.
  | standard_union |
  `---------------*/

  template <typename A, typename lhs_t, typename rhs_t>
  void do_union_of_standard_here(const AutomataBase<A>& ,
				 lhs_t& lhs,
				 const rhs_t& rhs)
  {
    typedef typename std::set<hedge_t>		edelta_ret_t;
    edelta_ret_t	aim;
    hstate_t		new_i, old_i;

    new_i = *lhs.initial().begin();
    sum_here(lhs, rhs);
    for (typename lhs_t::initial_iterator i = lhs.initial().begin();
	 i != lhs.initial().end();
	   ++i)
      {
	// FIXME : is there something like an iterator over the
	// support of initial ?
	if (*i != new_i)
	  {
	    old_i = *i;
	    lhs.set_final(new_i, 
			  lhs.get_final(new_i) +
			  lhs.get_final(old_i));
	    aim.clear();
	    lhs.deltac(aim, old_i, delta_kind::edges());
	    for (typename edelta_ret_t::const_iterator d = aim.begin();
		 d != aim.end();
		 ++d)
	      {
		lhs.add_edge(new_i, 
			     lhs.aim_of(*d),
			     lhs.label_of(*d));
		lhs.del_edge(*d);
	      }
	      aim.clear();
	      lhs.rdeltac(aim, old_i, delta_kind::edges());
	      for (typename edelta_ret_t::const_iterator d = aim.begin();
		   d != aim.end();
		   ++d)
		{
		  lhs.add_edge(lhs.origin_of(*d), 
				     new_i, 
				     lhs.label_of(*d));
		  lhs.del_edge(*d);
		}
	      lhs.del_state(old_i);
	  }
      } 
  }

  template<typename A, typename T, typename U>
  void union_of_standard_here(Element<A, T>& lhs, 
			      const Element<A, U>& rhs)
  {
    // assert (lhs.set() == rhs.set())
    do_union_of_standard_here(lhs.set(), lhs, rhs);
  }

  template<typename A, typename T, typename U>
  Element<A, T> 
  union_of_standard(const Element<A, T>& lhs, 
		    const Element<A, U>& rhs)
  {
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(lhs);
    ret.emancipate();
    do_union_of_standard_here(ret.set(), ret, rhs);
    return ret;
  }

  /*------------.
  | is_standard |
  `------------*/
  template <typename A, typename auto_t>
  bool
  do_is_standard(const AutomataBase<A>& ,
		 const auto_t& a)
  {
    if (a.initial().size() != 1)
      return false;
    std::set<hstate_t> delta_ret;
    a.rdeltac(delta_ret, *a.initial().begin());
    if (delta_ret.size() != 0)
      return false;
    return true;
  }

  template<typename A, typename T>
  bool
  is_standard(const Element<A, T>& a)
  {
    return do_is_standard(a.set(), a);
  }

  /*----------------.
  | standard_concat |
  `----------------*/
  template <typename A, typename lhs_t, typename rhs_t>
  void do_concat_of_standard_here(const AutomataBase<A>& ,
				     lhs_t& lhs,
				  const rhs_t& rhs)
  {
    typedef std::map<hstate_t, hstate_t>	map_t;
    typedef std::set<hedge_t>			delta_ret_t;
    
    /*-----------------.
    | Concat of states |
    `-----------------*/
    map_t	map_h;
    delta_ret_t	aim;
    hstate_t	new_state;

    // Add states except the initial one
    for (typename rhs_t::state_iterator s = rhs.states().begin();
	 s != rhs.states().end();
	 ++s)
      if (!rhs.is_initial(*s))
	{
	  new_state = lhs.add_state();
	  map_h[*s] = new_state;
	}

    // Add edges
    hstate_t rhs_i = *rhs.initial().begin();    
    aim.clear();
    rhs.deltac(aim, rhs_i, delta_kind::edges());
    for (typename lhs_t::final_iterator f = lhs.final().begin();
	 f != lhs.final().end();
	 ++f)
      for (typename delta_ret_t::const_iterator d = aim.begin();
	   d != aim.end();
	   ++d)
	lhs.add_edge(*f, map_h[rhs.aim_of(*d)], rhs.label_of(*d));
    
    for (typename lhs_t::state_iterator s = lhs.states().begin();
	 s != lhs.states().end();
	 ++s)
      lhs.set_final(*s, lhs.get_final(*s) * rhs.get_final(rhs_i));
    
    for (typename map_t::const_iterator nf = map_h.begin(); 
	 nf != map_h.end(); 
	 ++nf)
      if (rhs.is_final(nf->first))
	lhs.set_final(nf->second);

    /*----------------.
    | Concat of edges |
    `----------------*/
    for (typename rhs_t::state_iterator i = rhs.states().begin();
	 i != rhs.states().end();
	 ++i)
      if (!rhs.is_initial(*i))
	{
	  aim.clear();
	  rhs.deltac(aim, *i, delta_kind::edges());
	  for (typename delta_ret_t::const_iterator d = aim.begin();
	       d != aim.end();
	       ++d)
	    lhs.add_edge(map_h[*i],
			 map_h[rhs.aim_of(*d)], 
			 rhs.label_of(*d));			
	}
  }
  
  template<typename A, typename T, typename U>
  void concat_of_standard_here(Element<A, T>& lhs, 
			       const Element<A, U>& rhs)
  {
    // assert (lhs.set() == rhs.set())
    do_concat_of_standard_here(lhs.set(), lhs, rhs);
  }
  
  template<typename A, typename T, typename U>
  Element<A, T> 
  concat_of_standard(const Element<A, T>& lhs, 
		     const Element<A, U>& rhs)
  {
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(lhs);
    ret.emancipate();
    do_concat_of_standard_here(ret.set(), ret, rhs);
    return ret;
  }

  /*--------------.
  | standard_star |
  `--------------*/
  template <typename A, typename auto_t>
  void do_star_of_standard_here(const AutomataBase<A>& ,
				auto_t& a)
  {    
    typedef std::set<hedge_t>		edelta_ret_t;
    edelta_ret_t	aim;
    
    hstate_t 	new_i = *a.initial().begin();
    a.deltac(aim, new_i, delta_kind::edges());
    for (typename auto_t::final_iterator f = a.final().begin();
	 f != a.final().end();
	 ++f)
      {
	if (*f != new_i)
	  for (typename edelta_ret_t::iterator d = aim.begin();
	       d != aim.end();
	       ++d)
	    // FIXME: it is wanted that we can create two similar edges.
	    // FIXME: is it a good thing ?
	    a.add_edge(*f, a.aim_of(*d), a.label_of(*d));
    }
    a.set_final(new_i);      
  }

  template<typename A, typename T>
  void star_of_standard_here(Element<A, T>& a)
  {
    do_star_of_standard_here(a.set(), a);
  }

  template<typename A, typename T>
  Element<A, T> 
  star_of_standard(const Element<A, T>& a)
  {
    // assert(lhs.set() == rhs.set())
    Element<A, T> ret(a);
    ret.emancipate();
    do_star_of_standard_here(ret.set(), ret);
    return ret;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_STANDARD_HXX
