// transducer_ops.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HXX

# include <vaucanson/algebra/concept/monoid_base.hh>

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
  typename Element<S, T>::output_series_set_elt_t
  op_output_of(const TransducerBase<S>& s,
	       const T& v,
	       hedge_t e)
  {
    AutoType(series_set_elt_t) is = op_series_of(s, v, e);
    precondition(is.supp().size() == 1);
    return
      is.get(AutoType(monoid_elt_t) (is.structure().monoid(), *is.supp().begin()));
  }

  template <class S, class T>
  hedge_t
  op_add_io_edge(const TransducerBase<S>& s,
		 T& v,
		 hstate_t from,
		 hstate_t to,
		 AutoType(input_letter_t) i,
		 AutoType(output_letter_t) o,
		 AutoType(output_semiring_elt_t) w)
  {
    AutoType(input_monoid_elt_t) input_w(s.series().monoid(), i);
    AutoType(output_monoid_elt_t) output_w(s.series().semiring().monoid(), o);
    AutoType(output_series_set_elt_t) os(s.series().semiring());
    os.assoc(output_w, w);
    AutoType(series_set_elt_t) is(s.series());
    is.assoc(input_w, os);
    std::cout << "add io edge :" << o << " "
	      << output_w << " " << w << " "
	      << os << std::endl;
   return op_add_series_edge(s, v, from, to, is);
  }

  template <class S, class T>
  hedge_t
  op_add_io_edge(const TransducerBase<S>& s,
		 T& v,
		 hstate_t from,
		 hstate_t to,
		 AutoType(input_monoid_elt_t) input_w,
		 AutoType(output_monoid_elt_t) output_w,
		 AutoType(output_semiring_elt_t) w)
  {
    AutoType(output_series_set_elt_t) os(s.series().semiring());
    os.assoc(output_w, w);
    AutoType(series_set_elt_t) is(s.series());
    is.assoc(input_w, os);
    return op_add_series_edge(s, v, from, to, is);
  }

  template <class S, class T>
  hedge_t
  op_add_i_edge(const TransducerBase<S>& s,
		 T& v,
		 hstate_t from,
		 hstate_t to,
		 AutoType(input_letter_t) i,
		 AutoType(output_semiring_elt_t) w)
  {
    AutoType(input_monoid_elt_t) input_w(s.series().monoid(), i);
    AutoType(output_monoid_elt_t) output_w(s.series().semiring().monoid());
    AutoType(output_series_set_elt_t) os(s.series().semiring());
    os.assoc(output_w, w);
    AutoType(series_set_elt_t) is(s.series());
    is.assoc(input_w, os);
    return op_add_series_edge(s, v, from, to, is);
  }

  template <class S, class T>
  hedge_t
  op_add_o_edge(const TransducerBase<S>& s,
		 T& v,
		 hstate_t from,
		 hstate_t to,
		 AutoType(input_letter_t) o,
		 AutoType(output_semiring_elt_t) w)
  {
    AutoType(input_monoid_elt_t) input_w(s.series().monoid());
    AutoType(output_monoid_elt_t) output_w(s.series().semiring().monoid(), o);
    AutoType(output_series_set_elt_t) os(s.series().semiring());
    os.assoc(output_w, w);
    AutoType(series_set_elt_t) is(s.series());
    is.assoc(input_w, os);
    return op_add_series_edge(s, v, from, to, is);
  }

  template <class S, class T>
  AutoType(series_set_elt_t)
    make_series(const TransducerBase<S>& s,
		AutoType(output_monoid_elt_value_t) o)
  {
    AutoType(input_monoid_elt_t) empty =
      algebra::identity_as<AutoType(input_monoid_elt_value_t)>::
      of(s.series().monoid());
    AutoType(output_semiring_elt_t) semi_id =
      algebra::identity_as<AutoType(output_semiring_elt_value_t)>::
      of(s.series().semiring().semiring());

    AutoType(input_monoid_elt_t) input_w(s.series().monoid());
    AutoType(output_series_set_elt_t) os (s.series().semiring());

    Element<AutoType(output_monoid_t), AutoType(output_monoid_elt_value_t)>
      o_elt (s.series().semiring().monoid(), o);
    os.assoc(o_elt, semi_id);
    AutoType(series_set_elt_t) is (s.series());
    is.assoc(empty, os);
    return is;
  }

  template <class S, class T>
  void
  op_set_o_final(const TransducerBase<S>& s,
		 T& v,
		 hstate_t final,
		 AutoType(output_monoid_elt_value_t) o)
  {
    AutoType(series_set_elt_t) is = make_series<S, T>(s, o);
    op_set_final(s, v, final, is);
  }

  template <class S, class T>
  void
  op_set_o_initial(const TransducerBase<S>& s,
		   T& v,
		   hstate_t initial,
		   AutoType(output_monoid_elt_value_t) o)
  {
    AutoType(series_set_elt_t) is = make_series<S, T>(s, o);
    op_set_initial(s, v, initial, is);
  }

} // vcsn

#undef AutoType

#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_OPS_HXX
