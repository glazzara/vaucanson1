// contextual_transducer_functions.hxx: this file is part of the Vaucanson project.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

/*----------------.
| new automaton() |
`----------------*/

template <class InputIterator>
automaton_t new_automaton(InputIterator input_alphabet_begin,
			  InputIterator input_alphabet_end,
			  InputIterator output_alphabet_begin,
			  InputIterator output_alphabet_end)
{
  alphabet_t input_alpha;
  alphabet_t output_alpha;
  for (InputIterator e = input_alphabet_begin;
       e != input_alphabet_end; ++e)
    input_alpha.insert(*e);
  for (InputIterator e = output_alphabet_begin;
       e != output_alphabet_end; ++e)
    output_alpha.insert(*e);
  monoid_t output_freemonoid(output_alpha);
  typename output_series_set_t::semiring_t semiring;
  output_series_set_t output_series(semiring, output_freemonoid);
  monoid_t freemonoid(input_alpha);
  series_set_t series(output_series, freemonoid);
  automata_set_t automata_set(series);
  return automaton_t(automata_set);
}


template <class T>
automaton_t new_automaton(const T& input_alphabet,
			  const T& output_alphabet)
{
  return new_automaton(input_alphabet.begin(),
		       input_alphabet.end(),
		       output_alphabet.begin(),
		       output_alphabet.end());
}


template <typename TransStruct,
	  typename TransImpl,
	  typename MonoidStruct,
	  typename MonoidImpl>
output_series_set_elt_t
do_evaluation(const vcsn::TransducerBase<TransStruct>&,
	      const TransImpl&,
	      const vcsn::algebra::FreeMonoidBase<MonoidStruct>&,
	      const MonoidImpl& input,
	      const Element<TransStruct, TransImpl>& t,
	      const Element<MonoidStruct, MonoidImpl>&)
{
  return verbalize(eval(t, input));
}


template <typename TransStruct,
	  typename TransImpl,
	  typename SeriesStruct,
	  typename SeriesImpl,
	  typename S,
	  typename T>
output_series_set_elt_t
do_evaluation(const vcsn::TransducerBase<TransStruct>&,
	      const TransImpl&,
	      const SeriesStruct&,
	      const vcsn::rat::exp<S, T>& input,
	      const Element<TransStruct, TransImpl>& t,
	      const Element<SeriesStruct, SeriesImpl>&)
{
  boolean_automaton::automaton_t w = boolean_automaton::
    new_automaton(t.structure().series().monoid().alphabet());
  boolean_automaton::gen_automaton_t result (w.structure());
  standard_of(w, input);
  evaluation(w, t, result);
  return verbalize(aut_to_exp(result));
}


template <typename TransStruct,
	  typename TransImpl,
	  typename ArgStruct,
	  typename ArgImpl>
output_series_set_elt_t
evaluation(const Element<TransStruct, TransImpl>& t,
	   const Element<ArgStruct, ArgImpl>& input)
{
  return do_evaluation(t.structure(), t.value(),
		       input.structure(), input.value(),
		       t, input);
}
