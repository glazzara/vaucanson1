// usual.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_USUAL_HXX
# define VCSN_TOOLS_USUAL_HXX

namespace vcsn {

  namespace tools {

    template <class InputIterator>
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

    template <typename R, typename InputIterator>
    R new_automaton(InputIterator begin, InputIterator end)
    {
      typedef typename R::set_t Automata;
      typedef typename Automata::series_t Series;
      typedef typename Series::monoid_t Monoid;
      typedef typename Series::semiring_t Semiring;
      typedef typename Monoid::alphabet_t Alphabet;

      Alphabet alpha;
      for (InputIterator e = begin; e != end; ++e)
	alpha.insert(*e);
      Semiring semiring;
      Monoid freemonoid(alpha);
      Series series(semiring, freemonoid);
      Automata automata_set(series);
      return R(automata_set);
    }


    template <class T>
    usual_automaton_t new_automaton(const T& alphabet)
    {
      return new_automaton(alphabet.begin(), alphabet.end());
    }

    template <class R, class T>
    R new_automaton(const T& alphabet)
    {
      return new_automaton<R>(alphabet.begin(), alphabet.end());
    }


  } // tools

} // vcsn

#endif // VCSN_TOOLS_USUAL_HXX
