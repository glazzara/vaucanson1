<<<<<<< .working
<<<<<<< .working
// transducer_ops.hh
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH

# include <vaucanson/fundamental/fundamental.hh>
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
  typename Element<S, T>::output_serie_t
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
		 AutoType(output_weight_t) w);

  template <class S, class T>
  hedge_t
  op_add_i_edge(const TransducerBase<S>& s,
		T& v, 
		hstate_t from, 
		hstate_t to,
		AutoType(input_letter_t) i,
		AutoType(output_weight_t) w);

  template <class S, class T>
  hedge_t
  op_add_o_edge(const TransducerBase<S>& s,
		T& v, 
		hstate_t from, 
		hstate_t to,
		AutoType(input_letter_t) o,
		AutoType(output_weight_t) w);

} // vcsn

# include <vaucanson/automata/concept/transducer_ops.hxx>

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
=======
// transducer_ops.hh
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH

namespace vcsn {

#define AutoType(Type) \
  typename Element<S, T>::Type

  template <class S, class T>
  typename Element<S, T>::input_monoid_elt_t 
  op_input_of(const TransducerBase<S>& s,
	      const T& v,
	      hedge_t e);

  template <class S, class T>
  typename Element<S, T>::output_serie_t
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
		 AutoType(output_weight_t) w);

  template <class S, class T>
  hedge_t
  op_add_i_edge(const TransducerBase<S>& s,
		T& v, 
		hstate_t from, 
		hstate_t to,
		AutoType(input_letter_t) i,
		AutoType(output_weight_t) w);

  template <class S, class T>
  hedge_t
  op_add_o_edge(const TransducerBase<S>& s,
		T& v, 
		hstate_t from, 
		hstate_t to,
		AutoType(input_letter_t) o,
		AutoType(output_weight_t) w);

} // vcsn

# include <vaucanson/automata/concept/transducer_ops.hxx>

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
>>>>>>> .merge-right.r315
=======
// transducer_ops.hh
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH

# include <vaucanson/fundamental/fundamental.hh>
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
  typename Element<S, T>::output_serie_t
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
		 AutoType(output_weight_t) w);

  template <class S, class T>
  hedge_t
  op_add_i_edge(const TransducerBase<S>& s,
		T& v, 
		hstate_t from, 
		hstate_t to,
		AutoType(input_letter_t) i,
		AutoType(output_weight_t) w);

  template <class S, class T>
  hedge_t
  op_add_o_edge(const TransducerBase<S>& s,
		T& v, 
		hstate_t from, 
		hstate_t to,
		AutoType(input_letter_t) o,
		AutoType(output_weight_t) w);

} // vcsn

# include <vaucanson/automata/concept/transducer_ops.hxx>

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HH
>>>>>>> .merge-right.r318
