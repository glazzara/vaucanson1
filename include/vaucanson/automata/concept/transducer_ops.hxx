// transducer_ops.hxx
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

#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HXX

namespace vcsn {

#define AutoType(Type) \
  typename Element<S, T>::Type

  template <class S, class T>
  typename Element<S, T>::input_monoid_elt_t 
  op_input_of(const TransducerBase<S>& s,
	      const T& v,
	      hedge_t e)
  {
    return op_word_of(s, v, e);
  }

  template <class S, class T>
  typename Element<S, T>::output_serie_t
  op_output_of(const TransducerBase<S>& s,
	       const T& v,
	       hedge_t e)
  {
    AutoType(serie_t) is = op_serie_of(s, v, e);
    precondition(is.supp().size() == 1);
    return is.get(*is.supp().begin());
  }

  template <class S, class T>
  hedge_t
  op_add_io_edge(const TransducerBase<S>& s,
		 T& v, 
		 hstate_t from, 
		 hstate_t to,
		 AutoType(input_letter_t) i,
		 AutoType(output_letter_t) o,
		 AutoType(output_weight_t) w)
  {
    AutoType(input_monoid_elt_t) input_w(s.series().monoid(), i);
    AutoType(output_monoid_elt_t) output_w(s.series().weights().monoid(), o);
    AutoType(output_serie_t) os(s.series().weights());
    os.assoc(output_w, w);
    AutoType(serie_t) is(s.series());
    is.assoc(input_w, os);
    return op_add_serie_edge(s, v, from, to, is);
  }

  template <class S, class T>
  hedge_t
  op_add_i_edge(const TransducerBase<S>& s,
		 T& v, 
		 hstate_t from, 
		 hstate_t to,
		 AutoType(input_letter_t) i,
		 AutoType(output_weight_t) w)
  {
    AutoType(input_monoid_elt_t) input_w(s.series().monoid(), i);
    AutoType(output_monoid_elt_t) output_w(s.series().weights().monoid());
    AutoType(output_serie_t) os(s.series().weights());
    os.assoc(output_w, w);
    AutoType(serie_t) is(s.series());
    is.assoc(input_w, os);
    return op_add_serie_edge(s, v, from, to, is);
  }

  template <class S, class T>
  hedge_t
  op_add_o_edge(const TransducerBase<S>& s,
		 T& v, 
		 hstate_t from, 
		 hstate_t to,
		 AutoType(input_letter_t) o,
		 AutoType(output_weight_t) w)
  {
    AutoType(input_monoid_elt_t) input_w(s.series().monoid());
    AutoType(output_monoid_elt_t) output_w(s.series().weights().monoid(), o);
    AutoType(output_serie_t) os(s.series().weights());
    os.assoc(output_w, w);
    AutoType(serie_t) is(s.series());
    is.assoc(input_w, os);
    return op_add_serie_edge(s, v, from, to, is);
  }

} // vcsn

#undef AutoType

#endif // VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HXX
