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

    namespace tools
    {

    /*--------------------------------------.
    | Extract information about the types.  |
    `--------------------------------------*/

      /**
       * Tools to generate automaton labels from string, and to ensure type
       * compatibility.
       *
       */
      // Default.
      template <class S, class T>
      const char* get_semiring_set(const S&, const T&)
      { return "undefined"; }

# define GET_SEMIRING_SET(T, Value)			\
      template <class S>				\
      const char* get_semiring_set(const S&, const T&)	\
      { return Value; }

      GET_SEMIRING_SET(bool, "B")
      GET_SEMIRING_SET(double, "R")
      GET_SEMIRING_SET(float, "R")
      GET_SEMIRING_SET(int, "Z")
# undef GET_SEMIRING_SET

      // Transducer on P(B*).
      template <class S, class U, class V>
      const char* get_semiring_set(const S&,
				   const vcsn::rat::exp<U, V>&)
      { return "ratSeries"; }



      // Deals with the "operation" attribute of <semiring> tag.
      // Default.
      template <class S>
      const char* get_semiring_operations(const S&)
      { return "undefined"; }

# define GET_SEMIRING_OPERATIONS(S, Value)			\
      template <>						\
      inline const char* get_semiring_operations<S>(const S&)	\
      { return Value; }

      GET_SEMIRING_OPERATIONS(vcsn::algebra::NumericalSemiring,
			      "numerical")
      GET_SEMIRING_OPERATIONS(vcsn::z_max_plus_automaton::semiring_t,
			      "tropicalMax")
      GET_SEMIRING_OPERATIONS(vcsn::z_min_plus_automaton::semiring_t,
			      "tropicalMin")
# undef GET_SEMIRING_OPERATIONS



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


    /*---------.
    | Automata |
    `---------*/

    // Useful abbreviation to circumvent the impossibility to define
    // parametric typedefs.
# define AUTtype				\
    Element<Automata<S>, T>
# define TRANStype				\
    Element<Transducer<S>, T>
# define FMPtype      							  \
    Element<								  \
      Automata<								  \
      vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> > \
      >, T								  \
    >


      // Add the label as a string attribute
      template <class S, class T, class U>
      void add_label(xercesc::DOMElement* elt,
		     const Element<S, T>&,
		     const U& series)
      {
	std::string label = get_label(series);

	if (label.size())
	  elt->setAttribute(transcode("label"),
			    transcode(label));
      }

      // Add the label as an xml node
      template <class S, class T, class U>
      void add_xml_label(xercesc::DOMDocument* doc,
			 xercesc::DOMElement* elt,
			 const Element<S, T>& a,
			 const U& series)
      {
	typedef Element<S,T> automaton_t;
	typedef typename
	  rat::exp<typename automaton_t::monoid_elt_value_t,
	  typename automaton_t::semiring_elt_value_t> krat_exp_impl_t;
	typedef Element<typename automaton_t::series_set_t, krat_exp_impl_t> krat_exp_t;


	std::string label = get_label(series);
	if (label.size())
	{
	  krat_exp_t res (a.structure().series());
	  parse(label, res);
	  elt->appendChild(res.value().xml_tree(doc, "label"));
	}
      }


    /*----------------.
    | FMP Transducers |
    `----------------*/

      // Add the label as a string attribute
      template <class S, class T, class U, class M1, class M2>
      void add_label(xercesc::DOMElement* elt,
		     const FMPtype&,
		     const U& series)
      {
	if (series.supp().size() > 1)
	{
	  std::string out = get_label(series);
	  if (out.size())
	    elt->setAttribute(transcode("label"),
			      transcode(out));
	}
	else
	{
	  std::string in_word = get_label(series.supp()->first);
	  std::string out_word = get_label(series.supp()->second);
	  std::string mult = get_label(series.get(*(series.supp().begin())));
	  std::string out;
	  if (mult.size())
	    out = mult;
	  if (out != "" && out_word.size())
	    out += " ";
	  if (out_word.size())
	    out += out_word;

	  if (in_word.size())
	    elt->setAttribute(transcode("in"),
			      transcode(in_word));
	  if (out.size())
	    elt->setAttribute(transcode("out"),
			      transcode(out));
	}
      }

      // Add the label as an xml node
      template <class S, class T, class U, class M1, class M2>
      void add_xml_label(xercesc::DOMDocument* doc,
			 xercesc::DOMElement* elt,
			 const FMPtype& a,
			 const U& series)
      {
	std::string out;
	if (series.supp().size() > 1)
	{
	  out = get_label(series);
	  if (out.size())
	    elt->setAttribute(transcode("label"),
			      transcode(out));
	}
	else
	{
	  std::string in_word = get_label(series.supp()->first);
	  std::string out_word = get_label(series.supp()->second);
	  std::string mult = get_label(series.get(*(series.supp().begin())));

	  if (in_word.size() && in_word != "1")
	  {
	    using namespace vcsn::r_automaton;
	    automaton_t bin = make_automaton(
	      a.structure().series().monoid().first_monoid().alphabet());
	    rat_exp_t res_in(bin.structure().series());
	    parse(in_word, res_in);
	    elt->appendChild(res_in.value().xml_tree(doc, "in"));
	  }
	  if (out_word.size() && out_word != "1")
	  {
	    using namespace vcsn::r_automaton;
	    automaton_t bout = make_automaton(
	      a.structure().series().monoid().second_monoid().alphabet());
	    rat_exp_t res_out(bout.structure().series());
	    parse(out_word, res_out);
	    xercesc::DOMElement* out_node =
	      res_out.value().xml_tree(doc, "out");
	    if (mult.size())
	      out_node->setAttribute(transcode("weight"), transcode(mult));
	    elt->appendChild(out_node);
	  }
	}
      }


    /*---------------------.
    | Transducers on P(B*) |
    `---------------------*/

      // Add the label as a string attribute
      template <class S, class T, class U>
      void add_label(xercesc::DOMElement* elt,
		     const Element<Transducer<S>, T>&,
		     const U& series)
      {
	std::string in = get_label(*(series.supp().begin()));
	std::string out = get_label(series.get(*(series.supp().begin())));

	if (in.size() && in != "1")
	  elt->setAttribute(transcode("in"),
			    transcode(in));
	if (out.size() && out != "1")
	  elt->setAttribute(transcode("out"),
			    transcode(out));
      }

      // Add the label as an xml node
      template <class S, class T, class U>
      void add_xml_label(xercesc::DOMDocument* doc,
			 xercesc::DOMElement* elt,
			 const Element<Transducer<S>, T>& a,
			 const U& series)
      {
	std::string in = get_label(*(series.supp().begin()));
	std::string out = get_label(series.get(*(series.supp().begin())));

	if (in.size() && in != "1")
	{
	  using namespace vcsn::r_automaton;
	  automaton_t bin = make_automaton(
	    a.structure().series().monoid().alphabet());
	  rat_exp_t res_in(bin.structure().series());
	  parse(in, res_in);
	  elt->appendChild(res_in.value().xml_tree(doc, "in"));
	}
	if (out.size() && out != "1")
	{
	  using namespace vcsn::r_automaton;
	  automaton_t bout = make_automaton(
	    a.structure().series().semiring().monoid().alphabet());
	  rat_exp_t res_out(bout.structure().series());
	  parse(out, res_out);
	  elt->appendChild(res_out.value().xml_tree(doc, "out"));
	}
      }


      template <class L>
      const std::string	get_label(const L& l)
      {
	std::ostringstream os;
	os << l;
	return os.str();
      }

      inline const std::string get_label(const bool& l)
      {
	if (l)
	  return "";
	return "0";
      }


      inline const std::string get_label(const std::pair<std::string, std::string>& l)
      {
	std::ostringstream os;
	os << "(" << l.first << ", " << l.second << ")";
	return os.str().c_str();
      }

      template <class S, class Series>
      const std::string	get_label(const Element<Series,
				  vcsn::algebra::polynom<S, bool> >& l)
      {
	std::ostringstream os;
	os << l;
	if (os.str() == "1")
	  return "";
	return os.str();
      }


      template <class A>
      void create_alphabet(const A& alphabet, xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root)
      {
	typedef typename A::const_iterator alphabet_iterator;
	for_all_letters(l, alphabet)
	{
	  std::ostringstream letter;
	  xercesc::DOMElement* gen =
	    doc->createElement(transcode("generator"));
	  letter << *l;
	  gen->setAttribute(transcode("value"), transcode(letter.str().c_str()));
	  root->appendChild(gen);
	}
      }

      template <class M>
      xercesc::DOMElement* create_monoid(const M& monoid,
					 xercesc::DOMDocument* doc,
					 xercesc::DOMElement* elt)
      {
	xercesc::DOMElement* m = doc->createElement(transcode("monoid"));
	m->setAttribute(transcode("type"), transcode(get_monoid_type(monoid)));
	m->setAttribute(transcode("generators"), transcode("letters"));
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

	xercesc::DOMElement* s = doc->createElement(transcode("semiring"));

	if (get_semiring_set(semiring, value_t()) != "ratSeries")
	  s->setAttribute(transcode("operations"),
			  transcode(get_semiring_operations(semiring)));
	s->setAttribute(transcode("set"),
			transcode(get_semiring_set(semiring, value_t())));
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

	xercesc::DOMElement* s = doc->createElement(transcode("semiring"));
	s->setAttribute(transcode("operations"), transcode("numerical"));
	s->setAttribute(transcode("set"),
			transcode(get_semiring_set(semiring, value_t())));
	elt->appendChild(s);

	return s;
      }


# define VCSN_XML_NO_TYPE ""
# define VCSN_XML_SUM_TYPE "+"
# define VCSN_XML_PRODUCT_TYPE "."

      template <class T>
      std::string
      get_rec_xml_series(xercesc::DOMNode* n, T& aut,
			 std::string op_type = VCSN_XML_NO_TYPE,
			 std::string res = "")
      {
	xercesc::DOMElement* element_n;
	std::string next_op_type;

	if (!n)
	  return res;
	for (; n; n = n->getNextSibling())
	{
	  if (n->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
	  {
	    element_n = (static_cast<xercesc::DOMElement*>(n));

	    if (xml2str(n->getNodeName()) == "sum")
	      next_op_type = VCSN_XML_SUM_TYPE;
	    if (xml2str(n->getNodeName()) == "product")
	      next_op_type = VCSN_XML_PRODUCT_TYPE;

	    // Add weight (and opening brace if complex expression).
	    if (element_n->hasAttribute(transcode("weight")))
	      res += xml2str(element_n->getAttribute(transcode("weight")))
		+ " ";

	    // Add opening brace if attribute,complex weighted
	    // expression, sum in product, product in sum or star.
	    if ((element_n->hasAttribute(transcode("parenthesis")) &&
		 xml2str(element_n->getAttribute(transcode("parenthesis")))
		 == "true")
		|| ((element_n->hasAttribute(transcode("weight")))
		    && (xml2str(n->getNodeName()) != "word"))
		|| ((xml2str(n->getNodeName()) == "sum")
		    && (op_type == VCSN_XML_PRODUCT_TYPE))
		|| ((xml2str(n->getNodeName()) == "product")
		    && (op_type == VCSN_XML_SUM_TYPE))
		|| (xml2str(n->getNodeName()) == "star"))
	      res += "(";

	    // Word, zero or identity
	    if (xml2str(n->getNodeName()) == "word")
	      res += xml2str(element_n->getAttribute(transcode("value")));
	    if (xml2str(n->getNodeName()) == "zero")
	      res += "1";
	    if (xml2str(n->getNodeName()) == "identity")
	      res += "0";

	    // Recursive call
	    if (n->hasChildNodes())
	      res += get_rec_xml_series(n->getFirstChild(),
					aut, next_op_type);

	    // Add closing brace if parenthesis attribute
	    if ((element_n->hasAttribute(transcode("parenthesis")) &&
		 xml2str(element_n->getAttribute(transcode("parenthesis")))
		 == "true")
		// Or star/weight...
		|| ((((element_n->hasAttribute(transcode("star")))
		      && (xml2str(element_n->getAttribute(transcode("star")))
			  == "true"))
		     || (element_n->hasAttribute(transcode("weight"))))
		    // ...in a complex expression
		    && (xml2str(n->getNodeName()) != "word"))
		// Or a sum in a product
		|| ((xml2str(n->getNodeName()) == "sum")
		    && (op_type == VCSN_XML_PRODUCT_TYPE))
		// Or a product in a sum
		|| ((xml2str(n->getNodeName()) == "product")
		    && (op_type == VCSN_XML_SUM_TYPE))
		// Or star.
		|| (xml2str(n->getNodeName()) == "star"))
	      res += ")";

	    // Add star
	    if (xml2str(n->getNodeName()) == "star")
	      res += "*";

	    // Add operator
	    if ((n->getNextSibling())
		&& (n->getNextSibling()->getNextSibling()))
	      res += op_type;
	  }
	}
	return res;
      }


      /**
       * Get series from a XML label node.
       *
       * @arg \c T	Type of the automaton.
       *
       * @return	series_set_elt_t
       *
       * @param node	XML node.
       * @param aut	Automaton to store series.
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
	std::string str_res;
	krat_exp_t res (aut.structure().series());
	xercesc::DOMNode* n = node->getFirstChild();
	if (n && n->getNextSibling()
	    && (xml2str(n->getNextSibling()->getNodeName()) == "label"))
	  str_res = get_rec_xml_series(n, aut);
	if (str_res == "")
	{
	  if (xml2str(node->getAttribute(transcode("label"))) == "")
	    return
	      vcsn::algebra::identity_as<typename T::series_set_elt_t::value_t>
	      ::of(aut.structure().series());
	  else
	    parse(xml2str(node->getAttribute(transcode("label"))), res);
	}
	else
	  parse(str_res, res);

	return res;
      }


      template <class S, class T, class M1, class M2>
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


      template <class S, class T>
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
	  m = *i_exp.supp();
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
	  m1 = *i_exp.supp();
	else
	  m1 = vcsn::algebra::identity_as<md_value_t>
	    ::of(a.structure().series().monoid().first_monoid()).value();

	if (! o_res && o_exp.supp().size())
	{
	  sem = o_exp.get(*o_exp.supp());
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
	automaton_t bin = make_automaton(alphabet1);
	automaton_t bout = make_automaton(alphabet2);
	rat_exp_t i_exp(bin.structure().series());
	rat_exp_t o_exp(bout.structure().series());
	std::string in, out;

	std::pair<bool, std::string> i_res;
	std::pair<bool, std::string> o_res;

	xercesc::DOMNode* n = node->getFirstChild();

	if (n)
	  for (; n; n = n->getNextSibling())
	  {
	    if (xml2str(n->getNodeName()) == "in" && n->getFirstChild())
	    {
	      in = get_rec_xml_series(n->getFirstChild(), a);
	      i_res = parse(in, i_exp);
	    }
	    if (xml2str(n->getNodeName()) == "out" && n->getFirstChild())
	    {
	      out = get_rec_xml_series(n->getFirstChild(), a);
	      o_res = parse(out, o_exp);
	    }
	  }
	// No expression tag
	else
	{
	  if (node->hasAttribute(transcode("label")))
	  {
	    std::string label = xml2str(node->getAttribute(transcode("label")));
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
	    if (node->hasAttribute(transcode("weight")))
	      o_res = parse(xml2str(node->getAttribute(transcode("weight"))),
			    o_exp);
	  }
	  // No expression tag, no label attribute.
	  else
	  {
	    if (node->hasAttribute(transcode("in")))
	      i_res = parse(xml2str(node->getAttribute(transcode("in"))),
			    i_exp);
	    if (node->hasAttribute(transcode("out")))
	      o_res = parse(xml2str(node->getAttribute(transcode("out"))),
			    o_exp);
	  }
	}
	assoc_exp(a, i_exp, o_exp, res, i_res.first, o_res.first);
      }


      /**
       * Insert a letter in an alphabet.
       *
       * @arg \c U	Type of the letter.
       * @arg \c V	Type of the alphabet container.
       *
       * @param a	Alphabet to insert a letter.
       * @param str	string containing the letter.
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
       * @arg \c U	Type of the semiring.
       * @arg \c T	Type of the automaton.
       *
       * @param node	XML node to check.
       * @param a		Automaton.
       * @param param	Automaton semiring.
       *
       */
      template <class T, class U>
      void ensure_semiring_type(const xercesc::DOMElement* node,
				const T&, const U& param)
      {
	typedef typename T::series_set_elt_t::semiring_elt_t::value_t value_t;

	std::string set(tools::get_semiring_set(param, value_t()));
	std::string set_ref;

	if (node && node->hasAttribute(transcode("set")))
	  set_ref = xml2str(node->getAttribute(transcode("set")));
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

	if (node && node->hasAttribute(transcode("set")))
	  set_ref = xml2str(node->getAttribute(transcode("set")));
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

	if (node && node->hasAttribute(transcode("set")))
	  set_ref = xml2str(node->getAttribute(transcode("set")));
	else
	  set_ref = "ratSeries";
	if (set_ref != set)
	  FAIL("Bad semiring");
      }


      /**
       * Check semiring conformance of the automaton w.r.t. XML node.
       *
       * @arg \c U	Type of the monoid.
       *
       * @param node	XML node to check.
       * @param param	Automaton monoid.
       *
       */
      template <class U>
      void ensure_monoid_type(const xercesc::DOMElement* node, const U& param)
      {
	std::string monoid_type = tools::get_monoid_type(param);
	std::string monoid_type_ref;

	if (! node || ! node->hasAttribute(transcode("type")))
	  monoid_type_ref = "free";
	else
	  monoid_type_ref = xml2str(node->getAttribute(transcode("type")));
	if (monoid_type_ref != monoid_type)
	  FAIL("Bad monoid type");
      }


      template <class S, class T, class U, class M1, class M2>
      void ensure_monoid_type(const xercesc::DOMElement* node,
			      const FMPtype& param)
      {
	std::string monoid_type = tools::get_monoid_type(param);
	std::string monoid_type_ref;

	if (! node || ! node->hasAttribute(transcode("type")))
	  monoid_type_ref = "product";
	else
	  monoid_type_ref = xml2str(node->getAttribute(transcode("type")));
	if (monoid_type_ref != monoid_type)
	  FAIL("Bad monoid type");
      }


      template <class OStream>
      void print_transition(const xercesc::DOMElement* n,
			    OStream& os,
			    std::string& spacing)
      {
	os << spacing << "<" << xml2str(n->getNodeName());
# define VCSN_TRANS_OUTPUT(What)					\
	if (n->hasAttribute(transcode(What)))				\
	  os << " " What "=\""						\
	     << xml2str(n->getAttribute(transcode(What))) << "\""
	VCSN_TRANS_OUTPUT("src");
	VCSN_TRANS_OUTPUT("dst");
	VCSN_TRANS_OUTPUT("label");
	VCSN_TRANS_OUTPUT("weight");
	VCSN_TRANS_OUTPUT("in");
	VCSN_TRANS_OUTPUT("out");
# undef VCSN_TRANS_OUTPUT
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
       * @arg \c OStream	Type of output stream.
       *
       * @param node	XML root node to print.
       * @param os	Output stream.
       *
       */
      template <class OStream>
      void print_document(xercesc::DOMElement* node, OStream& os)
      {
	node->setAttribute(transcode("xmlns"),
			   transcode("http://vaucanson.lrde.epita.fr"));
	print_tree(node, os, "");
      }


    } // ! tools

  } // ! xml

} // ! vcsn


# undef AUTtype
# undef TRANStype
# undef FMPtype

#endif // ! VCSN_XML_TOOLS_HXX
