#ifndef VCSN_XML_XML_OPS_HXX
# define VCSN_XML_XML_OPS_HXX

# include <vaucanson/xml/xml_ops.hh>

# include <vaucanson/xml/errors.hh>

# include <string>

namespace vcsn
{
  namespace xml
  {
    using namespace xercesc;

    template <typename Tag>
    struct if_tag
    {
      static
      inline
      void set_root(DOMElement*, const Tag&)
      {
      }

      static
      inline
      void set_structure(DOMElement*, const Tag&)
      {
      }

      static
      inline
      void set_states(DOMElement*, Tag)
      {
      }

      static
      inline
      void set_edges(DOMElement*, const Tag&)
      {
      }

      static
      inline
      void set_initials(DOMElement*, const Tag&)
      {
      }

      static
      inline
      void set_finals(DOMElement*, const Tag&)
      {
      }

      static
      inline
      void set_state(DOMElement*, hstate_t, const Tag&)
      {
      }

      static
      inline
      void set_edge(DOMElement*, hedge_t, const Tag&)
      {
      }

      static
      inline
      void set_initial(DOMElement*, hstate_t, const Tag&)
      {
      }

      static
      inline
      void set_final(DOMElement*, hstate_t, const Tag&)
      {
      }

      static
      inline
      xercesc::DOMElement*
      add_state(XmlAutomaton& x, hstate_t s, const Tag&)
      {
	x.add_state(s);
	return NULL;
      }

      static
      inline
      void get_root(const DOMElement*, Tag&)
      {
      }

      static
      inline
      void set_structure(const DOMElement*, Tag&)
      {
      }

      static
      inline
      void get_structure(const DOMElement*, Tag&)
      {
      }

      static
      inline
      void get_states(const DOMElement*, Tag&)
      {
      }

      static
      inline
      void get_edges(const DOMElement*, Tag&)
      {
      }

      static
      inline
      void get_initials(const DOMElement*, Tag&)
      {
      }

      static
      inline
      void get_finals(const DOMElement*, Tag&)
      {
      }

      static
      inline
      void get_state(const DOMElement*, hstate_t, Tag&)
      {
      }

      static
      inline
      void get_edge(const DOMElement*, hedge_t, Tag&)
      {
      }

      static
      inline
      void get_initial(const DOMElement*, hstate_t, Tag&)
      {
      }

      static
      inline
      void get_final(const DOMElement*, hstate_t, Tag&)
      {
      }

    };

