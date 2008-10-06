// int_int_boolean_automaton_structures.hh: this file is part of the
// Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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

/*
 * CPP guard should not be inserted here as
 * VCSN_GRAPH_IMPL could be changed.
 */

# define VCSN_CONTEXT_NAMESPACE namespace int_int_boolean_automaton

# include <vaucanson/contexts/int_int_letter.thh>
# include <vaucanson/contexts/dynamic_alphabet.thh>
# include <vaucanson/contexts/free_monoid.thh>
# include <vaucanson/contexts/boolean_semiring.thh>
# include <vaucanson/contexts/generic_series.thh>
# include <vaucanson/contexts/generic_automaton_impl.thh>
# include <vaucanson/contexts/automaton.thh>

namespace vcsn
{
  namespace VCSN_GRAPH_IMPL
  {
    VCSN_CONTEXT_NAMESPACE
    {
      AUTOMATON_FREEMONOID_TYPES_EXACT(automaton_t);

      typedef algebra::alphabet_traits<alphabet_t::set_t,
	      alphabet_t::value_t>::first_projection_t
	      first_projection_alphabet_t;
      typedef algebra::alphabet_traits<alphabet_t::set_t,
	      alphabet_t::value_t>::second_projection_t
	      second_projection_alphabet_t;

      typedef algebra::word_traits<monoid_elt_t::set_t,
	      monoid_elt_t::value_t>::first_monoid_t first_monoid_t;
      typedef algebra::word_traits<monoid_elt_t::set_t,
	      monoid_elt_t::value_t>::second_monoid_t second_monoid_t;

      typedef algebra::word_traits<monoid_elt_t::set_t,
	      monoid_elt_t::value_t>::first_projection_t
	      first_projection_word_t;
      typedef algebra::word_traits<monoid_elt_t::set_t,
	      monoid_elt_t::value_t>::second_projection_t
	      second_projection_word_t;
    }
  }
}

# include <vaucanson/contexts/automaton_maker.thh>

# undef VCSN_CONTEXT_NAMESPACE

