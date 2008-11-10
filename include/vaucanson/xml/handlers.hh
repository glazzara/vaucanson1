// handlers.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_HANDLERS_HH
# define VCSN_XML_HANDLERS_HH

/**
 * @file handlers.hxx
 *
 * Handler classes for XML loading.
 *
 * @see vcsn::xml::parser
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <map>
# include <string>

# include <xercesc/sax2/SAX2XMLReader.hpp>
# include <xercesc/sax2/XMLReaderFactory.hpp>
# include <xercesc/sax2/DefaultHandler.hpp>
# include <xercesc/sax2/Attributes.hpp>

# include <xercesc/sax/SAXException.hpp>
# include <xercesc/util/XMLString.hpp>

# include <vaucanson/xml/xmleq.hh>
# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/handlers_base.hh>
# include <vaucanson/xml/builders.hh>
# include <vaucanson/xml/regexp.hh>

namespace vcsn
{
  namespace xml
  {
    /**
     * GeometryHandler class
     */
    template <typename T>
    class GeometryHandler : public Handler
    {
      public:
	typedef typename T::hstate_t		hstate_t;

	GeometryHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& aut,
		     hstate_t state);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	T&		aut_;
	hstate_t	state_;
    };
    /**
     * StateHandler class
     */
    template <typename T>
    class StateHandler : public Handler
    {
      public:
	typedef typename T::hstate_t		hstate_t;

	StateHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& aut,
		     hstate_t state);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	T&		aut_;
	hstate_t	state_;

	GeometryHandler<T>	geometryh_;
	UnsupHandler		unsuph_;
    };

    /**
     * StatesHandler class
     */
    template <typename T>
    class StatesHandler : public Handler
    {
      public:
	typedef typename T::hstate_t		hstate_t;
	typedef std::map<std::string, hstate_t> map_t;

	StatesHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& aut,
		     map_t& map);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	T&	aut_;
	map_t&	map_;

	StateHandler<T>*	stateh_;
    };

    /**
     * TransitionHandler class
     */
    template <typename T>
    class TransitionHandler : public Handler
    {
      public:
	typedef typename T::hstate_t	hstate_t;
	TransitionHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& aut,
		     hstate_t src,
		     hstate_t dst);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);

      private:
	typedef typename T::series_set_elt_t	series_set_elt_t;
	T&			aut_;
	hstate_t		src_;
	hstate_t		dst_;

	series_set_elt_t		s_;

	RegexpHandler<series_set_elt_t>	labelh_;
	UnsupHandler		unsuph_;
    };

    /**
     * InitFinalHandler class
     */
    template <typename T>
    class InitFinalHandler : public Handler
    {
      public:
	typedef typename T::hstate_t	hstate_t;
	InitFinalHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& aut,
		     hstate_t state,
		     bool initial = true);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);

      private:
	typedef typename T::series_set_elt_t	series_set_elt_t;
	T&			aut_;
	hstate_t		state_;

	bool			initial_;
	series_set_elt_t	s_;

	RegexpHandler<series_set_elt_t>	labelh_;
	UnsupHandler		unsuph_;
    };

    /**
     * TransitionsHandler class
     */
    template <typename T>
    class TransitionsHandler : public Handler
    {
      public:
	typedef typename T::hstate_t		    hstate_t;
	typedef std::map<std::string, hstate_t>	    map_t;

	TransitionsHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& aut,
		     map_t& map);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	T&			aut_;
	map_t&			map_;

	Handler*	transitionh_;
    };

    /**
     * ContHandler class
     */
    template <typename T>
    class ContHandler : public Handler
    {
      public:
	ContHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& aut);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	typedef typename T::hstate_t		    hstate_t;
	typedef std::map<std::string, hstate_t>	    map_t;

	T&	aut_;
	map_t	map_;


	StatesHandler<T>	statesh_;
	TransitionsHandler<T>	transitionsh_;
    };

    /**
     * TypeHandler class
     */
    template <typename T>
    class TypeHandler : public Handler
    {
      public:
	TypeHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& param);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	typedef typename T::monoid_t		monoid_t;
	typedef typename T::semiring_t		semiring_t;
	typedef typename T::series_set_t	series_set_t;

	monoid_t*			monoid_;
	semiring_t*			semiring_;

	// FIXME: maybe we should rename this attribute to aut_,
	// as with all the other handlers.
	T&		param_;
	Handler*	monoidh_;
	Handler*	semiringh_;
    };

    /**
     * AutHandler class
     */
    template <typename T>
    class AutHandler : public Handler
    {
      public:
	AutHandler (xercesc::SAX2XMLReader* parser,
		    Handler& root,
		    T& aut);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	T&			aut_;

	TypeHandler<T>	typeh_;
	ContHandler<T>	contenth_;
	UnsupHandler	unsuph_;
    };

    /**
     * DocHandler class, root class
     * Read <fsmxml>
     */
    template <typename T>
    class DocHandler : public Handler
    {
      public:
	DocHandler (xercesc::SAX2XMLReader* parser,
		    xercesc::DefaultHandler& root,
		    T& aut,
		    XMLEq& eq);
	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	T& aut_;

	AutHandler<T>	auth_;
	//TypeHandler<T>	typeh_;
    };

  } // !xml
} // !vcsn

# if ! defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/handlers.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_XML_HANDLERS_HH
