// handlers_base.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_HANDLERS_BASE_HH
# define VCSN_XML_HANDLERS_BASE_HH

/**
 * @file handlers_base.hxx
 *
 * Handler classes for XML loading.
 *
 * @see vcsn::xml::parser
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <map>
# include <string>

# include <xercesc/sax2/SAX2XMLReader.hpp>
# include <xercesc/sax2/XMLReaderFactory.hpp>
# include <xercesc/sax2/DefaultHandler.hpp>
# include <xercesc/sax2/Attributes.hpp>

# include <xercesc/sax/SAXException.hpp>
# include <xercesc/util/XMLString.hpp>

# include <vaucanson/xml/xmleq.hh>
# include <vaucanson/xml/strings.hh>

namespace vcsn
{
  namespace xml
  {
    /*
     * ErrHandler class, error handler.
     */
    class ErrHandler : public xercesc::DefaultHandler
    {
      public:
	ErrHandler () : DefaultHandler() {}

	void
	warning (const xercesc::SAXParseException& exc);
	// Receive notification of a warning.
	void
	error (const xercesc::SAXParseException& exc);
	// Receive notification of a recoverable error.
	void
	fatalError (const xercesc::SAXParseException& exc);
	// Receive notification of a non-recoverable error.
	void
	resetErrors () {}
	// Reset the Error handler object on its reuse.
    };

    namespace error
    {
      void token(const XMLCh* const localname);
      void attrs(const XMLCh* const localname,
		 const std::string& name,
		 const std::string& value);
      void missattrs(const XMLCh* const localname,
		     const std::string& name);
      void notletter(const std::string&);
    } // !error
    /*
     * Handler class
     */
    class Handler : public xercesc::DefaultHandler
    {
      public:
	Handler (xercesc::SAX2XMLReader* parser,
		 Handler& root);
	Handler (xercesc::SAX2XMLReader* parser,
		 xercesc::DefaultHandler& root,
		 XMLEq& eq);

	void
	startElement (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	endElement (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);

	virtual void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs) = 0;
	virtual void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname) = 0;

	XMLEq& eq() { return eq_; };
# ifdef DEBUG
	static int	indent_;
# endif
      protected:
	// Required to enable a change of the Handler while parsing.
	xercesc::SAX2XMLReader*		parser_;
	xercesc::DefaultHandler&	root_;

	XMLEq&	eq_;
    };
# ifdef DEBUG
    int Handler::indent_ = 0;
# endif

    /**
     * UnsupHandler class, Handler dedicated to "eat" all part
     * of the format Vaucanson still not supports.
     */
    class UnsupHandler : public Handler
    {
      public:
	UnsupHandler(xercesc::SAX2XMLReader* parser,
		     Handler& root);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	int				depth_;
    };
  } // !xml
} // !vcsn

# if ! defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/handlers_base.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_XML_HANDLERS_BASE_HH
