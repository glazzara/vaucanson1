// xerces_parser.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_XML_XERCES_PARSER_HH
# define VCSN_XML_XERCES_PARSER_HH
/**
 * @file xerces_parser.hh
 *
 * Xerces-C++ parser.
 *
 * @see vcsn::xml::XML
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


# include <iostream>
# include <cstdlib>

# include <xercesc/dom/DOM.hpp>
# include <xercesc/framework/Wrapper4InputSource.hpp>

# include <vaucanson/xml/XML.hh>
# include <vaucanson/xml/ios.hh>
# include <vaucanson/xml/strings.hh>
# include <vaucanson/xml/error_handler.hh>


namespace vcsn
{
  namespace xml
  {

    struct xerces_parser
    {
      /**
       * @brief Parse XML document from stream.
       *
       * @param IStream	Type of the input stream.
       *
       * @return	DOMElement pointer to root node.
       * @arg is	Input stream.
       */
      template <class IStream>
      static
      xercesc::DOMElement* stream_parser(IStream& is);

    private:
      template <class IStream>
      static
      xercesc::DOMDocument* loaddocument(xercesc::DOMBuilder* parser,
					 IStream& is);
    };
  } // xml

} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/xml/xerces_parser.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // VCSN_XML_XERCES_PARSER_HH
