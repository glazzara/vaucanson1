// translate.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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
#ifndef AUTOMATA_CONCEPT_TRANSLATE_HXX
# define AUTOMATA_CONCEPT_TRANSLATE_HXX

# include <vaucanson/automata/concept/translate.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <map>

namespace vcsn {

  template<typename lhs_t, typename rhs_t, typename F>
  void auto_translate_edges(lhs_t& dst_,
			    const rhs_t& from,
			    const F& translate_fun)
  {
    lhs_t dst;
    std::map<hstate_t, hstate_t> stmap;

    dst.create();
    dst.series() = from.series();
    for (typename rhs_t::state_iterator i = from.states().begin();
	 i != from.states().end();
	 ++i)
      {
	hstate_t s = dst.add_state();
	dst.set_final(s, from.get_final(*i));
	dst.set_initial(s, from.get_initial(*i));
	stmap[*i] = s;
      }
    for (typename rhs_t::edge_iterator i = from.edges().begin();
	 i != from.edges().end();
	 ++i)
      dst.add_serie_edge(stmap[i.origin()], stmap[i.aim()], 
			 translate_fun(from.serie_of(*i)));
    dst_.swap(dst);
  }

  template<typename auto_t, typename F>
  auto_t auto_translate_edges(const auto_t& from, const F& translate_fun)
  {
    auto_t dst;
    auto_translate_edges(dst, from, translate_fun);
    return dst;
  }
  
} // vcsn

#endif // AUTOMATA_CONCEPT_TRANSLATE_HXX
