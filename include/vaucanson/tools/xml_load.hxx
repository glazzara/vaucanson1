// xml_load.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_TOOLS_XML_LOAD_HXX
# define VCSN_TOOLS_XML_LOAD_HXX

/**
 * @file xml_load.hxx
 *
 * Calls a method to fill the automaton 'a' by reading on 'i'.
 *
 * @author Florent Terrones <florent.terrones@lrde.epita.fr>
 */

namespace vcsn {

  namespace tools {

    template <typename Auto, class IStream>
    void xml_load(IStream& i, Auto& a)
    {
      i >> automaton_loader(a, io::string_out(), xml::XML());
    }

  } // tools

} // vcsn

#endif // ! VCSN_TOOLS_XML_LOAD_HXX
