// vcsn_fmp_tdc.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VCSN_FMP_TRANSDUCER_STRUCTURES_HH
# define VCSN_FMP_TRANSDUCER_STRUCTURES_HH

# include <vaucanson/boolean_automaton_structures.hh>

# define AUTOMATON_CONTEXT boolean_automaton
# define VCSN_CONTEXT_NAMESPACE namespace fmp_transducer

namespace vcsn
{
  VCSN_CONTEXT_NAMESPACE
  {
    typedef AUTOMATON_CONTEXT::monoid_elt_t	first_monoid_elt_t;
    typedef first_monoid_elt_t::set_t		first_monoid_t;
    typedef first_monoid_elt_t::value_t		first_monoid_elt_value_t;
    typedef first_monoid_t::alphabet_t		first_alphabet_t;

    typedef AUTOMATON_CONTEXT::monoid_elt_t	second_monoid_elt_t;
    typedef second_monoid_elt_t::set_t		second_monoid_t;
    typedef second_monoid_elt_t::value_t	second_monoid_elt_value_t;
    typedef second_monoid_t::alphabet_t		second_alphabet_t;
  } // End of namespace VCSN_CONTEXT_NAMESPACE.
} // End of namespace vcsn

# include <vaucanson/contexts/free_monoid_product.thh>
# include <vaucanson/contexts/boolean_semiring.thh>
# include <vaucanson/contexts/polynom_series.thh>
# include <vaucanson/contexts/generic_automaton_impl.thh>
# include <vaucanson/contexts/automaton.thh>

# undef AUTOMATON_CONTEXT
# undef VCSN_CONTEXT_NAMESPACE

#endif // !VCSN_FMP_TRANSDUCER_STRUCTURES_HH
