// r_automaton.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004 The Vaucanson Group.
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
#ifndef VCSN_R_AUTOMATON_HH
# define VCSN_R_AUTOMATON_HH

# include <vaucanson/config/system.hh>
# include <fstream>
# include <sstream>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/concrete/predefs.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
# include <vaucanson/algebra/concrete/series/polynoms.hh>
# include <vaucanson/algebra/concrete/semiring/numerical_semiring.hh>
# include <vaucanson/algebra/concrete/series/series.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concrete/graph.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  namespace r_automaton {

    using namespace vcsn;
    using namespace vcsn::algebra;
    using namespace vcsn::algebra::char_letter;

    typedef polynom<WordValue, float> serie_value_t;

    typedef Series<NumericalSemiring, Words> series_t;

    typedef Graph
    <
      labels_are_series,
      WordValue,
      float,
      serie_value_t,
      char,
      NoTag>
    automaton_impl_t;

    typedef Element<Automata<series_t>, automaton_impl_t>
    automaton_t;

    AUTOMATON_TYPES_EXACT(automaton_t);

    template <class T>
    automaton_t new_automaton(const T& alphabet);

    template <class InputIterator>
    automaton_t new_automaton(InputIterator begin,
			      InputIterator end);

  } // z_automaton

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/r_automaton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_R_AUTOMATON_HH
