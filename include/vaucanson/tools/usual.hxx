// usual.hxx
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
#ifndef VCSN_TOOLS_USUAL_HXX
# define VCSN_TOOLS_USUAL_HXX

namespace vcsn {

  namespace tools {

    template <class InputIterator>
    inline
    usual_automaton_t new_automaton(InputIterator begin,
				    InputIterator end)
    {
      Alphabet alpha;
      for (InputIterator e = begin; e != end; ++e)
	alpha.insert(*e);
      NumericalSemiring semiring;
      Words freemonoid(alpha);
      usual_series_t series(semiring, freemonoid);
      Automata<usual_series_t> automata_set(series);
      return usual_automaton_t(automata_set);
    }

    template <class T>
    inline
    usual_automaton_t new_automaton(const T& alphabet)
    {
      return new_automaton(alphabet.begin(), alphabet.end());
    }


  } // tools

} // vcsn

#endif // VCSN_TOOLS_USUAL_HXX
