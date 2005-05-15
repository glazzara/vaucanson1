// xerces_parser.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
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

# define parser_set_property(prop) \
      if (parser->canSetFeature(XMLUni::prop, true)) \
	parser->setFeature(XMLUni::prop, true);

# define parser_set_value(prop, value) \
	parser->setProperty(XMLUni::prop, value);


namespace vcsn
{
  namespace xml
  {

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

      XMLCh* xsd_link =
	STR2XML("http://vaucanson.lrde.epita.fr vaucanson.xsd");
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

      /// FIXME: Handle sessions here.
      nodelist = doc->
	getElementsByTagNameNS(STR2XML("http://vaucanson.lrde.epita.fr"),
			       STR2XML("automaton"));
      if (! nodelist->getLength())
	{
	  nodelist = doc->
	    getElementsByTagNameNS(STR2XML("http://vaucanson.lrde.epita.fr"),
				   STR2XML("transducer"));
	  if (! nodelist->getLength())
	    FAIL("Cannot find any automaton / transducer root.");
	}
      DOMElement* node = static_cast<DOMElement*>(nodelist->item(0));
      return node;
    }

  } // xml

} // vcsn

# undef parser_set_property
# undef parser_set_value


#endif // VCSN_XML_XERCES_PARSER_HXX
