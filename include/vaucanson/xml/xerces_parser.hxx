// xerces_parser.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_XML_XERCES_PARSER_HXX
# define VCSN_XML_XERCES_PARSER_HXX
/**
 * @file xerces_parser.hxx
 *
 * Xerces-C++ parser.
 *
 * @see vcsn::xml::XML
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

# include <fstream>

namespace vcsn
{
  namespace xml
  {

    static inline std::string get_xsd_path ()
    {
      // Test the environment variable before anything.
      const char* path = getenv ("VCSN_DATA_PATH");
      const char* xsd = "vaucanson.xsd";
      if (path == 0)
	path = VCSN_DATA_PATH;
      std::string file = std::string (path) + "/" + xsd;
      if (std::ifstream (file.c_str ()).good ())
	return file;
      FAIL (std::string ("Error: cannot open `") + path + "/" + xsd "'.\n"
	    "Please set VCSN_DATA_PATH to the Vaucanson data directory,\n"
	    "containing `" + xsd + "'.");
      return "";
    }

    template <class IStream>
    xercesc::DOMDocument*
    xerces_parser::loaddocument(xercesc::DOMBuilder* parser, IStream& is)
    {
      using namespace xercesc;

# define PARSER_SET_PROPERTY(prop)			\
      if (parser->canSetFeature(XMLUni::prop, true))	\
	parser->setFeature(XMLUni::prop, true);

      PARSER_SET_PROPERTY(fgDOMValidation);
      PARSER_SET_PROPERTY(fgDOMNamespaces);
      PARSER_SET_PROPERTY(fgDOMDatatypeNormalization);
      PARSER_SET_PROPERTY(fgXercesSchema);
      PARSER_SET_PROPERTY(fgXercesUseCachedGrammarInParse);
      PARSER_SET_PROPERTY(fgXercesCacheGrammarFromParse);

# undef PARSER_SET_PROPERTY


# define PARSER_SET_VALUE(prop, value) \
	parser->setProperty(XMLUni::prop, value);

      PARSER_SET_VALUE(fgXercesSchemaExternalSchemaLocation,
		       transcode("http://vaucanson.lrde.epita.fr " + get_xsd_path ()));

# undef PARSER_SET_VALUE


      myDOMErrorHandler* err = new myDOMErrorHandler();
      parser->setErrorHandler(err);

      DOMDocument* doc;
      try
	{
	  CxxInputSource	i (&is);
	  Wrapper4InputSource	w (&i, false);
	  doc = parser->parse(w);
	}
      catch (const XMLException& e)
	{
	  FAIL(std::string ("XML exception: ") + xml2str(e.getMessage()));
	}
      catch (const DOMException& e)
	{
	  FAIL(std::string ("DOM exception: ") + xml2str(e.msg));
	}
      catch (...)
	{
	  FAIL("Unknown exception caught.");
	}

      if (err->has_error())
	FAIL(err->get_msg());
      // parser->release();
      delete err;
      return doc;
    }

    template <class IStream>
    xercesc::DOMElement*
    xerces_parser::stream_parser(IStream& is)
    {
      using namespace xercesc;

      DOMImplementation* impl =
	DOMImplementationRegistry::getDOMImplementation(transcode("LS"));
      DOMBuilder* parser = static_cast<DOMImplementationLS*> (impl)
	->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

      DOMDocument* doc = loaddocument(parser, is);

      DOMNodeList* nodelist;

      nodelist = doc->getElementsByTagName(transcode("session"));
      if (! nodelist->getLength())
	nodelist = doc->getElementsByTagName(transcode("automaton"));
      if (! nodelist->getLength())
	nodelist = doc->getElementsByTagName(transcode("transducer"));
      if (! nodelist->getLength())
	FAIL("Cannot find any appropriate root.");

      DOMElement* node = static_cast<DOMElement*>(nodelist->item(0));
      return node;
    }

  } // xml

} // vcsn

#endif // ! VCSN_XML_XERCES_PARSER_HXX
