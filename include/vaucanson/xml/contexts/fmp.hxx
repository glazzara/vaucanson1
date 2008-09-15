// fmp.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_XML_CONTEXTS_FMP_HXX
# define VCSN_XML_CONTEXTS_FMP_HXX

# include <vaucanson/xml/builders.hh>

namespace vcsn
{
  namespace xml
  {
    /**
     * FreeMonoidHandler
     */
    template <typename T>
    FreeMonoidProductHandler<T>::FreeMonoidProductHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& monoid)
      : Handler(parser, root),
	monoid_(monoid),
	unsuph_(parser, *this),
	first_(true)
    {
    }

    template <typename T>
    void
    FreeMonoidProductHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      if (xercesc::XMLString::equals(eq_.monoid, localname))
      {
	if (first_)
	{
	  monoidh_ = builders::create_monoidh(monoid_.first_monoid(), attrs, parser_, *this);
	  first_ = false;
	}
	else
	{
	  delete monoidh_;
	  monoidh_ = builders::create_monoidh(monoid_.second_monoid(), attrs, parser_, *this);
	}
	parser_->setContentHandler(monoidh_);
      }
      else if (xercesc::XMLString::equals(eq_.writingData, localname))
	parser_->setContentHandler(&unsuph_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    FreeMonoidProductHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      delete monoidh_;
      if (xercesc::XMLString::equals(eq_.monoid, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
    }


    namespace builders
    {
      TParamFMP
      typename FMPtype::monoid_t*
      create_monoid (FMPtype& param,
		     const XMLCh* const localname,
		     const xercesc::Attributes& attrs)
      {
	typename FMPtype::monoid_t::first_monoid_t::alphabet_t	at1;
	typename FMPtype::monoid_t::second_monoid_t::alphabet_t	at2;
	typename FMPtype::monoid_t::first_monoid_t	md1(at1);
	typename FMPtype::monoid_t::second_monoid_t	md2(at2);
	typedef typename FMPtype::monoid_t		monoid_t;

	monoid_t* monoid = new monoid_t(md1, md2);
	builders::check_monoid_consistency(param, localname, attrs);
	return monoid;
      }

      template <typename M1, typename M2>
      Handler*
      create_monoidh (vcsn::algebra::FreeMonoidProduct<M1, M2>& monoid,
		      const xercesc::Attributes&,
		      xercesc::SAX2XMLReader* parser,
		      Handler& root)
      {
	typedef typename vcsn::algebra::FreeMonoidProduct<M1, M2> monoid_t;
	return new FreeMonoidProductHandler<monoid_t>(parser, root, monoid);
      }
    } // !builders

    /*
     * ProdMonElmtHandler
     */
    template <typename T>
    ProdMonElmtHandler<T>::ProdMonElmtHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T param)
      : RegexpHandler<T>(parser, root, param),
	in_(1),
	count_(1),
	m1_(param.structure().monoid().first_monoid()),
	m2_(param.structure().monoid().second_monoid())
    {
      end_ = eq_.monElmt;
    }

    template <typename T>
    void
    ProdMonElmtHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.monElmt, localname))
      {
	in_++;
	count_++;
	if (in_ > 2)
	  error::token(localname);
      }
      else if (XMLString::equals(eq_.one, localname) && (in_ == 1))
      {
	in_++;
	count_++;
	if (count_ == 2)
	  m1_ = algebra::identity_as<typename T::monoid_elt_t::first_monoid_elt_value_t>
	    ::of(param_.structure().monoid().first_monoid());
	else if (count_ == 3)
	  m2_ = algebra::identity_as<typename T::monoid_elt_t::second_monoid_elt_value_t>
	    ::of(param_.structure().monoid().second_monoid());
	else
	  error::token(localname);
      }
      else if (XMLString::equals(eq_.monGen, localname))
      {
	const std::string val(xmlstr(tools::get_attribute(attrs, "value")));
	std::set<char> escaped;
	std::string::const_iterator i = val.begin();
	if (in_ == 2 && count_ == 2)
	{
	  if (!parse_word(m1_, val, i, escaped))
	    error::attrs(localname, "value", val);
	}
	else if (in_ == 2 && count_ == 3)
	{
	  if (!parse_word(m2_, val, i, escaped))
	    error::attrs(localname, "value", val);
	}
	else
	  error::token(localname);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    ProdMonElmtHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(end_, localname))
      {
	if (in_ == 1 && count_ == 3)
	{
	  // FIXME awful... but didn't find an easier way.
	  typename T::monoid_elt_value_t m(m1_.value(), m2_.value());
	  typename T::semiring_elt_value_t w =
	    algebra::identity_as<typename T::semiring_elt_value_t>::of(param_.structure().semiring()).value();
	  param_.assoc(m, w);
	  parser_->setContentHandler(&root_);
	}
	in_--;
      }
      else if (XMLString::equals(eq_.one, localname))
	in_--;
      else if (!XMLString::equals(eq_.monGen, localname))
	error::token(localname);
    }


    namespace builders
    {
      SParamFMP
      RegexpHandler<FMPseries >*
      create_monElmth(xercesc::SAX2XMLReader* parser,
		      RegexpHandler<FMPseries >& root,
		      FMPseries param)
      {
	return new ProdMonElmtHandler<FMPseries >(parser, root,
	    algebra::zero_as<typename FMPseries::value_t>::of(param.structure()));
      }
    } // !builders

    /**
     * Consistency
     */
    namespace builders
    {
      TParamFMP
      void
      check_monoid_consistency (FMPtype&,
				const XMLCh* const localname,
			        const xercesc::Attributes& attrs)
      {
	std::string val(xmlstr(tools::get_attribute(attrs, "type")));
	if (val != "product")
	  error::attrs(localname, "type", val);
	val = xmlstr(tools::get_attribute(attrs, "prodDim"));
	if (val != "2")
	  error::attrs(localname, "prodDim", val);
      };
    } // !builders

    /**
     *
     */
    namespace builders
    {
      TParamFMP
      void
      create_monoid_node(const FMPtype& aut,
			 xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root)
      {
	xercesc::DOMElement* node = tools::create_element(doc, "monoid");
	tools::set_attribute(node, "type", "product");
	tools::set_attribute(node, "prodDim", "2");
	root->appendChild(node);
	xercesc::DOMElement* first = tools::create_element(doc, "monoid");
	tools::set_attribute(first, "type", "free");
	tools::set_attribute(first, "genDescrip", "enum");
	tools::set_attribute(first, "genKind", algebra::letter_traits<typename FMPtype::monoid_t::first_monoid_t::alphabet_t::letter_t>::kind());
	node->appendChild(first);
	typedef typename FMPtype::monoid_t::first_monoid_t::alphabet_t::const_iterator first_alphabet_iterator;
	for_all_letters_(first_, l, aut.structure().series().monoid().first_monoid().alphabet())
	{
	  std::ostringstream letter;
	  xercesc::DOMElement* gen = tools::create_element(doc, "monGen");
	  letter << *l;
	  tools::set_attribute(gen, "value", letter.str());
	  first->appendChild(gen);
	}
	tools::set_attribute(first, "genSort", get_monoid_gen_sort(*(aut.structure().series().monoid().first_monoid().alphabet().begin())));
	xercesc::DOMElement* second = tools::create_element(doc, "monoid");
	tools::set_attribute(second, "type", "free");
	tools::set_attribute(second, "genDescrip", "enum");
	tools::set_attribute(second, "genKind", algebra::letter_traits<typename FMPtype::monoid_t::second_monoid_t::alphabet_t::letter_t>::kind());
	node->appendChild(second);
	typedef typename FMPtype::monoid_t::second_monoid_t::alphabet_t::const_iterator second_alphabet_iterator;
	for_all_letters_(second_, l, aut.structure().series().monoid().second_monoid().alphabet())
	{
	  std::ostringstream letter;
	  xercesc::DOMElement* gen = tools::create_element(doc, "monGen");
	  letter << *l;
	  tools::set_attribute(gen, "value", letter.str());
	  second->appendChild(gen);
	}
	tools::set_attribute(second, "genSort", get_monoid_gen_sort(*(aut.structure().series().monoid().second_monoid().alphabet().begin())));
      }

      /* FIXME there should not be 2 but one function here... however,
      ** when we add a template T instead of int the function is not called
      ** anymore... there is a probleme in the dispatch */
      template <>
      void
      create_monElmt_node(const std::pair<std::string, std::string>& m,
			 xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root)
      {
	xercesc::DOMElement* node;
	if (m.first.empty() && m.second.empty())
	  node = tools::create_element(doc, "one");
	else
	{
	  node = tools::create_element(doc, "monElmt");
	  create_monElmt_node(m.first, doc, node);
	  create_monElmt_node(m.second, doc, node);
	}
	root->appendChild(node);
      }

      template <>
      void
      create_monElmt_node(const std::pair<std::basic_string<int>, std::basic_string<int> >& m,
			 xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root)
      {
	xercesc::DOMElement* node;
	if (m.first.empty() && m.second.empty())
	  node = tools::create_element(doc, "one");
	else
	{
	  node = tools::create_element(doc, "monElmt");
	  create_monElmt_node(m.first, doc, node);
	  create_monElmt_node(m.second, doc, node);
	}
	root->appendChild(node);
      }
    } // !builders
  } // !xml
} // !vcsn

#endif // !VCSN_XML_CONTEXTS_FMP_HXX
