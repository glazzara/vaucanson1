// builders.hh: this file is part of the Vaucanson project.
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

#ifndef BUILDERS_HH
# define BUILDERS_HH

/**
 * @file builders.hh
 *
 * dispatch functions for handlers classes (automaton loading)
 *
 * @see vcsn::xml
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <string>
# include <xercesc/sax2/Attributes.hpp>

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/xml/tools.hh>

# include <vaucanson/xml/handlers.hh>

# define TParm					\
    template <class S, class T>
# define TParmFMP					\
    template <class S, class T, class M1, class M2>
# define AUTtype				\
    Element<Automata<S>, T>
# define TRANStype				\
    Element<Transducer<S>, T>

# define FMPtype							\
    Element<								\
      Automata<								\
	vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> > \
	>,								\
      T>

namespace vcsn
{
  namespace xml
  {
    namespace builders
    {
      // Processing monoid

      template <typename T>
      typename T::monoid_t*
      create_monoid (T&,
		     const xercesc::Attributes& attrs);

      TParmFMP
      typename FMPtype::monoid_t*
      create_monoid (FMPtype&,
		     const xercesc::Attributes& attrs);

      template <typename T>
      MonoidHandler*
      monoidh_factory(T& monoid,
		      const xercesc::Attributes& attrs,
		      xercesc::DefaultHandler& root,
		      xercesc::SAX2XMLReader* parser,
		      XMLEq& eq);

      template <typename T>
      void
      insert_letter (T& monoid,
		     std::string letter);

      // Processing semiring

      template <typename T>
      typename T::semiring_t*
      create_semiring (T&,
		       const xercesc::Attributes& attrs);

      TParm
      typename TRANStype::semiring_t*
      create_semiring (TRANStype&,
		       const xercesc::Attributes& attrs);

      template <typename V, typename T>
      SemiringHandler*
      semiringh_factory(V& param,
			const xercesc::Attributes& attrs,
			T& semiring,
			xercesc::DefaultHandler& root,
			xercesc::SAX2XMLReader* parser,
			XMLEq& eq);

      TParm
      SemiringHandler*
      semiringh_factory(TRANStype& param,
			const xercesc::Attributes& attrs,
			typename TRANStype::semiring_t& semiring,
			xercesc::DefaultHandler& root,
			xercesc::SAX2XMLReader* parser,
			XMLEq& eq);

      // Processing label attributes

      template <typename T>
      typename T::series_set_elt_t
      get_series (T& aut,
		  std::map<std::string, std::string>& attrs,
		  const char * token);

      // Ensuring correct attributes

      void
      check_consistency (const xercesc::Attributes& attrs,
			 const std::string& kind,
			 const char* key,
			 const std::string& expected);

      // Getters

      bool
      has_attribute (const xercesc::Attributes& attrs,
		     const char* key,
		     const XMLCh* const uri = 0);

      const XMLCh*
      get_attribute (const xercesc::Attributes& attrs,
		     const char* key,
		     const XMLCh* uri = 0);

      template <typename T>
      RegExpHandler<T>*
      labelh_factory(xercesc::DefaultHandler& root,
		     T& aut,
		     xercesc::SAX2XMLReader* parser,
		     XMLEq& eq,
		     const XMLCh* const localname,
		     const xercesc::Attributes& attrs);

      template <typename T>
      typename T::series_set_elt_t
      get_series_transition(T& aut,
			    std::map<std::string, std::string>& attrs,
			    LabelHandler<T>& labelh);
    } // !builders
  } // !xml
} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/builders.hxx>
# endif // VCSN_USE_INTERFACE_ONLY || !VCSN_USE_LIB

# undef AUTtype
# undef FMPtype
# undef TParm
# undef TParmFMP
# undef TRANStype

#endif // !BUILDERS_HH
