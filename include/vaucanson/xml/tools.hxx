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
 * @file xml/tools.hxx
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

      inline
      void
      set_attribute (xercesc::DOMElement* e, std::string k, std::string v)
      {
	e->setAttribute (transcode(k), transcode(v));
      }

      inline
      void
      xset_attribute (xercesc::DOMElement* e, std::string k, std::string v)
      {
	if (v != "")
	  set_attribute (e, k, v);
      }


      // Add the label as a string attribute.
      template <class S, class T, class U>
      void add_label(xercesc::DOMElement* elt,
		     const Element<S, T>&,
		     const U& series)
      {
	xset_attribute(elt, "label", get_label(series));
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

# define FMPtype      							  \
    Element<								  \
      Automata<								  \
      vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> > \
      >, T								  \
    >
      // Add the label as a string attribute
      template <class S, class T, class U, class M1, class M2>
      void add_label(xercesc::DOMElement* elt,
		     const FMPtype&,
		     const U& series)
      {
	if (series.supp().size() > 1)
	{
	  xset_attribute(elt, "label", get_label(series));
	}
	else
	{
	  std::string in_word = get_label((*(series.supp().begin())).first);
	  std::string out_word = get_label((*(series.supp().begin())).second);
	  std::string mult = get_label(series.get(*(series.supp().begin())));
	  std::string out;
	  if (mult.size())
	    out = mult;
	  if (out != "" && out_word.size())
	    out += " ";
	  if (out_word.size())
	    out += out_word;

	  xset_attribute(elt, "in", in_word);
	  xset_attribute(elt, "out", out);
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
	  xset_attribute(elt, "label", get_label(series));
	}
	else
	{
	  std::string in_word = get_label((*(series.supp())).first);
	  std::string out_word = get_label((*(series.supp())).second);
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
	    xset_attribute(out_node, "weight", mult);
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
	  set_attribute(elt, "in", in);
	if (out.size() && out != "1")
	  set_attribute(elt, "out", out);
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
	  set_attribute(gen, "value", letter.str().c_str());
	  root->appendChild(gen);
	}
      }

      template <class M>
      xercesc::DOMElement* create_monoid(const M& monoid,
					 xercesc::DOMDocument* doc,
					 xercesc::DOMElement* elt)
      {
	xercesc::DOMElement* m = doc->createElement(transcode("monoid"));
	set_attribute(m, "type", get_monoid_type(monoid));
	set_attribute(m, "generators", "letters");
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
	  set_attribute(s, "operations", get_semiring_operations(semiring));
	set_attribute(s, "set", get_semiring_set(semiring, value_t()));
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
	  Element<Transducer<S>, T>::series_set_elt_t::semiring_elt_t::semiring_elt_t::value_t
	  value_t;

	xercesc::DOMElement* s = doc->createElement(transcode("semiring"));
	set_attribute(s, "operations", "numerical");
	set_attribute(s, "set", get_semiring_set(semiring, value_t()));
	elt->appendChild(s);

	return s;
      }

      template <class T>
      Element<typename T::series_set_t, rat::exp<typename T::monoid_elt_value_t,
						 typename T::semiring_elt_value_t> >
      get_rec_xml_series(xercesc::DOMNode* n, T& aut)
      {
	typedef	 rat::exp<typename T::monoid_elt_value_t,
 	                  typename T::semiring_elt_value_t> krat_exp_impl_t;
	typedef Element<typename T::series_set_t, krat_exp_impl_t> krat_exp_t;
	krat_exp_t krat_exp (aut.structure().series());
	typename T::semiring_elt_value_t weight =
	  typename T::semiring_elt_value_t();

	xercesc::DOMElement* element_n;
	xercesc::DOMNode* ntmp;

	if (!n)
	  return vcsn::algebra::identity_as<krat_exp_impl_t>::
	    of(krat_exp.structure());

	for (; n ; n = n->getNextSibling())
	{
	  if (n->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
	  {
	    element_n = (static_cast<xercesc::DOMElement*>(n));

	    if ((xml2str(n->getNodeName()) == "label") ||
		(xml2str(n->getNodeName()) == "in") ||
		(xml2str(n->getNodeName()) == "out"))
	      return get_rec_xml_series(n->getFirstChild(), aut);

	    // Add weight
	    if (element_n->hasAttribute(transcode("weight")))
	    {
	      std::stringstream ss;
	      ss << xml2str(element_n->getAttribute(transcode("weight")));
	      ss >> weight;
	    }

	    // Explore the terms of a sum
	    if (xml2str(n->getNodeName()) == "sum")
	    {
	      ntmp = n->getFirstChild()->getNextSibling();
	      krat_exp = get_rec_xml_series(ntmp, aut);
	      if (ntmp)
		for (ntmp = ntmp->getNextSibling();
		     ntmp && ntmp->getNextSibling();
		     ntmp = ntmp->getNextSibling()->getNextSibling())
		  krat_exp += get_rec_xml_series(ntmp, aut);
	      return (weight != typename T::semiring_elt_t ())?
		typename T::semiring_elt_t (weight) * krat_exp : krat_exp;
	    }

	    // Explore the terms of a product
	    if (xml2str(n->getNodeName()) == "product")
	    {
	      ntmp = n->getFirstChild()->getNextSibling();
	      krat_exp = get_rec_xml_series(ntmp, aut);
	      if (ntmp)
		for (ntmp = ntmp->getNextSibling();
		     ntmp && ntmp->getNextSibling();
		     ntmp = ntmp->getNextSibling()->getNextSibling())
		  krat_exp *= get_rec_xml_series(ntmp, aut);
	      return (weight != typename T::semiring_elt_t ())?
		typename T::semiring_elt_t (weight) * krat_exp : krat_exp;
	    }

	    // Word, zero or identity
	    if (xml2str(n->getNodeName()) == "word")
	      krat_exp = typename T::monoid_elt_t (
		krat_exp.structure().monoid(),
		xml2str(element_n->getAttribute(transcode("value"))));

	    if (xml2str(n->getNodeName()) == "zero")
	      krat_exp = vcsn::algebra::
		zero_as<krat_exp_impl_t>::of(krat_exp.structure());

	    if (xml2str(n->getNodeName()) == "identity")
	      krat_exp =  vcsn::algebra::
		identity_as<krat_exp_impl_t>::of(krat_exp.structure());

	    // Add star
	    if (xml2str(n->getNodeName()) == "star")
	      krat_exp = (get_rec_xml_series(n->getFirstChild(), aut)).star();

	    return (weight != typename T::semiring_elt_t ())?
	      typename T::semiring_elt_t (weight) * krat_exp : krat_exp;
	  }
	}
	return krat_exp;
      }


      template <class T>
      typename T::series_set_elt_t
      get_series(xercesc::DOMElement* node, T& aut)
      {
	typedef typename
	  rat::exp<typename T::monoid_elt_value_t,
	  typename T::semiring_elt_value_t> krat_exp_impl_t;
	typedef Element<typename T::series_set_t, krat_exp_impl_t> krat_exp_t;
	krat_exp_t res (aut.structure().series());
	xercesc::DOMNode* n = node->getFirstChild();
	if (n && n->getNextSibling()
	    && (xml2str(n->getNextSibling()->getNodeName()) == "label"))
	  res = get_rec_xml_series(n, aut);
	if (res == vcsn::algebra::
	    zero_as<krat_exp_impl_t>::of(res.structure()))
	{
	  if (xml2str(node->getAttribute(transcode("label"))) == "")
	    return
	      vcsn::algebra::identity_as<typename T::series_set_elt_t::value_t>
	      ::of(aut.structure().series());
	  else
	    parse(xml2str(node->getAttribute(transcode("label"))), res);
	}
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


# define TRANStype				\
    Element<Transducer<S>, T>

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
	      i_exp = get_rec_xml_series(n->getFirstChild(), bin);
	    if (xml2str(n->getNodeName()) == "out" && n->getFirstChild())
	      o_exp = get_rec_xml_series(n->getFirstChild(), bout);
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
       * Check that observed declarations match the expectations.
       *
       * @param node    to check
       * @param kind    user readable kind of entity to check, e.g. "monoid"
       * @param key     key used in the XML document, e.g., "type"
       * @param deflt   default value, e.g., "B"
       * @param expected  value given the rest of the XML document.
       */
      void
      check_consistency (const xercesc::DOMElement* node,
			 const std::string& kind,
			 const char* key, const std::string& deflt,
			 const std::string& expected)
      {
	std::string observed;
	if (node && node->hasAttribute(transcode(key)))
	  observed = xml2str(node->getAttribute(transcode(key)));
	else
	  observed = deflt;
	if (expected != observed)
	  FAIL(std::string ("invalid ") + kind + ": " + observed
	       + ", expected: " + expected);
      }


      template <class T, class U>
      void ensure_semiring_type(const xercesc::DOMElement* node,
				const T&, const U& param)
      {
	typedef typename T::series_set_elt_t::semiring_elt_t::value_t value_t;
	check_consistency (node, "semiring",
			   "set", "B",
			   tools::get_semiring_set(param, value_t()));
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
	check_consistency (node, "semiring",
			   "set", "B",
			   tools::get_semiring_set(param, value_t()));
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

	check_consistency (node, "semiring", "set", "ratSeries", 
			   tools::get_semiring_set(param, value_t()));
      }


      template <class U>
      void ensure_monoid_type(const xercesc::DOMElement* node, const U& param)
      {
	check_consistency (node,
			   "monoid", "type", "free",
			   tools::get_monoid_type(param));
      }


      template <class S, class T, class U, class M1, class M2>
      void ensure_monoid_type(const xercesc::DOMElement* node,
			      const FMPtype& param)
      {
	check_consistency (node,
			   "monoid", "type", "product",
			   tools::get_monoid_type(param));
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


      template <class OStream>
      void print_document(xercesc::DOMElement* node, OStream& os)
      {
	set_attribute(node, "xmlns", "http://vaucanson.lrde.epita.fr");
	print_tree(node, os, "");
      }


    } // ! tools

  } // ! xml

} // ! vcsn


# undef TRANStype
# undef FMPtype

#endif // ! VCSN_XML_TOOLS_HXX
