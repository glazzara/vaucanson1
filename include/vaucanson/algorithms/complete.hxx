// complete.hxx
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


# include <set>

# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/tools/usual.hh>

namespace vcsn {

  template <typename A, typename T>
  void
  auto_in_complete(Element<A, T>& work)
  {
    typedef Element<A, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    hstate_t puits = work.add_state();

    for (state_iterator i = work.states().begin();
	 i != work.states().end(); i++)
      {
	std::set<hstate_t> aim;
	alphabet_t& alpha = work.series().monoid().alphabet();
	for (alphabet_iterator j = alpha.begin();
	     j != alpha.end(); j++)
	  {
	    aim.clear();
	    work.letter_deltac(aim, *i, *j, delta_kind::states());
	  
	    if (!aim.size())
	      work.add_letter_edge(*i, puits, *j);
	  }
	
      }
  }

  
  template <typename A, typename T>
  Element<A, T>
  auto_complete(const Element<A, T>& e)
  {
    Element<A, T> res(e);
    res.emancipate();
    auto_in_complete(res);
    return res;
  }

} //vcsn
