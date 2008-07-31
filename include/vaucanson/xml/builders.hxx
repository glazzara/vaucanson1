// builders.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_BUILDERS_HXX
# define VCSN_XML_BUILDERS_HXX

# include <vaucanson/algebra/concept/letter.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/xml/xml_exp_visitor.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>

namespace vcsn
{
  namespace xml
  {
    /**
     * monGenHandler
     */
    template <typename T>
    monGenHandler<T>::monGenHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& monoid,
				 const XMLCh* value)
      : Handler(parser, root),
	monoid_(monoid),
	value_(value)
    {
    }

    template <typename T>
    void
    monGenHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      error::token(localname);
    }

    template <typename T>
    void
    monGenHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      if (xercesc::XMLString::equals(eq_.monGen, localname))
      {
	if (value_)
	{
	  std::string letter = xmlstr(value_);
	  builders::insert_generator(monoid_.alphabet(), letter);
	  parser_->setContentHandler(&root_);
	}
	else
	{
	  error::missattrs(localname, "value");
	}
      }
      else
	error::token(localname);
    }

    /**
     * FreeMonoidHandler
     */
    template <typename T>
    FreeMonoidHandler<T>::FreeMonoidHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& monoid)
      : Handler(parser, root),
	monoid_(monoid),
	mongenh_(0),
	unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    FreeMonoidHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      if (xercesc::XMLString::equals(eq_.monGen, localname))
      {
	const XMLCh* value = tools::get_attribute(attrs, "value");
	if (mongenh_)
	  delete mongenh_;
	mongenh_ = new monGenHandler<T>(parser_, *this, monoid_, value);
	parser_->setContentHandler(mongenh_);
      }
      else if (xercesc::XMLString::equals(eq_.genSort, localname))
      {
	/* FIXME should store informations of genSort to ensure monoid consistency */
	parser_->setContentHandler(&unsuph_);
      }
      else if (xercesc::XMLString::equals(eq_.writingData, localname))
	parser_->setContentHandler(&unsuph_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    FreeMonoidHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      if (xercesc::XMLString::equals(eq_.monoid, localname))
      {
	if (mongenh_)
	  delete mongenh_;
	parser_->setContentHandler(&root_);
      }
      else if (!xercesc::XMLString::equals(eq_.monGen, localname))
	error::token(localname);
    }

    namespace builders
    {
      template <typename T>
      typename T::monoid_t*
      create_monoid (T& param,
		     const XMLCh* const localname,
		     const xercesc::Attributes& attrs)
      {
	typename T::monoid_t::alphabet_t	at;
	typedef typename T::monoid_t		monoid_t;

	monoid_t*	monoid = new monoid_t(at);
	builders::check_monoid_consistency(param, localname, attrs);
	return monoid;
      }

      template <typename T>
      Handler*
      create_monoidh (T& monoid,
		      const xercesc::Attributes&,
		      xercesc::SAX2XMLReader* parser,
		      Handler& root)
      {
	return new vcsn::xml::FreeMonoidHandler<T>(parser, root, monoid);
      }

      // FIXME should specialize type T (char ? int?)
      template <typename T>
      void
      insert_generator(T& monoid,
		       const std::string& str)
      {
	monoid.insert(str);
      }
    } // !builders
    /**
     * NumSemiringHandler
     */
    template <typename T>
    NumSemiringHandler<T>::NumSemiringHandler (xercesc::SAX2XMLReader* parser,
					       Handler& root,
					       T& semiring)
    : Handler(parser, root),
      semiring_(semiring),
      unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    NumSemiringHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      if (xercesc::XMLString::equals(eq_.writingData, localname))
	parser_->setContentHandler(&unsuph_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    NumSemiringHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      if (xercesc::XMLString::equals(eq_.semiring, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
    }

    namespace builders
    {
      template <typename T>
      typename T::semiring_t*
      create_semiring (T&,
		       const XMLCh* const localname,
		       const xercesc::Attributes& attrs)
      {
	typedef typename T::semiring_t semiring_t;
	semiring_t*	semiring = new semiring_t();

	typedef typename T::semiring_elt_t semiring_elt_t;
	semiring_elt_t	elt;
	builders::check_semiring_consistency(elt, localname, attrs);

	return semiring;
      }

      template <typename T>
      Handler*
      create_semiringh(T& semiring,
		       const xercesc::Attributes&,
		       xercesc::SAX2XMLReader* parser,
		       Handler& root)
      {
	return new NumSemiringHandler<T>(parser, root, semiring);
      }

    } // !builders

    /**
     * monElmtHandler
     */
    template <typename T>
    class MonElmtHandler;

    template <typename T>
    class WeightHandler;

    namespace builders
    {

      template <typename S, typename T>
      RegexpHandler<S>*
      create_monElmth(xercesc::SAX2XMLReader* parser,
		      RegexpHandler<T>& root,
		      S param)
      {
	return new MonElmtHandler<S>(parser, root, param);
      }

      template <typename T>
      RegexpHandler<T>*
      create_weighth(xercesc::SAX2XMLReader* parser,
		     RegexpHandler<T>& root,
		     T param,
		     const xercesc::Attributes& attrs)
      {
	typename T::monoid_elt_value_t m =
	  vcsn::algebra::identity_as<typename T::monoid_elt_value_t>::of(param.structure().monoid()).value();
	const std::string val(xmlstr(tools::get_attribute(attrs, "value")));
	std::string::const_iterator i = val.begin();
	typename T::semiring_elt_t w(param.structure().semiring());
	if (!parse_weight(w, val, i))
	  error::attrs(tools::get_attribute(attrs, "localname"), "value", val);
	param.assoc(m, w.value());
	return new WeightHandler<T>(parser, root, param);
      }
    } // !builders

    /**
     * Consistency
     */
    namespace builders
    {
      // Default.
      template <class T>
      const char* get_semiring_set(const T&)
      { return "undefined"; }

# define GET_SEMIRING_SET(T, Value)			\
      const char* get_semiring_set(const T&)	\
      { return Value; }

      GET_SEMIRING_SET(bool, "B")
      GET_SEMIRING_SET(double, "R")
      GET_SEMIRING_SET(float, "R")
      GET_SEMIRING_SET(int, "Z")
# undef GET_SEMIRING_SET

      template <class S>
      const char* get_semiring_operations(const S&)
      { return "classical"; }

      template <typename T>
      void
      check_monoid_consistency (T&,
				const XMLCh* const localname,
			        const xercesc::Attributes& attrs)
      {
	std::string val(xmlstr(tools::get_attribute(attrs, "type")));
	if (val != "free")
	  error::attrs(localname, "type", val);
      };

      template <typename T>
      void
      check_semiring_consistency (T& param,
				  const XMLCh* const localname,
				  const xercesc::Attributes& attrs)
      {
	std::string set(xmlstr(tools::get_attribute(attrs, "set")));
	if (builders::get_semiring_set(param.value()) != set)
	  error::attrs(localname, "set", set);
	std::string op(xmlstr(tools::get_attribute(attrs, "operations")));
	if (builders::get_semiring_operations(param.structure()) != op)
	  error::attrs(localname, "operations", op);
      };

      template <class T>
      const char* get_monoid_gen_sort(const T&)
      { return "undefined"; }
# define GET_MONOID_GEN_SORT(T, Value) \
      const char* get_monoid_gen_sort(const T&) \
      { return Value; }

      GET_MONOID_GEN_SORT(char, "letters")
      GET_MONOID_GEN_SORT(int, "integers")
# undef GET_MONOID_GEN_SORT
    } // !builders

    namespace builders
    {
      template <typename T>
      void
      create_semiring_node(const T& aut,
			   xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root)
      {
	typedef typename T::semiring_elt_t semiring_elt_t;
	semiring_elt_t semiring(aut.structure().series().semiring());
	xercesc::DOMElement* node = tools::create_element(doc, "semiring");
	tools::set_attribute(node, "type", "numerical");
	tools::set_attribute(node, "set", get_semiring_set(semiring.value()));
	tools::set_attribute(node, "operations", get_semiring_operations(semiring.structure()));
	root->appendChild(node);
      }
      template <typename T>
      void
      create_monoid_node(const T& aut,
			   xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root)
      {
	xercesc::DOMElement* node = tools::create_element(doc, "monoid");
	tools::set_attribute(node, "type", "free");
	tools::set_attribute(node, "genDescrip", "enum");
	tools::set_attribute(node, "genKind", "simple"); // FIXME get it
	root->appendChild(node);
	typedef typename T::monoid_t::alphabet_t::const_iterator alphabet_iterator;
	for_all_letters(l, aut.structure().series().monoid().alphabet())
	{
	  std::ostringstream letter;
	  xercesc::DOMElement* gen = tools::create_element(doc, "monGen");
	  letter << *l;
	  tools::set_attribute(gen, "value", letter.str());
	  node->appendChild(gen);
	}
	tools::set_attribute(node, "genSort", get_monoid_gen_sort(*(aut.structure().series().monoid().alphabet().begin())));
      }

      template <typename T>
      void
      create_regexp_node(const T& e,
			 xercesc::DOMDocument* doc,
			 xercesc::DOMElement* root)
      {
	typedef typename T::value_t::monoid_elt_value_t	monoid_elt_value_t;
	typedef typename T::value_t::semiring_elt_value_t	semiring_elt_value_t;
	typedef typename rat::exp<monoid_elt_value_t, semiring_elt_value_t> krat_exp_impl_t;

	typedef Element<typename T::set_t, krat_exp_impl_t > krat_exp_t;

	krat_exp_t res(e);
	rat::XmlExpVisitor<monoid_elt_value_t, semiring_elt_value_t> v(doc, "label");
	res.value().accept(v);
	root->appendChild(v.get());
      }

      template <typename U>
      void
      create_monElmt_node(const U& word,
			  xercesc::DOMDocument* doc,
			  xercesc::DOMElement* root)
      {
	xercesc::DOMElement* node;
	// FIXME we shouldn't have to do that... and loop on the alphabet.
	if (word.empty())
	  node = tools::create_element(doc, "one");
	else
	{
	  node = tools::create_element(doc, "monElmt");
	  for (typename U::const_iterator i = word.begin(); i != word.end(); ++i)
	  {
	    xercesc::DOMElement* gen = tools::create_element(doc, "monGen");
	    tools::set_attribute(gen, "value",
				 algebra::letter_traits<typename U::value_type>::
				 letter_to_literal(*i));
	    node->appendChild(gen);
	  }
	}
	root->appendChild(node);
      }
    } // !builders
  } // !xml
} // !vcsn

#endif // !VCSN_XML_BUILDERS_HXX
