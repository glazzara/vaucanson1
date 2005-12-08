// xml_dump.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_XML_DUMP_HH
# define VCSN_TOOLS_XML_DUMP_HH

/**
 * @file xml_dump.hh
 *
 * Calls a method to display an automaton 'a' in XML format on the stream 'o'.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

# include <iostream>
# include <string>
# include <vaucanson/tools/io.hh>
# include <vaucanson/xml/XML.hh>

namespace vcsn
{
  namespace tools
  {
    template <typename Auto>
    void xml_dump(std::ostream& o, const Auto& a,
		  const std::string& name = "");
  }
}

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/tools/xml_dump.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_TOOLS_XML_DUMP_HH
