// xml_converter.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_XML_CONVERTER_HH
# define VCSN_XML_XML_CONVERTER_HH

/**
 * @file xml_converter.hh
 *
 * XML conversion class.  Convert stream containing XML to automaton,
 * and conversely.
 *
 * @see vcsn::xml::xml_chooser, vcsn::xml::Node, vcsn::Factory
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

# include <xercesc/dom/DOM.hpp>
# include <xercesc/util/XMLString.hpp>
# include <xercesc/util/PlatformUtils.hpp>

# include <string>
# include <sstream>

# include <vaucanson/design_pattern/element.hh>
# include <vaucanson/design_pattern/factory.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/xml/xerces_parser.hh>
# include <vaucanson/xml/node.hh>
# include <vaucanson/xml/xml_chooser.hh>

namespace vcsn
{
  namespace xml
  {
    /**
     * @brief Base conversion class.
     *
     * @arg \c Auto	Type of the automaton to load / save.
     *
     */
    template <class Auto>
    struct xml_converter
    {
      xml_converter(bool use_label_node = false);

      typedef typename Auto::hstate_t			hstate_t;
      typedef typename Auto::htransition_t		htransition_t;
      typedef std::map<hstate_t, std::string>		map_t;
      typedef typename Auto::set_t			auto_set_t;
      typedef typename Auto::value_t			auto_impl_t;
      typedef xml_chooser<auto_set_t, auto_impl_t>	xml_chooser_t;

      /**
       * @brief Save automaton to stream.
       *
       * @arg \c OStream	Type of the output stream.
       *
       * @param a	Automaton to save.
       * @param out	Output stream.
       * @param name	String containing the name of the automaton.
       */
      template <class OStream>
      void save(const Auto& a, OStream& out, const std::string& name = "");

      /**
       * @brief Load automaton from stream.
       *
       * @arg \c IStream	Type of the input stream.
       *
       * @param a	Automaton to load.
       * @param in	Input stream.
       */
      template <class IStream>
      void load(Auto& a, IStream& in);

      /// Create the DOM document for @a aut, named @a name.
      void create_document(const Auto& aut, const std::string& name = "");

      /// The root of the created DOM document.
      xercesc::DOMElement* root_get();

    private:
      std::string create_state(hstate_t s, const Auto& aut,
			       xercesc::DOMElement* root);
      void create_transition(htransition_t e, const Auto& aut,
			     xercesc::DOMElement* root, map_t& state2str);
      void create_initial(hstate_t s, const Auto& aut,
			  xercesc::DOMElement* root, map_t& state2str);
      void create_final(hstate_t s, const Auto& aut,
			xercesc::DOMElement* root, map_t& state2str);

      template <class Map, class Key>
      void add_xml_geometry(Map& map, Key& key, xercesc::DOMElement* node);

      template <class Map, class Key>
      void add_xml_drawing(Map& map, Key& key, xercesc::DOMElement* node);

      xercesc::DOMImplementation*  impl_;
      xercesc::DOMDocument*	   doc_;
      xercesc::DOMElement*	   root_;
      xml_chooser_t		   chooser_;
      bool			   use_label_node_;
    };

  } // !xml

} // !vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/xml_converter.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XML_CONVERTER_HH
