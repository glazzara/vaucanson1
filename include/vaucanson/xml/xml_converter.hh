// xml_converter.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_XML_XML_CONVERTER_HH
# define VCSN_XML_XML_CONVERTER_HH

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

# include <xercesc/framework/MemBufFormatTarget.hpp>
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
       */
      template <class OStream>
      void save(const Auto& a, OStream& out);

      /**
       * @brief Load automaton from stream.
       *
       * @param IStream	Type of the input stream.
       *
       * @arg a		Automaton to save.
       * @arg in	Input stream.
       */
      template <class IStream>
      void load(Auto& a, IStream& in);

    private:
      template <class OStream>

      void print_document(OStream&);
      std::string create_state(hstate_t, const Auto&, xercesc::DOMElement*);
      void create_transition(hedge_t, const Auto&,
			     xercesc::DOMElement*, map_t&);
      void create_initial(hstate_t, const Auto&,
			  xercesc::DOMElement*, map_t&);
      void create_final(hstate_t, const Auto&,
			xercesc::DOMElement*, map_t&);
      void add_xml_geometry(hstate_t, const Auto& aut, xercesc::DOMElement*);
      void add_xml_geometry(hedge_t, const Auto& aut, xercesc::DOMElement*);

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

#endif // VCSN_XML_XML_CONVERTER_HH




