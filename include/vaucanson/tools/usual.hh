// usual.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_USUAL_HH
# define VCSN_TOOLS_USUAL_HH

# include <vaucanson/config/system.hh>
# include <fstream>
# include <sstream>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/implementation/predefs.hh>
# include <vaucanson/algebra/implementation/free_monoid/str_words.hh>
# include <vaucanson/algebra/implementation/series/polynoms.hh>
# include <vaucanson/algebra/implementation/semiring/numerical_semiring.hh>
# include <vaucanson/algebra/implementation/semiring/tropical_semiring.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/implementation/graph.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  namespace tools {

    using namespace vcsn;
    using namespace vcsn::algebra;
    using namespace vcsn::algebra::char_letter;

    typedef polynom<WordValue, bool> usual_series_value_t;
    typedef polynom<WordValue, int> weighted_series_value_t;

    typedef Series<NumericalSemiring, Words> usual_series_t;
    typedef Series<TropicalSemiring<TropicalMax>, Words> tropical_max_series_t;
    typedef Series<TropicalSemiring<TropicalMin>, Words> tropical_min_series_t;

    typedef Graph
    <
      labels_are_series,
      WordValue,
      bool,
      usual_series_value_t,
      char,
      NoTag>
    usual_automaton_impl_t;

    typedef Graph
    <
      labels_are_series,
      WordValue,
      int,
      weighted_series_value_t,
      char,
      NoTag>
    weighted_automaton_impl_t;

    typedef Element<Automata<usual_series_t>, usual_automaton_impl_t>
    usual_automaton_t;

    typedef Element<Automata<usual_series_t>, weighted_automaton_impl_t>
    numerical_automaton_t;

    typedef Element<Automata<tropical_max_series_t>, weighted_automaton_impl_t>
    tropical_max_automaton_t;

    typedef Element<Automata<tropical_min_series_t>, weighted_automaton_impl_t>
    tropical_min_automaton_t;

    template <class T>
    usual_automaton_t new_automaton(const T& alphabet);

    template <typename R, typename T>
    R new_automaton(const T& alphabet);

    template <class InputIterator>
    usual_automaton_t new_automaton(InputIterator, InputIterator);

    template <typename R, typename InputIterator>
    R new_automaton(InputIterator, InputIterator);

  } // tools

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/tools/usual.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_TOOLS_USUAL_HH
