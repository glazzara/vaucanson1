// rw.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_CONTEXTS_RW_HXX
# define VCSN_XML_CONTEXTS_RW_HXX

# include <vaucanson/xml/builders.hh>

namespace vcsn
{
  namespace xml
  {
    /**
     * SeriesSemiringHandler
     */
    template <typename T>
    SeriesSemiringHandler<T>::SeriesSemiringHandler (xercesc::SAX2XMLReader* parser,
					       Handler& root,
					       T& semiring)
    : Handler(parser, root),
      semiring_(semiring),
      ssemiringh_(0),
      monoidh_(0),
      unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    SeriesSemiringHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      if (xercesc::XMLString::equals(eq_.semiring, localname))
      {
	ssemiringh_ = builders::create_semiringh(semiring_.semiring(), attrs, parser_, *this);
	parser_->setContentHandler(ssemiringh_);
      }
      else if (xercesc::XMLString::equals(eq_.monoid, localname))
      {
	monoidh_ = builders::create_monoidh(const_cast <typename T::monoid_t&>(semiring_.monoid()), attrs, parser_, *this);
	parser_->setContentHandler(monoidh_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    SeriesSemiringHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      if (xercesc::XMLString::equals(eq_.semiring, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
      delete ssemiringh_;
      delete monoidh_;
    }

    namespace builders
    {
      template <typename S, typename K, typename T>
      typename TRANStype::semiring_t*
      create_semiring (TRANStype&,
		       const XMLCh* const,
		       const xercesc::Attributes&)
      {
	typename TRANStype::semiring_t::monoid_t::alphabet_t	at;
	typename TRANStype::semiring_t::monoid_t	md(at);
	typename TRANStype::semiring_t::semiring_t	ssg;
	typedef typename TRANStype::semiring_t semiring_t;
	semiring_t*	semiring = new semiring_t(ssg, md);

	return semiring;
      }

      template <typename S, typename T>
      Handler*
      create_semiringh(TRANSsemiring& semiring,
		       const xercesc::Attributes&,
		       xercesc::SAX2XMLReader* parser,
		       Handler& root)
      {
	return new SeriesSemiringHandler<TRANSsemiring >(parser, root, semiring);
      }

    } // !builders

    /**
     * Consistency
     */
    namespace builders
    {
      template <typename S, typename T>
      const char* get_semiring_operations(const vcsn::algebra::Series<S, T>&)
      {
	return "SHOULD not append";
      }
    } // !builders

    namespace builders
    {
      template <typename S, typename K, typename T>
      void
      create_semiring_node(const TRANStype& aut,
			   xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root)
      {
	xercesc::DOMElement* node = tools::create_element(doc, "semiring");
	tools::set_attribute(node, "type", "series");
	xercesc::DOMElement* semiringn = tools::create_element(doc, "semiring");
	xercesc::DOMElement* monoid = tools::create_element(doc, "monoid");

	typedef typename TRANStype::semiring_elt_t::semiring_elt_t semiring_elt_t;
	semiring_elt_t semiring;
	tools::set_attribute(semiringn, "set", get_semiring_set(semiring.value()));
	tools::set_attribute(semiringn, "operations", get_semiring_operations(semiring.structure()));

	tools::set_attribute(monoid, "type", "free");
	tools::set_attribute(monoid, "genDescrip", "enum");
	tools::set_attribute(monoid, "genKind", algebra::letter_traits<typename TRANStype::semiring_t::monoid_t::alphabet_t::letter_t>::kind());
	typedef typename TRANStype::semiring_t::monoid_t::alphabet_t::const_iterator alphabet_iterator;
	for_all_letters(l, aut.series().semiring().monoid().alphabet())
	{
	  std::ostringstream letter;
	  xercesc::DOMElement* gen = tools::create_element(doc, "monGen");
	  letter << *l;
	  tools::set_attribute(gen, "value", letter.str());
	  monoid->appendChild(gen);
	}
	tools::set_attribute(monoid, "genSort", get_monoid_gen_sort(*(aut.series().semiring().monoid().alphabet().begin())));
	node->appendChild(semiringn);
	node->appendChild(monoid);
	root->appendChild(node);
      }
    }

    /**
     * WeightHandler
     */

    SParamTRANS
    WeightHandler<TRANSseries >::WeightHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       TRANSseries param)
      : RegexpHandler<TRANSseries >(parser, root, param),
	weighth_(0)
    {
      end_ = eq_.weight;
    }

    SParamTRANS
    void
    WeightHandler<TRANSseries >::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      //RegexpHandler<series_set_elt_t>* tmp = new RegexpHandler<series_set_elt_t>(parser_, *this,
//	  algebra::identity_as<typename series_set_elt_t::value_t>::of(param_.structure().semiring()));
      if (!(weighth_ = create_weighth(localname)))
	error::token(localname);
      else
	parser_->setContentHandler(weighth_);
    }

    SParamTRANS
    void
    WeightHandler<TRANSseries >::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {

      using namespace xercesc;
      if (XMLString::equals(end_, localname))
      {
	TRANSseries s = algebra::identity_as<typename TRANSseries::value_t>::of(param_.structure());
	typename TRANSseries::semiring_elt_t w(weighth_->series());
	param_ = param_ * w;

	parser_->setContentHandler(&root_);
	delete weighth_;
      }
      else
	error::token(localname);
    }

    SParamTRANS
    RegexpHandler<typename WeightHandler<TRANSseries >::series_set_elt_t>*
    WeightHandler<TRANSseries >::create_weighth (const XMLCh* const localname)
    {
      using namespace xercesc;
      series_set_elt_t elt(param_.structure().semiring());

      if (XMLString::equals(eq_.monElmt, localname))
	return builders::create_monElmth(parser_, *this, algebra::identity_as<typename series_set_elt_t::value_t>::of(elt.structure()));
      else if (XMLString::equals(eq_.star, localname))
	return new StarHandler<series_set_elt_t>(parser_, *this, algebra::identity_as<typename series_set_elt_t::value_t>::of(elt.structure()));
      else if (XMLString::equals(eq_.leftExtMul, localname))
	return new ExtMulHandler<series_set_elt_t>(parser_, *this, algebra::identity_as<typename series_set_elt_t::value_t>::of(elt.structure()), true);
      else if (XMLString::equals(eq_.rightExtMul, localname))
	return new ExtMulHandler<series_set_elt_t>(parser_, *this, algebra::identity_as<typename series_set_elt_t::value_t>::of(elt.structure()), false);
      else if (XMLString::equals(eq_.sum, localname))
	return new SumHandler<series_set_elt_t>(parser_, *this, algebra::identity_as<typename series_set_elt_t::value_t>::of(elt.structure()));
      else if (XMLString::equals(eq_.product, localname))
	return new ProductHandler<series_set_elt_t>(parser_, *this, algebra::identity_as<typename series_set_elt_t::value_t>::of(elt.structure()));
      else if (XMLString::equals(eq_.one, localname))
	return new AtomHandler<series_set_elt_t>(parser_, *this, algebra::identity_as<typename series_set_elt_t::value_t>::of(elt.structure()), eq_.one);
      else if (XMLString::equals(eq_.zero, localname))
	return new AtomHandler<series_set_elt_t>(parser_, *this, algebra::zero_as<typename series_set_elt_t::value_t>::of(elt.structure()), eq_.zero);
      else
	return 0;
    }

    namespace builders
    {
      SParamTRANS
      RegexpHandler<TRANSseries >*
      create_weighth(xercesc::SAX2XMLReader* parser,
		     RegexpHandler<TRANSseries >& root,
		     TRANSseries param,
		     const xercesc::Attributes&)
      {
	return new WeightHandler<TRANSseries >(parser, root, param);
      }
    } // !builders
  } // !xml
} // !vcsn

#endif // !VCSN_XML_CONTEXTS_RW_HXX
