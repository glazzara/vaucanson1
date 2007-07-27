// handlers.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_HANDLERS_HH
# define VCSN_XML_HANDLERS_HH

/**
 * @file handlers.hxx
 *
 * Handler classes for xml automaton loading.
 *
 * @see vcsn::xml::builders
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

# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/xmleq.hh>

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>


namespace vcsn
{
  namespace xml
  {
    /*
     * Handler class
     */
    class Handler : public xercesc::DefaultHandler
    {
      public:
	Handler (xercesc::SAX2XMLReader* parser,
		 XMLEq& eq,
		 xercesc::DefaultHandler& root);

	void
	startElement (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs) = 0;
	void
	endElement (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname) = 0;
      protected:
	// Required to enable a change of the Handler while parsing.
	xercesc::SAX2XMLReader*	parser_;
	xercesc::DefaultHandler&	root_;

	XMLEq& eq_;
    };

    /*
     * ErrHandler class, error handler.
     */
    class ErrHandler : public xercesc::DefaultHandler
    {
      public:
	ErrHandler () : DefaultHandler() {}

	void
	warning (const xercesc::SAXParseException& exc);
	// Receive notification of a warning.
	void
	error (const xercesc::SAXParseException& exc);
	// Receive notification of a recoverable error.
	void
	fatalError (const xercesc::SAXParseException& exc);
	// Receive notification of a non-recoverable error.
	void
	resetErrors () {}
	// Reset the Error handler object on its reuse.
    };

