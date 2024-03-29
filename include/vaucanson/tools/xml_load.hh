// xml_load.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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

#ifndef VCSN_TOOLS_XML_LOAD_HH
# define VCSN_TOOLS_XML_LOAD_HH

/**
 * @file xml_load.hh
 *
 * Calls a method to fill the automaton 'a' by reading on 'i'.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

# include <iostream>
# include <vaucanson/tools/io.hh>
# include <vaucanson/xml/XML.hh>

namespace vcsn
{
  namespace tools
  {
    template <typename Auto, class IStream>
    void xml_load(IStream& i, Auto& a);

  }
}

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/tools/xml_load.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_TOOLS_XML_LOAD_HH
