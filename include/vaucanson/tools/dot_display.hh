// dot_display.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_TOOLS_DOT_DISPLAY_HH
# define VCSN_TOOLS_DOT_DISPLAY_HH

/**
 * @file dot_display.hxx
 *
 * Calls out_display with dot_dump as the function to launch by out_display.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 */

# include <vaucanson/design_pattern/element.hh>

# include <string>

namespace vcsn
{
  namespace tools
  {
    static char *const dotty_argv[] = { "dotty", "-", 0 };

    template <class S, class T>
    bool
    dot_display(const Element<S, T>& a,
		const std::string& name,
		const bool bg = false,
		char *const argv[] = dotty_argv);

  }
}

# ifndef VCSN_USE_INTERFACE_ONLY
# include <vaucanson/tools/dot_display.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_TOOLS_DOT_DISPLAY_HH
