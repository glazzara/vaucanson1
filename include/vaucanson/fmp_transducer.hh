// fmp_transducer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_FMP_TRANSDUCER_HH
# define VCSN_FMP_TRANSDUCER_HH

# include <vaucanson/contextual_headers.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/semiring/numerical_semiring.hh>

namespace vcsn {
  namespace fmp_transducer {

    using namespace vcsn;
    using namespace vcsn::algebra;
    using namespace vcsn::algebra::char_letter;

    // Types of the monoids on which the free monoid product will be
    // based.

    typedef char				first_letter_t;
    typedef char				second_letter_t;

    typedef Words				first_monoid_t;
    typedef Words				second_monoid_t;

    typedef WordValue				first_monoid_elt_value_t;
    typedef WordValue				second_monoid_elt_value_t;

    typedef Element<first_monoid_t, first_monoid_elt_value_t>
						first_monoid_elt_t;
    typedef Element<second_monoid_t, second_monoid_elt_value_t>
						second_monoid_elt_t;

    typedef first_monoid_t::alphabet_t		first_alphabet_t;
    typedef second_monoid_t::alphabet_t		second_alphabet_t;

    // Types of the free monoid product.

    typedef FreeMonoidProduct<first_monoid_t, second_monoid_t>
						monoid_t;
    typedef std::pair<std::string, std::string>
						monoid_elt_value_t;
    typedef Element<monoid_t, monoid_elt_value_t>
						monoid_elt_t;


    // Types of the semiring.

    typedef NumericalSemiring			semiring_t;
    typedef bool				semiring_elt_value_t;
    typedef Element<semiring_t, semiring_elt_value_t>
						semiring_elt_t;


    // Types of the series.

    typedef Series<semiring_t, monoid_t>	series_set_t;
    typedef polynom<monoid_elt_value_t, semiring_elt_value_t>
						series_set_elt_value_t;
    typedef Element<series_set_t, series_set_elt_value_t>
						series_set_elt_t;


    typedef Automata<series_set_t>		automata_set_t;

    typedef Graph
    <
      labels_are_series,
      monoid_elt_value_t,
      semiring_elt_value_t,
      series_set_elt_value_t,
      char,
      NoTag>					automaton_impl_t;

    typedef Element<automata_set_t, automaton_impl_t>
						automaton_t;

    AUTOMATON_TYPES_EXACT(automaton_t);


  } // fmp_transducer
} // vcsn

#endif // ! VCSN_FMP_TRANSDUCER_HH
