// tools.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_XML_TOOLS_HXX
# define VCSN_XML_TOOLS_HXX

# include <vaucanson/xml/strings.hh>

namespace vcsn
{
  namespace xml
  {
    namespace tools
    {
      /**
       * Getters
       */

      inline
      bool
      has_attribute (const xercesc::Attributes& attrs,
		     const char* key,
		     const XMLCh* const uri)
      {
	return (get_attribute(attrs, key, uri) != 0);
      }

      inline
      const XMLCh*
      get_attribute (const xercesc::Attributes& attrs,
		     const char* key,
		     const XMLCh* const uri)
      {
	XMLCh* xkey = transcode(key);
	const XMLCh* tmp = attrs.getValue(uri, xkey);
	xercesc::XMLString::release(&xkey);
	return tmp;
      }

      /**
       * Setters
       */
      void
      set_attribute (xercesc::DOMElement* e,
		     const std::string& k, const std::string& v)
      {
	if (v != "")
	  e->setAttribute (transcode(k), transcode(v));
      }
      /**
       * XML Dom builders
       */
      xercesc::DOMElement*
      create_element(xercesc::DOMDocument* doc,
		     const std::string& e)
      {
	return doc->createElement(transcode(e));
      }
    } // !tools
  } // !xml
} // !vcsn

#endif // !VCSN_XML_TOOLS_HXX