    template <>
    struct if_tag<XmlInfosTag>
    {

# define SET_ATTR(Section, Attr)                                      \
         if ( Section . Attr .set) {                                  \
	   std::ostringstream strs;                                   \
	   strs << Section . Attr .value;                             \
           node->removeAttribute(str_##Attr);                         \
           XMLCh* value = XMLString::transcode(strs.str().c_str());   \
           if (node->hasAttribute(str_##Attr)) {                      \
             if (XMLString::compareIString(node->                     \
		        		   getAttribute(str_##Attr),  \
                                           value))                    \
               node->setAttribute(str_##Attr, value);                 \
           }                                                          \
           else                                                       \
           node->setAttribute(str_##Attr, value);                     \
	   XMLString::release(&value);                                \
         }

# define OPTION_ATTR(Field, Attr, Do)                                 \
         if ( Field . Attr .set) {                                    \
           Do                                                         \
         }

# define OPTION(Section, Attr, Value, Str)                            \
         if ( Section . Attr .value == Value )                        \
           node->setAttribute(str_##Attr, str_##Str);

      static
      inline
      void set_default(DOMElement* n, const XmlInfosTag::Geometry& g)
      {
	DOMElement* node = NULL;
	DOMNode* child = n->getFirstChild();
	while (child) {
	  if ((child->getNodeType() == DOMNode::ELEMENT_NODE)
	      && (!XMLString::compareIString(child->getNodeName(),
					     str_geometry))) {
	    node = static_cast<DOMElement*>(child);
	  }
	  child = child->getNextSibling();
	}

	if (!node) {
	  if (g.set) {
	    node = n->getOwnerDocument()->createElement(str_geometry);
	    if (n->hasChildNodes())
	      n->insertBefore(node, n->getFirstChild());
	    else
	      n->appendChild(node);
	  }
	  else {
	    return ;
	  }
	}

	if (!g.set) {
	  n->removeChild(node);
	}

# include <vaucanson/xml/loadgeometry.inc>

      }

# undef SET_ATTR
# undef OPTION_ATTR
# undef OPTION

      static
      inline
      void set_root(DOMElement* node, const XmlInfosTag& tag)
      {
	set_default(node, tag.root);
      }

      static
      inline
      void set_structure(DOMElement* node, const XmlInfosTag& tag)
      {
	set_default(node, tag.structure);
      }

      static
      inline
      void set_states(DOMElement* node, const XmlInfosTag& tag)
      {
	set_default(node, tag.states);
      }

      static
      inline
      void set_edges(DOMElement* node, const XmlInfosTag& tag)
      {
	set_default(node, tag.edges);
      }

      static
      inline
      void set_initials(DOMElement* node, const XmlInfosTag& tag)
      {
	set_default(node, tag.initials);
      }

      static
      inline
      void set_finals(DOMElement* node, const XmlInfosTag& tag)
      {
	set_default(node, tag.finals);
      }

      static
      inline
      void set_state(DOMElement* n, hstate_t s, XmlInfosTag tag)
      {
	XMLCh* name = XMLString::transcode(tag.states
					   .name[s].c_str());
	n->setAttribute(str_name, name);
	XMLString::release(&name);

	if (tag.states.label[s].set) {
	  XMLCh* label = XMLString::transcode(tag.states
					     .label[s].value.c_str());
	  n->setAttribute(str_label, label);
	  XMLString::release(&label);
	}

	set_default(n, tag.states[s]);
      }

      static
      inline
      void set_edge(DOMElement* node, hedge_t s, XmlInfosTag tag)
      {
	set_default(node, tag.edges[s]);
      }

      static
      inline
      void set_initial(DOMElement* node, hstate_t s, XmlInfosTag tag)
      {
	set_default(node, tag.initials[s]);
      }

      static
      inline
      void set_final(DOMElement* node, hstate_t s, XmlInfosTag tag)
      {
	set_default(node, tag.initials[s]);
      }

      static
      inline
      xercesc::DOMElement*
      add_state(XmlAutomaton& x, hstate_t s, const XmlInfosTag& tag)
      {
	if (tag.states.name.find(s)->second == "") {
	  return x.add_state_elt(s);
	}
	else {
	  return x.add_state_elt(s, tag.states.name.find(s)->second);
	}
      }

# define SET_ATTR(Section, Attr)                                     \
        if (node->hasAttribute(str_##Attr )) {                       \
          std::istringstream strs(xml2str(node                       \
		->getAttribute(str_##Attr )));                       \
          strs >> Section . Attr .value;                             \
          Section . Attr .set = true;                                \
        }                                                            \
        else                                                         \
          Section . Attr .set = false;

# define OPTION_ATTR(Field, Attr, Do)                                \
         if (node->hasAttribute(str_##Attr )) {                      \
           Do                                                        \
         }

# define OPTION(Section, Attr, Value, Str)                           \
         if (!XMLString::compareIString(str_##Str,                   \
              node->getAttribute(str_##Attr ))) {                    \
           Section . Attr .set = true;                               \
           Section . Attr .value = Value;                            \
         }

      static
      inline
      void get_default(const DOMElement* n, XmlInfosTag::Geometry& g)
      {
	const DOMNode* child = n->getFirstChild();
	while (child) {
	  if ((child->getNodeType() == DOMNode::ELEMENT_NODE)
	      && (!XMLString::compareIString(child->getNodeName(),
					     str_geometry))) {
	    const DOMElement* node = static_cast<const DOMElement*>(child);

	    g.set = true;

# include <vaucanson/xml/loadgeometry.inc>

	    return ;
	  }
	  child = child->getNextSibling();
	}

	g.set = false;
      }

# undef SET_ATTR
# undef OPTION_ATTR
# undef OPTION

      static
      inline
      void get_root(const DOMElement* node, XmlInfosTag& tag)
      {
	get_default(node, tag.root);
      }

      static
      inline
      void get_structure(const DOMElement* node, XmlInfosTag& tag)
      {
	get_default(node, tag.structure);
      }

      static
      inline
      void get_states(const DOMElement* node, XmlInfosTag& tag)
      {
	get_default(node, tag.states);
      }

      static
      inline
      void get_edges(const DOMElement* node, XmlInfosTag& tag)
      {
	get_default(node, tag.edges);
      }

      static
      inline
      void get_initials(const DOMElement* node, XmlInfosTag& tag)
      {
	get_default(node, tag.initials);
      }

      static
      inline
      void get_finals(const DOMElement* node, XmlInfosTag& tag)
      {
	get_default(node, tag.finals);
      }

      static
      inline
      void get_state(const DOMElement* n, hstate_t s, XmlInfosTag& tag)
      {
	tag.states.name[s]
	  = xml2str(n->getAttribute(str_name));
	if (n->hasAttribute(str_label)) {
	  tag.states.label[s].set = true;
	  tag.states.label[s].value = xml2str(n->getAttribute(str_label));
	}
	else
	  tag.states.label[s].set = false;

	get_default(n, tag.states[s]);
      }

      static
      inline
      void get_edge(const DOMElement* node, hedge_t s, XmlInfosTag& tag)
      {
	get_default(node, tag.edges[s]);
      }

      static
      inline
      void get_initial(const DOMElement* node, hstate_t s, XmlInfosTag& tag)
      {
	get_default(node, tag.initials[s]);
      }

      static
      inline
      void get_final(const DOMElement* node, hstate_t s, XmlInfosTag& tag)
      {
	get_default(node, tag.finals[s]);
      }
    };
  }

  template<typename S, typename St>
  inline
  St& op_rout(const AutomataBase<S>&, St& st, const xml::XmlAutomaton& v)
  {
    v.serialize(st);
    return st;
  }

  template<typename S, typename St>
  inline
  St& op_rin(const AutomataBase<S>& s, St& st, xml::XmlAutomaton& v)
  {
    using namespace xercesc;
    using namespace xml;

    typedef Element<S, XmlAutomaton> auto_t;
    AUTOMATON_TYPES(auto_t);

    DOMImplementation* impl = xercesc::DOMImplementationRegistry
      ::getDOMImplementation(str_LS);

    DOMBuilder* parser = ((DOMImplementationLS*)impl)
      ->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

    DOMDocument* doc = loaddocument(parser, st);
    DOMNodeList* nodelist = doc->
      getElementsByTagNameNS(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			     str_automaton);
    if (!nodelist->getLength())
      FAIL("Cannot find any automaton root.");
    DOMNode* node = nodelist->item(0);
    XmlAutomaton x(doc, static_cast<DOMElement*>(node));
    alphabet_t alphabet;

    DOMNode* child = x.monoid_node_->getFirstChild();
    while (child) {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	DOMElement* elt = static_cast<DOMElement*>(child);
	if (!XMLString::compareIString(elt->getNodeName(), str_letter)) {
	  const XMLCh* str = elt->getAttribute(str_value);
	  if (str) {
	    std::istringstream s(xml2str(str));
	    char value;
	    s >> value;
	    alphabet.insert(char(value));
	  }
	}
      }
      child = child->getNextSibling();
    }
    auto_t xa = auto_t(series_t(semiring_t(),
				monoid_t(alphabet)), x);

    v = xa.value();
    // s.self() = xa.set();
    return st;
  }

  xml::XmlAutomaton
  op_default(SELECTOR(xml::XmlSet), SELECTOR(xml::XmlAutomaton))
  {
    return xml::XmlAutomaton();
  }

  namespace xml {
    inline
    xercesc::DOMDocument*
    loaddocument(DOMBuilder* parser, std::istream& in)
    {
      using namespace xercesc;

      if (parser->canSetFeature(XMLUni::fgDOMValidation, true))
	parser->setFeature(XMLUni::fgDOMValidation, true);
      if (parser->canSetFeature(XMLUni::fgDOMNamespaces, true))
	parser->setFeature(XMLUni::fgDOMNamespaces, true);
      if (parser->canSetFeature(XMLUni::fgDOMDatatypeNormalization, true))
	parser->setFeature(XMLUni::fgDOMDatatypeNormalization, true);
      myDOMErrorHandler* err = new myDOMErrorHandler();
      parser->setErrorHandler(err);

      DOMDocument* doc;
      try {
	CxxInputSource input(&in);
	Wrapper4InputSource w(&input, false);
	doc = parser->parse(w);
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

      if (err->has_error())
	FAIL(err->get_msg());

      delete err;
      return doc;
    }
  }

  template<typename St>
  inline
  St& op_rin(xml::XmlSet& s, St& st, xml::XmlAutomaton& v)
  {
    using namespace xercesc;
    using namespace xml;

    typedef Element<XmlSet, XmlAutomaton> auto_t;

    DOMImplementation* impl = xercesc::DOMImplementationRegistry
      ::getDOMImplementation(str_LS);

    DOMBuilder* parser = ((DOMImplementationLS*)impl)
      ->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

    DOMDocument* doc = loaddocument(parser, st);
    DOMNodeList* nodelist = doc->
      getElementsByTagNameNS(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			     str_automaton);
    if (!nodelist->getLength())
      FAIL("Cannot find any automaton root.");
    DOMNode* node = nodelist->item(0);
    XmlAutomaton x(doc, static_cast<DOMElement*>(node));
    auto_t xa = auto_t(XmlSet(static_cast<DOMElement*>(node)), x);

    v = xa.value();
    s = xa.set();
    return st;
  }

  template <typename Tm, typename Tw, typename S>
  inline
  algebra::polynom<Tm,Tw> op_convert(const algebra::SeriesBase<S>& s,
				     SELECTOR2(algebra::polynom<Tm, Tw>),
				     const xml::XmlValue& v)
  {
    Element<S,
      rat::exp<Tm, Tw> >
      exp(s.self());
    algebra::parse(v.value(), exp);

    return algebra::krat_to_polynom(exp).value();
  }

  template<typename I, typename J>
  inline
  I op_convert(const I& i, const J&)
  {
    return i;
  }

  template<typename Tm, typename Tw, typename S>
  inline
  rat::exp<Tm,Tw> op_convert(const algebra::SeriesBase<S>& s,
			     SELECTOR2(rat::exp<Tm, Tw>),
			     const xml::XmlValue& v)
  {
    Element<S,
      rat::exp<Tm, Tw> >
      exp(s.self());
    algebra::parse(v.value(), exp);

    return exp.value();
  }

  // Specializations does not work on function template

  template<typename Tm, typename Tw, typename S>
  inline
  xml::XmlValue op_convertx(const algebra::SeriesBase<S>& s,
			    SELECTOR(xml::XmlValue),
			    const algebra::polynom<Tm, Tw>& p)
  {
    xml::XmlValue v;

    std::ostringstream o;

    op_rout(s.self(), o, p);
    v.value() = o.str();

    return v;
  }

  template<typename Tm, typename Tw, typename S>
  inline
  xml::XmlValue op_convertx(const algebra::SeriesBase<S>& s,
			    SELECTOR(xml::XmlValue),
			    const rat::exp<Tm, Tw>& e)
  {
    xml::XmlValue v;

    std::ostringstream o;

    op_rout(s.self(), o, e);
    v.value() = o.str();

    return v;
  }

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag,
	    typename W,
	    typename M>
  xml::XmlAutomaton op_convert(const Automata<algebra::Series<W, M> >& s,
			       SELECTOR(xml::XmlAutomaton),
			       const Graph<Kind,
			       WordValue,
			       WeightValue,
			       SerieValue,
			       Letter,
			       Tag>& a)
  {
    using namespace xml;

    typedef Element<Automata<algebra::Series<W, M> >,
      Graph<Kind, WordValue, WeightValue, SerieValue, Letter, Tag> > auto_t;
    AUTOMATON_TYPES(auto_t);
    XmlAutomaton x;

    x.semiring_node_->setAttribute(str_structural, attr_semiring<W>::getstr());
    x.semiring_node_->setAttribute(str_set, attr_semiring_impl<WeightValue>
				   ::getstr());
    x.monoid_node_->setAttribute(str_structural, attr_monoid<M>::getstr());
    x.monoid_node_->setAttribute(str_set, attr_monoid_impl<WordValue>::getstr());

    for_each_letter(i, s.series().monoid().alphabet()) {
      std::ostringstream s;
      s << *i;
      XMLCh* xs = XMLString::transcode(s.str().c_str());
      DOMElement* node = x.doc_->createElement(str_letter);
      node->setAttribute(str_value, xs);
      XMLString::release(&xs);
      x.monoid_node_->appendChild(node);
    }

    if_tag<Tag>::set_root(x.root_, a.tag());
    if_tag<Tag>::set_structure(x.structure_, a.tag());
    if_tag<Tag>::set_states(x.states_node_, a.tag());
    for_each_state(i, a) {
      if_tag<Tag>::set_state(if_tag<Tag>::add_state(x, *i, a.tag()),
			     *i, a.tag());
    }

    if_tag<Tag>::set_edges(x.edges_node_, a.tag());
    for_each_edge(i, a) {
      x.add_edge(a.origin_of(*i), a.aim_of(*i),
		 Element<algebra::Series<W,M>, SerieValue>(s.series(),
							   a.label_of(*i)));
      if_tag<Tag>::set_edge(x.edges_nodes_[*i], *i, a.tag());
    }

    Element<algebra::Series<W,M>,SerieValue>
      zero(s.series(),
	   zero_value(SELECT2(algebra::Series<W,M>),SELECT(SerieValue)));

    if_tag<Tag>::set_initials(x.initials_node_, a.tag());
    for_each_initial_state(i, a) {
      Element<algebra::Series<W,M>,SerieValue>
	v(s.series(), a.get_initial(*i, zero.value()));
      if_tag<Tag>::set_initial(x.set_initial(*i, v, zero), *i, a.tag());
    }

    if_tag<Tag>::set_finals(x.finals_node_, a.tag());
    for_each_final_state(i, a) {
      Element<algebra::Series<W,M>,SerieValue>
	v(s.series(), a.get_final(*i, zero.value()));
      if_tag<Tag>::set_final(x.set_final(*i, v, zero), *i, a.tag());
    }

    return x;
  }

  template <class W,
	    class M>
  Automata<algebra::Series<W, M> >
  op_convert(const Automata<algebra::Series<W, M> >&,
	     const xml::XmlSet& set)
  {
    using namespace xml;
    using namespace xercesc;
    typedef typename algebra::Series<W, M>::monoid_t::alphabet_t alpha_t;

    alpha_t alphabet;

    const DOMNode* child = set.monoid_alphabet();
    while (child) {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	const DOMElement* elt = static_cast<const DOMElement*>(child);
	if (!XMLString::compareIString(elt->getNodeName(), str_letter)) {
	  const XMLCh* value = elt->getAttribute(str_value);
	  std::stringstream s;
	  char i;

	  s << xml2str(value);
	  s >> i;
	  alphabet.insert(char(i));
	}
      }
      child = child->getNextSibling();
    }

    return Automata<algebra::Series<W, M> >
      (algebra::Series<W, M>(W(), M(alphabet)));
  }

  template <typename W,
	    typename M>
  xml::XmlAutomaton
  op_convert(const Automata<algebra::Series<W, M> >&,
	     const xml::XmlAutomaton&,
	     const xml::XmlSet&,
	     const xml::XmlAutomaton& x)
  {
    return x;
  }

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag,
	    typename W,
	    typename M>
  Graph<Kind, WordValue, WeightValue, SerieValue, Letter, Tag>
  op_convert(const Automata<algebra::Series<W, M> >& type,
	     const Graph<Kind,
	     WordValue,
	     WeightValue,
	     SerieValue,
	     Letter,
	     Tag>&,
	     const xml::XmlAutomaton& x)
  {
    using namespace xml;

    typedef Element<Automata<algebra::Series<W, M> >,
      Graph<Kind, WordValue, WeightValue, SerieValue, Letter, Tag> > auto_t;
    AUTOMATON_TYPES(auto_t);

    Graph<Kind,
      WordValue,
      WeightValue,
      SerieValue,
      Letter,
      Tag> a;

    if (x.semiring_node_->hasAttribute(str_structural)
	&& (XMLString::compareIString(x.semiring_node_
				      ->getAttribute(str_structural),
				      attr_semiring<W>::getstr())))
      FAIL("Bad semiring");
    if (x.semiring_node_->hasAttribute(str_set)
	&& (XMLString::compareIString(x.semiring_node_
				      ->getAttribute(str_set),
				      attr_semiring_impl<WeightValue>
				      ::getstr())))
      FAIL("Bad semiring");
    if (x.monoid_node_->hasAttribute(str_structural)
	&& (XMLString::compareIString(x.monoid_node_
				      ->getAttribute(str_structural),
				      attr_monoid<M>::getstr())))
      FAIL("Bad monoid");
    if (x.monoid_node_->hasAttribute(str_set)
	&& (XMLString::compareIString(x.monoid_node_
				      ->getAttribute(str_set),
				      attr_monoid_impl<WordValue>::getstr())))
      FAIL("Bad monoid");

    if_tag<Tag>::get_root(x.root_, a.tag());
    if_tag<Tag>::get_structure(x.structure_, a.tag());
    if_tag<Tag>::get_states(x.states_node_, a.tag());
    for (std::map<hstate_t,std::string>::const_iterator i
	   = x.snum2name_.begin();
	 i != x.snum2name_.end();
	 i++) {
      while (!a.has_state((*i).first))
	a.add_state();
    }
    for_each_state(i, a) {
      if (!(x.has_state(*i)))
	a.del_state(*i);
    }

    DOMNode* child = x.states_node_->getFirstChild();
    while (child) {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	DOMElement* elt = static_cast<DOMElement*>(child);
	if (!XMLString::compareIString(elt->getNodeName(), str_state)) {
	  if (elt->hasAttribute(str_name)) {
	    if_tag<Tag>::get_state(elt,
				   x.sname2num_.
				   find(xml2str(elt->getAttribute(str_name)))
				   ->second,
				   a.tag());
	  }
	}
      }
      child = child->getNextSibling();
    }

    if_tag<Tag>::get_edges(x.edges_node_, a.tag());
    child = x.edges_node_->getFirstChild();
    while (child) {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	DOMElement* elt = static_cast<DOMElement*>(child);
	if (!XMLString::compareIString(elt->getNodeName(), str_edge)) {
	  if (elt->hasAttribute(str_src)
	      && elt->hasAttribute(str_dst)
	      && elt->hasAttribute(str_label)) {
	    const XMLCh* src = elt->getAttribute(str_src);
	    const XMLCh* dst = elt->getAttribute(str_dst);
	    const XMLCh* label = elt->getAttribute(str_label);
	    std::string l;
	    if (elt->hasAttribute(str_weight)) {
	      const XMLCh* weight = elt->getAttribute(str_weight);
	      l = "(" + xml2str(weight) + " " + xml2str(label) + ")";
	    }
	    else
	      l = xml2str(label);
	    series_elt_t lelt(type.series());
	    lelt = xml::XmlValue(l);
	    hedge_t e = a.add_edge(x.sname2num_.find(xml2str(src))->second,
				   x.sname2num_.find(xml2str(dst))->second,
				   lelt.value());
	    if_tag<Tag>::get_edge(elt, e, a.tag());
	  }
	}
      }
      child = child->getNextSibling();
    }

    if_tag<Tag>::get_initials(x.initials_node_, a.tag());
    child = x.initials_node_->getFirstChild();
    while (child) {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	DOMElement* elt = static_cast<DOMElement*>(child);
	if (!XMLString::compareIString(elt->getNodeName(), str_initial)) {
	  if (elt->hasAttribute(str_state)
	      && elt->hasAttribute(str_label)) {
	    const XMLCh* state = elt->getAttribute(str_state);
	    const XMLCh* label = elt->getAttribute(str_label);
	    std::string l;
	    if (elt->hasAttribute(str_weight)) {
	      const XMLCh* weight = elt->getAttribute(str_weight);
	      l = "(" + xml2str(weight) + " " + xml2str(label) + ")";
	    }
	    else
	      l = xml2str(label);

	    series_elt_t lelt(type.series());
	    lelt = xml::XmlValue(l);
	    hstate_t s = x.sname2num_.find(xml2str(state))->second;
	    a.set_initial(s, lelt.value(),
			  zero_value(SELECT(series_t),
				     SELECT(serie_value_t)));
	    if_tag<Tag>::get_initial(elt, s, a.tag());
	  }
	}
      }
      child = child->getNextSibling();
    }

    if_tag<Tag>::get_finals(x.finals_node_, a.tag());
    child = x.finals_node_->getFirstChild();
    while (child) {
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	DOMElement* elt = static_cast<DOMElement*>(child);
	if (!XMLString::compareIString(elt->getNodeName(), str_final)) {
	  if (elt->hasAttribute(str_state)
	      && elt->hasAttribute(str_label)) {
	    const XMLCh* state = elt->getAttribute(str_state);
	    const XMLCh* label = elt->getAttribute(str_label);
	    std::string l;
	    if (elt->hasAttribute(str_weight)) {
	      const XMLCh* weight = elt->getAttribute(str_weight);
	      l = "(" + xml2str(weight) + " " + xml2str(label) + ")";
	    }
	    else
	      l = xml2str(label);

	    series_elt_t lelt(type.series());
	    lelt = xml::XmlValue(l);
	    hstate_t s = x.sname2num_.find(xml2str(state))->second;
	    a.set_final(s, lelt.value(), zero_value(SELECT(series_t),
						    SELECT(serie_value_t)));
	    if_tag<Tag>::get_final(elt, s, a.tag());
	  }
	}
      }
      child = child->getNextSibling();
    }

    return a;
  }

  template<typename Tm, typename Tw, typename W, typename M>
  inline
  void op_assign(const algebra::Series<W, M>& s,
		 algebra::polynom<Tm, Tw>& dst,
		 const xml::XmlValue& src)
  {
    dst = op_convert(s,
		     dst,
		     src);
  }

  xml::XmlAutomaton
  op_convert(const xml::XmlSet&,
	     const xml::XmlAutomaton&,
	     const xml::XmlAutomaton& src)
  {
    return src;
  }

  void op_assign(const xml::XmlSet&,
		 const xml::XmlSet&,
		 xml::XmlAutomaton& dst,
		 const xml::XmlAutomaton& src)
  {
    dst = src;
  }

  template<class S>
  inline
  void op_assign(const AutomataBase<S>&,
		 const xml::XmlSet&,
		 xml::XmlAutomaton& dst,
		 const xml::XmlAutomaton& src)
  {
    dst = src;
  }

  template<typename Tm, typename Tw, typename W, typename M>
  inline
  void op_assign(const algebra::Series<W, M>& s,
		 rat::exp<Tm, Tw>& dst,
		 const xml::XmlValue& src)
  {
    dst = op_convert(s,
		     dst,
		     src);
  }

  template<typename Tm, typename Tw, typename W, typename M>
  inline
  void op_assign(const algebra::Series<W, M>& s,
		 xml::XmlValue& dst,
		 const rat::exp<Tm, Tw>& src)
  {
    dst = op_convert(s,
		     dst,
		     src);
  }

  template<typename Tm, typename Tw, typename W, typename M>
  inline
  void op_assign(const algebra::Series<W, M>& s,
		 xml::XmlValue& dst,
		 const algebra::polynom<Tm, Tw>& src)
  {
    dst = op_convert(s,
		     dst,
		     src);
  }

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag,
	    typename W,
	    typename M>
  inline
  void
  op_assign(const Automata<algebra::Series<W, M> >& s,
	    Graph<Kind,
	    WordValue,
	    WeightValue,
	    SerieValue,
	    Letter,
	    Tag>& dst,
	    const xml::XmlAutomaton& src)
  {
    dst = op_convert(s,
		     dst,
		     src);
  }

  template <class Kind,
	    class WordValue,
	    class WeightValue,
	    class SerieValue,
	    class Letter,
	    class Tag,
	    typename W,
	    typename M>
  inline
  void
  op_assign(const Automata<algebra::Series<W, M> >& s,
	    xml::XmlAutomaton& dst,
	    const Graph<Kind,
	    WordValue,
	    WeightValue,
	    SerieValue,
	    Letter,
	    Tag>& src)
  {
    dst = op_convert(s,
		     dst,
		     src);
  }
}

#endif // VCSN_XML_XML_OPS_HXX
