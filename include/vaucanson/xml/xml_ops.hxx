// xml_ops.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XML_OPS_HXX
# define VCSN_XML_XML_OPS_HXX

# include <string>

# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>

# include <vaucanson/xml/xml_ops.hh>

# include <vaucanson/xml/if_tag.hh>
# include <vaucanson/xml/errors.hh>

namespace vcsn
{

  namespace xml
  {

    inline
    xercesc::DOMDocument*
    loaddocument(DOMBuilder* parser, std::istream& is)
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

    /*-------------.
    | Op functions |
    `-------------*/

    using xercesc::DOMElement;
    using xercesc::DOMNode;

    /*--------------.
    | I/O Functions |
    `--------------*/

    template <class Ostream>
    Ostream&
    op_rout(const xml_automata_set_t& xs,
	    Ostream& os,
	    const xml_automaton_impl_t& xv)
    {
      using namespace xercesc;

      DOMImplementation* impl =
	DOMImplementationRegistry::getDOMImplementation(str_LS);

      MemBufFormatTarget buf;

      DOMWriter* serializer =
	static_cast<DOMImplementationLS*> (impl)->createDOMWriter();
      serializer->setEncoding(str_ISO8859_d1);

      if (serializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent,
				    true))
	serializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, true);

      if (serializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
	serializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);

      DOMDocumentType* doctype =
	impl->createDocumentType(str_automaton, 0, str_vaucanson_pdtd);
      DOMDocument* doc =
	impl->createDocument(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			     str_automaton, doctype);

      DOMElement*	root = doc->getDocumentElement();

      DOMNode*		type =
	doc->importNode(const_cast<DOMElement*> (xs.type()), true);
      DOMNode*		structure =
	doc->importNode(const_cast<DOMElement*> (xv.structure()), true);

      root->appendChild(type);
      root->appendChild(structure);

      serializer->writeNode(&buf, *doc);
      os << buf.getRawBuffer();
      serializer->release();

