// z_transducer.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_Z_TRANSDUCER_HH
# define VCSN_Z_TRANSDUCER_HH

# include <vaucanson/z_automaton.hh>
# include <vaucanson/boolean_automaton.hh>

# define VCSN_CONTEXT_NAMESPACE z_transducer

# include <vaucanson/contexts/char_letter.thh>
# include <vaucanson/contexts/dynamic_alphabet.thh>
# include <vaucanson/contexts/free_monoid.thh>

namespace vcsn
{

  namespace VCSN_CONTEXT_NAMESPACE
  {
    typedef z_automaton::semiring_elt_t		output_semiring_elt_t;
    typedef output_semiring_elt_t::set_t	output_semiring_t;
    typedef output_semiring_elt_t::value_t	output_semiring_elt_value_t;

    typedef z_automaton::rat_exp_t		output_series_set_elt_t;
    typedef output_series_set_elt_t::set_t	output_series_set_t;
    typedef output_series_set_elt_t::value_t	output_series_set_elt_value_t;

  } // End of namespace VCSN_CONTEXT_NAMESPACE.

} // End of namespace vcsn.

# include <vaucanson/contexts/ratseries_semiring.thh>
# include <vaucanson/contexts/polynom_series.thh>
# include <vaucanson/contexts/generic_automaton_impl.thh>
# include <vaucanson/contexts/transducer.thh>

namespace vcsn
{

  namespace VCSN_CONTEXT_NAMESPACE
  {

    AUTOMATON_TYPES_EXACT(automaton_t);
    AUTOMATON_FREEMONOID_TYPES_EXACT(automaton_t);

  } // End of namespace VCSN_CONTEXT_NAMESPACE.

} // End of namespace vcsn.

# include <vaucanson/contexts/transducer_functions.thh>

# undef VCSN_CONTEXT_NAMESPACE

#endif // ! VCSN_Z_TRANSDUCER_HH
