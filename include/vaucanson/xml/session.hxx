// session.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_SESSION_HXX
# define VCSN_XML_SESSION_HXX

/**
 * @file session.hxx
 *
 * XML session management.
 *
 *
 * @see vcsn::xml::XML, vcsn::xml::xerces_parser
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


namespace vcsn
{
  namespace xml
  {

    xml_session::xml_session()
    {
      using namespace xercesc;

      XMLPlatformUtils::Initialize();
      impl = DOMImplementationRegistry::getDOMImplementation(transcode("LS"));
      doc = impl->createDocument(transcode("http://vaucanson.lrde.epita.fr"),
				 transcode("session"), 0);
      root = doc->getDocumentElement();
    }


    xml_session::~xml_session()
    {
      xercesc::XMLPlatformUtils::Terminate();
    }

  } // ! xml

  template<typename S, typename T>
  xml::xml_session&
  op_rout(const S& structure,
	  xml::xml_session& s,
	  const T& value)
  {
    xercesc::XMLPlatformUtils::Initialize();

    Element<S, T> a(structure, value);
    xml::xml_converter<Element<S, T> > x;
    x.create_document(a);
    xercesc::DOMNode* node =
      s.doc->importNode(static_cast<xercesc::DOMNode*>(x.root_get()), true);

    s.root->appendChild(node);

    return s;
  }


  template <class S, class T>
  xml::xml_session& op_rin(S& structure,
			   xml::xml_session& s,
			   T& value)
  {
    using namespace xercesc;
    using namespace vcsn;
    using namespace vcsn::xml;

    XMLPlatformUtils::Initialize();
    Element<S, T> a(structure, value);

    // Clear the automaton content.
    for (typename Element<S, T>::state_iterator is = a.states().begin();
	 is != a.states().end(); ++is)
      a.del_state(*is);

    if (! s.root->getFirstChild())
      FAIL("No more automaton in session");
    for (DOMNode* n = s.root->getFirstChild(); n; n = n->getNextSibling())
      if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	{
	  DOMElement* elt = static_cast<DOMElement*>(n);

	  typedef Element<S, T> automaton_t;
	  typedef Node<automaton_t> node_t;
	  Factory<node_t, std::string> f;
	  register_all_factory(f, automaton_t);
	  typename node_t::map_t str2state;

	  node_t* node = factory_create(f, xml2str(n->getNodeName()));
	  node->process(elt, a, str2state, f);
	  s.root->removeChild(n);
	}
    op_assign(structure.self(), value, a.value());

    return s;
  }


  template <class IStream>
  IStream& operator >> (IStream& is, xml::xml_session& s)
  {
    using namespace xercesc;

    xercesc::XMLPlatformUtils::Initialize();
    DOMNode* node = xml::xerces_parser::stream_parser(is);

    for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
      if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	(s.root)->appendChild(s.doc->importNode(n, true));

    return is;
  }


  template <class OStream>
  OStream& operator << (OStream& out, const xml::xml_session& s)
  {
    xercesc::XMLPlatformUtils::Initialize();
    xml::tools::print_document((xercesc::DOMImplementationLS*) s.impl, s.root, out);

    return out;
  }


} // !vcsn

#endif // ! VCSN_XML_SESSION_HXX