      delete doc;
      return os;
    }

    template <class Istream>
    Istream&
    op_rin(xml_automata_set_t& s, Istream& is, xml_automaton_impl_t& v)
    {
      using namespace xercesc;

      DOMImplementation* impl =
	DOMImplementationRegistry::getDOMImplementation(str_LS);

      DOMBuilder* parser = static_cast<DOMImplementationLS*> (impl)
	->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

      DOMDocument* doc = loaddocument(parser, is);
      DOMNodeList* nodelist = doc->
	getElementsByTagNameNS(str_http_c_s_swww_plrde_pepita_pfr_svaucanson,
			       str_automaton);
      if (not nodelist->getLength())
	FAIL("Cannot find any automaton root.");
      DOMNode* node = nodelist->item(0);

      v = xml_automaton_impl_t (static_cast<DOMElement*> (node));
      s = xml_automata_set_t (static_cast<DOMElement*> (node));

      return is;
    }

    /*----------------------.
    | Structure conversions |
    `----------------------*/

    template <class Auto>
    xml_automata_set_t
    op_convert(const xml_automata_set_t&, const AutomataBase<Auto>& s)
    {
      AUTOMATA_SET_TYPES(Auto);

      xml_automata_set_t xs;

      // Set the structure.
      xs.semiring()->setAttribute(str_operations,
				  attr_semiring<semiring_t>::getstr());
      xs.monoid()->setAttribute(str_generators,
				attr_monoid<monoid_t>::getstr());

      // Set the alphabet.

      typedef typename alphabet_t::const_iterator alphabet_iterator;

      for_each_letter(i, s.series().monoid().alphabet())
	{
	  std::ostringstream	os;
	  os << *i;
	  XMLCh*		c = XMLString::transcode(os.str().c_str());
	  DOMElement*		node = xs.doc()->createElement(str_generator);

	  node->setAttribute(str_value, c);
	  XMLString::release(&c);
	  xs.monoid()->appendChild(node);
	}

      return xs;
    }

    template <class Auto>
    Auto
    op_convert(const AutomataBase<Auto>&, const xml_automata_set_t& s)
    {
      using namespace xercesc;

      AUTOMATA_SET_TYPES(Auto);

      // Check the semiring.
      if (s.semiring()->hasAttribute(str_operations) and
	  XMLString::compareIString(s.semiring()->getAttribute(str_operations),
				    attr_semiring<semiring_t>::getstr()))
	FAIL("Bad semiring");

      // Check the monoid.
      if (s.monoid()->hasAttribute(str_generators) and
	  XMLString::compareIString(s.monoid()->getAttribute(str_generators),
				    attr_monoid<monoid_t>::getstr()))
	FAIL("Bad monoid");

      // Get the alphabet.
      alphabet_t	alphabet;
      const DOMNode*	child = s.monoid()->getFirstChild();

      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      const DOMElement* elt = static_cast<const DOMElement*> (child);
	      if (not XMLString::compareIString(elt->getNodeName(),
						str_generator))
		{
		  const XMLCh*		v = elt->getAttribute(str_value);
		  std::stringstream	s;
		  letter_t		i;

		  s << xml2str(v);
		  s >> i;
		  alphabet.insert(i);
		}
	    }
	  child = child->getNextSibling();
	}

      // Return a fresh structure.
      return
	automata_set_t (series_set_t (semiring_t (), monoid_t (alphabet)));
    }

    /*------------------.
    | Value conversions |
    `------------------*/

    template <class S, class T>
    xml_automaton_impl_t
    op_convert(const xml_automata_set_t& xs, const xml_automaton_impl_t& ,
	       const AutomataBase<S>&	 s,  const T&			 v)
    {
      using namespace xercesc;

      typedef Element<S, T> automaton_t;
      AUTOMATON_TYPES(automaton_t);

      // FIXME: We should not modify the structure from here.
      // FIXME: Damn, those casts are ugly.
      const_cast<xml_automata_set_t&> (xs)
	.semiring()->setAttribute(str_set,
				  attr_semiring_impl<semiring_elt_value_t>
				  ::getstr());
      const_cast<xml_automata_set_t&> (xs)
	.monoid()->setAttribute(str_type,
				attr_monoid_impl<monoid_elt_value_t>
				::getstr());

      xml_automaton_impl_t a;

      if_tag<tag_t>::set_root(a.root(), op_tag(s.self(), v));
      if_tag<tag_t>::set_structure(a.structure(), op_tag(s.self(), v));

      // Create states.
      if_tag<tag_t>::set_states(a.states(), op_tag(s.self(), v));
      for_each_state(i, v) // FIXME: That macro should not be used on values.
	{
	  DOMElement* h =
	    if_tag<tag_t>::add_state(a, *i, op_tag(s.self(), v));

	  if_tag<tag_t>::set_state(h, *i, op_tag(s.self(), v));
	}

      // Create edges.
      if_tag<tag_t>::set_edges(a.edges(), op_tag(s.self(), v));
      for_each_edge(i, v)  // FIXME: That macro should not be used on values.
	{
	  a.add_edge(op_origin_of(s.self(), v, *i),
		     op_aim_of(s.self(), v, *i),
		     op_convert(s.series(),
				SELECT(xml_value_t),
				op_label_of(s.self(), v, *i)));

	  if_tag<tag_t>::set_edge(a.edges_nodes_[*i], *i, op_tag(s.self(), v));
	}

      series_set_elt_t zero = s.series().zero(SELECT(series_set_elt_value_t));

      // Set initials.
      if_tag<tag_t>::set_initials(a.initials(), op_tag(s.self(), v));
      for_each_initial_state(i, v)
	{
	  series_set_elt_t w = op_get_initial(s.self(), v, *i);
	  if_tag<tag_t>::set_initial(a.set_initial(*i, w, zero),
				     *i, op_tag(s.self(), v));
	}

      // Set finals.
      if_tag<tag_t>::set_finals(a.finals(), op_tag(s.self(), v));
      for_each_final_state(i, v)
	{
	  series_set_elt_t w = op_get_final(s.self(), v, *i);
	  if_tag<tag_t>::set_final(a.set_final(*i, w, zero),
				   *i, op_tag(s.self(), v));
	}

      return a;
    }

    template <class S, class T>
    T
    op_convert(const AutomataBase<S>&	 s,  const T&			 ,
	       const xml_automata_set_t& xs, const xml_automaton_impl_t& xv)

    {
      using namespace xercesc;

      typedef Element<S, T> automaton_t;
      AUTOMATON_TYPES(automaton_t);

      T a;

      // Semiring implementation check.
      if (xs.semiring()->hasAttribute(str_set) and
	  XMLString::compareIString(xs.semiring()
				    ->getAttribute(str_set),
				    attr_semiring_impl<semiring_elt_value_t>
				    ::getstr()))
	FAIL("Bad semiring");

      // Monoid implementation check.
      if (xs.monoid()->hasAttribute(str_type) and
	  XMLString::compareIString(xs.monoid()
				    ->getAttribute(str_type),
				    attr_monoid_impl<monoid_elt_value_t>
				    ::getstr()))
	FAIL("Bad monoid");

      // Mystic tag stuff.
      if_tag<tag_t>::get_root(xv.root(), op_tag(s.self(), a));
      if_tag<tag_t>::get_structure(xv.structure(), op_tag(s.self(), a));

      // Create states.
      // FIXME: That method is an ugly hack and should be done a better way.
      if_tag<tag_t>::get_states(xv.states(), op_tag(s.self(), a));
      {
	typedef
	  typename std::map<hstate_t, std::string>::const_iterator
	  const_iterator;

	for (const_iterator i = xv.snum2name_.begin();
	     i != xv.snum2name_.end();
	     ++i)
	  while (not op_has_state(s.self(), a, i->first))
	    op_add_state(s.self(), a);
	for_each_state(i, a) // FIXME: That macro should not be used.
	  if (not xv.has_state(*i))
	    op_del_state(s.self(), a, *i);
      }

      // Get states tag.
      DOMNode* child = xv.states()->getFirstChild();
      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*> (child);
	      if (not XMLString::compareIString(elt->getNodeName(), str_state)
		  and elt->hasAttribute(str_name))
		{
		  const std::string t = xml2str(elt->getAttribute(str_name));

		  if_tag<tag_t>::get_state(elt,
					   xv.sname2num_.find(t)->second,
					   op_tag(s.self(), a));
		}
	    }
	  child = child->getNextSibling();
	}

      // Create edges.
      if_tag<tag_t>::get_edges(xv.edges(), op_tag(s.self(), a));
      child = xv.edges()->getFirstChild();

      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*> (child);
	      if (not XMLString::compareIString(elt->getNodeName(), str_edge)
		  and elt->hasAttribute(str_src)
		  and elt->hasAttribute(str_dst)
		  and elt->hasAttribute(str_label))
		{
		  const XMLCh*	src = elt->getAttribute(str_src);
		  const XMLCh*	dst = elt->getAttribute(str_dst);
		  const XMLCh*	lbl = elt->getAttribute(str_label);

		  std::string str = xml2str(lbl);
		  if (elt->hasAttribute(str_weight))
		    {
		      const XMLCh* weight = elt->getAttribute(str_weight);
		      str = str + " " + xml2str(weight);
		    }

		  typedef
		    rat::exp<monoid_elt_value_t, semiring_elt_value_t>
		    krat_exp_impl_t;
		  typedef Element<series_set_t, krat_exp_impl_t> krat_exp_t;

		  krat_exp_t exp (s.series());
		  parse(str, exp);

		  hedge_t e =
		    op_add_series_edge(s.self(), a,
				       xv.sname2num_.find(xml2str(src))
				       ->second,
				       xv.sname2num_.find(xml2str(dst))
				       ->second,
				       exp);

		  if_tag<tag_t>::get_edge(elt, e, op_tag(s.self(), a));
		}
	    }
	  child = child->getNextSibling();
	}

      // Set initials.
      if_tag<tag_t>::get_initials(xv.initials(), op_tag(s.self(), a));
      child = xv.initials()->getFirstChild();
      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*> (child);
	      if (not XMLString::compareIString(elt->getNodeName(),
						str_initial) and
		  elt->hasAttribute(str_state))
		{
		  const XMLCh* state = elt->getAttribute(str_state);
		  const XMLCh* label = elt->getAttribute(str_label);
		  std::string l;
		  if (elt->hasAttribute(str_weight))
		    {
		      const XMLCh* weight = elt->getAttribute(str_weight);
		      l = "(" + xml2str(weight) + " " + xml2str(label) + ")";
		    }
		  else
		    l = xml2str(label);

		  const hstate_t h =
		    xv.sname2num_.find(xml2str(state))->second;
		  op_set_initial(s.self(), a, h,
				 series_set_elt_t (s.series(),
						   xml_value_t (l)));

		  if_tag<tag_t>::get_initial(elt, h, op_tag(s.self(), a));
		}
	    }
	  child = child->getNextSibling();
	}

      // Set finals.
      if_tag<tag_t>::get_finals(xv.finals(), op_tag(s.self(), a));
      child = xv.finals()->getFirstChild();
      while (child)
	{
	  if (child->getNodeType() == DOMNode::ELEMENT_NODE)
	    {
	      DOMElement* elt = static_cast<DOMElement*> (child);
	      if (not XMLString::compareIString(elt->getNodeName(), str_final)
		  and elt->hasAttribute(str_state))
		{
		  const XMLCh* state = elt->getAttribute(str_state);
		  const XMLCh* label = elt->getAttribute(str_label);
		  std::string l;
		  if (elt->hasAttribute(str_weight))
		    {
		      const XMLCh* weight = elt->getAttribute(str_weight);
		      l = "(" + xml2str(weight) + " " + xml2str(label) + ")";
		    }
		  else
		    l = xml2str(label);

		  const hstate_t h =
		    xv.sname2num_.find(xml2str(state))->second;
		  op_set_final(s.self(), a, h,
			       series_set_elt_t (s.series(),
						 xml_value_t (l)));

		  if_tag<tag_t>::get_final(elt, h, op_tag(s.self(), a));
		}
	    }
	  child = child->getNextSibling();
	}

      return a;
    }

    /*-----------.
    | Assignment |
    `-----------*/

    template <typename S>
    void
    op_assign(AutomataBase<S>&		lhs,
	      const xml_automata_set_t&	rhs)
    {
      lhs.self() = op_convert(lhs.self(), rhs);
    }

    template <typename S, typename T>
    void
    op_assign(const AutomataBase<S>&		lhs_s,
	      const xml_automata_set_t&		rhs_s,
	      T&				lhs_v,
	      const xml_automaton_impl_t&	rhs_v)
    {
      lhs_v = op_convert(lhs_s, lhs_v, rhs_s, rhs_v);
    }

    /*---------------------.
    | Conversion of series |
    `---------------------*/

    template <typename S, typename T>
    T
    op_convert(const algebra::SeriesBase<S>& s,
	       const T&,
	       const xml_value_t& v)
    {
      typedef Element<S, T>				series_set_elt_t;
      typedef
	typename series_set_elt_t::monoid_elt_value_t	monoid_elt_value_t;
      typedef
	typename series_set_elt_t::semiring_elt_value_t	semiring_elt_value_t;

      typedef
	rat::exp<monoid_elt_value_t, semiring_elt_value_t>
	krat_exp_impl_t;
      typedef Element<S, krat_exp_impl_t>		krat_exp_t;

      krat_exp_t exp (s.self());
      parse(v.value(), exp);

      return op_convert(s.self(), SELECT(T),
			// FIXME: Why the hell is that cast needed?!
			// FIXME: The linker fails when it is not here.
			static_cast<krat_exp_impl_t> (exp.value()));
    }

    template<typename S, typename T>
    xml_value_t
    op_convert(const algebra::SeriesBase<S>& s,
	       SELECTOR(xml_value_t),
	       const T& p)
    {
      std::ostringstream o;
      op_rout(s.self(), o, p);

      return xml_value_t (o.str());
    }

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_XML_OPS_HXX
