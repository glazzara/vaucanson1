// strings.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2006 The Vaucanson Group.
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

#include <vaucanson/config/system.hh>

#if not defined (VCSN_XML_STRINGS_HH) and VCSN_INCLUDE_XML()
# define VCSN_XML_STRINGS_HH

# ifndef VCSN_USE_XML
#  error Vaucanson XML support is disabled.
# endif

# include <string>

# include <xercesc/util/XMLUniDefs.hpp>
# include <xercesc/util/XMLString.hpp>

namespace vcsn
{

  namespace xml
  {

    /// Transcode \a cpp to XML.
    inline
    XMLCh* transcode (const char* ccp);

    /// Transcode \a s to XML.
    inline
    XMLCh* transcode (const std::string& s);

    /// Convert back to a C++ string.
    inline
    std::string xml2str(const XMLCh*);

  } // End of namespace xml.

} // End of namespace vcsn.

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/strings.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_STRINGS_HH && VCSN_INCLUDE_XML()
