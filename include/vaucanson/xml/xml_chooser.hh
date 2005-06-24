// xml_chooser.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_XML_XML_CHOOSER_HH
# define VCSN_XML_XML_CHOOSER_HH

/**
 * @file xml_chooser.hh
 *
 * XML specialized class, providing methods to create <type> tag and to
 * create labels in the XML document.
 *
 * @see vcsn::xml::xml_converter, vcsn::xml::Node
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */
# include <string>
# include <sstream>
# include <xercesc/dom/DOM.hpp>

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/boolean_automaton.hh>
# include <vaucanson/z_automaton.hh>
# include <vaucanson/z_max_plus_automaton.hh>
# include <vaucanson/z_min_plus_automaton.hh>
# include <vaucanson/r_automaton.hh>
# include <vaucanson/fmp_transducer.hh>
# include <vaucanson/boolean_transducer.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/xml/tools.hh>


namespace vcsn
{
  namespace xml
  {
    /**
     * @brief Chooser base class. All specialization should inherit from it.
     *
     * @param S		Automaton structure type.
     * @param T		Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser_base
    {
      const char* choose_start_tag();
      void create_type_tag(const Element<S, T>&, xercesc::DOMDocument*,
			   xercesc::DOMElement*);
      void create_label(hedge_t, const Element<S, T>&, xercesc::DOMElement*);
      void create_initial_label(hstate_t, const Element<S, T>&,
				xercesc::DOMElement*);
      void create_final_label(hstate_t, const Element<S, T>&,
			      xercesc::DOMElement*);
    };

    /**
     * @brief Default Chooser class.
     *
     * @param S		Automaton structure type.
     * @param T		Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser : xml_chooser_base<S, T>
    {};

    /**
     * @brief Chooser specialization for automata.
     *
     * @param S		Automaton structure type.
     * @param T		Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser<Automata<S>, T> : xml_chooser_base<Automata<S>, T>
    {};

    /**
     * @brief Chooser specialization for transducers on P(B*).
     *
     * @param S		Automaton structure type.
     * @param T		Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser<Transducer<S>, T> : xml_chooser_base<Transducer<S>, T>
    {
      const char* choose_start_tag();
      void create_type_tag(const Element<Transducer<S>, T>&,
			   xercesc::DOMDocument*, xercesc::DOMElement*);
    };

    /**
     * @brief Chooser specialization for FMP transducers.
     *
     * @param S		Automaton semiring type.
     * @param T		Automaton implementation type.
     * @param M1	Automaton first monoid type.
     * @param M2	Automaton second monoid type.
     *
     */
# define TParmFMP						\
      template <class S, class T, class M1, class M2>
# define FMPtype							   \
      Automata<								   \
      vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> >  \
      >, T

    TParmFMP
    struct xml_chooser<FMPtype> : xml_chooser_base<FMPtype>
    {
      const char* choose_start_tag();
      void create_type_tag(const Element<FMPtype>&, xercesc::DOMDocument*,
			   xercesc::DOMElement*);
    };


  } // !xml

} // !vcsn



# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xml_chooser.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_XML_XML_CHOOSER_HH
