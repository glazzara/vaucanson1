// complete.hxx
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

#ifndef VCSN_ALGORITHMS_COMPLETE_HXX
# define VCSN_ALGORITHMS_COMPLETE_HXX

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual.hh>
# include <set>

namespace vcsn {

  template <typename A, typename T>
  void
  auto_in_complete(Element<A, T>& work)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    hstate_t puits = work.add_state();
    for_each_state(i, work)
      {
	std::set<hstate_t> aim;
	for_each_letter(j, work.set().series().monoid().alphabet())
	  {
	    aim.clear();
	    work.letter_deltac(aim, *i, *j, delta_kind::states());
	    if (aim.size() == 0)
	      work.add_letter_edge(*i, puits, *j);
	  }
      }
  }

  template <typename A, typename T>
  Element<A, T>
  auto_complete(const Element<A, T>& e)
  {
    Element<A, T> res(e);
    auto_in_complete(res);
    return res;
  }

  template <class A, class T>
  bool
  is_complete(const Element<A, T>& e)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for_each_state(i, e)
      {
	std::set<hstate_t> aim;
	const alphabet_t& alpha = e.set().series().monoid().alphabet();
	for_each_letter(j, alpha)
	  {
	    aim.clear();
	    e.letter_deltac(aim, *i, *j, delta_kind::states());
	  
	    if (aim.size() == 0)
	      return false;
	  }
      }
    return true;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_COMPLETE_HXX
