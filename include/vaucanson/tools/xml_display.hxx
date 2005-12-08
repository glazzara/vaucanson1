// xml_display.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_XML_DISPLAY_HXX
# define VCSN_TOOLS_XML_DISPLAY_HXX

/**
 * @file xml_display.hxx
 *
 * Calls out_display with xml_dump as the function to launch by out_display.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

# include <ostream>
# include <string>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/xml_dump.hh>
# include <vaucanson/tools/out_display.hh>

namespace vcsn {

  namespace tools {

    template <class S, class T>
    bool
    xml_display(const Element<S, T>& a,
		const std::string& name,
		const bool bg,
		char *const argv[])
    {
      return out_display(a.structure(), a.value(),
			 a, name, bg, argv,
			 xml_dump<Element<S, T> >);
    }

  } // End of namespace tools.

} // End of namespace vcsn.

#endif // ! VCSN_TOOLS_XML_DISPLAY_HXX
