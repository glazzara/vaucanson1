// transducer_base.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HXX
# define VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HXX

# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/automata/concept/transducer_ops.hh>

namespace vcsn {

  template <typename Self>
  TransducerBase<Self>::TransducerBase()
  {}

  template <typename Self>
  TransducerBase<Self>::TransducerBase(const TransducerBase& other) :
    AutomataBase<Self>(other)
  {}

  /** */
  template <typename Self, typename T>
  MetaElement<TransducerBase<Self>, T>::MetaElement()
  {}

  /** copy constructor */
  template <typename Self, typename T>
  MetaElement<TransducerBase<Self>, T>::MetaElement(const MetaElement& a):
    MetaElement<AutomataBase<Self>, T>::MetaElement(a)
  {}

  template <typename Self, typename T>
  typename MetaElement<TransducerBase<Self>, T>::input_monoid_elt_t
  MetaElement<TransducerBase<Self>, T>::input_of(hedge_t e) const
  {
    return op_input_of(this->structure(), this->value(), e);
  }

  template <typename Self, typename T>
  typename MetaElement<TransducerBase<Self>, T>::output_series_set_elt_t
  MetaElement<TransducerBase<Self>, T>::output_of(hedge_t e) const
  {
    return op_output_of(this->structure(), this->value(), e);
  }

  template <typename Self, typename T>
  hedge_t
  MetaElement<TransducerBase<Self>, T>::
  add_io_edge(hstate_t from,
	      hstate_t to,
	      input_monoid_elt_value_t i,
	      output_monoid_elt_value_t o,
	      output_semiring_elt_t w)
  {
    if (w == output_semiring_elt_t())
      w = algebra::identity_as<output_semiring_elt_value_t>
	::of(this->series().semiring().semiring());
    Element<input_monoid_t, input_monoid_elt_value_t>
      i_elt (this->structure().series().monoid(), i);
    Element<output_monoid_t, output_monoid_elt_value_t>
      o_elt (this->structure().series().semiring().monoid(), o);
    return op_add_io_edge(this->structure(), this->value(),
			  from, to, i_elt, o_elt, w);
  }


  template <typename Self, typename T>
  hedge_t
  MetaElement<TransducerBase<Self>, T>::add_io_edge(hstate_t from,
						    hstate_t to,
						    input_letter_t i,
						    output_letter_t o,
						    output_semiring_elt_t w)
  {
    if (w == output_semiring_elt_t())
      w = algebra::identity_as<output_semiring_elt_value_t>
	::of(this->series().semiring().semiring());
    return op_add_io_edge(this->structure(), this->value(),
			  from, to, i, o, w);
  }

  template <typename Self, typename T>
  hedge_t
  MetaElement<TransducerBase<Self>, T>::add_o_edge(hstate_t from,
						   hstate_t to,
						   output_letter_t o,
						   output_semiring_elt_t w)
  {
    if (w == output_semiring_elt_t())
      w = algebra::identity_as<output_semiring_elt_value_t>
	::of(this->series().semiring().semiring());

    return op_add_o_edge(this->structure(), this->value(),
			  from, to, o, w);
  }

  template <typename Self, typename T>
  hedge_t
  MetaElement<TransducerBase<Self>, T>::add_i_edge(hstate_t from,
						   hstate_t to,
						   input_letter_t i,
						   output_semiring_elt_t w)
  {
    if (w == output_semiring_elt_t())
      w = algebra::identity_as<output_semiring_elt_value_t>
	::of(this->series().semiring().semiring());

    return op_add_i_edge(this->structure(), this->value(),
			 from, to, i, w);
  }

  template <typename Self, typename T>
  void
  MetaElement<TransducerBase<Self>, T>::
  set_o_final(hstate_t final,
	      output_monoid_elt_value_t o)
  {
    op_set_o_final(this->structure(), this->value(), final, o);
  }

  template <typename Self, typename T>
  void
  MetaElement<TransducerBase<Self>, T>::
  set_o_initial(hstate_t initial,
		output_monoid_elt_value_t o)
  {
    op_set_o_initial(this->structure(), this->value(), initial, o);
  }

} // vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSDUCER_BASE_HXX
