// builders.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_BUILDERS_HH
# define VCSN_XML_BUILDERS_HH

/**
 * @file builders.hh
 *
 * Tools to help loading automata.
 *
 * @see vcsn::xml::*Handler
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <string>

// These includes are here to satisfy sanity checks, but we need a way
// to force the inclusion of the XML related headers after the automaton
// type is fully constructed (no undefined_type), and improve sanity
// checks.
# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>
# include <vaucanson/algebra/implementation/series/series.hh>

# include <xercesc/sax2/Attributes.hpp>
# include <xercesc/util/XMLString.hpp>
# include <xercesc/dom/DOM.hpp>

# include <vaucanson/xml/handlers_base.hh>

namespace vcsn
{
  namespace xml
  {
    /**
     * monGenAction
     */
    template <typename T>
    class monGenAction
    {
    public:
      monGenAction(const T&);
    };

    // An action on a free monoid (insert monGen inside its alphabet)
    template <typename T>
    class monGenAction<vcsn::algebra::FreeMonoid<T> >
    {
    public:
      typedef vcsn::algebra::FreeMonoid<T> self_t;
      typedef typename self_t::alphabet_t alphabet_t;

      monGenAction(self_t&);
      void operator () (const std::string&);
    private:
      alphabet_t& alphabet_;
    };

    // An action on a series element (multiply it by monGen)
    template <typename T, typename U, typename V>
    class monGenAction<vcsn::Element<vcsn::algebra::Series<T, U>, V> >
    {
    public:
      typedef vcsn::Element<vcsn::algebra::Series<T, U>, V> self_t;

      monGenAction(self_t&);
      void operator () (const std::string&);
    private:
      self_t& s_;
    };

    /**
     * monGenHandler
     * 
     * @arg T the type of the monoid
     * @arg U the type of the object we will act on
     */
    template <typename T, typename U>
    class monGenHandler : public Handler
    {
      public:
	monGenHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     const monGenAction<U>& action,
		     const XMLCh* value = 0);

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
	const XMLCh*	value_;

	// What to do with value_.
	monGenAction<U>	action_;
    };

    /**
     * monGenTupleHandler
     * 
     * @arg T the type of the monoid
     * @arg U the type of the object we will act on
     */
    template <typename T, typename U>
    class monGenTupleHandler : public Handler
    {
      public:
	monGenTupleHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     const monGenAction<U>& action);

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
	std::string	value_;
	bool		wait_begin_;
	int		count_;

	// What to do with value_.
	monGenAction<U>	action_;
    };

    /**
     * FreeMonoidHandler
     */
    template <typename T>
    class FreeMonoidHandler : public Handler
    {
      public:
	FreeMonoidHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& monoid);

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
	T&		monoid_;

	Handler*	mongenh_;
	UnsupHandler	unsuph_;
    };

    namespace builders
    {
      template <typename T>
      typename T::monoid_t*
      create_monoid (T&,
		     const XMLCh* const localname,
		     const xercesc::Attributes& attrs);

      template <typename T>
      Handler*
      create_monoidh (T& monoid,
		      const xercesc::Attributes& attrs,
		      xercesc::SAX2XMLReader* parser,
		      Handler& root);

    } // !builders

    /**
     * NumSemiringHandler
     */
    template <typename T>
    class NumSemiringHandler : public Handler
    {
      public:
	NumSemiringHandler (xercesc::SAX2XMLReader* parser,
		     Handler& root,
		     T& semiring);

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
	T&		semiring_;

	UnsupHandler	unsuph_;
    };

    namespace builders
    {
      template <typename T>
      typename T::semiring_t*
      create_semiring (T&,
		       const XMLCh* const localname,
		       const xercesc::Attributes& attrs);

      template <typename T>
      Handler*
      create_semiringh (T& semiring,
			const xercesc::Attributes& attrs,
			xercesc::SAX2XMLReader* parser,
			Handler& root);

    } // !builders

    /**
     * monElmtHandler
     */
    template <typename T>
    class RegexpHandler;

    namespace builders
    {

      template <typename S, typename T>
      RegexpHandler<S>*
      create_monElmth(xercesc::SAX2XMLReader* parser,
		      RegexpHandler<T>& root,
		      S param);

      template <typename T>
      RegexpHandler<T>*
      create_weight(xercesc::SAX2XMLReader* parser,
		    RegexpHandler<T>& root,
		    T param,
		    const xercesc::Attributes& attrs);
    } // !builders

    /**
     * Consistency
     */
    namespace builders
    {
      template <typename T>
      void
      check_monoid_consistency (T& param,
				const XMLCh* const localname,
			        const xercesc::Attributes& attrs);

      template <typename T>
      void
      check_semiring_consistency (T& param,
				  const XMLCh* const localname,
				  const xercesc::Attributes& attrs);
    } // !builders

    /**
     *
     */
    namespace builders
    {
      template <typename T>
      void
      create_semiring_node(const T& semiring,
			   xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root);

      template <typename T>
      void
      create_monoid_node(const T& monoid,
			 xercesc::DOMDocument* doc,
			 xercesc::DOMElement* root);

      template <typename T>
      void
      create_regexp_node(const T&,
			 xercesc::DOMDocument* doc,
			 xercesc::DOMElement* root);

      template <typename T>
      void
      create_monElmt_node(const T&,
			  xercesc::DOMDocument* doc,
			  xercesc::DOMElement* root);

      // Functor to allow partial specialization.
      template <typename T>
      struct
      create_monGen_node;

    } // ! builders

  } // ! xml

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/builders.hxx>
# endif // VCSN_USE_INTERFACE_ONLY || !VCSN_USE_LIB

#endif // !VCSN_XML_BUILDERS_HH
