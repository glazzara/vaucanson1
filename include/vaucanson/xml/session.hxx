// session.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_XML_SESSION_HXX
# define VCSN_XML_SESSION_HXX

# include <vaucanson/xml/session.hh>

# include <vaucanson/xml/errors.hh>

# include <string>

namespace vcsn
{

  namespace xml
  {

    inline
    XmlSession::XmlSession() : roots_()
    {
      DOMImplementation* impl =
	xercesc::DOMImplementationRegistry::getDOMImplementation(str_LS);

      parser_ = ((DOMImplementationLS*)impl)
	->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

      if (parser_->canSetFeature(XMLUni::fgDOMValidation, true))
	parser_->setFeature(XMLUni::fgDOMValidation, true);
      if (parser_->canSetFeature(XMLUni::fgDOMNamespaces, true))
	parser_->setFeature(XMLUni::fgDOMNamespaces, true);
      if (parser_->canSetFeature(XMLUni::fgDOMDatatypeNormalization, true))
	parser_->setFeature(XMLUni::fgDOMDatatypeNormalization, true);
      err_ = new myDOMErrorHandler();
      parser_->setErrorHandler(err_);

      DOMDocumentType* doctype =
	impl->createDocumentType(str_session, 0, str_vaucanson_pdtd);

      doc_ =
	impl->createDocument(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			     str_session, doctype);
    }

    inline
    XmlSession::~XmlSession()
    {
      //FIXME: free them (attached to XMLImpl).
      //doc_->release();
      //parser_->release();
    }

    inline
    void
    XmlSession::operator << (const xml_automaton_t& x)
    {
      DOMNode* structure =
	doc_->importNode(const_cast<DOMElement*> (x.value().structure()),
			 true);
      DOMNode* type =
	doc_->importNode(const_cast<DOMElement*> (x.structure().type()), true);

      DOMElement* root = doc_->createElement(str_automaton);

      root->appendChild(type);
      root->appendChild(structure);
      roots_.push_back(root);
    }

    inline
    void
    XmlSession::operator >> (xml_automaton_t& x)
    {
      if (roots_.begin() == roots_.end())
	FAIL("no more automaton in this session");
      DOMElement *root = roots_.back();
      roots_.pop_back();

      xml_automata_set_t	xs (root);
      xml_automaton_impl_t	xv (root);

      x.attach(xs);
      x.value() = xv;
    }

    inline
    std::ostream&
    operator << (std::ostream& o, const XmlSession& session)
    {
      using namespace xercesc;

      DOMElement* root = session.doc_->getDocumentElement();

      for (std::list<DOMElement*>::const_iterator i = session.roots_.begin();
	   i != session.roots_.end();
	   i++)
	{
	  root->appendChild(*i);
	}

      MemBufFormatTarget buf;

      DOMImplementation* impl =
	DOMImplementationRegistry::getDOMImplementation(str_LS);

      DOMWriter* serializer =
	static_cast<DOMImplementationLS*> (impl)->createDOMWriter();
      serializer->setEncoding(str_ISO8859_d1);

      if (serializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent,
				    true))
	serializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, true);

      if (serializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
	serializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);

      serializer->writeNode(&buf, *(session.doc_));
      o << buf.getRawBuffer();
      serializer->release();

      DOMNode* child = root->getFirstChild();

      while (child)
	{
	  root->removeChild(child);
	  DOMNode* next = child->getNextSibling();
	  child->release();
	  child = next;
	}
      return o;
    }

    inline
    std::istream&
    operator >> (std::istream& in, XmlSession& session)
    {
      using namespace xercesc;

      DOMDocument* doc;
      try
	{
	  CxxInputSource input(&in);
	  Wrapper4InputSource w(&input, false);
	  doc = session.parser_->parse(w);
	}
      catch (const XMLException& e)
	{
	  FAIL(std::string("XML exception: ") + xml2str(e.getMessage()));
	}
      catch (const DOMException& e)
	{
	  FAIL(std::string("DOM exception: ") + xml2str(e.msg));
	}
      catch (...)
	{
	  FAIL("Unknown caught exception.");
	}

      if (session.err_->has_error())
	FAIL(session.err_->get_msg());

      DOMNodeList* nodelist = doc->
	getElementsByTagNameNS(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			       str_automaton);
      unsigned n = nodelist->getLength();
      if (not n)
	FAIL("Cannot find any automaton root.");

      for (unsigned i = 0; i < n; i++)
	{
	  session.roots_.push_back(static_cast<DOMElement*>
				   (session.doc_->importNode(nodelist->item(i),
							     true)));
	}

      return in;
    }

    template<typename S, typename T>
    XmlSession&
    op_rout(const AutomataBase<S>& s,
	    XmlSession& session,
	    const T& a)
    {
      xml_automata_set_t	xs = op_convert(SELECT(xml_automata_set_t), s);
      xml_automaton_t		x (xs, op_convert(xs,
						  SELECT(xml_automaton_impl_t),
						  s,
						  a));
      session << x;
      return session;
    }

    template <class S, class T>
    XmlSession&
    op_rin(AutomataBase<S>&	structure,
	   XmlSession&		session,
	   T&			value)
    {
      XmlStructure	xs;
      xml_automaton_t	x (xs);

      session >> x;

      op_assign(structure, x.structure());
      op_assign(structure, x.structure(), value, x.value());
      return session;
    }

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_SESSION_HXX
