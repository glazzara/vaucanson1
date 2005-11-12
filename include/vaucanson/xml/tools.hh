// tools.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_XML_TOOLS_HH
# define VCSN_XML_TOOLS_HH

/**
 * @file tools.hh
 *
 * Some useful utility functions.
 *
 *
 * @see vcsn::xml::xml_converter, vcsn::xml::Node
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */
# include <xercesc/dom/DOM.hpp>
# include <xercesc/framework/MemBufFormatTarget.hpp>
# include <xercesc/util/XMLString.hpp>
# include <xercesc/util/PlatformUtils.hpp>

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/boolean_automaton.hh>
# include <vaucanson/z_automaton.hh>
# include <vaucanson/z_max_plus_automaton.hh>
# include <vaucanson/z_min_plus_automaton.hh>
# include <vaucanson/r_automaton.hh>
# include <vaucanson/fmp_transducer.hh>
# include <vaucanson/boolean_transducer.hh>

# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/automata/concept/transducer_base.hh>

# include <vaucanson/xml/strings.hh>

namespace vcsn
{
  namespace xml
  {
    namespace tools
    {
      template <class S>
      const char* get_monoid_type(const S&);

      template <class S>
      const char* get_semiring_operations(const S&);

      template <class S, class T>
      const char* get_semiring_set(const S&, const T&);

      template <class S, class T, class U>
      void add_label(xercesc::DOMElement*, const Element<S, T>&, const U&);

      template <class M>
      xercesc::DOMElement* create_monoid(const M& monoid,
					 xercesc::DOMDocument* doc,
					 xercesc::DOMElement* elt);
      template <class A>
      void create_alphabet(const A& alphabet, xercesc::DOMDocument* doc,
			   xercesc::DOMElement* root);
      template <class A, class S>
      xercesc::DOMElement* create_semiring(const A& aut,
					   const S& semiring,
					   xercesc::DOMDocument* doc,
					   xercesc::DOMElement* elt);

      template <class T>
      typename T::series_set_elt_t get_series(xercesc::DOMElement*, T&);

      template <class U, class V>
      void insert_letter(Element<vcsn::algebra::AlphabetSet<U>, V>&,
			 const std::string&);

      template <class U>
      void ensure_monoid_type(const xercesc::DOMElement*, const U&);

      template <class T, class U>
      void ensure_semiring_type(const xercesc::DOMElement*, const T&,
				const U&);

      template <class OStream>
      void print_document(xercesc::DOMElement*, OStream&);

    } // ! tools

  } // ! xml

} // ! vcsn

# define TParm					\
    template <class S, class T>
# define TParmFMP					\
      template <class S, class T, class M1, class M2>
# define AUTtype				\
    Element<Automata<S>, T>
# define TRANStype				\
    Element<Transducer<S>, T>
# define FMPtype      							  \
    Element<								  \
      Automata<								  \
      vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> > \
      >, T								  \
    >


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/tools.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_TOOLS_HH
