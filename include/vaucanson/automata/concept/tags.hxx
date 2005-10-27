// tags.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TAGS_HXX
# define VCSN_AUTOMATA_CONCEPT_TAGS_HXX

# include <vaucanson/automata/concept/tags.hh>

static inline bool operator==(const vcsn::NoTag&, const vcsn::NoTag&)
{ return true; }
static inline bool operator!=(const vcsn::NoTag&, const vcsn::NoTag&)
{ return false; }

#endif // ! VCSN_AUTOMATA_CONCEPT_TAGS_HXX
