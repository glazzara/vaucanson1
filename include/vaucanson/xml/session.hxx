#ifndef VCSN_XML_SESSION_HXX
# define VCSN_XML_SESSION_HXX

# include <vaucanson/xml/session.hh>

# include <vaucanson/xml/errors.hh>

# include <string>

namespace vcsn
{
  inline
  std::ostream&
  operator<<(std::ostream& o, const xml::XmlSession& session)
  {
    using namespace xml;
    using namespace xercesc;

    DOMElement* root = session.doc_->getDocumentElement();

    for (std::list<DOMElement*>::const_iterator i = session.roots_.begin();
	 i != session.roots_.end();
	 i++) {
	root->appendChild(*i);
    }

    MemBufFormatTarget buf;

    DOMImplementation* impl = xercesc::DOMImplementationRegistry
      ::getDOMImplementation(str_LS);

    DOMWriter* serializer
      = ((DOMImplementationLS*)impl)->createDOMWriter();
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

    while (child) {
      root->removeChild(child);
      DOMNode* next = child->getNextSibling();
      child->release();
      child = next;
    }
    return o;
  }

  inline
  std::istream&
  operator>>(std::istream& in, xml::XmlSession& session)
  {
    using namespace xml;
    using namespace xercesc;

    DOMDocument* doc;
    try {
      CxxInputSource input(&in);
      Wrapper4InputSource w(&input, false);
      doc = session.parser_->parse(w);
    }
    catch (const XMLException& e) {
      FAIL(std::string("XML exception: ") + xml2str(e.getMessage()));
    }
    catch (const DOMException& e) {
      FAIL(std::string("DOM exception: ") + xml2str(e.msg));
    }
    catch (...) {
      FAIL("Unknown caught exception.");
    }

    if (session.err_->has_error())
      FAIL(session.err_->get_msg());

    DOMNodeList* nodelist = doc->
      getElementsByTagNameNS(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			     str_automaton);
    unsigned n = nodelist->getLength();
    if (!n)
      FAIL("Cannot find any automaton root.");

    for (unsigned i = 0; i < n; i++) {
      session.roots_.push_back(static_cast<DOMElement*>
			       (session.doc_->importNode(nodelist->item(i),
							 true)));
    }

    return in;
  }

  template<typename S>
  inline
  xml::XmlSession& op_rout(const AutomataBase<S>&,
			   xml::XmlSession& session,
			   const xml::XmlAutomaton& x)
  {
    session << x;
    return session;
  }

  namespace xml
  {
    inline
    XmlSession::XmlSession() : roots_()
    {
      DOMImplementation* impl = xercesc::DOMImplementationRegistry
	::getDOMImplementation(str_LS);

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
	impl->createDocumentType(str_session, NULL,
				 str_vaucanson_pdtd);

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
    XmlSession::operator<<(const XmlAutomaton& x)
    {
      roots_.push_back(static_cast<DOMElement*>(doc_->importNode(x.root_,
								 true)));
    }

    inline
    void
    XmlSession::operator>>(Element<XmlSet, XmlAutomaton>& x)
    {
      if (roots_.begin() == roots_.end())
	FAIL("no more automaton in this session");
      DOMElement *root = roots_.back();
      roots_.pop_back();
      x = Element<XmlSet, XmlAutomaton>(XmlSet(root),
					XmlAutomaton(doc_, root));
    }
  }
}

#endif // VCSN_XML_SESSION_HXX
