// z_max_plus_automaton.hh:
// this file is part of the Vaucanson project.
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
#ifndef VCSN_Z_MAX_PLUS_AUTOMATON_HH
# define VCSN_Z_MAX_PLUS_AUTOMATON_HH

# include <vaucanson/algebra/implementation/predefs.hh>
# include <vaucanson/algebra/implementation/free_monoid/str_words.hh>
# include <vaucanson/algebra/implementation/series/polynoms.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/algebra/implementation/semiring/tropical_semiring.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/implementation/graph.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  namespace z_max_plus_automaton {

    using namespace vcsn;
    using namespace vcsn::algebra;
    using namespace vcsn::algebra::char_letter;

    typedef polynom<WordValue, int> series_value_t;

    typedef TropicalSemiring<TropicalMax> semiring_t;
    typedef Series<semiring_t, Words> series_t;

    typedef Graph
    <
      labels_are_series,
      WordValue,
      int,
      series_value_t,
      char,
      NoTag>
    automaton_impl_t;

    typedef Element<Automata<series_t>, automaton_impl_t>
    automaton_t;

    AUTOMATON_TYPES_EXACT(automaton_t);

    typedef rat::exp<monoid_elt_value_t, semiring_elt_value_t>	krat_exp_impl_t;
    typedef Element<series_t, krat_exp_impl_t>			krat_exp_t;

# include <vaucanson/contextual_functions.hh>

  } // z_max_plus_automaton

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/z_max_plus_automaton.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_Z_MAX_PLUS_AUTOMATON_HH
