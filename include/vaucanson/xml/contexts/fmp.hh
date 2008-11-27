// fmp.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_CONTEXTS_FMP_HH
# define VCSN_XML_CONTEXTS_FMP_HH

/**
 * @file fmp.hh
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

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/automata_kind.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>

# define FMPtype							\
    Element<								\
      Automata<								\
        vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> >, \
        labels_are_series \
	>,								\
      T>
# define TParamFMP template <class S, class T, class M1, class M2>
# define FMPsreptype algebra::series_rep<S, algebra::FreeMonoidProduct<M1, M2> >

# define FMPseries Element<vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> >, T>
# define SParamFMP template <class S, class T, class M1, class M2>


namespace vcsn
{
  namespace xml
  {
    /**
     * FreeMonoidProductHandler
     */
    template <typename T>
    class FreeMonoidProductHandler : public Handler
    {
      public:
	FreeMonoidProductHandler (xercesc::SAX2XMLReader* parser,
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
	Handler*	monoidh_;
	UnsupHandler	unsuph_;

	bool		first_;
    };

    /**
     * SeriesRepresentationHandler specialization for FMP
     */
    template <typename S, typename M1, typename M2>
    class SeriesRepresentationHandler<FMPsreptype> : public Handler
    {
      public:
	// Type helpers.
	typedef FMPsreptype self_t;

	SeriesRepresentationHandler(xercesc::SAX2XMLReader* parser,
				    Handler& root,
				    self_t& srep);

	void start(const XMLCh* const uri,
		   const XMLCh* const localname,
		   const XMLCh* const qname,
		   const xercesc::Attributes& attrs);

	void end(const XMLCh* const uri,
		 const XMLCh* const localname,
		 const XMLCh* const qname);

      private:
	self_t&		rep_;

	Handler*	reph_;
	UnsupHandler	unsuph_;
	bool		first_;
    };

    namespace builders
    {
      TParamFMP
      typename FMPtype::monoid_t*
      create_monoid (FMPtype& aut,
		     const XMLCh* const localname,
		     const xercesc::Attributes& attrs,
		     XMLEq&);

      template <typename M1, typename M2>
      Handler*
      create_monoidh (vcsn::algebra::FreeMonoidProduct<M1, M2>& monoid,
		      const xercesc::Attributes& attrs,
		      xercesc::SAX2XMLReader* parser,
		      Handler& root);
    } // !builders

    /**
     * monElmtHandler
     */
    template <typename T>
    class ProdMonElmtHandler
      : public RegexpHandler<T>
    {
      // Access to base class protected members.
      using RegexpHandler<T>::eq_;
      using RegexpHandler<T>::parser_;
      using RegexpHandler<T>::end_;
      using RegexpHandler<T>::param_;
      using RegexpHandler<T>::root_;

      public:
	ProdMonElmtHandler (xercesc::SAX2XMLReader* parser,
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
      protected:
	int	in_;
	int	count_;


	typedef typename T::monoid_elt_t::first_monoid_t	first_monoid_t;
	typedef typename T::monoid_elt_t::second_monoid_t	second_monoid_t;
	typedef typename T::monoid_elt_t::first_monoid_elt_t	first_monoid_elt_t;
	typedef typename T::monoid_elt_t::second_monoid_elt_t	second_monoid_elt_t;
	first_monoid_elt_t	m1_;
	second_monoid_elt_t	m2_;
    };

    namespace builders
    {
      SParamFMP
      RegexpHandler<FMPseries >*
      create_monElmth(xercesc::SAX2XMLReader* parser,
		      RegexpHandler<FMPseries >& root,
		      FMPseries param);
    } // !builders

    /**
     * Consistency
     */
    namespace builders
    {
      TParamFMP
      void
      check_monoid_consistency (FMPtype&,
				const XMLCh* const localname,
			        const xercesc::Attributes& attrs,
				XMLEq&);
    } // !builders

    /**
     *
     */
    namespace builders
    {
      TParamFMP
      void
      create_type_writingData_node(const FMPtype& aut,
				   xercesc::DOMDocument* doc,
				   xercesc::DOMElement* root);

      TParamFMP
      void
      create_monoid_node(const FMPtype& aut,
			 xercesc::DOMDocument* doc,
			 xercesc::DOMElement* root);
    } // !builders
  } // !xml
} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/contexts/fmp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY || !VCSN_USE_LIB

# undef SParamFMP
# undef FMPseries
# undef TParamFMP
# undef FMPtype

#endif // !VCSN_XML_CONTEXTS_FMP_HH
