// xml_chooser.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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

#ifndef VCSN_XML_XML_CHOOSER_HH
# define VCSN_XML_XML_CHOOSER_HH

/**
 * @file xml_chooser.hh
 *
 * XML specialized class, providing methods to create @c <labelType> tag
 * and to create labels in the XML document.
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
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/xml/tools.hh>


namespace vcsn
{
  namespace xml
  {
    /**
     * @brief Chooser base class. All specialization should inherit from it.
     *
     * @arg \c S	Automaton structure type.
     * @arg \c T	Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser_base
    {
	void create_type_tag(const Element<S, T>& aut,
			     xercesc::DOMDocument* doc,
			     xercesc::DOMElement* root);

	void create_label(xercesc::DOMDocument* doc,
			  htransition_t e, const Element<S, T>&aut,
			  xercesc::DOMElement* elt, bool use_label_node);

	void create_initial_label(xercesc::DOMDocument* doc,
				  hstate_t s, const Element<S, T>& aut,
				  xercesc::DOMElement* elt,
				  bool use_label_node);
	void create_final_label(xercesc::DOMDocument* doc,
				hstate_t s, const Element<S, T>& aut,
				xercesc::DOMElement* elt,
				bool use_label_node);
    };

    /**
     * @brief Default Chooser class.
     *
     * @arg \c S	Automaton structure type.
     * @arg \c T	Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser : xml_chooser_base<S, T>
    {};

    /**
     * @brief Chooser specialization for automata.
     *
     * @arg \c S	Automaton structure type.
     * @arg \c T	Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser<Automata<S>, T> : xml_chooser_base<Automata<S>, T>
    {};

    /**
     * @brief Chooser specialization for transducers on P(B*).
     *
     * @arg \c S	Automaton structure type.
     * @arg \c T	Automaton implementation type.
     *
     */
    template <class S, class T>
    struct xml_chooser<Transducer<S>, T> : xml_chooser_base<Transducer<S>, T>
    {
	void create_type_tag(const Element<Transducer<S>, T>& aut,
			     xercesc::DOMDocument* doc,
			     xercesc::DOMElement* root);
    };

    /**
     * @brief Chooser specialization for FMP transducers.
     *
     * @arg \c S	Automaton semiring type.
     * @arg \c T	Automaton implementation type.
     * @arg \c M1	Automaton first monoid type.
     * @arg \c M2	Automaton second monoid type.
     *
     */
# define FMPtype							\
    Automata<								\
      vcsn::algebra::Series<S, vcsn::algebra::FreeMonoidProduct<M1, M2> > \
      >, T

    template <class S, class T, class M1, class M2>
    struct xml_chooser<FMPtype> : xml_chooser_base<FMPtype>
    {
	void create_type_tag(const Element<FMPtype>& aut,
			     xercesc::DOMDocument* doc,
			     xercesc::DOMElement* root);
    };


  } // !xml

} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/xml_chooser.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

# undef FMPtype

#endif // ! VCSN_XML_XML_CHOOSER_HH
