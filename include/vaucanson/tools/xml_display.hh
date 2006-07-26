// xml_display.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_TOOLS_XML_DISPLAY_HH
# define VCSN_TOOLS_XML_DISPLAY_HH

/**
 * @file xml_display.hh
 *
 * Calls out_display with xml_dump as the function to launch by out_display.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

# include <vaucanson/design_pattern/element.hh>

# include <string>

namespace vcsn
{
  namespace tools
  {
    static char *const xml_argv[] = { "./VGI", 0 };

    template <class S, class T>
    bool
    xml_display(const Element<S, T>& a,
		const std::string& name,
		const bool bg = false,
		char *const argv[] = xml_argv);
  }
}

# ifndef VCSN_USE_INTERFACE_ONLY
# include <vaucanson/tools/xml_display.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_TOOLS_XML_DISPLAY_HH
