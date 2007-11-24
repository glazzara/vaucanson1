// dot_display.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2007 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_DOT_DISPLAY_HXX
# define VCSN_TOOLS_DOT_DISPLAY_HXX

/**
 * @file dot_display.hxx
 *
 * Calls out_display with dot_dump as the function to launch by out_display.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 */

# include <vaucanson/tools/dot_display.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/dot_dump.hh>

# include <ostream>
# include <string>
# include <vaucanson/tools/out_display.hh>

namespace vcsn {

  namespace tools {

    template <class S, class T>
    bool
    dot_display(const Element<S, T>& a,
		const std::string& name,
		const bool bg,
		const char *const argv[])
    {
      return out_display(a.structure(), a.value(),
			 a, name, bg, argv,
			 dot_dump<Element<S, T> >);
    }

  } // End of namespace tools.

} // End of namespace vcsn.

#endif // ! VCSN_TOOLS_DOT_DISPLAY_HXX
