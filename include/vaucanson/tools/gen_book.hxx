// gen_book.hxx
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
#ifndef VCSN_TOOLS_GEN_BOOK_HXX
# define VCSN_TOOLS_GEN_BOOK_HXX

# include <vaucanson/tools/gen_book.hh>
# include <vaucanson/tools/usual.hh>

namespace vcsn {

  namespace tools {

    template <class Auto_>
    Auto_	lombardy(unsigned size)
    {
      AUTOMATON_TYPES(Auto_);
      
      // FIXME:add assert "we want automaton on char."
      alphabets_elt_t	alpha;
      alpha.insert('a');
      alpha.insert('b');
      monoid_t		monoid(alpha);
      weights_t		weights;
      series_t		series(weights, monoid);
      automaton_t	automaton;
      automaton.create();
      automaton.series() = series;
      hstate_t		initial = automaton.add_state();
      hstate_t		c	= initial;

      for (unsigned i = 0; i < size; ++i)
	{
	  hstate_t	next = automaton.add_state();
	  automaton.add_letter_edge(c, c, 'a');
	  automaton.add_letter_edge(c, next, 'b');
	  automaton.set_initial(c);
	  c = next;
	}
      automaton.set_final(c);
      automaton.set_initial(c);
      automaton.add_letter_edge(c, initial, 'a');
      return automaton;
    }

  } // tools

} // vcsn

#endif // VCSN_TOOLS_GEN_BOOK_HXX
