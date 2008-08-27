// handlers_base.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_HANDLERS_BASE_HXX
# define VCSN_XML_HANDLERS_BASE_HXX

# include <xercesc/util/XMLString.hpp>

# include <vaucanson/xml/tools.hh>

namespace vcsn
{
  namespace xml
  {
    /*
     * ErrHandler
     */
    void
    ErrHandler::warning (const xercesc::SAXParseException& exc)
    {
      char* msg = xercesc::XMLString::transcode(exc.getMessage());
      std::cerr << "Warning: " << msg << std::endl;
      xercesc::XMLString::release(&msg);
    }

    void
    ErrHandler::error (const xercesc::SAXParseException& exc)
    {
      char* msg = xercesc::XMLString::transcode(exc.getMessage());
      std::cerr << "Error: " << msg << std::endl;
      xercesc::XMLString::release(&msg);
    }

    void
    ErrHandler::fatalError (const xercesc::SAXParseException& exc)
    {
      char* msg = xercesc::XMLString::transcode(exc.getMessage());
      std::cerr << "Fatal error: " << msg << std::endl;
      xercesc::XMLString::release(&msg);
      throw exc;
    }

    namespace error
    {
      void token(const XMLCh* const localname)
      {
	std::cerr << "Unexpected token: " << xmlstr(localname) << std::endl;
	assertion(false);
      }
      void attrs(const XMLCh* const localname,
		 const std::string& name,
		 const std::string& value)
      {
	std::cerr << "Unexpected value of `" << name << "' (" << value << ") in token: " << xmlstr(localname) << std::endl;
	assertion(false);
      }

      void missattrs(const XMLCh* const localname,
		     const std::string& name)
      {
	std::cerr << "Missing attribute `" << name << " in token: " << xmlstr(localname) << std::endl;
	assertion(false);
      }
    } // !error
    /*
     * Handler
     */
    Handler::Handler (xercesc::SAX2XMLReader* parser,
		      xercesc::DefaultHandler& root,
		      XMLEq& eq)
      : DefaultHandler(),
	parser_(parser),
	root_(root),
	eq_(eq)
    {
    }

    Handler::Handler (xercesc::SAX2XMLReader* parser,
		      Handler& root)
      : DefaultHandler(),
	parser_(parser),
	root_(root),
	eq_(root.eq_)
    {
    }

    void
    Handler::startElement (const XMLCh* const uri,
				const XMLCh* const localname,
				const XMLCh* const qname,
				const xercesc::Attributes& attrs)
    {
# ifdef DEBUG
      indent_++;
      std::cout << std::string(2 * indent_, ' ') << "<" << xmlstr(localname) << ">" << std::endl;
# endif
      start(uri, localname, qname, attrs);
    }

    void
    Handler::endElement (const XMLCh* const uri,
			      const XMLCh* const localname,
			      const XMLCh* const qname)
    {
      end(uri, localname, qname);
# ifdef DEBUG
      std::cout << std::string(2 * indent_, ' ') << "</" << xmlstr(localname) << ">" << std::endl;
      indent_--;
# endif
    }
    /*
     * UnsupHandler
     */
    UnsupHandler::UnsupHandler (xercesc::SAX2XMLReader* parser,
				Handler& root)
      : Handler(parser, root),
	depth_(1)
    {
    }

    void
    UnsupHandler::start (const XMLCh* const,
				const XMLCh* const,
				const XMLCh* const,
				const xercesc::Attributes&)
    {
      depth_++;
    }

    void
    UnsupHandler::end (const XMLCh* const,
# ifdef DEBUG
			      const XMLCh* const localname,
# else
			      const XMLCh* const,
# endif
			      const XMLCh* const)
    {
# ifdef DEBUG
      std::cerr << std::string((indent_ + 1) * 2, ' ') << "unsupported token: " << xmlstr(localname) << std::endl;
# endif
      depth_--;
      if (depth_ <= 0)
      {
	parser_->setContentHandler(&root_);
	depth_ = 1;
      }
    }
  } // !xml
} // !vcsn

#endif // !VCSN_XML_HANDLERS_BASE_HXX
