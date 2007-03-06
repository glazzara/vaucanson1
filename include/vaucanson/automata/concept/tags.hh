// tags.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TAGS_HH
# define VCSN_AUTOMATA_CONCEPT_TAGS_HH


namespace vcsn
{
  struct NoTag
  {};

} // vcsn

static inline bool operator==(const vcsn::NoTag& a, const vcsn::NoTag& b);
static inline bool operator!=(const vcsn::NoTag& a, const vcsn::NoTag& b);


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/concept/tags.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_TAGS_HH
