// vcsn_r.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_R_HH_
# define VCSN_R_HH_

# define VCSN_CONTEXT r_automaton
# define VCSN_CONTEXT_NAMESPACE namespace VCSN_CONTEXT

# include <vaucanson/contexts/char_letter.thh>
# include <vaucanson/contexts/dynamic_alphabet.thh>
# include <vaucanson/contexts/free_monoid.thh>
# include <vaucanson/contexts/r_semiring.thh>
# include <vaucanson/contexts/generic_series.thh>
# include <vaucanson/contexts/generic_automaton_impl.thh>
# include <vaucanson/contexts/automaton.thh>

# undef VCSN_CONTEXT_NAMESPACE

#endif // !VCSN_R_HH_ //
