// strings.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_XML_STRINGS_HXX
# define VCSN_XML_STRINGS_HXX

# include <vaucanson/xml/strings.hh>

# include <vaucanson/misc/contract.hh>

namespace vcsn
{
  namespace xml
  {

    /*----------------.
    | Converter tools |
    `----------------*/

    // Transcode \a cpp to XML.
    inline
    XMLCh*
    transcode (const char* ccp)
    {
      return xercesc::XMLString::transcode(ccp);
    }

    // Transcode \a s to XML.
    inline
    XMLCh*
    transcode (const std::string& s)
    {
      return transcode (s.c_str());
    }


    inline
    std::string
    xml2str(const XMLCh* xmlstr)
    {
      assertion(xmlstr != 0);

      char* cstr = xercesc::XMLString::transcode(xmlstr);
      assertion(cstr != 0);

      std::string ret (cstr);
      xercesc::XMLString::release(&cstr);

      return ret;
    }

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_STRINGS_HXX
