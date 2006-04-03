// tools.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_TOOLS_HXX
# define VCSN_XML_TOOLS_HXX
/**
 * @file tools.hxx
 *
 * Some useful utility functions.
 *
 *
 * @see vcsn::xml::xml_converter, vcsn::xml::Node
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

namespace vcsn
{
  namespace xml
  {
    /*----------------.
    | Converter tools |
    `----------------*/
    namespace tools
    {
      template <class S, class T, class U>
      void add_label(xercesc::DOMElement* elt,
		     const Element<S, T>&,
		     const U& series)
      {
	std::string label = get_label(series);

	if (label.size())
	  elt->setAttribute(STR2XML("label"),
			    STR2XML(label.c_str()));
      }

      template <class S, class T, class U, class M1, class M2>
      void add_label(xercesc::DOMElement* elt,
		     const FMPtype&,
		     const U& series)
      {
	std::string out;
	if (series.supp().size() > 1)
	  {
	    out = get_label(series);
	    if (out.size())
	      elt->setAttribute(STR2XML("label"),
				STR2XML(out.c_str()));
	  }
	else
	  {
	    std::string in_word =
	      get_label((*(series.supp().begin())).first);
	    std::string out_word =
	      get_label((*(series.supp().begin())).second);
	    std::string mult =
	      get_label(series.get(*(series.supp().begin())));
	    if (mult.size())
	      out = mult;
	    if (out != "" && out_word.size())
	      out += " ";
	    if (out_word.size())
	      out += out_word;

	    if (in_word.size())
	      elt->setAttribute(STR2XML("in"),
				STR2XML(in_word.c_str()));
	    if (out.size())
	      elt->setAttribute(STR2XML("out"),
				STR2XML(out.c_str()));
	  }
      }

      template <class S, class T, class U>
      void add_label(xercesc::DOMElement* elt,
		     const Element<Transducer<S>, T>&,
		     const U& series)
      {
	std::string in = get_label(*(series.supp().begin()));
	std::string out = get_label((series.get(*(series.supp().begin()))));

	if (in.size() && in != "1")
	  elt->setAttribute(STR2XML("in"),
			    STR2XML(in.c_str()));
	if (out.size() && out != "1")
	  elt->setAttribute(STR2XML("out"),
			    STR2XML(out.c_str()));
      }

      template <class L>
      const char*	get_label(const L& l)
      {
	std::ostringstream os;
	os << l;
	return os.str().c_str();
      }

      const char*	get_label(const bool& l)
      {
	if (l)
	  return "";
	return "0";
      }


      const char* get_label(const std::pair<std::string, std::string>& l)
      {
	std::ostringstream os;
	os << "(" << l.first << ", " << l.second << ")";
	return os.str().c_str();
      }

      template <class S, class Series>
      const char*	get_label(const Element<Series,
				  vcsn::algebra::polynom<S, bool> >& l)
      {
	std::ostringstream os;
	typedef typename Element<Series,
	  vcsn::algebra::polynom<S, bool> >::support_t::const_iterator iter;

	iter i = l.supp().begin();
	if (l.supp().size() > 0)
	  {
	    os << get_label(*(i++));
	    for (; i != l.supp().end(); ++i)
	      os << "+" << get_label(*i);
	  }
	else
	  os << "0";

	return os.str().c_str();
      }


      template <class A>
      void create_alphabet(const A& alphabet, xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root)
      {
	typedef typename A::const_iterator alphabet_iterator;
	for_each_letter(l, alphabet)
	  {
	    std::ostringstream letter;
	    xercesc::DOMElement* gen =
	      doc->createElement(STR2XML("generator"));
	    letter << *l;
	    gen->setAttribute(STR2XML("value"), STR2XML(letter.str().c_str()));
	    root->appendChild(gen);
	  }
      }

      template <class M>
      xercesc::DOMElement* create_monoid(const M& monoid,
					 xercesc::DOMDocument* doc,
					 xercesc::DOMElement* elt)
      {
	xercesc::DOMElement* m = doc->createElement(STR2XML("monoid"));
	m->setAttribute(STR2XML("type"), STR2XML(get_monoid_type(monoid)));
	m->setAttribute(STR2XML("generators"), STR2XML("letters"));
	elt->appendChild(m);

	return m;
      }

      template <class A, class S>
      xercesc::DOMElement* create_semiring(const A&,
					   const S& semiring,
					   xercesc::DOMDocument* doc,
					   xercesc::DOMElement* elt)
      {
	typedef typename A::series_set_elt_t::semiring_elt_t::value_t value_t;

	xercesc::DOMElement* s = doc->createElement(STR2XML("semiring"));

	if (get_semiring_set(semiring, value_t()) != "ratSeries")
	s->setAttribute(STR2XML("operations"),
			STR2XML(get_semiring_operations(semiring)));
	s->setAttribute(STR2XML("set"),
			STR2XML(get_semiring_set(semiring, value_t())));
	elt->appendChild(s);

	return s;
      }

      template <class S, class T>
      xercesc::DOMElement*
      create_semiring(const Element<Transducer<S>, T>&,
		      const vcsn::algebra::NumericalSemiring& semiring,
		      xercesc::DOMDocument* doc,
		      xercesc::DOMElement* elt)
      {
	typedef typename
	  Element<Transducer<S>, T>::series_set_elt_t::semiring_elt_t::semiring_elt_t::value_t value_t;

	xercesc::DOMElement* s = doc->createElement(STR2XML("semiring"));
	s->setAttribute(STR2XML("operations"), STR2XML("numerical"));
	s->setAttribute(STR2XML("set"),
			STR2XML(get_semiring_set(semiring, value_t())));
	elt->appendChild(s);

	return s;
      }


    /**
     * Tools to generate automaton labels from string, and to ensure type
     * compatibility.
     *
     */
# define GET_SEMIRING_SET(T, Value)			\
    template <class S>					\
    const char* get_semiring_set(const S&, const T&)	\
    { return Value; }

      // Default.
      template <class S, class T>
      const char* get_semiring_set(const S&, const T&)
      { return "undefined"; }

      // Transducer on P(B*).
      template <class S, class U, class V>
      const char* get_semiring_set(const S&,
				   const vcsn::rat::exp<U, V>&)
      { return "ratSeries"; }

GET_SEMIRING_SET(bool, "B")
GET_SEMIRING_SET(double, "R")
GET_SEMIRING_SET(float, "R")
GET_SEMIRING_SET(int, "Z")

	// Deals with the "operation" attribute of <semiring> tag.
# define GET_SEMIRING_OPERATIONS(S, Value)		\
    const char* get_semiring_operations(const S&)	\
    { return Value; }

      // Default.
      template <class S>
      const char* get_semiring_operations(const S&)
      { return "undefined"; }

GET_SEMIRING_OPERATIONS(vcsn::algebra::NumericalSemiring, "numerical")
GET_SEMIRING_OPERATIONS(vcsn::z_max_plus_automaton::semiring_t, "tropicalMax")
GET_SEMIRING_OPERATIONS(vcsn::z_min_plus_automaton::semiring_t, "tropicalMin")


      // Deal with the "type" attribute of <monoid> tag.
      // Default.
      template <class S>
      const char* get_monoid_type(const S&)
      { return "undefined"; }

      template <class S>
      const char* get_monoid_type(const vcsn::algebra::FreeMonoid<S>&)
      { return "free"; }

      template <class S1, class S2>
      const char*
      get_monoid_type(const vcsn::algebra::FreeMonoidProduct<S1, S2>&)
      { return "product"; }


      /**
       * Get series from a XML node.
       *
       * @return	series_set_elt_t
       *
       * @param T	Type of the automaton.
       *
       * @arg node	XML node.
       * @arg aut	Automaton to store series.
       *
       */
      template <class T>
      typename T::series_set_elt_t
      get_series(xercesc::DOMElement* node, T& aut)
      {
	typedef typename
	  rat::exp<typename T::monoid_elt_value_t,
	  typename T::semiring_elt_value_t> krat_exp_impl_t;
	typedef Element<typename T::series_set_t, krat_exp_impl_t> krat_exp_t;

	krat_exp_t res (aut.structure().series());
	if (xml2str(node->getAttribute(STR2XML("label"))) == "")
	  return
	    vcsn::algebra::identity_as<typename T::series_set_elt_t::value_t>
	    ::of(aut.structure().series());
	parse(xml2str(node->getAttribute(STR2XML("label"))), res);

	return res;
      }


      TParmFMP
      typename FMPtype::series_set_elt_t
      get_series(xercesc::DOMElement* node, FMPtype& a)
      {
 	typename FMPtype::series_set_elt_t res(a.structure().series());

	parse_label(node, a,
		    a.structure().series().monoid().first_monoid().alphabet(),
		    a.structure().series().monoid().second_monoid().alphabet(),
		    res);

	return res;
      }


      TParm
      typename TRANStype::series_set_elt_t
      get_series(xercesc::DOMElement* node,
		 TRANStype& a)
      {
 	typename TRANStype::series_set_elt_t res(a.structure().series());

	parse_label(node, a,
		    a.structure().series().monoid().alphabet(),
		    a.structure().series().semiring().monoid().alphabet(),
		    res);

	return res;
      }


      template <class S, class T, class E1, class E2, class R>
      void assoc_exp(TRANStype& a, E1& i_exp, E2& o_exp, R& res,
		     bool i_res, bool o_res)
      {
	typedef typename TRANStype::monoid_elt_t::value_t md_value_t;
	typedef typename TRANStype::semiring_elt_t::value_t sg_value_t;
	typename TRANStype::monoid_elt_t m(a.structure().series().monoid());

	if (! i_res && i_exp.supp().size())
	    m = *(i_exp.supp().begin());
	else
	  m = vcsn::algebra::identity_as<md_value_t>
	    ::of(a.structure().series().monoid());

	if (! o_res && ! o_exp.supp().size())
	  res.assoc(m,
		    vcsn::algebra::identity_as<sg_value_t>
		    ::of(a.structure().series().semiring()));
	else
	  res.assoc(m, o_exp);
      }


      template <class S, class T, class M1, class M2,
		class E1, class E2, class R>
      void assoc_exp(FMPtype& a, E1& i_exp, E2& o_exp, R& res,
		     bool i_res, bool o_res)
      {
	typename FMPtype::monoid_elt_t m(a.structure().series().monoid());
	typename FMPtype::monoid_elt_t::first_monoid_elt_value_t m1("");
	typename FMPtype::monoid_elt_t::second_monoid_elt_value_t m2("");
	typename FMPtype::semiring_elt_value_t sem = 1;
	typedef typename FMPtype::monoid_elt_t::first_monoid_elt_t::value_t
	  md_value_t;
	typedef typename FMPtype::semiring_elt_value_t sg_value_t;

	if (! i_res && i_exp.supp().size())
	  m1 = *(i_exp.supp().begin());
	else
	  m1 = vcsn::algebra::identity_as<md_value_t>
	    ::of(a.structure().series().monoid().first_monoid()).value();

	if (! o_res && o_exp.supp().size())
	  {
	    m2 = *(o_exp.supp().begin());
	    sem = o_exp.get(m2);
	  }
	else
	  {
	    m2 = vcsn::algebra::identity_as<md_value_t>
	      ::of(a.structure().series().monoid().second_monoid()).value();
	    sem = vcsn::algebra::identity_as<sg_value_t>
	      ::of(a.structure().series().semiring()).value();
	  }
	m = std::make_pair(m1, m2);
  	res.assoc(m, sem);
      }


      template <class A, class A1, class A2, class S>
      void parse_label(xercesc::DOMElement* node, A& a,
		       const A1& alphabet1, const A2& alphabet2, S& res)
      {
	using namespace vcsn::r_automaton;
	automaton_t bin = new_automaton(alphabet1);
 	automaton_t bout = new_automaton(alphabet2);
 	rat_exp_t i_exp(bin.structure().series());
 	rat_exp_t o_exp(bout.structure().series());

	std::pair<bool, std::string> i_res;
	std::pair<bool, std::string> o_res;

	if (node->hasAttribute(STR2XML("label")))
	  {
	    std::string label = xml2str(node->getAttribute(STR2XML("label")));
	    std::string in, out;
	    unsigned int pos = label.find("|");
	    if (pos != std::string::npos)
	      {
		in = label.substr(0, pos);
		out = label.substr(pos + 1);
		i_res = parse(in, i_exp);
		o_res = parse(out, o_exp);
	      }
	    else
	      i_res = parse(label, i_exp);
	    if (node->hasAttribute(STR2XML("weight")))
	      o_res = parse(xml2str(node->getAttribute(STR2XML("weight"))),
			    o_exp);
	  }
	else
	  {
	    if (node->hasAttribute(STR2XML("in")))
	      i_res = parse(xml2str(node->getAttribute(STR2XML("in"))),
			    i_exp);
	    if (node->hasAttribute(STR2XML("out")))
		o_res = parse(xml2str(node->getAttribute(STR2XML("out"))),
			    o_exp);
	  }
	assoc_exp(a, i_exp, o_exp, res, i_res.first, o_res.first);
      }


      /**
       * Insert a letter in an alphabet.
       *
       * @param U	Type of the letter.
       * @param V	Type of the alphabet container.
       *
       * @arg a		Alphabet to insert a letter.
       * @arg str	string containing the letter.
       *
       */
      template <class U, class V>
      void insert_letter(Element<vcsn::algebra::AlphabetSet<U>, V>&,
			 const std::string&)
      {
	FAIL("No available implementation for this type of letter");
      }

      template <class V>
      void insert_letter(Element<vcsn::algebra::AlphabetSet<char>, V>& a,
			 const std::string& str)
      {
	a.insert(str[0]);
      }


      /**
       * Check semiring conformance of the automaton w.r.t. XML node.
       *
       * @param U	Type of the semiring.
       * @param T	Type of the automaton.
       *
       * @arg node	XML node to check.
       * @arg a		Automaton.
       * @arg param	Automaton semiring.
       *
       */
      template <class T, class U>
      void ensure_semiring_type(const xercesc::DOMElement* node,
				const T&, const U& param)
      {
	typedef typename T::series_set_elt_t::semiring_elt_t::value_t value_t;

	std::string set(tools::get_semiring_set(param, value_t()));
	std::string set_ref;

	if (node && node->hasAttribute(STR2XML("set")))
	  set_ref = xml2str(node->getAttribute(STR2XML("set")));
	else
	  set_ref = "B";
	if (set_ref != set)
	  FAIL("Bad semiring");
      }


      template <class S, class T>
      void ensure_semiring_type(const xercesc::DOMElement* node,
				const Element<Transducer<S>, T>&,
				const typename Element<Transducer<S>, T>
				::semiring_t::semiring_t& param)
      {
	typedef Element<Transducer<S>, T> trans_t;
	typedef typename
	  trans_t::series_set_elt_t::semiring_elt_t::semiring_elt_t::value_t
	  value_t;

	std::string set(tools::get_semiring_set(param, value_t()));
	std::string set_ref;

	if (node && node->hasAttribute(STR2XML("set")))
	  set_ref = xml2str(node->getAttribute(STR2XML("set")));
	else
	  set_ref = "B";
	if (set_ref != set)
	  FAIL("Bad semiring");
      }


      template <class S, class T, class U>
      void ensure_semiring_type(const xercesc::DOMElement* node,
				const Element<Transducer<S>, T>&,
				const typename Element<Transducer<S>, T>
				::semiring_t& param)
      {
	typedef Element<Transducer<S>, T> trans_t;
	typedef typename
	  trans_t::series_set_elt_t::semiring_elt_t::value_t value_t;

	std::string set(tools::get_semiring_set(param, value_t()));
	std::string set_ref;

	if (node && node->hasAttribute(STR2XML("set")))
	  set_ref = xml2str(node->getAttribute(STR2XML("set")));
	else
	  set_ref = "ratSeries";
	if (set_ref != set)
	  FAIL("Bad semiring");
      }


      /**
       * Check semiring conformance of the automaton w.r.t. XML node.
       *
       * @param U	Type of the monoid.
       *
       * @arg node	XML node to check.
       * @arg param	Automaton monoid.
       *
       */
      template <class U>
      void ensure_monoid_type(const xercesc::DOMElement* node, const U& param)
      {
	std::string monoid_type = tools::get_monoid_type(param);
	std::string monoid_type_ref;

	if (! node || ! node->hasAttribute(STR2XML("type")))
	  monoid_type_ref = "free";
	else
	  monoid_type_ref = xml2str(node->getAttribute(STR2XML("type")));
	if (monoid_type_ref != monoid_type)
	  FAIL("Bad monoid type");
      }


      template <class S, class T, class U, class M1, class M2>
      void ensure_monoid_type(const xercesc::DOMElement* node,
			      const FMPtype& param)
      {
	std::string monoid_type = tools::get_monoid_type(param);
	std::string monoid_type_ref;

	if (! node || ! node->hasAttribute(STR2XML("type")))
	  monoid_type_ref = "product";
	else
	  monoid_type_ref = xml2str(node->getAttribute(STR2XML("type")));
	if (monoid_type_ref != monoid_type)
	  FAIL("Bad monoid type");
      }


      template <class OStream>
      void print_transition(const xercesc::DOMElement* n,
			    OStream& os,
			    std::string& spacing)
      {
	os << spacing << "<" << xml2str(n->getNodeName());
	if (n->hasAttribute(STR2XML("src")))
	  os << " src=\""
	     << xml2str(n->getAttribute(STR2XML("src"))) << "\"";
	if (n->hasAttribute(STR2XML("dst")))
	  os << " dst=\""
	     << xml2str(n->getAttribute(STR2XML("dst"))) << "\"";
	if (n->hasAttribute(STR2XML("label")))
	  os << " label=\""
	     << xml2str(n->getAttribute(STR2XML("label"))) << "\"";
	if (n->hasAttribute(STR2XML("weight")))
	  os << " weight=\""
	     << xml2str(n->getAttribute(STR2XML("weight"))) << "\"";
	if (n->hasAttribute(STR2XML("in")))
	  os << " in=\""
	     << xml2str(n->getAttribute(STR2XML("in"))) << "\"";
	if (n->hasAttribute(STR2XML("out")))
	  os << " out=\""
	     << xml2str(n->getAttribute(STR2XML("out"))) << "\"";
      }


      template <class OStream>
      void print_tree(const xercesc::DOMElement* node,
		      OStream& os,
		      std::string spacing)
      {
	using namespace xercesc;
	unsigned i;
	DOMNamedNodeMap* m;

	if (xml2str(node->getNodeName()) == "transition")
	  print_transition(static_cast<const DOMElement*>(node), os, spacing);
	else
	  {
	    os << spacing << "<" << xml2str(node->getNodeName());
	    for (m = node->getAttributes(), i = 0;
		 i < m->getLength(); ++i)
	      {
		os << " " << xml2str(m->item(i)->getNodeName())
		   << "=\"" << xml2str(m->item(i)->getNodeValue())
		   << "\"";
	      }
	  }
	if (node->hasChildNodes())
	  os << ">";
	else
	  os << "/>";
	os << std::endl;
	for (DOMNode* n = node->getFirstChild(); n; n = n->getNextSibling())
	  if (n->getNodeType() == DOMNode::ELEMENT_NODE)
	    print_tree(static_cast<const DOMElement*>(n), os, spacing + "  ");
	if (node->hasChildNodes())
	  os << spacing << "</" << xml2str(node->getNodeName()) << ">"
	     << std::endl;
      }


      /**
       * Print XML tree to output stream.
       *
       * @param OStream	Type of output stream.
       *
       * @arg node	XML root node to print.
       * @arg os	Output stream.
       *
       */
      template <class OStream>
      void print_document(xercesc::DOMElement* node, OStream& os)
      {
	node->setAttribute(STR2XML("xmlns"),
			   STR2XML("http://vaucanson.lrde.epita.fr"));
	print_tree(node, os, "");
      }


    } // ! tools

  } // ! xml

} // ! vcsn


# undef GET_FREEMONOID_TYPE
# undef GET_SEMIRING_OPERATIONS
# undef GET_SEMIRING_SET
# undef AUTtype
# undef TRANStype
# undef FMPtype
# undef TParm
# undef TParmFMP

#endif // ! VCSN_XML_TOOLS_HXX
