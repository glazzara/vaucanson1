// contextual_functions.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_CONTEXTUAL_FUNCTIONS_HXX
# define VCSN_CONTEXTUAL_FUNCTIONS_HXX

# include <vaucanson/contextual_functions.hh>

/*----------------.
| new_automaton() |
`----------------*/

template <class InputIterator>
automaton_t new_automaton(InputIterator begin,
			  InputIterator end)
{
  alphabet_t		alpha;
  for (InputIterator e = begin; e != end; ++e)
    alpha.insert(*e);
  semiring_t		semiring;
  monoid_t		freemonoid (alpha);
  series_set_t		series (semiring, freemonoid);
  automata_set_t	automata_set(series);
  return automaton_t (automata_set);
}

template <class T>
automaton_t new_automaton(const T& alphabet)
{
  return new_automaton(alphabet.begin(), alphabet.end());
}

/*--------------.
| standard_of() |
`--------------*/

template <class SeriesImpl>
automaton_t
do_standard_of(const series_set_t& structure, const SeriesImpl& impl)
{
  automaton_t r = new_automaton(structure.monoid().alphabet());
  standard_of(r, impl);
  return r;
}

template <class SeriesSet, class SeriesImpl>
automaton_t
standard_of(const Element<SeriesSet, SeriesImpl>& e)
{
  return do_standard_of(e.structure(), e.value());
}

/*--------------.
| thompson_of() |
`--------------*/

template <class SeriesImpl>
automaton_t
do_thompson_of(const series_set_t& structure, const SeriesImpl& impl)
{
  automaton_t r = new_automaton(structure.monoid().alphabet());
  thompson_of(r, impl);
  return r;
}

template <class SeriesSet, class SeriesImpl>
automaton_t
thompson_of(const Element<SeriesSet, SeriesImpl>& e)
{
  return do_thompson_of(e.structure(), e.value());
}

#endif // ! VCSN_CONTEXTUAL_FUNCTIONS_HXX