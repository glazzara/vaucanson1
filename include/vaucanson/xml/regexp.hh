// regexp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008, 2011 The Vaucanson Group.
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

#ifndef VCSN_XML_REGEXP_HH
# define VCSN_XML_REGEXP_HH

/**
 * @file regexp.hxx
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

namespace vcsn
{
  namespace xml
  {
    /**
     * RegexpHandler class
     */
    template <typename T>
    class RegexpHandler : public Handler
    {
      public:
	RegexpHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param);
	RegexpHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param,
		       XMLCh* end);
	virtual ~RegexpHandler ();

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);

	T& series();

	T& series(T& param);
	// Create the Handler accordingly to localname
	// Return 0 if localname is incorrect.
	RegexpHandler<T>*
	create (const XMLCh* const localname);

      protected:
	RegexpHandler<T>*
	create_weight (const xercesc::Attributes& attrs);

	XMLCh*	end_;

	T	param_;

	RegexpHandler<T>*	lefth_;
    };
    /**
     * WeightHandlerHandler class
     */
    template <typename T>
    class WeightHandler : public RegexpHandler<T>
    {
      // Access to base class protected members.
      using RegexpHandler<T>::parser_;
      using RegexpHandler<T>::eq_;
      using RegexpHandler<T>::root_;
      using RegexpHandler<T>::end_;

      public:
	WeightHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
    };
    /**
     * ExtMulHamdlerHandler class
     */
    template <typename T>
    class ExtMulHandler : public RegexpHandler<T>
    {
      // Access to base class protected members.
      using RegexpHandler<T>::parser_;
      using RegexpHandler<T>::eq_;
      using RegexpHandler<T>::root_;
      using RegexpHandler<T>::end_;
      using RegexpHandler<T>::param_;
      using RegexpHandler<T>::lefth_;
      using RegexpHandler<T>::create_weight;
      using RegexpHandler<T>::create;

      public:
	ExtMulHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param,
		       bool left);
	virtual ~ExtMulHandler();

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
	bool			left_;
	RegexpHandler<T>*	righth_;
    };
    /**
     * StarHandler class
     */
    template <typename T>
    class StarHandler : public RegexpHandler<T>
    {
      // Access to base class protected members.
      using RegexpHandler<T>::parser_;
      using RegexpHandler<T>::eq_;
      using RegexpHandler<T>::root_;
      using RegexpHandler<T>::end_;
      using RegexpHandler<T>::param_;
      using RegexpHandler<T>::lefth_;
      using RegexpHandler<T>::create;

      public:
	StarHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param);

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
	int			in_;
    };
    /**
     * ProductHandler class
     */
    template <typename T>
    class ProductHandler : public RegexpHandler<T>
    {
      // Access to base class protected members.
      using RegexpHandler<T>::parser_;
      using RegexpHandler<T>::eq_;
      using RegexpHandler<T>::root_;
      using RegexpHandler<T>::end_;
      using RegexpHandler<T>::param_;
      using RegexpHandler<T>::lefth_;
      using RegexpHandler<T>::create;

      public:
	ProductHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param);
	virtual ~ProductHandler ();

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
	int			in_;
	RegexpHandler<T>*	righth_;
    };
    /**
     * SumHandler class
     */
    template <typename T>
    class SumHandler : public RegexpHandler<T>
    {
      // Access to base class protected members.
      using RegexpHandler<T>::parser_;
      using RegexpHandler<T>::eq_;
      using RegexpHandler<T>::root_;
      using RegexpHandler<T>::end_;
      using RegexpHandler<T>::param_;
      using RegexpHandler<T>::lefth_;
      using RegexpHandler<T>::create;

      public:
	SumHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param);
	virtual ~SumHandler ();

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
	int			in_;
	RegexpHandler<T>*	righth_;
    };
    /**
     * MonElmtHandler class
     */
    template <typename T>
    class MonElmtHandler : public RegexpHandler<T>
    {
      // Access to base class protected members.
      using RegexpHandler<T>::parser_;
      using RegexpHandler<T>::eq_;
      using RegexpHandler<T>::root_;
      using RegexpHandler<T>::end_;
      using RegexpHandler<T>::param_;

      public:
	MonElmtHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param);

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
	Handler* mongenh_;
    };
    /**
     * AtomHandler class (one or zero)
     */
    template <typename T>
    class AtomHandler : public RegexpHandler<T>
    {
      // Access to base class protected members.
      using RegexpHandler<T>::parser_;
      using RegexpHandler<T>::root_;
      using RegexpHandler<T>::end_;

      public:
	AtomHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       T param,
		       XMLCh* end);
	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);
    };
  } // !xml
} // !vcsn

# if ! defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/regexp.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_XML_REGEXP_HH
