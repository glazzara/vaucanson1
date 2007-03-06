// usual_escaped_characters.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_USUAL_ESCAPED_CHARACTERS_HH
# define VCSN_MISC_USUAL_ESCAPED_CHARACTERS_HH

/**
 * @file usual_escaped_characters.hh
 *
 * Declarations of the @a usual_escaped_characters function.
 * @see vcsn::misc::usual_escaped_characters ().
 * @author Loic Fosse <loic.fosse@lrde.epita.fr>
 */

# include <set>

namespace vcsn {

  namespace misc {

    /// Return a set filled with ".+* ()\ 10[]".
    std::set<char> usual_escaped_characters ();

  } // End of namespace misc.

} // End of namespace vcsn.

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/usual_escaped_characters.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_MISC_USUAL_ESCAPED_CHARACTERS_HH
