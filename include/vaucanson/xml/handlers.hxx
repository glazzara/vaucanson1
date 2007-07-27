// handlers.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007 The Vaucanson Group.
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

#ifndef HANDLERS_HXX
# define HANDLERS_HXX

/**
 * @file handler.hxx
 *
 * Abstract class for all handler dedicated to parse an XML Automaton
 *
 * @see vcsn::xml::builders
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */


# include <iostream>
# include <xercesc/sax2/Attributes.hpp>

# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/builders.hh>

namespace vcsn
{
  namespace xml
  {
    /*
     * ErrHandler
     */
    void
    ErrHandler::warning (const xercesc::SAXParseException& exc)
    {
      char* msg = xercesc::XMLString::transcode(exc.getMessage());
      std::cout << "Warning: " << msg << std::endl;
      xercesc::XMLString::release(&msg);
    }

    void
    ErrHandler::error (const xercesc::SAXParseException& exc)
    {
      char* msg = xercesc::XMLString::transcode(exc.getMessage());
      std::cout << "Error: " << msg << std::endl;
      xercesc::XMLString::release(&msg);
    }

    void
    ErrHandler::fatalError (const xercesc::SAXParseException& exc)
    {
      char* msg = xercesc::XMLString::transcode(exc.getMessage());
      std::cout << "Fatal error: " << msg << std::endl;
      xercesc::XMLString::release(&msg);
    }

    /*
     * Handler
     */
    Handler::Handler (xercesc::SAX2XMLReader* parser,
		      XMLEq& eq,
		      xercesc::DefaultHandler& root)
      : DefaultHandler(),
	parser_(parser),
	root_(root),
	eq_(eq)
    {
    }

    /*
     * UnsupHandler
     */
    UnsupHandler::UnsupHandler (xercesc::DefaultHandler& root,
				xercesc::SAX2XMLReader* parser)
      : DefaultHandler(),
        parser_(parser),
	root_(root),
	depth_(1)
    {
    }

    void
    UnsupHandler::startElement (const XMLCh* const,
				const XMLCh* const,
				const XMLCh* const,
				const xercesc::Attributes&)
    {
      depth_++;
    }

    void
    UnsupHandler::endElement (const XMLCh* const,
			      const XMLCh* const,
			      const XMLCh* const)
    {
      depth_--;
      if (depth_ <= 0)
      {
	parser_->setContentHandler(&root_);
	depth_ = 1;
      }
    }

    /*
     * AutHandler
     */
    template <typename T>
    AutHandler<T>::AutHandler (T& aut,
			       xercesc::SAX2XMLReader* parser,
			       XMLEq& eq)
      : DefaultHandler(),
	parser_(parser),
	eq_(eq),
	aut_(aut),
	end_(false),
	unsuph_(*this, parser),
	contenth_(*this, aut, parser, eq),
	typeh_(*this, aut, parser, eq)
    {
    }