# define HANDLER_DEF_FUN				\
  void							\
  startElement (const XMLCh* const uri,			\
		const XMLCh* const localname,		\
		const XMLCh* const qname,		\
		const xercesc::Attributes& attrs);	\
  void							\
  endElement (const XMLCh* const uri,			\
	      const XMLCh* const localname,		\
	      const XMLCh* const qname);

    /*
     * Predecls
     */
    template <typename T>
    class ContHandler;
    template <typename T>
    class TypeHandler;
    template <typename T>
    class TransitionsHandler;
    template <typename T>
    class StatesHandler;

    /*
     * UnsupHandler class, Handler dedicated to "eat" all part
     * of the format Vaucanson still not supports.
     */
    class UnsupHandler : public xercesc::DefaultHandler
    {
      public:
	UnsupHandler (xercesc::DefaultHandler& root,
		      xercesc::SAX2XMLReader* parser);

	void
	startElement (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	endElement (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
      private:
	xercesc::SAX2XMLReader*	parser_;
	xercesc::DefaultHandler&	root_;
	int		depth_;
    };

    /*
     * AutHandler class, Handler for <automaton> tag.
     */
    template <typename T>
    class AutHandler : public xercesc::DefaultHandler
    {
      public:
	AutHandler (T& aut,
		    xercesc::SAX2XMLReader* parser,
		    XMLEq& eq);

	void
	startElement (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	endElement (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
	// Used by SessHandler
	bool
	end ();

      private:
	xercesc::SAX2XMLReader*	parser_;
	XMLEq& eq_;
	// the automaton to be filled.
	T&			aut_;
	// used only for session management.
	bool			end_;

	// Handlers that could be called while parsing.
	UnsupHandler	unsuph_;
	ContHandler<T>	contenth_;
	TypeHandler<T>	typeh_;
    };

    /*
     * MonoidHandler class, dedicated to parse <monoid> tag.
     */
    class MonoidHandler : public Handler
    {
      public:
	MonoidHandler (xercesc::DefaultHandler& father,
		       xercesc::SAX2XMLReader* parser,
		       XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs) = 0;
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname) = 0;
    };
    template <typename T>
    class FreeMonoidHandler : public MonoidHandler
    {
      public:
	FreeMonoidHandler (xercesc::DefaultHandler& father,
			   T& monoid,
			   xercesc::SAX2XMLReader* parser,
			   XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      private:
	T&				monoid_;
    };
    template <typename T>
    class ProdMonoidHandler : public MonoidHandler
    {
      public:
	ProdMonoidHandler (xercesc::DefaultHandler& father,
			   T& monoid,
			   xercesc::SAX2XMLReader* parser,
			   XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      private:
	T&	monoid_;
	bool	first_;

	MonoidHandler*			monoidh_;
    };

    /*
     * SemiringHandler class, dedicated to parse <semiring> tag.
     */
    class SemiringHandler : public Handler
    {
      public:
	SemiringHandler (xercesc::DefaultHandler& father,
			 xercesc::SAX2XMLReader* parser,
			 XMLEq& eq);
    };
    template <typename T>
    class SeriesSemiringHandler : public SemiringHandler
    {
      public:
	SeriesSemiringHandler (xercesc::DefaultHandler& father,
			       T& semiring,
			       xercesc::SAX2XMLReader* parser,
			       XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      private:
	T&			semiring_;
	SemiringHandler*	semiringh_;
	MonoidHandler*		monoidh_;
    };
    template <typename T>
    class NumSemiringHandler : public SemiringHandler
    {
      public:
	NumSemiringHandler (xercesc::DefaultHandler& father,
			    T& semiring,
			    xercesc::SAX2XMLReader* parser,
			    XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      private:
	T&	semiring_;
    };

    /*
     * TypeHandler class, dedicated to parse <labelType> tag.
     */
    template <typename T>
    class TypeHandler : public Handler
    {
      public:
	TypeHandler (xercesc::DefaultHandler& father,
		     T& aut,
		     xercesc::SAX2XMLReader* parser,
		     XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      private:
	typedef typename T::monoid_t		monoid_t;
	typedef typename T::semiring_t		semiring_t;
	typedef typename T::series_set_t	series_set_t;

	monoid_t*			monoid_;
	semiring_t*			semiring_;

	T&				aut_;

	SemiringHandler*		semiringh_;
	MonoidHandler*			monoidh_;
    };

    /*
     * ContHandler class, dedicated to parse <content> tag.
     */
    template <typename T>
    class ContHandler : public Handler
    {
      public:
	ContHandler (xercesc::DefaultHandler& father,
		     T& aut,
		     xercesc::SAX2XMLReader* parser,
		     XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      private:
	typedef std::map<std::string, hstate_t> map_t;

	T&				aut_;
	TransitionsHandler<T>		transh_;
	StatesHandler<T>		statesh_;

	map_t				map_;
    };

    /*
     * StateHandler class, dedicated to parse <state> tag.
     */
    class StateHandler : public Handler
    {
      public:
	typedef std::map<std::string, hstate_t> map_t;

	StateHandler (xercesc::DefaultHandler& father,
		      map_t& map,
		      xercesc::SAX2XMLReader* parser,
		      XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);
	void reset (hstate_t* state);
      private:
	map_t&				map_;

	hstate_t*			state_;
	UnsupHandler	unsuph_;
    };

    /*
     * StatesHandler class, dedicated to parse <states> tag.
     */
    template <typename T>
    class StatesHandler : public Handler
    {
      public:
	typedef std::map<std::string, hstate_t> map_t;

	StatesHandler (xercesc::DefaultHandler& father,
		       T& aut,
		       map_t& map,
		       xercesc::SAX2XMLReader* parser,
		       XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      private:
	map_t&				map_;

	T&				aut_;
	StateHandler			stateh_;
    };

    /*
     * RegExpHandler class, dedicated to parse regular expression tag.
     */
    template <typename T>
    class RegExpHandler : public Handler
    {
      public:
	typedef typename T::series_set_elt_t series_set_elt_t;
	//typedef Element<typename T::series_set_t,
	//		rat::exp<typename T::monoid_elt_value_t,
	//			 typename T::semiring_elt_value_t> >
	//	series_set_elt_t;

	RegExpHandler (xercesc::DefaultHandler& father,
		       T& aut,
		       xercesc::SAX2XMLReader* parser,
		       XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs) = 0;
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname) = 0;

	series_set_elt_t
	get_series ();
      protected:
	T&				aut_;

	series_set_elt_t		krat_exp_;
    };

    template <typename T>
    class SumHandler : public RegExpHandler<T>
    {
      public:
	SumHandler (xercesc::DefaultHandler& father,
		    T& aut,
		    xercesc::SAX2XMLReader* parser,
		    XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      protected:
	bool			first_;
	RegExpHandler<T>*	lefth_;
	RegExpHandler<T>*	righth_;
    };
    template <typename T>
    class ProdHandler : public RegExpHandler<T>
    {
      public:
	ProdHandler (xercesc::DefaultHandler& father,
		     T& aut,
		     xercesc::SAX2XMLReader* parser,
		     XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      protected:
	bool			first_;
	RegExpHandler<T>*	lefth_;
	RegExpHandler<T>*	righth_;
    };
    template <typename T>
    class StarHandler : public RegExpHandler<T>
    {
      public:
	StarHandler (xercesc::DefaultHandler& father,
		     T& aut,
		     xercesc::SAX2XMLReader* parser,
		     XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);

      protected:
	RegExpHandler<T>*	sonh_;
    };
    template <typename T>
    class WordHandler : public RegExpHandler<T>
    {
      public:
	WordHandler (xercesc::DefaultHandler& father,
		     T& aut,
		     xercesc::SAX2XMLReader* parser,
		     XMLEq& eq,
		     typename RegExpHandler<T>::series_set_elt_t val);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);
    };

    /*
     * LabelHandler class, dedicated to parse <label> tag.
     */
    template <typename T>
    class LabelHandler : public RegExpHandler<T>
    {
      public:
	typedef typename T::series_set_elt_t series_set_elt_t;
	LabelHandler (xercesc::DefaultHandler& father,
		      T& aut,
		      xercesc::SAX2XMLReader* parser,
		      XMLEq& eq);

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);
	bool used ();
	void reset ();
	series_set_elt_t
	value();
      protected:
	RegExpHandler<T>*	sonh_;
	bool			used_;
    };

    /*
     * TransitionHandler class, dedicated to parse <transition> tag.
     */
    template <typename T>
    class TransitionHandler : public Handler
    {
      public:
	typedef std::map<std::string, hstate_t> map_t;
	typedef std::map<std::string, std::string> curattrs_t;

	TransitionHandler (xercesc::DefaultHandler& father,
			   T& aut,
			   map_t& map,
			   curattrs_t& attrs,
			   xercesc::SAX2XMLReader* parser,
			   XMLEq& eq);
	~TransitionHandler();

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);
      private:
	typedef typename T::series_set_elt_t	series_set_elt_t;

	curattrs_t&			attrs_;
	map_t&				map_;

	T&				aut_;
	UnsupHandler			unsuph_;
	LabelHandler<T>			labelh_;
    };

    /*
     * TransitionsHandler class, dedicated to parse <transitions> tag.
     */
    template <typename T>
    class TransitionsHandler : public Handler
    {
      public:
	typedef std::map<std::string, hstate_t> map_t;

	TransitionsHandler (xercesc::DefaultHandler& father,
			    T& aut,
			    map_t& map,
			    xercesc::SAX2XMLReader* parser,
			    XMLEq& eq);
	~TransitionsHandler();

	void startElement (const XMLCh* const uri,
			   const XMLCh* const localname,
			   const XMLCh* const qname,
			   const xercesc::Attributes& attrs);
	void endElement (const XMLCh* const uri,
			 const XMLCh* const localname,
			 const XMLCh* const qname);
      private:
	typedef typename T::series_set_elt_t	series_set_elt_t;
	typedef std::map<std::string, std::string> curattrs_t;

	curattrs_t			curattrs_;

	map_t&				map_;

	T&				aut_;
	//TransitionHandler<typename T::set_t, typename T::value_t>	transh_;
	TransitionHandler<T>	transh_;
    };

# undef HANDLER_DEF_FUN
  } // !xml
} // !vcsn

# if ! defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/handlers.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_XML_HANDLERS_HH
