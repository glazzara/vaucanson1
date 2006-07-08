// delta_kind.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_DELTA_KIND_HH
# define VCSN_AUTOMATA_CONCEPT_DELTA_KIND_HH

namespace vcsn {

  /// These are helpers for @c delta functions: transition or state
  /// oriented delta are chosen according to them.

  namespace delta_kind {

    /// Not for public use.
    struct kind_transitions_ {};
    struct kind_states_ {};

    template <typename T>
    struct kind;

    template <>
    struct kind<kind_transitions_> {};

    template <>
    struct kind<kind_states_> {};

    /// Use them.
    typedef kind<kind_transitions_> transitions;
    typedef kind<kind_states_> states;
  } // delta_kind

} // vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_DELTA_KIND_HH
