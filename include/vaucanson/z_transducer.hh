// z_transducer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_Z_TRANSDUCER_HH
# define VCSN_Z_TRANSDUCER_HH

# include <vaucanson/z_automaton.hh>
# include <vaucanson/boolean_automaton.hh>

# define VCSN_CONTEXT_NAMESPACE z_transducer
# define AUTOMATON_CONTEXT z_automaton

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
