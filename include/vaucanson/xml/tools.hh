// tools.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_TOOLS_HH
# define VCSN_XML_TOOLS_HH

/**
 * @file tools.hh
 *
 * Tools to help loading automata.
 *
 * @see vcsn::xml::*Handler
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <string>

# include <xercesc/sax2/Attributes.hpp>
# include <xercesc/util/XMLString.hpp>
# include <xercesc/dom/DOM.hpp>

namespace vcsn
{
  namespace xml
  {
    namespace tools
    {
      /**
       * Getters
       */
      bool
      has_attribute (const xercesc::Attributes& attrs,
		     const char* key,
		     const XMLCh* const uri = 0);

      bool
      has_attribute (const xercesc::Attributes& attrs,
		     const XMLCh* xkey,
		     const XMLCh* const uri = 0);

      const XMLCh*
      get_attribute (const xercesc::Attributes& attrs,
		     const char* key,
		     const XMLCh* uri = 0);

      const XMLCh*
      get_attribute (const xercesc::Attributes& attrs,
		     const XMLCh* xkey,
		     const XMLCh* uri = 0);

      /**
       * Setters
       */
      void
      set_attribute (xercesc::DOMElement* e,
		     const std::string& k, const std::string& v);
      /**
       * XML Dom builders
       */
      xercesc::DOMElement*
      create_element(xercesc::DOMDocument* doc,
		     const std::string& e);
    } // !tools
  } // !xml
} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/tools.hxx>
# endif // VCSN_USE_INTERFACE_ONLY || !VCSN_USE_LIB

#endif // !VCSN_XML_TOOLS_HH
