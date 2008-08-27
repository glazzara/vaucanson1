// parsers.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_XML_PARSERS_HXX
# define VCSN_XML_PARSERS_HXX

# include <fstream>
# include <xercesc/sax2/XMLReaderFactory.hpp>

# include <vaucanson/xml/ios.hh>

namespace vcsn
{
  namespace xml
  {
    /*
     * Parser class.
     */
    std::string
    Parser::get_xsd_path ()
    {
      const char*	path = getenv("VCSN_DATA_PATH");
      const char*	xsd = "vaucanson.xsd";

      if (path == 0)
	path = VCSN_DATA_PATH;
      std::string file = std::string (path) + "/" + xsd;

      if (std::ifstream (file.c_str()).good())
	return file;
      FAIL (std::string ("Error: cannot open `") + path + "/" + xsd + "'.\n"
	    "Please set VCSN_DATA_PATH to the Vaucanson data directory,\n"
	    "containing `" + xsd + "'.");
      return "";
    }

    Parser::Parser (bool check)
      : parser_(0), eq_()
    {
      using namespace xercesc;
      parser_ = XMLReaderFactory::createXMLReader();

      if (check)
      {
	parser_->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
	parser_->setFeature(XMLUni::fgSAX2CoreValidation, true);
	parser_->setFeature(XMLUni::fgXercesSchema, true);
	 parser_->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
	parser_->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);
	parser_->setFeature(XMLUni::fgXercesUseCachedGrammarInParse, true);
	parser_->setFeature(XMLUni::fgXercesCacheGrammarFromParse, true);
	 XMLCh* xsd = transcode(VCSN_XMLNS " " + get_xsd_path());
	 parser_->setProperty(XMLUni::fgXercesSchemaExternalSchemaLocation, xsd);
	 XMLString::release(&xsd);
      }

      err_handler_ = new ErrHandler();
      parser_->setErrorHandler(err_handler_);
    }

    Parser::~Parser ()
    {
      delete parser_;
      delete err_handler_;
    }

    /*
     * AutParser class.
     */
    template <typename Auto>
    AutParser<Auto>::AutParser (Auto& a, bool check)
      : Parser(check), a_(a)
    {
      doc_handler_ = new DocHandler<Auto>(parser_, *err_handler_, a_, eq_);
      parser_->setContentHandler(doc_handler_);
    }

    template <typename Auto>
    AutParser<Auto>::~AutParser ()
    {
      delete doc_handler_;
    }

    template <typename Auto>
    void
    AutParser<Auto>::parse (std::istream& in)
    {
      CxxInputSource is(&in);
      parser_->parse(is);
    }
  } // !xml
} // !vcsn

#endif // !VCSN_XML_PARSERS_HXX
