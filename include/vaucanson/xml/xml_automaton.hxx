#ifndef VCSN_XML_XML_AUTOMATON_HXX
# define VCSN_XML_XML_AUTOMATON_HXX

# include <vaucanson/xml/xml_automaton.hh>

# include <vaucanson/automata/concrete/graph.hh>
# include <vaucanson/algebra/concrete/free_monoid/words.hh>
# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>
# include <include/vaucanson/algebra/concrete/alphabets/predefs.hh>
# include <include/vaucanson/algebra/concrete/free_monoid/predefs.hh>
# include <vaucanson/algebra/concept/numerical_semiring.hh>
# include <vaucanson/algebra/concept/tropical_semiring.hh>
# include <vaucanson/xml/krat_to_polynom.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>

# include <vaucanson/xml/infos.hh>
# include <vaucanson/xml/ios.hh>
# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/error_handler.hh>

# include <xercesc/framework/MemBufFormatTarget.hpp>
# include <xercesc/framework/Wrapper4InputSource.hpp>

namespace vcsn
{
  namespace xml
  {
    using namespace xercesc;

# define NEW_ATTR(X) \
  template <typename I> \
  struct attr_##X { \
    static const XMLCh* getstr() \
    { \
      return V; \
    } \
  };

# define NEW_ATTR_VALUE(X,Y,V) \
  template <> \
  struct attr_##X < Y > { \
    static const XMLCh* getstr() \
    { \
      return V; \
    } \
  };

    NEW_ATTR(semiring)
    NEW_ATTR_VALUE(semiring, algebra::NumericalSemiring, str_numerical)
    //    NEW_ATTR_VALUE(semiring, algebra::NumericalSemiring, str_boolean)
    NEW_ATTR_VALUE(semiring, algebra::TropicalSemiring<algebra::TropicalMax>,
		   str_tropicalMax)
    NEW_ATTR_VALUE(semiring, algebra::TropicalSemiring<algebra::TropicalMin>,
		   str_tropicalMin)

    NEW_ATTR(semiring_impl)
    NEW_ATTR_VALUE(semiring_impl, bool, str_B)
    NEW_ATTR_VALUE(semiring_impl, int, str_Z)
    NEW_ATTR_VALUE(semiring_impl, float, str_R)

    NEW_ATTR(monoid)
    NEW_ATTR_VALUE(monoid, algebra::char_letter::Words, str_letters)
    NEW_ATTR_VALUE(monoid, algebra::char_pair::Words, str_pairs)
    NEW_ATTR_VALUE(monoid, algebra::weighted_letter::Words, str_weighted)
    NEW_ATTR_VALUE(monoid, algebra::int_letter::Words, str_integers)

    NEW_ATTR(monoid_impl)
    NEW_ATTR_VALUE(monoid_impl, algebra::char_letter::WordValue, str_free)
    NEW_ATTR_VALUE(monoid_impl, algebra::char_pair::WordValue, str_free)
    NEW_ATTR_VALUE(monoid_impl, algebra::weighted_letter::WordValue, str_free)
    NEW_ATTR_VALUE(monoid_impl, algebra::int_letter::WordValue, str_free)
    // NEW_ATTR_VALUE(monoid_impl, algebra::char_letter::WordValue, str_unit)

    inline
    XmlAutomaton::XmlAutomaton()
      : handled_doc_(0), edges_nodes_(), sname2num_(), snum2name_()
    {
      DOMImplementation* impl = xercesc::DOMImplementationRegistry
	::getDOMImplementation(str_LS);

      DOMDocumentType* doctype =
	impl->createDocumentType(str_automaton, NULL,
				 str_vaucanson_pdtd);

      doc_ =
	impl->createDocument(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			     str_automaton, doctype);
      root_ = doc_->getDocumentElement();

      monoid_node_   = doc_->createElement(str_monoid);
      semiring_node_ = doc_->createElement(str_semiring);
      states_node_   = doc_->createElement(str_states);
      edges_node_    = doc_->createElement(str_edges);
      initials_node_ = doc_->createElement(str_initials);
      finals_node_   = doc_->createElement(str_finals);

      type_          = doc_->createElement(str_type);
      structure_     = doc_->createElement(str_content);

      type_->appendChild(monoid_node_);
      type_->appendChild(semiring_node_);
      structure_->appendChild(states_node_);
      structure_->appendChild(edges_node_);
      structure_->appendChild(initials_node_);
      structure_->appendChild(finals_node_);

      root_->appendChild(type_);
      root_->appendChild(structure_);
    }

    inline
    XmlAutomaton::XmlAutomaton(DOMElement* root)
      : doc_(root->getOwnerDocument()), handled_doc_(false), root_(root)
    {
      DOMNode* i = root->getFirstChild();

      structure_     = NULL;
      type_          = NULL;
      monoid_node_   = NULL;
      semiring_node_ = NULL;
      edges_node_    = NULL;
      states_node_   = NULL;
      initials_node_ = NULL;
      finals_node_   = NULL;

      while (i) {
	if (i->getNodeType() == DOMNode::ELEMENT_NODE) {
	  if (!XMLString::compareIString(i->getNodeName(), str_type)) {
	    DOMNode* child = i->getFirstChild();
	    type_ = static_cast<DOMElement*>(i);
	    while (child) {
	      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
		DOMElement* elt = static_cast<DOMElement*>(child);
		if (!XMLString::compareIString(elt->getNodeName(), str_monoid))
		  monoid_node_   = elt;
		else if (!XMLString::compareIString(elt->getNodeName(),
						    str_semiring))
		  semiring_node_ = elt;
	      }
	      child = child->getNextSibling();
	    }
	  }
	  else if (!XMLString::compareIString(i->getNodeName(),
					      str_content)) {
	    structure_ = static_cast<DOMElement*>(i);
	    DOMNode* child = i->getFirstChild();
	    while (child) {
	      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
		DOMElement* elt = static_cast<DOMElement*>(child);
		if (!XMLString::compareIString(elt->getNodeName(), str_edges))
		  edges_node_    = elt;
		else if (!XMLString::compareIString(elt->getNodeName(),
						    str_states))
		  states_node_ = elt;
		else if (!XMLString::compareIString(elt->getNodeName(),
						    str_initials))
		initials_node_ = elt;
		else if (!XMLString::compareIString(elt->getNodeName(),
						    str_finals))
		  finals_node_   = elt;
	      }
	      child = child->getNextSibling();
	    }
	  }
	}
	i = i ->getNextSibling();
      }
      if (!structure_) {
	structure_ = doc_->createElement(str_content);
	root_->appendChild(structure_);
      }
      if (!type_) {
	type_ = doc_->createElement(str_type);
	root_->insertBefore(type_, structure_);
      }
      if (!finals_node_) {
	finals_node_ = doc_->createElement(str_finals);
	structure_->appendChild(finals_node_);
      }
      if (!initials_node_) {
	initials_node_ = doc_->createElement(str_initials);
	structure_->insertBefore(initials_node_, finals_node_);
      }
      if (!edges_node_) {
	edges_node_ = doc_->createElement(str_edges);
	structure_->insertBefore(edges_node_, finals_node_);
      }
      if (!states_node_) {
	states_node_ = doc_->createElement(str_states);
	structure_->insertBefore(states_node_, edges_node_);
      }
      if (!semiring_node_) {
	semiring_node_ = doc_->createElement(str_semiring);
	type_->appendChild(semiring_node_);
      }
      if (!monoid_node_) {
	monoid_node_ = doc_->createElement(str_monoid);
	type_->insertBefore(monoid_node_, semiring_node_);
      }

      DOMNode* child = states_node_->getFirstChild();
      unsigned j = 0;
      while (child) {
	if ((child->getNodeType() == DOMNode::ELEMENT_NODE)
	    && (!XMLString::compareIString(child->getNodeName(),
					    str_state))) {
	  DOMElement* elt = static_cast<DOMElement*>(child);
	  if (elt->hasAttribute(str_name)) {
	    std::string name = xml2str(elt->getAttribute(str_name));
	    hstate_t state(j++);
	    sname2num_[name] = state;
	    snum2name_[state] = name;
	  }
	}
	child = child->getNextSibling();
      }

      child = edges_node_->getFirstChild();
      j = 0;
      while (child) {
	if ((child->getNodeType() == DOMNode::ELEMENT_NODE)
	    && (!XMLString::compareIString(child->getNodeName(),
					    str_edge))) {
	  DOMElement* elt = static_cast<DOMElement*>(child);
	  hedge_t edge(j++);
	  edges_nodes_[edge] = elt;
	}
	child = child->getNextSibling();
      }
    }

    inline
    XmlAutomaton::~XmlAutomaton()
    {
      if (handled_doc_)
	delete doc_;
    }

    inline
    void
    XmlAutomaton::serialize(std::ostream& o) const
    {
      DOMImplementation* impl = xercesc::DOMImplementationRegistry
	::getDOMImplementation(str_LS);

      MemBufFormatTarget buf;

      DOMWriter* serializer
	= ((DOMImplementationLS*)impl)->createDOMWriter();
      serializer->setEncoding(str_ISO8859_d1);

      if (serializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent,
				    true))
	serializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, true);

      if (serializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
	serializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);

      serializer->writeNode(&buf, *doc_);
      o << buf.getRawBuffer();
      serializer->release();
    }

    inline
    hstate_t
    XmlAutomaton::add_state()
    {
      std::string str("s0");
      unsigned i = 0;
      if  ((sname2num_.find(str) != sname2num_.end()) ||
	   (snum2name_.find(i) != snum2name_.end())) {
	do {
	  i++;
	  std::ostringstream s;
	  s << i;
	  str = std::string("s") + s.str();
	} while ((sname2num_.find(str) != sname2num_.end()) ||
		 (snum2name_.find(i) != snum2name_.end()));
      }
      return add_state(i, str);
    }

    inline
    xercesc::DOMElement*
    XmlAutomaton::add_state_elt(hstate_t i)
    {
      std::ostringstream s;
      s << i;
      return add_state_elt(i, std::string("s") + s.str());
    }

    inline
    hstate_t
    XmlAutomaton::add_state(hstate_t i)
    {
      std::ostringstream s;
      s << i;
      return add_state(i, std::string("s") + s.str());
    }

    inline
    hstate_t
    XmlAutomaton::add_state(const std::string& name)
    {
      unsigned i = 0;
      while (snum2name_.find(i) != snum2name_.end())
	i++;
      return add_state(i, name);
    }

    inline
    hstate_t
    XmlAutomaton::add_state(hstate_t i, const std::string& str)
    {
      DOMElement* state = doc_->createElement(str_state);
      states_node_->appendChild(state);
      snum2name_[i] = str;
      sname2num_[str] = i;
      XMLCh* name = XMLString::transcode(str.c_str());
      state->setAttribute(str_name, name);
      XMLString::release(&name);
      return i;
    }

    inline
    xercesc::DOMElement*
    XmlAutomaton::add_state_elt(hstate_t i, const std::string& str)
    {
      DOMElement* state = doc_->createElement(str_state);
      states_node_->appendChild(state);
      snum2name_[i] = str;
      sname2num_[str] = i;
      XMLCh* name = XMLString::transcode(str.c_str());
      state->setAttribute(str_name, name);
      XMLString::release(&name);
      return state;
    }

    inline
    void
    XmlAutomaton::del_state(hstate_t state)
    {
      assertion(has_state(state));
      if (!has_state(state))
	return ;
      std::string statename = snum2name_[state];

      DOMNode* i = states_node_->getFirstChild();
      while (i) {
	if (i->getNodeType() == DOMNode::ELEMENT_NODE) {
	  DOMElement* elt = static_cast<DOMElement*>(i);
	  if (xml2str(elt->getAttribute(str_name)) == statename) {
	    states_node_->removeChild(i);
	    snum2name_.erase(state);
	    sname2num_.erase(statename);
	    return ;
	  }
	}
	i = i->getNextSibling();
      }
    }

    inline
    bool
    XmlAutomaton::has_state(hstate_t state) const
    {
      return (snum2name_.find(state) != snum2name_.end());
    }

    inline
    hedge_t
    XmlAutomaton::add_edge(hstate_t source,
			   hstate_t destination,
			   const label_t& label)
    {
      precondition(has_state(source) && has_state(destination));
      DOMElement* edge = doc_->createElement(str_edge);
      edges_node_->appendChild(edge);
      XMLCh* lbl = XMLString::transcode(label.value().c_str());
      edge->setAttribute(str_label, lbl);
      XMLString::release(&lbl);

      lbl = XMLString::transcode(snum2name_[source].c_str());
      edge->setAttribute(str_src, lbl);
      XMLString::release(&lbl);
      lbl = XMLString::transcode(snum2name_[destination].c_str());
      edge->setAttribute(str_dst, lbl);
      XMLString::release(&lbl);

      unsigned n = 0;
      while (has_edge(hedge_t(n)))
	n++;
      edges_nodes_[hedge_t(n)] = edge;
      return n;
    }

    inline
    void
    XmlAutomaton::del_edge(hedge_t n)
    {
      precondition(has_edge(n));

      edges_node_->removeChild(edges_nodes_[n]);
      edges_nodes_.erase(n);
    }

    inline
    bool
    XmlAutomaton::has_edge(hedge_t edge) const
    {
      return (edges_nodes_.find(edge) != edges_nodes_.end());
    }

    inline
    hstate_t
    XmlAutomaton::origin_of(hedge_t edge) const
    {
      precondition(has_edge(edge));

      return sname2num_.find(xml2str(edges_nodes_.find(edge)->second
				     ->getAttribute(str_dst)))->second;
    }

    inline
    hstate_t
    XmlAutomaton::aim_of(hedge_t edge) const
    {
      precondition(has_edge(edge));
      return sname2num_.find(xml2str(edges_nodes_.find(edge)->second
				     ->getAttribute(str_src)))->second;
    }

    inline
    XmlValue
    XmlAutomaton::label_of(hedge_t edge) const
    {
      precondition(has_edge(edge));
      return xml2str(edges_nodes_.find(edge)->second
		     ->getAttribute(str_label));
    }

    inline
    xercesc::DOMElement*
    XmlAutomaton::set_initial(hstate_t state, const XmlValue& v,
			      const XmlValue& z)
    {
      precondition(has_state(state));
      std::string statename = snum2name_[state];
      DOMNode* i = initials_node_->getFirstChild();
      DOMElement* init = NULL;
      while (i) {
	if (i->getNodeType() == DOMNode::ELEMENT_NODE) {
	  DOMElement* elt = static_cast<DOMElement*>(i);
	  const XMLCh* l = elt->getAttribute(str_state);
	  if (xml2str(l) == statename) {
	    init = elt;
	    break ;
	  }
	}
	i = i->getNextSibling();
      }
      if (z == v) {
	if (init) {
	  initials_node_->removeChild(init);
	  init->release();
	}
	return NULL;
      }
      else {
	if (!init) {
	  init = doc_->createElement(str_initial);
	  initials_node_->appendChild(init);
	  XMLCh* n = XMLString::transcode(statename.c_str());
	  init->setAttribute(str_state, n);
	  XMLString::release(&n);
	}
	XMLCh* lbl = XMLString::transcode(v.value().c_str());
	init->setAttribute(str_label, lbl);
	XMLString::release(&lbl);
	return init;
      }
    }

    inline
    XmlValue
    XmlAutomaton::get_initial(hstate_t state,
			      const XmlValue& z)
    {
      precondition(has_state(state));
      std::string statename = snum2name_[state];
      DOMNode* i = initials_node_->getFirstChild();
      while (i) {
	if (i->getNodeType() == DOMNode::ELEMENT_NODE) {
	  DOMElement* elt = static_cast<DOMElement*>(i);
	  const XMLCh* l = elt->getAttribute(str_state);
	  if (xml2str(l) == statename) {
	    if (elt->getAttribute(str_label)) {
	      const XMLCh* label = elt->getAttribute(str_label);
	      if (elt->hasAttribute(str_weight)) {
		const XMLCh* weight = elt->getAttribute(str_weight);
		return "(" + xml2str(weight) + " " + xml2str(label) + ")";
	      }
	      else
		return xml2str(label);
	    }
	  }
	}
	i = i->getNextSibling();
      }
      return z;
    }

    inline
    void			XmlAutomaton::clear_initial()
    {
      DOMNode* i = initials_node_->getFirstChild();
      DOMNode* next;

      while (i) {
	next = i->getNextSibling();
	initials_node_->removeChild(i);
	i = next;
      }
    }

    inline
    xercesc::DOMElement*
    XmlAutomaton::set_final(hstate_t state, const XmlValue& v,
			    const XmlValue& z)
    {
      precondition(has_state(state));
      std::string statename = snum2name_[state];
      DOMNode* i = finals_node_->getFirstChild();
      DOMElement* final = NULL;
      while (i) {
	if (i->getNodeType() == DOMNode::ELEMENT_NODE) {
	  DOMElement* elt = static_cast<DOMElement*>(i);
	  const XMLCh* l = elt->getAttribute(str_state);
	  if (xml2str(l) == statename) {
	    final = elt;
	    break ;
	  }
	}
	i = i->getNextSibling();
      }
      if (z == v) {
	if (final) {
	  finals_node_->removeChild(final);
	  final->release();
	}
	return NULL;
      }
      else {
	if (!final) {
	  final = doc_->createElement(str_final);
	  finals_node_->appendChild(final);
	  XMLCh* n = XMLString::transcode(statename.c_str());
	  final->setAttribute(str_state, n);
	  XMLString::release(&n);
	}
	XMLCh* lbl = XMLString::transcode(v.value().c_str());
	final->setAttribute(str_label, lbl);
	XMLString::release(&lbl);
	return final;
      }
    }

    inline
    XmlValue
    XmlAutomaton::get_final(hstate_t state,
			    const XmlValue& z)
    {
      precondition(has_state(state));
      std::string statename = snum2name_[state];
      DOMNode* i = finals_node_->getFirstChild();
      while (i) {
	if (i->getNodeType() == DOMNode::ELEMENT_NODE) {
	  DOMElement* elt = static_cast<DOMElement*>(i);
	  const XMLCh* l = elt->getAttribute(str_state);
	  if (xml2str(l) == statename) {
	    if (elt->hasAttribute(str_label)) {
	      const XMLCh* label = elt->getAttribute(str_label);
	      if (elt->hasAttribute(str_weight)) {
		const XMLCh* weight = elt->getAttribute(str_weight);
		return "(" + xml2str(weight) + " " + xml2str(label) + ")";
	      }
	      else
		return xml2str(label);
	    }
	  }
	}
	i = i->getNextSibling();
      }
      return z;
    }

    inline
    void
    XmlAutomaton::clear_final()
    {
      DOMNode* i = initials_node_->getFirstChild();
      DOMNode* next;

      while (i) {
	next = i->getNextSibling();
	finals_node_->removeChild(i);
	i = next;
      }
    }

    inline
    void
    XmlAutomaton::update(hedge_t edge, label_t label)
    {
      precondition(has_edge(edge));

      XMLCh* lbl = XMLString::transcode(label.value().c_str());
      if (edges_nodes_[edge]->hasAttribute(str_weight))
	edges_nodes_[edge]->removeAttribute(str_weight);
      edges_nodes_[edge]->setAttribute(str_label, lbl);
      XMLString::release(&lbl);
    }
  }
}

# endif // VCSN_XML_XML_AUTOMATON_HXX
