// transducer_ops.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/transducer_base.hh>

namespace vcsn {

#define AutoType(Type) \
  typename Element<S, T>::Type

  template <class S, class T>
  typename Element<S, T>::input_monoid_elt_t 
  op_input_of(const TransducerBase<S>& s,
	      const T& v,
	      hedge_t e);

  template <class S, class T>
  typename Element<S, T>::output_series_set_elt_t
  op_output_of(const TransducerBase<S>& s,
	       const T& v,
	       hedge_t e);

  template <class S, class T>
  hedge_t
  op_add_io_edge(const TransducerBase<S>& s,
		 T& v, 
		 hstate_t from, 
		 hstate_t to,
		 AutoType(input_letter_t) i,
		 AutoType(output_letter_t) o,
		 AutoType(output_semiring_elt_t) w);

  template <class S, class T>
  hedge_t
  op_add_io_edge(const TransducerBase<S>& s,
		 T& v, 
		 hstate_t from, 
		 hstate_t to,
		 AutoType(input_monoid_elt_t) input_w,
		 AutoType(output_monoid_elt_t) output_w,
		 AutoType(output_semiring_elt_t) w);

  template <class S, class T>
  hedge_t
  op_add_i_edge(const TransducerBase<S>& s,
		T& v, 
		hstate_t from, 
		hstate_t to,
		AutoType(input_letter_t) i,
		AutoType(output_semiring_elt_t) w);

  template <class S, class T>
  hedge_t
  op_add_o_edge(const TransducerBase<S>& s,
		T& v, 
		hstate_t from, 
		hstate_t to,
		AutoType(input_letter_t) o,
		AutoType(output_semiring_elt_t) w);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concept/transducer_ops.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
