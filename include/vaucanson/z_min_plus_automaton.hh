// z_min_plus_automaton.hh:
// this file is part of the Vaucanson project.
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
#ifndef VCSN_Z_MIN_PLUS_AUTOMATON_HH
# define VCSN_Z_MIN_PLUS_AUTOMATON_HH

# include <vaucanson/contextual_headers.hh>
# include <vaucanson/algebra/implementation/semiring/tropical_semiring.hh>

namespace vcsn {

  namespace z_min_plus_automaton {

    using namespace vcsn;
    using namespace vcsn::algebra;
    using namespace vcsn::algebra::char_letter;

    typedef polynom<WordValue, int> series_set_elt_value_t;

    typedef TropicalSemiring<TropicalMin> semiring_t;
    typedef Series<semiring_t, Words> series_set_t;

    typedef Graph
    <
      labels_are_series,
      WordValue,
      int,
      series_set_elt_value_t,
      char,
      NoTag>
    automaton_impl_t;

    typedef Element<Automata<series_set_t>, automaton_impl_t>
    automaton_t;

    typedef generalized_traits<automaton_t>::automaton_t gen_automaton_t;
    
    AUTOMATON_TYPES_EXACT(automaton_t);

    typedef rat::exp<monoid_elt_value_t, semiring_elt_value_t>	krat_exp_impl_t;
    typedef Element<series_set_t, krat_exp_impl_t>			krat_exp_t;

# include <vaucanson/contextual_automaton_functions.thh>

  } // z_min_plus_automaton

} // vcsn

#endif // VCSN_Z_MIN_PLUS_AUTOMATON_HH