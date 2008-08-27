// rw.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_CONTEXTS_RW_HH
# define VCSN_XML_CONTEXTS_RW_HH

/**
 * @file rw.hh
 *
 * Tools to help loading automata.
 *
 * @see vcsn::xml::*Handler
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <string>

# include <xercesc/sax2/Attributes.hpp>
# include <xercesc/util/XMLString.hpp>

# include <vaucanson/xml/handlers_base.hh>
# include <vaucanson/xml/builders.hh>
# include <vaucanson/xml/regexp.hh>
# include <vaucanson/xml/xml_exp_visitor.hh>

# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/algebra/implementation/series/series.hh>

# define TRANStype				\
    Element<Transducer<S>, T>

# define TRANSseries				\
    Element<vcsn::algebra::Series<vcsn::algebra::Series<R, S>, T>, U>

# define SParamTRANS \
    template <typename R, typename S, typename T, typename U>

# define TRANSsemiring \
  vcsn::algebra::Series<S, T>

namespace vcsn
{
  namespace xml
  {
    /**
     * SeriesSemiringHandler
     */
    template <typename T>
    class SeriesSemiringHandler : public Handler
    {
      public:
	SeriesSemiringHandler (xercesc::SAX2XMLReader* parser,
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
	Handler*	ssemiringh_;
	Handler*	monoidh_;
	UnsupHandler	unsuph_;
    };

    SParamTRANS
    class WeightHandler<TRANSseries > : public RegexpHandler<TRANSseries >
    {
      // Access to base class protected members.
      using RegexpHandler<TRANSseries >::eq_;
      using RegexpHandler<TRANSseries >::parser_;
      using RegexpHandler<TRANSseries >::param_;
      using RegexpHandler<TRANSseries >::root_;
      using RegexpHandler<TRANSseries >::end_;

      public:
	WeightHandler (xercesc::SAX2XMLReader* parser,
		       Handler& root,
		       TRANSseries param);

	void
	start (const XMLCh* const uri,
		      const XMLCh* const localname,
		      const XMLCh* const qname,
		      const xercesc::Attributes& attrs);
	void
	end (const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname);

      protected:
	typedef typename TRANSseries::set_t::semiring_t	series_set_t;
	typedef typename TRANSseries::value_t::semiring_elt_value_t	series_set_elt_value_t;
	typedef vcsn::Element<series_set_t, series_set_elt_value_t> series_set_elt_t;

	RegexpHandler<series_set_elt_t>*
	create_weighth(const XMLCh* const localname);

	RegexpHandler<series_set_elt_t>*	weighth_;
    };

    namespace builders
    {
      template <typename S, typename T>
      typename TRANStype::semiring_t*
      create_semiring (TRANStype&,
		       const XMLCh* const localname,
		       const xercesc::Attributes& attrs);

      template <typename S, typename T>
      Handler*
      create_semiringh(TRANSsemiring& semiring,
			const xercesc::Attributes& attrs,
			xercesc::SAX2XMLReader* parser,
			Handler& root);

    } // !builders

    namespace builders
    {
      SParamTRANS
      RegexpHandler<TRANSseries >*
      create_weighth(xercesc::SAX2XMLReader* parser,
		     RegexpHandler<TRANSseries >& root,
		     TRANSseries param,
		     const xercesc::Attributes& attrs);
    }
    /**
     * Consistency
     */
    namespace builders
    {
      template <typename S, typename T>
      const char* get_semiring_operations(const vcsn::algebra::Series<S, T>&);
    } // !builders

    namespace builders
    {
      template <typename S, typename T>
      void
      create_semiring_node(const TRANStype&,
			   xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root);
    }
  } // !xml
} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/contexts/rw.hxx>
# endif // VCSN_USE_INTERFACE_ONLY || !VCSN_USE_LIB

# undef TRANStype
# undef TRANSseries
# undef SParamTRANS
# undef TRANSsemiring

#endif // !VCSN_XML_CONTEXTS_RW_HH
