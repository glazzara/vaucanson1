// usual_escaped_characters.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_USUAL_ESCAPED_CHARACTERS_HXX
# define VCSN_MISC_USUAL_ESCAPED_CHARACTERS_HXX

# include <vaucanson/misc/usual_escaped_characters.hh>

namespace vcsn {
  namespace misc {

    inline
    std::set<char>
    usual_escaped_characters ()
    {
      std::set<char> result;
      result.insert ('.');
      result.insert ('+');
      result.insert ('*');
      result.insert ('(');
      result.insert (')');
      result.insert ('\\');
      result.insert (' ');
      result.insert ('1');
      result.insert ('0');
      result.insert ('[');
      result.insert (']');
      return result;
    }

  } // misc
} // vcsn

#endif // ! VCSN_MISC_USUAL_ESCAPED_CHARACTERS_HXX