    template <typename T>
    void
    AutHandler<T>::startElement (const XMLCh* const uri,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.automaton, localname) && !end_)
      {
	const XMLCh* autname = builders::get_attribute(attrs, "name", uri);
	if (autname != 0)
	  aut_.geometry().name() = xml2str(autname);
      }
      else // <labelType>, <content>
      {
	if (XMLString::equals(eq_.type, localname))
	  parser_->setContentHandler(&typeh_);
	else
	  if (XMLString::equals(eq_.content, localname))
	    parser_->setContentHandler(&contenth_);
	  else
	    if (XMLString::equals(eq_.drawing, localname))
	      parser_->setContentHandler(&unsuph_);
	    else
	      if (XMLString::equals(eq_.geometry, localname))
		parser_->setContentHandler(&unsuph_);
	      // else
	      // <FSMXML>
      }
    }

    template <typename T>
    void
    AutHandler<T>::endElement (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.automaton, localname))
	end_ = true;
    }

    template <typename T>
    bool
    AutHandler<T>::end ()
    {
      return end_;
    }

    /*
     * TypeHandler
     */
    template <typename T>
    TypeHandler<T>::TypeHandler (xercesc::DefaultHandler& root,
				 T& aut,
				 xercesc::SAX2XMLReader* parser,
				 XMLEq& eq)
      : Handler(parser, eq, root),
	aut_(aut)
    {
    }

    template <typename T>
    void
    TypeHandler<T>::startElement (const XMLCh* const,
				  const XMLCh* const localname,
				  const XMLCh* const,
				  const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      // Possible optimisation :
      // - using a simple boolean better than a comparison
      if (XMLString::equals(eq_.monoid, localname))
      {
	monoid_ = builders::create_monoid(aut_, attrs);
	monoidh_ = builders::monoidh_factory(*monoid_, attrs, *this, parser_, eq_);
	parser_->setContentHandler(monoidh_);
      }
      else // <semiring>, <numericalSemiring>
      {
	// Attach the alphabet to the autmaton
	series_set_t	series(aut_.structure().series().semiring(), *monoid_);
	aut_.attach(series);

	// parse semiring
	semiring_ = builders::create_semiring(aut_, attrs);
	semiringh_ = builders::semiringh_factory(aut_, attrs, *semiring_, *this, parser_, eq_);
	parser_->setContentHandler(semiringh_);
      }
    }

    template <typename T>
    void
    TypeHandler<T>::endElement (const XMLCh* const,
			        const XMLCh* const localname,
			        const XMLCh* const)
    {
      using namespace xercesc;

      // Attach the semiring to the automaton
      series_set_t	series(*semiring_, aut_.structure().series().monoid());
      aut_.attach(series);

      delete semiringh_;
      delete monoidh_;
      delete semiring_;
      delete monoid_;
      if (XMLString::equals(eq_.type, localname))
	parser_->setContentHandler(&root_);
  } // !xml

    /*
     * MonoidHandler
     */
    MonoidHandler::MonoidHandler (xercesc::DefaultHandler& root,
				  xercesc::SAX2XMLReader* parser,
				  XMLEq& eq)
      : Handler(parser, eq, root)
    {
    }

    /*
     * FreeMonoidHandler
     */
    template <typename T>
    FreeMonoidHandler<T>::FreeMonoidHandler (xercesc::DefaultHandler& root,
					     T& monoid,
					     xercesc::SAX2XMLReader* parser,
					     XMLEq& eq)
      : MonoidHandler(root, parser, eq),
	monoid_(monoid)
    {
    }

    template <typename T>
    void
    FreeMonoidHandler<T>::startElement (const XMLCh* const,
					const XMLCh* const,
					const XMLCh* const,
					const xercesc::Attributes& attrs)
    {
      // Should necessary be a <generator> tag
      const XMLCh* value = builders::get_attribute(attrs, "value");
      std::string letter = xml2str(value);
      builders::insert_letter(monoid_, letter);
    }

    template <typename T>
    void
    FreeMonoidHandler<T>::endElement (const XMLCh* const,
				      const XMLCh* const localname,
				      const XMLCh* const)
    {
      if (xercesc::XMLString::equals(eq_.monoid, localname))
	parser_->setContentHandler(&root_);
    }
    /*
     * ProdMonoidHandler
     */
    template <typename T>
    ProdMonoidHandler<T>::ProdMonoidHandler (xercesc::DefaultHandler& root,
					     T& monoid,
					     xercesc::SAX2XMLReader* parser,
					     XMLEq& eq)
      : MonoidHandler(root, parser, eq),
	monoid_(monoid),
	first_(true)
    {
    }

    template <typename T>
    void
    ProdMonoidHandler<T>::startElement (const XMLCh* const,
					const XMLCh* const,
					const XMLCh* const,
					const xercesc::Attributes& attrs)
    {
      if (first_)
      {
	monoidh_ = builders::monoidh_factory(monoid_.first_monoid(), attrs, *this, parser_, eq_);
	first_ = false;
      }
      else
      {
	delete monoidh_;
	monoidh_ = builders::monoidh_factory(monoid_.second_monoid(), attrs, *this, parser_, eq_);
      }
      parser_->setContentHandler(monoidh_);
    }

    template <typename T>
    void
    ProdMonoidHandler<T>::endElement (const XMLCh* const,
				      const XMLCh* const,
				      const XMLCh* const)
    {
      delete monoidh_;
      parser_->setContentHandler(&root_);
    }

    /*
     * SemiringHandler
     */
    SemiringHandler::SemiringHandler (xercesc::DefaultHandler& root,
				      xercesc::SAX2XMLReader* parser,
				      XMLEq& eq)
      : Handler(parser, eq, root)
    {
    }
    /*
     * SeriesSemiringHandler
     */
    template <typename T>
    SeriesSemiringHandler<T>::SeriesSemiringHandler (xercesc::DefaultHandler& root,
						     T& semiring,
						     xercesc::SAX2XMLReader* parser,
						     XMLEq& eq)
      : SemiringHandler(root, parser, eq),
	semiring_(semiring)
    {
    }

    template <typename T>
    void
    SeriesSemiringHandler<T>::startElement (const XMLCh* const,
					    const XMLCh* const localname,
					    const XMLCh* const,
					    const xercesc::Attributes& attrs)
    {
      using namespace xercesc;

      if (XMLString::equals(eq_.monoid, localname))
      {
	monoidh_ = builders::monoidh_factory(const_cast
					     <typename T::monoid_t&>
					     (semiring_.monoid()), attrs, *this, parser_, eq_);
	parser_->setContentHandler(monoidh_);
      }
      else
      {
	semiringh_ = builders::semiringh_factory(semiring_, attrs, semiring_.semiring(),
						 *this, parser_, eq_);
	parser_->setContentHandler(semiringh_);
      }
    }

    template <typename T>
    void
    SeriesSemiringHandler<T>::endElement (const XMLCh* const,
					  const XMLCh* const,
					  const XMLCh* const)
    {
      delete monoidh_;
      delete semiringh_;
      parser_->setContentHandler(&root_);
    }
    /*
     * NumSemiringHandler
     */
    template <typename T>
    NumSemiringHandler<T>::NumSemiringHandler (xercesc::DefaultHandler& root,
					       T& semiring,
					       xercesc::SAX2XMLReader* parser,
					       XMLEq& eq)
      : SemiringHandler(root, parser, eq),
	semiring_(semiring)
    {
    }

    template <typename T>
    void
    NumSemiringHandler<T>::startElement (const XMLCh* const,
					    const XMLCh* const,
					    const XMLCh* const,
					    const xercesc::Attributes&)
    {
    }

    template <typename T>
    void
    NumSemiringHandler<T>::endElement (const XMLCh* const,
					  const XMLCh* const,
					  const XMLCh* const)
    {
      parser_->setContentHandler(&root_);
    }

    /*
     * ContentHandler
     */
    template <typename T>
    ContHandler<T>::ContHandler (xercesc::DefaultHandler& root,
				 T& aut,
				 xercesc::SAX2XMLReader* parser,
				 XMLEq& eq)
      : Handler(parser, eq, root),
	aut_(aut),
	transh_(*this, aut, map_, parser, eq),
	statesh_(*this, aut, map_, parser, eq)
    {
    }

    template <typename T>
    void
    ContHandler<T>::startElement (const XMLCh* const,
				  const XMLCh* const localname,
				  const XMLCh* const,
				  const xercesc::Attributes&)
    {
      using namespace xercesc;

      // Possible optimisation :
      // - using a simple boolean better than a comparaison
      if (XMLString::equals(eq_.states, localname))
	parser_->setContentHandler(&statesh_);
      else
	parser_->setContentHandler(&transh_);
    }

    template <typename T>
    void
    ContHandler<T>::endElement (const XMLCh* const,
			        const XMLCh* const,
			        const XMLCh* const)
    {
      parser_->setContentHandler(&root_);
    }

    /*
     * StatesHandler
     */
    template <typename T>
    StatesHandler<T>::StatesHandler (xercesc::DefaultHandler& root,
				     T& aut,
				     map_t& map,
				     xercesc::SAX2XMLReader* parser,
				     XMLEq& eq)
      : Handler(parser, eq, root),
	map_(map),
	aut_(aut),
	stateh_(*this, map_, parser, eq)
    {
    }

    template <typename T>
    void
    StatesHandler<T>::startElement (const XMLCh* const,
				    const XMLCh* const,
				    const XMLCh* const,
				    const xercesc::Attributes& attrs)
    {
      hstate_t state = aut_.add_state();
      map_[xml2str(builders::get_attribute(attrs, "name"))] = state;

      stateh_.reset(&state);
      parser_->setContentHandler(&stateh_);
    }

    template <typename T>
    void
    StatesHandler<T>::endElement (const XMLCh* const,
				  const XMLCh* const,
				  const XMLCh* const)
    {
      parser_->setContentHandler(&root_);
    }

    /*
     * StateHandler
     */
    StateHandler::StateHandler (xercesc::DefaultHandler& root,
				map_t& map,
				xercesc::SAX2XMLReader* parser,
				XMLEq& eq)
      : Handler(parser, eq, root),
	map_(map),
	unsuph_(*this, parser)
    {
    }

    void
    StateHandler::startElement (const XMLCh* const,
				const XMLCh* const,
				const XMLCh* const,
				const xercesc::Attributes&)
    {
      // geometry / drawing
      parser_->setContentHandler(&unsuph_);
    }

    void
    StateHandler::endElement (const XMLCh* const,
			      const XMLCh* const localname,
			      const XMLCh* const)
    {
      if (xercesc::XMLString::equals(eq_.state, localname))
	parser_->setContentHandler(&root_);
    }

    void
    StateHandler::reset (hstate_t* state)
    {
      state_ = state;
    }

    /*
     * RegExpHandler
     */
    template <typename T>
    RegExpHandler<T>::RegExpHandler (xercesc::DefaultHandler& root,
				     T& aut,
				     xercesc::SAX2XMLReader* parser,
				     XMLEq& eq)
      : Handler(parser, eq, root),
	aut_(aut),
	krat_exp_(aut.structure().series())
    {
    }

    template <typename T>
    typename RegExpHandler<T>::series_set_elt_t
    RegExpHandler<T>::get_series()
    {
      return krat_exp_;
    }

    template <typename T>
    SumHandler<T>::SumHandler (xercesc::DefaultHandler& root,
			       T& aut,
			       xercesc::SAX2XMLReader* parser,
			       XMLEq& eq)
      : RegExpHandler<T>(root, aut, parser, eq),
	first_(true)
    {
    }
    template <typename T>
    void
    SumHandler<T>::startElement (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      if (first_)
      {
	lefth_ = builders::labelh_factory(*this, this->aut_,
					  this->parser_, this->eq_,
					  localname, attrs);
	this->parser_->setContentHandler(lefth_);
      }
      else
      {
	righth_ = builders::labelh_factory(*this, this->aut_,
					  this->parser_, this->eq_,
					  localname, attrs);
	this->parser_->setContentHandler(righth_);
      }
      first_ = false;
    }
    template <typename T>
    void
    SumHandler<T>::endElement (const XMLCh* const,
			       const XMLCh* const,
			       const XMLCh* const)
    {
      this->krat_exp_ = lefth_->get_series() + righth_->get_series();
      this->parser_->setContentHandler(&this->root_);
      delete lefth_;
      delete righth_;
    }

    template <typename T>
    ProdHandler<T>::ProdHandler (xercesc::DefaultHandler& root,
				 T& aut,
				 xercesc::SAX2XMLReader* parser,
				 XMLEq& eq)
      : RegExpHandler<T>(root, aut, parser, eq),
	first_(true)
    {
    }
    template <typename T>
    void
    ProdHandler<T>::startElement (const XMLCh* const,
				  const XMLCh* const localname,
				  const XMLCh* const,
				  const xercesc::Attributes& attrs)
    {
      if (first_)
      {
	lefth_ = builders::labelh_factory(*this, this->aut_,
					  this->parser_, this->eq_,
					  localname, attrs);
	this->parser_->setContentHandler(lefth_);
      }
      else
      {
	righth_ = builders::labelh_factory(*this, this->aut_,
					  this->parser_, this->eq_,
					  localname, attrs);
	this->parser_->setContentHandler(righth_);
      }
      first_ = false;
    }
    template <typename T>
    void
    ProdHandler<T>::endElement (const XMLCh* const,
			        const XMLCh* const,
			        const XMLCh* const)
    {
      this->krat_exp_ = lefth_->get_series() * righth_->get_series();
      this->parser_->setContentHandler(&this->root_);
      delete lefth_;
      delete righth_;
    }

    template <typename T>
    StarHandler<T>::StarHandler (xercesc::DefaultHandler& root,
			         T& aut,
			         xercesc::SAX2XMLReader* parser,
			         XMLEq& eq)
      : RegExpHandler<T>(root, aut, parser, eq)
    {
    }
    template <typename T>
    void
    StarHandler<T>::startElement (const XMLCh* const,
				  const XMLCh* const localname,
				  const XMLCh* const,
				  const xercesc::Attributes& attrs)
    {
      sonh_ = builders::labelh_factory(*this, this->aut_,
				       this->parser_, this->eq_,
				       localname, attrs);
      this->parser_->setContentHandler(sonh_);
    }
    template <typename T>
    void
    StarHandler<T>::endElement (const XMLCh* const,
			        const XMLCh* const,
			        const XMLCh* const)
    {
      this->krat_exp_ = sonh_->get_series().star();
      this->parser_->setContentHandler(&this->root_);
      delete sonh_;
    }

    template <typename T>
    WordHandler<T>::WordHandler (xercesc::DefaultHandler& root,
				 T& aut,
				 xercesc::SAX2XMLReader* parser,
				 XMLEq& eq,
				 typename RegExpHandler<T>::series_set_elt_t val)
      : RegExpHandler<T>(root, aut, parser, eq)
    {
      this->krat_exp_ = val;
    }
    template <typename T>
    void
    WordHandler<T>::startElement (const XMLCh* const,
				  const XMLCh* const,
				  const XMLCh* const,
				  const xercesc::Attributes&)
    {
    }
    template <typename T>
    void
    WordHandler<T>::endElement (const XMLCh* const,
			        const XMLCh* const,
			        const XMLCh* const)
    {
      this->parser_->setContentHandler(&this->root_);
    }
    template <typename T>
    LabelHandler<T>::LabelHandler (xercesc::DefaultHandler& root,
				   T& aut,
				   xercesc::SAX2XMLReader* parser,
				   XMLEq& eq)
      : RegExpHandler<T>(root, aut, parser, eq),
	used_(false)
    {
    }
    template <typename T>
    void
    LabelHandler<T>::startElement (const XMLCh* const,
				   const XMLCh* const localname,
				   const XMLCh* const,
				   const xercesc::Attributes& attrs)
    {
      used_ = true;
      sonh_ = builders::labelh_factory(*this, this->aut_,
				       this->parser_, this->eq_,
				       localname, attrs);
      this->parser_->setContentHandler(sonh_);
    }
    template <typename T>
    void
    LabelHandler<T>::endElement (const XMLCh* const,
			         const XMLCh* const,
			         const XMLCh* const)
    {
      this->krat_exp_ = sonh_->get_series();
      this->parser_->setContentHandler(&this->root_);
    }
    template <typename T>
    bool
    LabelHandler<T>::used ()
    {
      return used_;
    }
    template <typename T>
    void
    LabelHandler<T>::reset ()
    {
      used_ = false;
      this->krat_exp_ = typename RegExpHandler<T>::series_set_elt_t(this->aut_.structure().series());
    }

    template <typename T>
    typename LabelHandler<T>::series_set_elt_t
    LabelHandler<T>::value ()
    {
      return this->krat_exp_;
    }

    /*
     * TransitionsHandler
     */
    template <typename T>
    TransitionsHandler<T>::TransitionsHandler (xercesc::DefaultHandler& root,
					       T& aut,
					       map_t& map,
					       xercesc::SAX2XMLReader* parser,
					       XMLEq& eq)
      : Handler(parser, eq, root),
	map_(map),
	aut_(aut),
	transh_(*this, aut, map, curattrs_, parser, eq)
    {
    }

    template <typename T>
    TransitionsHandler<T>::~TransitionsHandler()
    {
    }

    template <typename T>
    void
    TransitionsHandler<T>::startElement (const XMLCh* const,
					 const XMLCh* const,
					 const XMLCh* const,
					 const xercesc::Attributes& attrs)
    {
      curattrs_.clear();
      for (unsigned int i = 0; i < attrs.getLength(); i++)
	curattrs_[xml2str(attrs.getLocalName(i))] =  xml2str(attrs.getValue(i));
      parser_->setContentHandler(&transh_);
    }

    template <typename T>
    void
    TransitionsHandler<T>::endElement (const XMLCh* const,
				       const XMLCh* const,
				       const XMLCh* const)
    {
      parser_->setContentHandler(&root_);
    }


    /*
     * TransitionHandler
     */
    template <typename T>
    TransitionHandler<T>::TransitionHandler (xercesc::DefaultHandler& root,
					     T& aut,
					     map_t& map,
					     curattrs_t& attrs,
					     xercesc::SAX2XMLReader* parser,
					     XMLEq& eq)
      : Handler(parser, eq, root),
	attrs_(attrs),
	map_(map),
	aut_(aut),
	unsuph_(*this, parser),
	labelh_(*this, aut, parser, eq)
    {
    }

    template <typename T>
    void
    TransitionHandler<T>::startElement (const XMLCh* const,
					const XMLCh* const localname,
					const XMLCh* const,
					const xercesc::Attributes&)
    {
      if (xercesc::XMLString::equals(eq_.label, localname))
	parser_->setContentHandler(&labelh_);
      else
	if (xercesc::XMLString::equals(eq_.drawing, localname))
	  parser_->setContentHandler(&unsuph_);
	else
	  if (xercesc::XMLString::equals(eq_.geometry, localname))
	    parser_->setContentHandler(&unsuph_);
    }

    template <typename T>
    TransitionHandler<T>::~TransitionHandler ()
    {
    }

    template <typename T>
    void
    TransitionHandler<T>::endElement (const XMLCh* const,
				      const XMLCh* const localname,
				      const XMLCh* const)
    {
      if (xercesc::XMLString::equals(eq_.transition, localname))
      {
	typename T::series_set_elt_t s =
	  builders::get_series_transition(aut_, attrs_, labelh_);

	// no checks are made because the xsd ensure the existence of these keys
	hstate_t src = map_[attrs_["src"]];
	hstate_t dst = map_[attrs_["dst"]];
	htransition_t e = aut_.add_series_transition(src, dst, s);
      }
      else // tag == "initial" || tag == "final"
      {
	typename T::series_set_elt_t s =
	  builders::get_series_transition(aut_, attrs_, labelh_);

	// no checks are made because the xsd ensure the existence of this key
	hstate_t state = map_[attrs_["state"]];
	if (xercesc::XMLString::equals(eq_.initial, localname))
	  aut_.set_initial(state, s);
	else // tag == "final"
	  aut_.set_final(state, s);
      }
      labelh_.reset();
      parser_->setContentHandler(&root_);
    }
  } // !xml
} // !vcsn

#endif /* !HANDLERS_HXX */
