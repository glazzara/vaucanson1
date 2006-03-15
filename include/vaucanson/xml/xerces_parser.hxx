// xerces_parser.hxx: this file is part of the Vaucanson project.
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

# define parser_set_property(prop) \
      if (parser->canSetFeature(XMLUni::prop, true)) \
	parser->setFeature(XMLUni::prop, true);

# define parser_set_value(prop, value) \
	parser->setProperty(XMLUni::prop, value);


namespace vcsn
{
  namespace xml
  {

    static inline std::string get_xsd_path ()
    {
      { // Test the environment variable before anything.
	const char* xsd_env = getenv ("VCSN_XSD_PATH");
	if (xsd_env)
	  return xsd_env;
      }
      static const char* possible_xsds[] =
	{ "vaucanson.xsd", VCSN_XSD_PATH, 0 };
      const char**	 result;
      for (result = possible_xsds; *result; ++result)
      {
	std::ifstream is (*result);
	if (is.good ())
	  break;
      }
      if (*result)
	return *result;
      return "";
    }

    template <class IStream>
    xercesc::DOMDocument*
    xerces_parser::loaddocument(xercesc::DOMBuilder* parser, IStream& is)
    {
      using namespace xercesc;

      parser_set_property(fgDOMValidation);
      parser_set_property(fgDOMNamespaces);
      parser_set_property(fgDOMDatatypeNormalization);
      parser_set_property(fgXercesSchema);
      parser_set_property(fgXercesUseCachedGrammarInParse);
      parser_set_property(fgXercesCacheGrammarFromParse);

      std::string xsd_file = get_xsd_path ();
      if (xsd_file == "")
	FAIL ("Error: XSD file not found.");

      XMLCh* xsd_link =
	STR2XML(("http://vaucanson.lrde.epita.fr " + xsd_file).c_str ());
      parser_set_value(fgXercesSchemaExternalSchemaLocation, xsd_link);

      // fgXercesSchemaExternalNoNamespaceSchemaLocation

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
	DOMImplementationRegistry::getDOMImplementation(STR2XML("LS"));
      DOMBuilder* parser = static_cast<DOMImplementationLS*> (impl)
	->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

      DOMDocument* doc = loaddocument(parser, is);

      DOMNodeList* nodelist;

      nodelist = doc->getElementsByTagName(STR2XML("session"));
      if (! nodelist->getLength())
	nodelist = doc->getElementsByTagName(STR2XML("automaton"));
      if (! nodelist->getLength())
	nodelist = doc->getElementsByTagName(STR2XML("transducer"));
      if (! nodelist->getLength())
	FAIL("Cannot find any appropriate root.");

      DOMElement* node = static_cast<DOMElement*>(nodelist->item(0));
      return node;
    }

  } // xml

} // vcsn

# undef parser_set_property
# undef parser_set_value


#endif // ! VCSN_XML_XERCES_PARSER_HXX
