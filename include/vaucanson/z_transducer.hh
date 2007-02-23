// z_transducer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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

# include <vaucanson/z_transducer_structures.hh>

# define VCSN_CONTEXT_NAMESPACE namespace z_transducer
# define AUTOMATON_CONTEXT z_automaton

# include <vaucanson/contexts/transducer_functions.thh>

# undef AUTOMATON_CONTEXT
# undef VCSN_CONTEXT_NAMESPACE

#endif // ! VCSN_Z_TRANSDUCER_HH
