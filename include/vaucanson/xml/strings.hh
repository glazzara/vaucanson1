// strings.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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

#ifndef VCSN_XML_STRINGS_HH
# define VCSN_XML_STRINGS_HH

# include <string>

# include <xercesc/util/XMLUniDefs.hpp>
# include <xercesc/util/XMLString.hpp>

namespace vcsn
{

  namespace xml
  {

    /// Transcode @a cpp to XML.
    inline
    XMLCh* transcode (const char* ccp);

    /// Transcode @a s to XML.
    inline
    XMLCh* transcode (const std::string& s);

    /// Convert back to a C++ string.
    inline
    std::string xmlstr(const XMLCh*);

  } // End of namespace xml.

} // End of namespace vcsn.

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/strings.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_STRINGS_HH
