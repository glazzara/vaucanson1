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

# include <sstream>

# include <vaucanson/algebra/concept/letter.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/xml/xml_exp_visitor.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/algebra/implementation/monoid/monoid_rep.hh>

namespace vcsn
{
  namespace xml
  {
    /**
     * monGenAction
     */
    template <typename T>
    monGenAction<T>::monGenAction(const T&)
    {
      static_error(need_to_specialize_monGenAction_for_T)
    }

    template <typename T>
    monGenAction<vcsn::algebra::FreeMonoid<T> >::
    monGenAction(self_t& monoid)
    : alphabet_(monoid.alphabet())
    {
    }

    template <typename T, typename U, typename V>
    monGenAction<vcsn::Element<vcsn::algebra::Series<T, U>, V> >::
    monGenAction(self_t& s)
    : s_(s)
    {
    }

    // Real work done here (insertion).
    template <typename T>
    void
    monGenAction<vcsn::algebra::FreeMonoid<T> >::
    operator () (const std::string& str)
    {
      alphabet_.insert(str);
    }

    // Real work done here (concatanation).
    template <typename T, typename U, typename V>
    void
    monGenAction<vcsn::Element<vcsn::algebra::Series<T, U>, V> >::
    operator () (const std::string& str)
    {
      typename self_t::monoid_elt_t m(s_.structure().monoid(), str);
      self_t tmp(s_.structure(), m);

      s_ = s_ * tmp;
    }

    /**
     * monGenHandler
     */
    template <typename T, typename U>
    monGenHandler<T, U>::monGenHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 const monGenAction<U>& action,
				 const XMLCh* value)
      : Handler(parser, root),
	value_(value),
	action_(action)
    {
    }

