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

# include <vaucanson/contextual_transducer_functions.hh>
# include <vaucanson/algorithms/evaluation.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/automata/implementation/generalized.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_verbalization.hh>


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

template<typename TS, typename TT>
output_series_set_elt_t
evaluation(const monoid_elt_t& input_word, const Element<TS, TT>& t)
{
  typedef polynom<WordValue, bool> bool_series_set_elt_value_t;
  typedef Series<NumericalSemiring, Words> bool_series_set_t;
  typedef Graph
    <
      labels_are_series,
      WordValue,
      bool,
      bool_series_set_elt_value_t,
      char,
      NoTag>
    bool_automaton_impl_t;

    typedef Element<Automata<bool_series_set_t>, bool_automaton_impl_t>
    bool_automaton_t;
  AUTOMATON_TYPES_EXACT_(bool_automaton_t, b_);
    
  output_series_set_elt_t e(t.structure().series().semiring());
  parse(input_word.value(), e);
  b_monoid_t b_monoid(t.series().monoid().alphabet());
  b_semiring_t b_semiring;
  b_series_set_t b_series(b_semiring, b_monoid);
  b_automata_set_t b_automata_set(b_series);
  bool_automaton_t w(b_automata_set);
  generalized_traits<bool_automaton_t>::automaton_t
    result(w.structure());
  standard_of(w, e.value());
  evaluation(w, t, result);
  return verbalize(aut_to_exp(generalized(result)));
}
