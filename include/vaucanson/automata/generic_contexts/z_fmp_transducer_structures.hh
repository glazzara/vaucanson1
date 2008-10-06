// z_fmp_transducer_structures.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

# include GRAPH_CONTEXT_HEADER_(z_automaton_structures.hh)

# define AUTOMATON_CONTEXT z_automaton
# define VCSN_CONTEXT_NAMESPACE namespace z_fmp_transducer

namespace vcsn
{
  namespace VCSN_GRAPH_IMPL
  {
    VCSN_CONTEXT_NAMESPACE
    {

      typedef AUTOMATON_CONTEXT::monoid_elt_t	first_monoid_elt_t;
      typedef first_monoid_elt_t::set_t		first_monoid_t;
      typedef first_monoid_elt_t::value_t	first_monoid_elt_value_t;
      typedef first_monoid_t::alphabet_t	first_alphabet_t;

      typedef AUTOMATON_CONTEXT::monoid_elt_t	second_monoid_elt_t;
      typedef second_monoid_elt_t::set_t	second_monoid_t;
      typedef second_monoid_elt_t::value_t	second_monoid_elt_value_t;
      typedef second_monoid_t::alphabet_t	second_alphabet_t;

    } // End of namespace VCSN_CONTEXT_NAMESPACE.
  } // End of namespace VCSN_GRAPH_IMPL
} // End of namespace vcsn

# include <vaucanson/contexts/free_monoid_product.thh>
# include <vaucanson/contexts/z_semiring.thh>
# include <vaucanson/contexts/polynom_series.thh>
# include <vaucanson/contexts/generic_automaton_impl.thh>
# include <vaucanson/contexts/automaton.thh>
# include <vaucanson/contexts/fmp_transducer.thh>

# include <vaucanson/contexts/fmp_transducer_maker.thh>

# undef AUTOMATON_CONTEXT
# undef VCSN_CONTEXT_NAMESPACE