    template <typename T, typename U>
    void
    monGenHandler<T, U>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      error::token(localname);
    }

    template <typename T, typename U>
    void
    monGenHandler<T, U>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      if (xercesc::XMLString::equals(eq_.monGen, localname))
      {
	if (value_)
	{
	  std::string letter = xmlstr(value_);
	  action_(letter);
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
     * monGenTupleHandler
     */
    template <typename T, typename U>
    monGenTupleHandler<T, U>::monGenTupleHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 const monGenAction<U>& action)
      : Handler(parser, root),
	value_("("),
	wait_begin_(true),
	count_(0),
	action_(action)
    {
    }

    template <typename T, typename U>
    void
    monGenTupleHandler<T, U>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      if (xercesc::XMLString::equals(eq_.monCompGen, localname) && wait_begin_)
      {
	wait_begin_ = false;
	const XMLCh* attr = tools::get_attribute(attrs, eq_.value);
	if (!attr)
	  error::missattrs(localname, "value");
	value_ += xmlstr(attr);
	if (count_ == algebra::letter_traits<typename T::alphabet_t::letter_t>::dim() - 2)
	  value_ += ",";
      }
      else
	error::token(localname);
    }

    template <typename T, typename U>
    void
    monGenTupleHandler<T, U>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      int dim = algebra::letter_traits<typename T::alphabet_t::letter_t>::
      dim();

      if (xercesc::XMLString::equals(eq_.monGen, localname)
	  && count_ == dim)
      {
	value_ += ")";
	action_(value_);
	parser_->setContentHandler(&root_);
      }
      else if (xercesc::XMLString::equals(eq_.monCompGen, localname)
	       && !wait_begin_ && count_ < dim)
      {
	wait_begin_ = true;
	count_++;
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
      using namespace xercesc;

      if (XMLString::equals(eq_.monGen, localname))
      {
	// When we have a monGen, we will insert it in the monoid alphabet.
	monGenAction<T> action(monoid_);

	// Delete the old handler.
	if (mongenh_)
	  delete mongenh_;

	// Choose statically the kind of generator.
	if (algebra::letter_traits<typename T::alphabet_t::letter_t>::kind() == "simple")
	{
	  const XMLCh* value = tools::get_attribute(attrs, eq_.value);
	  mongenh_ = new monGenHandler<T, T>(parser_, *this, action, value);
	}
	else
	  mongenh_ = new monGenTupleHandler<T, T>(parser_, *this, action);

	// Setup the new handler.
	parser_->setContentHandler(mongenh_);
      }
      else if (XMLString::equals(eq_.genSort, localname))
      {
	// FIXME: we should store the informations of genSort to ensure monoid consistency.
	parser_->setContentHandler(&unsuph_);
      }
      else if (XMLString::equals(eq_.writingData, localname))
      {
	algebra::monoid_rep<T> rep;
	if (tools::has_attribute(attrs, eq_.identitySymbol))
	  rep.empty = xmlstr(tools::get_attribute(attrs, eq_.identitySymbol));
	if (tools::has_attribute(attrs, eq_.concat))
	  rep.concat = xmlstr(tools::get_attribute(attrs, eq_.concat));
	monoid_.set_representation(rep);
	parser_->setContentHandler(&unsuph_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    FreeMonoidHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;

      if (XMLString::equals(eq_.monoid, localname))
      {
	// We are done with the monoid, so delete remaining data.
	if (mongenh_)
	  delete mongenh_;

	// Go up one level.
	parser_->setContentHandler(&root_);
      }
      else if (!XMLString::equals(eq_.monGen, localname))
	error::token(localname);
    }

    /**
     * SeriesRepresentationHandler
     */
    template <typename T>
    SeriesRepresentationHandler<T>::SeriesRepresentationHandler(xercesc::SAX2XMLReader* parser,
								Handler& root,
								T& srep)
      : Handler(parser, root),
	rep_(srep),
	unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    SeriesRepresentationHandler<T>::start(const XMLCh* const,
					  const XMLCh* const localname,
					  const XMLCh* const,
					  const xercesc::Attributes& attrs)
    {
      error::token(localname);
    }

    template <typename T>
    void
    SeriesRepresentationHandler<T>::end(const XMLCh* const,
					const XMLCh* const localname,
					const XMLCh* const)
    {
      using namespace xercesc;

      if (XMLString::equals(eq_.writingData, localname))
      {
	// Go up one level.
	parser_->setContentHandler(&root_);
      }
      else
	error::token(localname);
    }

    namespace builders
    {
      template <typename T>
      typename T::monoid_t*
      create_monoid(T& param,
		    const XMLCh* const localname,
		    const xercesc::Attributes& attrs,
		    XMLEq& eq)
      {
	// Type helpers.
	typename T::monoid_t::alphabet_t	at;
	typedef typename T::monoid_t		monoid_t;

	monoid_t*	monoid = new monoid_t(at, *(param.structure().series().monoid().representation()));
	builders::check_monoid_consistency(param, localname, attrs, eq);

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

      template <typename T>
      typename T::series_set_t::series_rep_t*
      create_series_representation(T& param,
				   const XMLCh* const localname,
				   const xercesc::Attributes& attrs,
				   XMLEq& eq)
      {
	// Type helpers.
	typedef typename T::series_set_t::series_rep_t series_rep_t;

	return new series_rep_t();
      }

      template <typename T>
      Handler*
      create_series_representationh(T& srep,
				    const xercesc::Attributes& attrs,
				    xercesc::SAX2XMLReader* parser,
				    Handler& root,
				    XMLEq& eq)
      {
	if (tools::has_attribute(attrs, eq.openPar))
	  srep.open_par = xmlstr(tools::get_attribute(attrs, eq.openPar));
	if (tools::has_attribute(attrs, eq.closePar))
	  srep.close_par = xmlstr(tools::get_attribute(attrs, eq.closePar));
	if (tools::has_attribute(attrs, eq.plusSym))
	  srep.plus = xmlstr(tools::get_attribute(attrs, eq.plusSym));
	if (tools::has_attribute(attrs, eq.timesSym))
	  srep.times = xmlstr(tools::get_attribute(attrs, eq.timesSym));
	if (tools::has_attribute(attrs, eq.starSym))
	  srep.star = xmlstr(tools::get_attribute(attrs, eq.starSym));
	if (tools::has_attribute(attrs, eq.zeroSym))
	  srep.zero = xmlstr(tools::get_attribute(attrs, eq.zeroSym));
	if (tools::has_attribute(attrs, eq.openWeight))
	  srep.open_weight = xmlstr(tools::get_attribute(attrs, eq.openWeight));
	if (tools::has_attribute(attrs, eq.closeWeight))
	  srep.close_weight = xmlstr(tools::get_attribute(attrs, eq.closeWeight));
	if (tools::has_attribute(attrs, eq.spacesSym))
	{
	  srep.spaces.clear();
	  srep.spaces.push_back(xmlstr(tools::get_attribute(attrs, eq.spacesSym)));
	}

	return new SeriesRepresentationHandler<T>(parser, root, srep);
      }

    } // ! builders

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
	const std::string val(xmlstr(tools::get_attribute(attrs, root.eq().value)));
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
      check_monoid_consistency(T&,
			       const XMLCh* const localname,
			       const xercesc::Attributes& attrs,
			       XMLEq& eq)
      {
	const XMLCh* val = tools::get_attribute(attrs, eq.type);
	if (!xercesc::XMLString::equals(val, eq.free))
	  error::attrs(localname, xmlstr(eq.type), xmlstr(val));
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

      template <class T>
      const char* get_monoid_gen_sort(const T&, int)
      { return "undefined"; }

      template <class U, class V>
      const char* get_monoid_gen_sort(const std::pair<U,V>& a, int i)
      {
	return i ? get_monoid_gen_sort(a.second) : get_monoid_gen_sort(a.first);
      }
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
	std::string letter_kind = algebra::letter_traits<typename T::monoid_t::alphabet_t::letter_t>::kind();
	xercesc::DOMElement* node = tools::create_element(doc, "monoid");
	tools::set_attribute(node, "type", "free");
	tools::set_attribute(node, "genDescrip", "enum");
	tools::set_attribute(node, "genKind", letter_kind);
	root->appendChild(node);

	xercesc::DOMElement* writingData = tools::create_element(doc, "writingData");
	tools::set_attribute(writingData, "identitySym", aut.series().monoid().representation()->empty);
	tools::set_attribute(writingData, "timesSym", aut.series().monoid().representation()->concat);
	node->appendChild(writingData);

	typedef typename T::monoid_t::alphabet_t::const_iterator alphabet_iterator;

	if (letter_kind == "simple")
	  tools::set_attribute(node, "genSort", get_monoid_gen_sort(*(aut.structure().series().monoid().alphabet().begin())));
	else
	{
	  std::stringstream genDim;
	  int dim = algebra::letter_traits<typename T::monoid_t::alphabet_t::letter_t>::dim();
	  genDim << dim;
	  tools::set_attribute(node, "genDim", genDim.str());
	  xercesc::DOMElement* genSort = tools::create_element(doc, "genSort");
	  node->appendChild(genSort);
	  xercesc::DOMElement* genCompSort;
	  for (int i = 0; i != dim; i++)
	  {
	    genCompSort = tools::create_element(doc, "genCompSort");
	    tools::set_attribute(genCompSort, "value", get_monoid_gen_sort(*(aut.structure().series().monoid().alphabet().begin()), i));
	    genSort->appendChild(genCompSort);
	  }
	}

	create_monGen_node<typename T::monoid_t::alphabet_t::letter_t> monGen_maker;
	for_all_letters(l, aut.structure().series().monoid().alphabet())
	  monGen_maker(*l, doc, node);

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

	if (word.empty())
	  node = tools::create_element(doc, "one");
	else
	{
	  node = tools::create_element(doc, "monElmt");
	  create_monGen_node<typename U::value_type> monGen_maker;
	  for (typename U::const_iterator i = word.begin(); i != word.end(); ++i)
	    monGen_maker(*i, doc, node);
	}
	root->appendChild(node);
      }

      template <typename T>
      void
      create_type_writingData_node(const T& aut,
				   xercesc::DOMDocument* doc,
				   xercesc::DOMElement* root)
      {
	xercesc::DOMElement* writingData = tools::create_element(doc, "writingData");

	// FIXME: we should use XMLEq
	tools::set_attribute(writingData, "plusSym", aut.series().representation()->plus);
	tools::set_attribute(writingData, "timesSym", aut.series().representation()->times);
	tools::set_attribute(writingData, "starSym", aut.series().representation()->star);
	tools::set_attribute(writingData, "zeroSym", aut.series().representation()->zero);
	tools::set_attribute(writingData, "openWeight", aut.series().representation()->open_weight);
	tools::set_attribute(writingData, "closeWeight", aut.series().representation()->close_weight);
	tools::set_attribute(writingData, "openPar", aut.series().representation()->open_par);
	tools::set_attribute(writingData, "closePar", aut.series().representation()->close_par);
	tools::set_attribute(writingData, "spacesSym", aut.series().representation()->spaces.front());

	root->appendChild(writingData);
      }

      // FIXME: We should be able to specialize for all type U,
      // whose letter_traits::kind() is "simple".
      template <typename U>
      struct create_monGen_node
      {
	void
	operator()(const U& letter,
		   xercesc::DOMDocument* doc,
		   xercesc::DOMElement* root)
	{
	  xercesc::DOMElement* gen = tools::create_element(doc, "monGen");

	  tools::set_attribute(gen, "value",
			       algebra::letter_traits<U>::
			       letter_to_literal(letter));

	  root->appendChild(gen);
	}
      };

      // FIXME: We should be able to specialize for all type U,
      // whose kind() is "tuple" and dim() is 2 and has_first is
      // true and has_second is true.
      template <typename U, typename V>
      struct create_monGen_node<std::pair<U, V> >
      {
	void
	operator()(const std::pair<U, V>& letter,
		   xercesc::DOMDocument* doc,
		   xercesc::DOMElement* root)
	{
	  xercesc::DOMElement* gen = tools::create_element(doc, "monGen");

	  std::stringstream sstr_first;
	  std::stringstream sstr_second;
	  xercesc::DOMElement* first = tools::create_element(doc, "monCompGen");
	  xercesc::DOMElement* second = tools::create_element(doc, "monCompGen");
	  sstr_first << letter.first;
	  sstr_second << letter.second;
	  tools::set_attribute(first, "value", sstr_first.str());
	  tools::set_attribute(second, "value", sstr_second.str());
	  gen->appendChild(first);
	  gen->appendChild(second);

	  root->appendChild(gen);
	}
      };

    } // ! builders

  } // ! xml

} // ! vcsn

#endif // ! VCSN_XML_BUILDERS_HXX
