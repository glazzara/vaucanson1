// xml_converter.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XML_CONVERTER_HH
# define VCSN_XML_XML_CONVERTER_HH

#include <vaucanson/config/system.hh>
#ifndef VCSN_USE_XML
# error Vaucanson XML support is disabled.
#endif

/**
 * @file xml_converter.hh
 *
 * XML conversion class. Used to convert stream containing XML to automaton,
 * and vice et versa.
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
# include <vaucanson/tools/usual_macros.hh>
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
     * @param Auto	Type of the automaton to load / save.
     *
     */
    template <class Auto>
    struct xml_converter
    {
      xml_converter() : impl_(0), doc_(0), root_(0) {};

      typedef std::map<hstate_t, std::string>		map_t;
      typedef typename Auto::set_t			auto_set_t;
      typedef typename Auto::value_t			auto_impl_t;
      typedef xml_chooser<auto_set_t, auto_impl_t>	xml_chooser_t;

      /**
       * @brief Save automaton to stream.
       *
       * @param OStream	Type of the output stream.
       *
       * @arg a		Automaton to save.
       * @arg out	Output stream.
       * @arg name	String containing the name of the automaton.
       */
      template <class OStream>
      void save(const Auto& a, OStream& out, const std::string& name = "");

      /**
       * @brief Load automaton from stream.
       *
       * @param IStream	Type of the input stream.
       *
       * @arg a		Automaton to load.
       * @arg in	Input stream.
       */
      template <class IStream>
      void load(Auto& a, IStream& in);

      void create_document(const Auto& aut, const std::string& name = "");

      xercesc::DOMElement* root_get() { return root_; }

    private:
      std::string create_state(hstate_t, const Auto&, xercesc::DOMElement*);
      void create_transition(hedge_t, const Auto&,
			     xercesc::DOMElement*, map_t&);
      void create_initial(hstate_t, const Auto&,
			  xercesc::DOMElement*, map_t&);
      void create_final(hstate_t, const Auto&,
			xercesc::DOMElement*, map_t&);

      template <class Map, class Key>
      void add_xml_geometry(Map&, Key&, xercesc::DOMElement* node);
      template <class Map, class Key>
      void add_xml_drawing(Map&, Key&, xercesc::DOMElement* node);

      xercesc::DOMImplementation*			impl_;
      xercesc::DOMDocument*				doc_;
      xercesc::DOMElement*				root_;
      xml_chooser_t					chooser_;
    };

  } // !xml

} // !vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xml_converter.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_XML_XML_CONVERTER_HH
