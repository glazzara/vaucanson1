// handlers.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_HANDLERS_HXX
# define VCSN_XML_HANDLERS_HXX

# include <xercesc/util/XMLString.hpp>

# include <vaucanson/xml/tools.hh>

namespace vcsn
{
  namespace xml
  {
    /*
     * DocRegExpHandler
     */
    template <typename T>
    DocRegExpHandler<T>::DocRegExpHandler (xercesc::SAX2XMLReader* parser,
			       xercesc::DefaultHandler& root,
			       T& regexp,
			       XMLEq& eq)
      : Handler(parser, root, eq),
	regexp_(regexp),
	regexph_(parser, *this, regexp)
    {
    }

    template <typename T>
    void
    DocRegExpHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.fsmxml, localname))
      {
	// T version
	// T xmlns
	parser_->setContentHandler(&regexph_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    DocRegExpHandler<T>::end (const XMLCh* const,
			       const XMLCh* const,
			       const XMLCh* const)
    {
    }

    /*
     * DocAutHandler
     */
    template <typename T>
    DocAutHandler<T>::DocAutHandler (xercesc::SAX2XMLReader* parser,
			       xercesc::DefaultHandler& root,
			       T& aut,
			       XMLEq& eq)
      : Handler(parser, root, eq),
	aut_(aut),
	auth_(parser, *this, aut)
    {
    }

    template <typename T>
    void
    DocAutHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.fsmxml, localname))
      {
	// T version
	// T xmlns
	parser_->setContentHandler(&auth_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    DocAutHandler<T>::end (const XMLCh* const,
			       const XMLCh* const,
			       const XMLCh* const)
    {
    }

    /**
     * RegExpHandler
     */
    template <typename T>
    RegExpHandler<T>::RegExpHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T& regexp)
      : Handler(parser, root),
	regexp_(regexp),
	typeh_(parser, *this, regexp),
	contenth_(parser, *this, regexp, eq_.typedRegExp),
	unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    RegExpHandler<T>::start (const XMLCh* const uri,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.regExp, localname))
      {
	// nothing to do ?
      }
      else if (XMLString::equals(eq_.drawing, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.geometry, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.valueType, localname))
	parser_->setContentHandler(&typeh_);
      else if (XMLString::equals(eq_.typedRegExp, localname))
	parser_->setContentHandler(&contenth_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    RegExpHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.regExp, localname))
      {
	parser_->setContentHandler(&root_);
	regexp_ = contenth_.series();
      }
    }

    /**
     * AutHandler
     */
    template <typename T>
    AutHandler<T>::AutHandler (xercesc::SAX2XMLReader* parser,
			       Handler& root,
			       T& aut)
      : Handler(parser, root),
	aut_(aut),
	typeh_(parser, *this, aut),
	contenth_(parser, *this, aut),
	unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    AutHandler<T>::start (const XMLCh* const uri,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.automaton, localname))
      {
	const XMLCh* autname = tools::get_attribute(attrs, "name", uri);
	if (autname != 0)
	  aut_.geometry().name() = xmlstr(autname);
	// T readingDirection
      }
      else if (XMLString::equals(eq_.drawing, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.geometry, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.valueType, localname))
	parser_->setContentHandler(&typeh_);
      else if (XMLString::equals(eq_.content, localname))
	parser_->setContentHandler(&contenth_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    AutHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.automaton, localname))
	parser_->setContentHandler(&root_);
    }

    /**
     * TypeHandler
     */
    template <typename T>
    TypeHandler<T>::TypeHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& param)
      : Handler(parser, root),
        monoid_(0),
	semiring_(0),
	rep_(0),
	param_(param),
	monoidh_(0),
	reph_(0),
	semiringh_(0),
	unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    TypeHandler<T>::start(const XMLCh* const,
			  const XMLCh* const localname,
			  const XMLCh* const,
			  const xercesc::Attributes& attrs)
    {
      using namespace xercesc;

      if (XMLString::equals(eq_.semiring, localname))
      {
	semiring_ = builders::create_semiring(param_, localname, attrs);
	semiringh_ = builders::create_semiringh(*semiring_, attrs, parser_, *this);
	parser_->setContentHandler(semiringh_);
      }
      else if (XMLString::equals(eq_.monoid, localname))
      {
	monoid_ = builders::create_monoid(param_, localname, attrs, eq_);
	monoidh_ = builders::create_monoidh(*monoid_, attrs, parser_, *this);
	parser_->setContentHandler(monoidh_);
      }
      else if (XMLString::equals(eq_.writingData, localname))
      {
	rep_ = builders::create_series_representation(param_, localname, attrs, eq_);
	reph_ = builders::create_series_representationh(*rep_, attrs, parser_, *this, eq_);
	parser_->setContentHandler(reph_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    TypeHandler<T>::end(const XMLCh* const,
			const XMLCh* const localname,
			const XMLCh* const)
    {
      using namespace xercesc;


      // The series representation is optional.
      if (rep_)
      {
	typename T::series_set_t series(*semiring_, *monoid_, *rep_);
	param_.attach(series);
      }
      else
      {
	typename T::series_set_t series(*semiring_, *monoid_);
	param_.attach(series);
      }

      if (XMLString::equals(eq_.valueType, localname))
	parser_->setContentHandler(&root_);

      delete monoid_;
      delete monoidh_;
      delete rep_;
      delete reph_;
      delete semiring_;
      delete semiringh_;
    }

    /**
     * ContHandler
     */
    template <typename T>
    ContHandler<T>::ContHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& aut)
      : Handler(parser, root),
	aut_(aut),
	statesh_(parser, *this, aut, map_),
	transitionsh_(parser, *this, aut, map_)
    {
    }

    template <typename T>
    void
    ContHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.states, localname))
	parser_->setContentHandler(&statesh_);
      else if (XMLString::equals(eq_.transitions, localname))
	parser_->setContentHandler(&transitionsh_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    ContHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.content, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
    }

    /**
     * StatesHandler
     */
    template <typename T>
    StatesHandler<T>::StatesHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& aut,
				 map_t& map)
      : Handler(parser, root),
	aut_(aut),
	map_(map),
	stateh_(0)
    {
    }

    template <typename T>
    void
    StatesHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.state, localname))
      {
	hstate_t state = aut_.add_state();
	map_[xmlstr(tools::get_attribute(attrs, eq_.id))] = state;
	delete stateh_;
	stateh_ = new StateHandler<T>(parser_, *this, aut_, state);
	parser_->setContentHandler(stateh_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    StatesHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.states, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
      delete stateh_;
    }

    /**
     * StateHandler
     */
    template <typename T>
    StateHandler<T>::StateHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& aut,
				 hstate_t state)
      : Handler(parser, root),
	aut_(aut),
	state_(state),
	geometryh_(parser, *this, aut, state),
	unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    StateHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.drawing, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.geometry, localname))
      {
	typedef typename T::geometry_t::states_geometry_map_t gmap_t;

	double y = 0;
	double x = 0;
	if (tools::has_attribute(attrs, eq_.x))
	{
	  std::istringstream xstr(xmlstr(tools::get_attribute(attrs, eq_.x)));
	  xstr >> x;
	}
	if (tools::has_attribute(attrs, eq_.y))
	{
	  std::istringstream ystr(xmlstr(tools::get_attribute(attrs, eq_.y)));
	  ystr >> y;
	}
	gmap_t& map = aut_.geometry().states();
	map[state_] = std::make_pair(x,y);
	parser_->setContentHandler(&geometryh_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    StateHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.state, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
    }

    /**
     * TransitionsHandler
     */
    template <typename T>
    TransitionsHandler<T>::TransitionsHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& aut,
				 map_t& map)
      : Handler(parser, root),
	aut_(aut),
	map_(map),
	transitionh_(0)
    {
    }

    template <typename T>
    void
    TransitionsHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.transition, localname))
      {
	hstate_t src = map_[xmlstr(tools::get_attribute(attrs, eq_.source))];
	hstate_t dst = map_[xmlstr(tools::get_attribute(attrs, eq_.target))];
	delete transitionh_;
	transitionh_ = new TransitionHandler<T>(parser_, *this, aut_, src, dst);
	parser_->setContentHandler(transitionh_);
      }
      else if (XMLString::equals(eq_.final, localname))
      {
	hstate_t state = map_[xmlstr(tools::get_attribute(attrs, eq_.state))];
	delete transitionh_;
	transitionh_ = new InitFinalHandler<T>(parser_, *this, aut_, state, false);
	parser_->setContentHandler(transitionh_);
      }
      else if (XMLString::equals(eq_.initial, localname))
      {
	hstate_t state = map_[xmlstr(tools::get_attribute(attrs, eq_.state))];
	delete transitionh_;
	transitionh_ = new InitFinalHandler<T>(parser_, *this, aut_, state, true);
	parser_->setContentHandler(transitionh_);
      }
      else
	error::token(localname);
    }

    template <typename T>
    void
    TransitionsHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.transitions, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
      delete transitionh_;
    }

    /**
     * TransitionHandler
     */
    template <typename T>
    TransitionHandler<T>::TransitionHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& aut,
				 hstate_t src,
				 hstate_t dst)
      : Handler(parser, root),
	aut_(aut),
	src_(src),
	dst_(dst),
	s_(aut.series()),
	labelh_(parser, *this, s_, eq_.label),
	unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    TransitionHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.drawing, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.geometry, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.label, localname))
	parser_->setContentHandler(&labelh_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    TransitionHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.transition, localname))
      {
	parser_->setContentHandler(&root_);
	aut_.add_series_transition(src_, dst_, labelh_.series());
      }
      else
	error::token(localname);
    }

    /**
     * InitFinalHandler
     */
    template <typename T>
    InitFinalHandler<T>::InitFinalHandler (xercesc::SAX2XMLReader* parser,
				 Handler& root,
				 T& aut,
				 hstate_t state,
				 bool initial)
      : Handler(parser, root),
	aut_(aut),
	state_(state),
	initial_(initial),
	s_(aut.series().one_), // hack shouldn't exist.
	labelh_(parser, *this, s_, eq_.label),
	unsuph_(parser, *this)
    {
    }

    template <typename T>
    void
    InitFinalHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.drawing, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.geometry, localname))
	parser_->setContentHandler(&unsuph_);
      else if (XMLString::equals(eq_.label, localname))
	parser_->setContentHandler(&labelh_);
      else
	error::token(localname);
    }

    template <typename T>
    void
    InitFinalHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.initial, localname) && initial_)
      {
	parser_->setContentHandler(&root_);
	aut_.set_initial(state_, labelh_.series());
      }
      else if (XMLString::equals(eq_.final, localname) && !initial_)
      {
	parser_->setContentHandler(&root_);
	aut_.set_final(state_, labelh_.series());
      }
      else
	error::token(localname);
    }

    /**
     * GeometryHandler
     */
    template <typename T>
    GeometryHandler<T>::GeometryHandler (xercesc::SAX2XMLReader* parser,
				        Handler& root,
					T& aut,
					hstate_t state)
      : Handler(parser, root),
	aut_(aut),
	state_(state)
    {
    }

    template <typename T>
    void
    GeometryHandler<T>::start (const XMLCh* const,
				 const XMLCh* const localname,
				 const XMLCh* const,
				 const xercesc::Attributes&)
    {
      error::token(localname);
    }

    template <typename T>
    void
    GeometryHandler<T>::end (const XMLCh* const,
			       const XMLCh* const localname,
			       const XMLCh* const)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.geometry, localname))
	parser_->setContentHandler(&root_);
      else
	error::token(localname);
    }

    /**
     * RegExpHandler
     */
    template <typename T>
    RegexpHandler<T>*
    RegexpHandler<T>::create (const XMLCh* const localname)
    {
      using namespace xercesc;
      if (XMLString::equals(eq_.monElmt, localname))
	return builders::create_monElmth(parser_, *this, algebra::identity_as<typename T::value_t>::of(param_.structure()));
      else if (XMLString::equals(eq_.star, localname))
	return new StarHandler<T>(parser_, *this, algebra::identity_as<typename T::value_t>::of(param_.structure()));
      else if (XMLString::equals(eq_.leftExtMul, localname))
	return new ExtMulHandler<T>(parser_, *this, algebra::identity_as<typename T::value_t>::of(param_.structure()), true);
      else if (XMLString::equals(eq_.rightExtMul, localname))
	return new ExtMulHandler<T>(parser_, *this, algebra::identity_as<typename T::value_t>::of(param_.structure()), false);
      else if (XMLString::equals(eq_.sum, localname))
	return new SumHandler<T>(parser_, *this, algebra::identity_as<typename T::value_t>::of(param_.structure()));
      else if (XMLString::equals(eq_.product, localname))
	return new ProductHandler<T>(parser_, *this, algebra::identity_as<typename T::value_t>::of(param_.structure()));
      else if (XMLString::equals(eq_.one, localname))
	return new AtomHandler<T>(parser_, *this, algebra::identity_as<typename T::value_t>::of(param_.structure()), eq_.one);
      else if (XMLString::equals(eq_.zero, localname))
	return new AtomHandler<T>(parser_, *this, algebra::zero_as<typename T::value_t>::of(param_.structure()), eq_.zero);
      else
	return 0;
    }

    template <typename T>
    RegexpHandler<T>*
    RegexpHandler<T>::create_weight (const xercesc::Attributes& attrs)
    {
      using namespace xercesc;
      return builders::create_weighth(parser_, *this,
	algebra::identity_as<typename T::value_t>::of(param_.structure()), attrs);
    }
  } // !xml
} // !vcsn

#endif // !VCSN_XML_HANDLERS_HXX
