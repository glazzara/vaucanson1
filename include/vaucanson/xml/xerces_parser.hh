// xerces_parser.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XERCES_PARSER_HH
# define VCSN_XML_XERCES_PARSER_HH
/**
 * @file xerces_parser.hh
 *
 * Xerces-C++ parser.
 *
 * @see vcsn::xml::XML
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


# include <iostream>
# include <cstdlib>

# include <xercesc/dom/DOM.hpp>
# include <xercesc/framework/Wrapper4InputSource.hpp>

# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/xml/ios.hh>
# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/error_handler.hh>


namespace vcsn
{
  namespace xml
  {

    struct xerces_parser
    {
      /**
       * @brief Parse XML document from stream.
       *
       * @param IStream	Type of the input stream.
       *
       * @return	DOMElement pointer to root node.
       * @arg is	Input stream.
       */
      template <class IStream>
      static
      xercesc::DOMElement* stream_parser(IStream& is);

    private:
      template <class IStream>
      static
      xercesc::DOMDocument* loaddocument(xercesc::DOMBuilder* parser,
					 IStream& is);
    };
  } // xml

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xerces_parser.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_XML_XERCES_PARSER_HH
